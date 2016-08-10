#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "GraphicsHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::GraphicsCache cache{Component::NO_ENTITY, nullptr};
#endif

void GraphicsHelper::set_mesh(EntitySystem& ents, tdt::uint id, const std::string& mesh)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		comp->mesh = mesh;
}

const std::string& GraphicsHelper::get_mesh(EntitySystem& ents, tdt::uint id)
{
	static const std::string NO_MESH{"cube.mesh"};

	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		return comp->mesh;
	else
		return NO_MESH;
}

void GraphicsHelper::set_material(EntitySystem& ents, tdt::uint id, const std::string& material)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
	{
		comp->material = material;
		if(comp->entity)
			comp->entity->setMaterialName(comp->material);
	}
}

const std::string& GraphicsHelper::get_material(EntitySystem& ents, tdt::uint id)
{
	static const std::string NO_MATERIAL{"colour/pink"};

	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		return comp->material;
	else
		return NO_MATERIAL;
}

void GraphicsHelper::set_visible(EntitySystem& ents, tdt::uint id, bool val)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
	{
		comp->visible = val;
		if(comp->node)
			comp->node->setVisible(val);
	}
}

bool GraphicsHelper::is_visible(EntitySystem& ents, tdt::uint id)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		return comp->visible;
	else
		return false;
}

void GraphicsHelper::set_manual_scaling(EntitySystem& ents, tdt::uint id, bool val)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		comp->manual_scaling = val;
}

bool GraphicsHelper::get_manual_scaling(EntitySystem& ents, tdt::uint id)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		return comp->manual_scaling;
	else
		return false;
}

void GraphicsHelper::set_scale(EntitySystem& ents, tdt::uint id, const Ogre::Vector3& val)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		comp->scale = val;
}

const Ogre::Vector3& GraphicsHelper::get_scale(EntitySystem& ents, tdt::uint id)
{
	static const Ogre::Vector3 NO_SCALE{0.f, 0.f, 0.f};

	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		return comp->scale;
	else
		return NO_SCALE;
}

void GraphicsHelper::look_at(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	GraphicsComponent* comp1{nullptr};
	GET_COMPONENT(id1, ents, comp1, GraphicsComponent);
	auto comp2 = ents.get_component<PhysicsComponent>(id2);
	if(comp1 && comp2)
	{
		auto& target_pos = comp2->position;
		comp1->node->lookAt(
				Ogre::Vector3{target_pos.x, comp1->node->getPosition().y, target_pos.z},
				Ogre::Node::TransformSpace::TS_WORLD,
				Ogre::Vector3::UNIT_Z
			);
	}
}

void GraphicsHelper::rotate(EntitySystem& ents, tdt::uint id, Ogre::Real delta, PLANE plane)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
	{
		Ogre::Vector3 plane_vector{0.f, 0.f, 0.f};
		switch(plane)
		{
			case PLANE::X:
				plane_vector.x = 1.f;
				break;
			case PLANE::Y:
				plane_vector.y = 1.f;
				break;
			case PLANE::Z:
				plane_vector.z = 1.f;
				break;
		}
		comp->node->rotate(plane_vector, Ogre::Radian{delta});
	}
}

const Ogre::AxisAlignedBox& GraphicsHelper::get_bounds(EntitySystem& ents, tdt::uint id)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp)
		return comp->entity->getWorldBoundingBox();
	else
		return Ogre::AxisAlignedBox::BOX_NULL; // TODO: Test this vs BOX_INFINITE.
}

bool GraphicsHelper::collide(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	return get_bounds(ents, id1).intersects(get_bounds(ents, id2));
}

void GraphicsHelper::init_graphics_component(EntitySystem& ents, Ogre::SceneManager& scene, tdt::uint id)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);

	if(!comp)
		return;

	if(comp->node && comp->entity)
	{
		comp->node->detachObject(comp->entity);
		scene.destroyEntity(comp->entity);
	}
	
	if(!comp->node)
		comp->node = scene.getRootSceneNode()->createChildSceneNode("entity_" + std::to_string(id));
	
	comp->entity = scene.createEntity(comp->mesh);
	comp->entity->setRenderingDistance(4000.f);
	comp->node->attachObject(comp->entity);
	comp->node->setVisible(comp->visible);

	if(comp->manual_scaling)
		comp->node->setScale(comp->scale);

	if(comp->material != "NO_MAT")
		comp->entity->setMaterialName(comp->material);

	auto half_height = comp->entity->getWorldBoundingBox(true).getHalfSize().y;
	auto phys_comp = ents.get_component<PhysicsComponent>(id);
	if(phys_comp)
	{
		phys_comp->half_height = half_height;
		phys_comp->position = Ogre::Vector3{phys_comp->position.x,
												   half_height, phys_comp->position.z};
		comp->node->setPosition(phys_comp->position);
	}

	auto light = ents.get_component<LightComponent>(id);
	if(light && light->light)
	{
		light->node = comp->node;
		light->node->attachObject(light->light);
	}
}

void GraphicsHelper::set_query_flags(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp && comp->entity)
		comp->entity->setQueryFlags(val);
}

tdt::uint GraphicsHelper::get_query_flags(EntitySystem& ents, tdt::uint id)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp && comp->entity)
		return comp->entity->getQueryFlags();
	else
		return tdt::uint{};
}

void GraphicsHelper::apply_scale(EntitySystem& ents, tdt::uint id)
{
	GraphicsComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GraphicsComponent);
	if(comp && comp->manual_scaling && comp->node)
		comp->node->setScale(comp->scale);
}
