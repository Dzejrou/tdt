#include "RayCaster.hpp"
#include "Enums.hpp"
#include "GUI.hpp"

RayCaster::RayCaster(Ogre::SceneManager& mgr)
	: query_{mgr.createRayQuery(Ogre::Ray{})}
{
	query_->setSortByDistance(true);
	query_->setQueryMask((int)ENTITY_TYPE::WALL || (int)ENTITY_TYPE::BUILDING);
}

std::pair<bool, Ogre::Real> RayCaster::cast(const Ogre::Vector3& start, const Ogre::Vector3& dir,
											  const std::string& target) const
{
	if(!query_)
		return std::make_pair(false, Ogre::Real());

	Ogre::Ray ray{start, dir};
	query_->setRay(ray);
	auto result = query_->execute();
	if(result.size() <= 0)
		return std::make_pair(false, Ogre::Real());

	std::pair<bool, Ogre::Real> closest{};
	closest.first = false;
	closest.second = std::numeric_limits<Ogre::Real>::max();

	std::size_t vertex_count{}, index_count{};
	std::vector<Ogre::Vector3> vertices{};
	std::vector<std::size_t> indices{};
	Ogre::Entity* ent{};
	for(std::size_t i = 0; i < result.size(); ++i)
	{
		if(closest.second < result[i].distance)
			break;

		if(result[i].movable)
		{
			if(i == 0 && result[i].movable->getParentSceneNode()->getName() == target)
				return std::make_pair(false, Ogre::Real{});

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

			if(hit.first && hit.second < closest.second)
			{
				closest.first = hit.first;
				closest.second = hit.second;
			}
		}
	
	}

	if(closest.second < std::numeric_limits<Ogre::Real>::max())
		return std::make_pair(true, closest.second);
	else
		return std::make_pair(false, Ogre::Real{});
}

void RayCaster::get_info(const Ogre::Entity& ent, std::size_t& v_count, std::size_t& i_count, std::vector<Ogre::Vector3>& verts, std::vector<std::size_t>& inds,
						 const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::Vector3& scale) const
{
	bool shared{false};
	std::size_t curr_offset{}, shared_offset{}, next_offset{}, index_offset{};
	v_count = i_count = 0;

	auto mesh = ent.getMesh();
	std::size_t sub_count{mesh->getNumSubMeshes()};
	for(unsigned short i = 0; i < sub_count; ++i)
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

	verts.resize(v_count);
	inds.resize(i_count);
	shared = false;

	for(unsigned short i = 0; i < sub_count; ++i)
	{
		auto sub = mesh->getSubMesh(i);
	
		auto shared_allowed = sub->useSharedVertices;
		auto* v_data = shared_allowed ? mesh->sharedVertexData : sub->vertexData;

		if(!shared_allowed || (shared_allowed && !shared))
		{
			if(shared_allowed)
			{
				shared = true;
				shared_offset = curr_offset;
			}
			const auto* elem = v_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			auto v_buf = v_data->vertexBufferBinding->getBuffer(elem->getSource());
			unsigned char* vertex = (unsigned char*)v_buf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
			float* tmp;

			for(std::size_t j = 0; j < v_data->vertexCount; ++j, vertex += v_buf->getVertexSize())
			{
				elem->baseVertexPointerToElement(vertex, &tmp);
				verts[curr_offset + j] = orientation * (Ogre::Vector3{tmp[0], tmp[1], tmp[2]} * scale) + position;
			}
			v_buf->unlock();
			next_offset += v_data->vertexCount;
		}
		auto* index_data = sub->indexData;
		std::size_t tri_count = index_data->indexCount / 3;
		auto i_buf = index_data->indexBuffer;

		unsigned long* lock_32bit = (unsigned long*)i_buf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
		std::size_t offset = sub->useSharedVertices ? shared_offset : curr_offset;
		std::size_t last_index = tri_count * 3 + index_data->indexStart;

		if(i_buf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT)
		{
			for(std::size_t j = index_data->indexStart; j < last_index; ++j)
				inds[index_offset++] = lock_32bit[j] + (unsigned long)offset;
		}
		else
		{
			unsigned short* lock_16bit = (unsigned short*)lock_32bit;
			for(std::size_t j = index_data->indexStart; j < last_index; ++j)
				inds[index_offset++] = (unsigned long)lock_16bit[j] + (unsigned long)offset;
		
		}

		i_buf->unlock();
		curr_offset = next_offset;
	}
}
