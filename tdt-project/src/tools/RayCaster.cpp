#include <limits>
#include <gui/GUI.hpp>
#include <Enums.hpp>
#include "RayCaster.hpp"

RayCaster::RayCaster(Ogre::SceneManager& mgr)
	: query_{mgr.createRayQuery(Ogre::Ray{})}
{
	query_->setSortByDistance(true);
	query_->setQueryMask((int)ENTITY_TYPE::WALL || (int)ENTITY_TYPE::BUILDING);
}

std::pair<bool, tdt::real> RayCaster::cast(const Ogre::Vector3& start, const Ogre::Vector3& dir,
											  const std::string& target) const
{
	if(!query_)
		return std::make_pair(false, tdt::real());

	Ogre::Ray ray{start, dir};
	query_->setRay(ray);
	auto result = query_->execute();
	if(result.size() <= 0)
		return std::make_pair(false, tdt::real());

	std::pair<bool, tdt::real> closest{};
	closest.first = false;
	closest.second = std::numeric_limits<tdt::real>::max();

	tdt::uint vertex_count{}, index_count{};
	std::vector<Ogre::Vector3> vertices{};
	std::vector<tdt::uint> indices{};
	Ogre::Entity* ent{};
	for(tdt::uint i = 0; i < result.size(); ++i)
	{
		if(closest.second < result[i].distance)
			break;

		if(result[i].movable)
		{
			if(i == 0 && result[i].movable->getParentSceneNode()->getName() == target)
				return std::make_pair(false, tdt::real{});

			if(result[i].movable->getMovableType() != "Entity")
				continue; // Shouldn't happen, but other types might get added later.

			ent = (Ogre::Entity*)result[i].movable;
			get_info(*ent, vertex_count, index_count, vertices, indices,
					 ent->getParentNode()->_getDerivedPosition(),
					 ent->getParentNode()->_getDerivedOrientation(),
					 ent->getParentNode()->_getDerivedScale());
		}

		for(tdt::uint j = 0; j < index_count; j += 3)
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

	if(closest.second < std::numeric_limits<tdt::real>::max())
		return std::make_pair(true, closest.second);
	else
		return std::make_pair(false, tdt::real{});
}

void RayCaster::get_info(const Ogre::Entity& ent, tdt::uint& v_count, tdt::uint& i_count, std::vector<Ogre::Vector3>& verts, std::vector<tdt::uint>& inds,
						 const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::Vector3& scale) const
{
	bool shared{false};
	tdt::uint curr_offset{}, shared_offset{}, next_offset{}, index_offset{};
	v_count = i_count = 0;

	auto mesh = ent.getMesh();
	tdt::uint sub_count{mesh->getNumSubMeshes()};
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

			for(tdt::uint j = 0; j < v_data->vertexCount; ++j, vertex += v_buf->getVertexSize())
			{
				elem->baseVertexPointerToElement(vertex, &tmp);
				verts[curr_offset + j] = orientation * (Ogre::Vector3{tmp[0], tmp[1], tmp[2]} * scale) + position;
			}
			v_buf->unlock();
			next_offset += v_data->vertexCount;
		}
		auto* index_data = sub->indexData;
		tdt::uint tri_count = index_data->indexCount / 3;
		auto i_buf = index_data->indexBuffer;

		unsigned long* lock_32bit = (unsigned long*)i_buf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
		tdt::uint offset = sub->useSharedVertices ? shared_offset : curr_offset;
		tdt::uint last_index = tri_count * 3 + index_data->indexStart;

		if(i_buf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT)
		{
			for(tdt::uint j = index_data->indexStart; j < last_index; ++j)
				inds[index_offset++] = lock_32bit[j] + (unsigned long)offset;
		}
		else
		{
			unsigned short* lock_16bit = (unsigned short*)lock_32bit;
			for(tdt::uint j = index_data->indexStart; j < last_index; ++j)
				inds[index_offset++] = (unsigned long)lock_16bit[j] + (unsigned long)offset;
		
		}

		i_buf->unlock();
		curr_offset = next_offset;
	}
}
