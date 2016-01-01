#include "RayCaster.hpp"

RayCaster::RayCaster(Ogre::SceneManager& mgr)
	: query_{mgr.createRayQuery(Ogre::Ray{})}
{
	query_->setSortByDistance(true);
}

std::pair<bool, Ogre::Vector3> RayCaster::cast(const Ogre::Vector3& start, const Ogre::Vector3& dir)
{
	if(!query_)
		return std::make_pair(false, Ogre::Vector3());

	Ogre::Ray ray{start, dir};
	query_->setRay(ray);
	auto& result = query_->execute();
	if(result.size() <= 0)
		return std::make_pair(false, Ogre::Vector3());

	std::pair<Ogre::Real, Ogre::Vector3> closest{};
	closest.first = std::numeric_limits<Ogre::Real>::max();

	std::size_t vertex_count{}, index_count{};
	std::vector<Ogre::Vector3> vertices{};
	std::vector<std::size_t> indices{};
	Ogre::Entity* ent{};
	for(std::size_t i = 0; i < result.size(); ++i)
	{
		if(closest.first < result[i].distance)
			break;

		if(result[i].movable)
		{
			if(result[i].movable->getMovableType() != "Entity")
				continue; // Shouldn't happen, but other types might get added later.

			ent = (Ogre::Entity*)result[i].movable;
			get_info(*ent, vertex_count, index_count, vertices, indices,
					 ent->getParentNode()->_getDerivedPosition(),
					 ent->getParentNode()->_getDerivedOrientation(),
					 ent->getParentNode()->_getDerivedScale());
		}

		for(std::size_t j = 0; j < index_count; j += 3)
		{
			auto hit = Ogre::Math::intersects(ray, vertices[indices[j]], vertices[indices[j + 1]],
											  vertices[indices[j + 2]], true, false);

			if(hit.first && hit.second < closest.first)
			{
				closest.first = hit.first;
				closest.second = ray.getPoint(closest.first);
			}
		}
	
	}

	if(closest.first < std::numeric_limits<Ogre::Real>::max())
		return std::make_pair(true, closest.second);
	else
		return std::make_pair(false, Ogre::Vector3());
}

void RayCaster::get_info(const Ogre::Entity& ent, std::size_t& v_count, std::size_t& i_count, std::vector<Ogre::Vector3>& verts, std::vector<std::size_t>& inds,
						 const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::Vector3& scale)
{
	bool shared{false};
	std::size_t curr_offset{}, shared_offset{}, next_offset{}, index_offset{};
	v_count = i_count = 0;

	auto mesh = ent.getMesh();
	for(std::size_t i = 0; i < mesh->getNumSubMeshes(); ++i)
	{
		auto sub = mesh->getSubMesh(i);
		if(sub->useSharedVertices)
		{
			if(!shared)
			{
				v_count += mesh->sharedVertexData->vertexCount;
				shared = true;
			}
		}
		else
			v_count += sub->vertexData->vertexCount;
		i_count += sub->indexData->indexCount;
	}

	verts.reserve(v_count);
	inds.reserve(i_count);
	shared = false;
}
