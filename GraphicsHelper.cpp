#include "GraphicsHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void GraphicsHelper::set_mesh(EntitySystem& ents, std::size_t id, const std::string& mesh)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		comp->mesh = mesh;
}

const std::string& GraphicsHelper::get_mesh(EntitySystem& ents, std::size_t id)
{
	static const std::string NO_MESH{"ERROR.mesh"}; // TODO: Create error mesh.

	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->mesh;
	else
		return NO_MESH;
}

void GraphicsHelper::set_material(EntitySystem& ents, std::size_t id, const std::string& material)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
	{
		comp->material = material;
		if(comp->entity)
			comp->entity->setMaterialName(comp->material);
	}
}

const std::string& GraphicsHelper::get_material(EntitySystem& ents, std::size_t id)
{
	static const std::string NO_MATERIAL{"colour/pink"}; // TODO: Create pink error material.

	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->material;
	else
		return NO_MATERIAL;
}

void GraphicsHelper::set_visible(EntitySystem& ents, std::size_t id, bool val)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
	{
		comp->visible = val;
		if(comp->node)
			comp->node->setVisible(val);
	}
}

bool GraphicsHelper::is_visible(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->visible;
	else
		return false;
}

void GraphicsHelper::set_manual_scaling(EntitySystem& ents, std::size_t id, bool val)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		comp->manual_scaling = val;
}

bool GraphicsHelper::get_manual_scaling(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->manual_scaling;
	else
		return false;
}

void GraphicsHelper::set_scale(EntitySystem& ents, std::size_t id, const Ogre::Vector3& val)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		comp->scale = val;
}

const Ogre::Vector3& GraphicsHelper::get_scale(EntitySystem& ents, std::size_t id)
{
	static const Ogre::Vector3 NO_SCALE{0.f, 0.f, 0.f};

	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->scale;
	else
		return NO_SCALE;
}

void GraphicsHelper::look_at(EntitySystem& ents, std::size_t id1, std::size_t id2)
{
	auto comp1 = ents.get_component<GraphicsComponent>(id1);
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

void GraphicsHelper::rotate(EntitySystem& ents, std::size_t id, Ogre::Real delta, PLANE plane)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
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

const Ogre::AxisAlignedBox& GraphicsHelper::get_bounds(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->entity->getWorldBoundingBox();
	else
		return Ogre::AxisAlignedBox::BOX_NULL; // TODO: Test this vs BOX_INFINITE.
}

bool GraphicsHelper::collide(EntitySystem& ents, std::size_t id1, std::size_t id2)
{
	return get_bounds(ents, id1).intersects(get_bounds(ents, id2));
}

void GraphicsHelper::init_graphics_component(EntitySystem& ents, Ogre::SceneManager& scene, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);

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

void GraphicsHelper::set_query_flags(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp && comp->entity)
		comp->entity->setQueryFlags(val);
}

std::size_t GraphicsHelper::get_query_flags(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp && comp->entity)
		return comp->entity->getQueryFlags();
	else
		return std::size_t{};
}

void GraphicsHelper::apply_scale(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp && comp->manual_scaling && comp->node)
		comp->node->setScale(comp->scale);
}
