#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "SelectionHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::SelectionCache cache{Component::NO_ENTITY, nullptr};
#endif

void SelectionHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& blueprint)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		comp->blueprint = blueprint;
}

const std::string& SelectionHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void SelectionHelper::set_material(EntitySystem& ents, tdt::uint id, const std::string& material)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		comp->material = material;
}

const std::string& SelectionHelper::get_material(EntitySystem& ents, tdt::uint id)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		return comp->material;
	else
		return ents.NO_MATERIAL;
}

bool SelectionHelper::select(EntitySystem& ents, tdt::uint id, bool single)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
	{
		if(comp->blueprint != "ERROR")
			lpp::Script::instance().call<void, tdt::uint, bool>(comp->blueprint + ".select", id, single);

		if(!comp->entity)
		{
			auto graph = ents.get_component<GraphicsComponent>(id);
			if(graph && graph->node)
			{ // Should always be non-null, but just to be sure.
				if(comp->marker_type == SELECTION_MARKER_TYPE::CIRCLE)
					comp->entity = ents.get_scene_manager().createEntity("selection_circle.mesh");
				else if(comp->marker_type == SELECTION_MARKER_TYPE::SQUARE)
					comp->entity = ents.get_scene_manager().createEntity("selection_square.mesh");
				else if(comp->marker_type == SELECTION_MARKER_TYPE::HALF_SQUARE)
					comp->entity = ents.get_scene_manager().createEntity("selection_half_square.mesh");
				else
					return false;

				if(comp->material != "NO_MAT")
					comp->entity->setMaterialName(comp->material);
				auto child = graph->node->createChildSceneNode("selection_" + std::to_string(id));
				child->attachObject(comp->entity);

				if(comp->marker_type == SELECTION_MARKER_TYPE::CIRCLE)
					child->translate(0.f, -1.f * graph->node->getPosition().y + 1.f , 0.f, Ogre::Node::TS_WORLD);
				else if(comp->marker_type == SELECTION_MARKER_TYPE::SQUARE || comp->marker_type == SELECTION_MARKER_TYPE::HALF_SQUARE)
				{
					if(graph->mesh == "cube-4.mesh") // This one is a bit lower.
						child->translate(0.f, graph->node->getPosition().y + 3.f , 0.f, Ogre::Node::TS_WORLD);
					else
						child->translate(0.f, graph->node->getPosition().y + 1.f , 0.f, Ogre::Node::TS_WORLD);
				}

				if(comp->marker_type == SELECTION_MARKER_TYPE::HALF_SQUARE)
					child->rotate(Ogre::Vector3::UNIT_Y, comp->rotation);

				child->setScale(comp->scale);
			}
		}
		return true;
	}
	else
		return false;
}

bool SelectionHelper::deselect(EntitySystem& ents, tdt::uint id)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
	{
		if(comp->blueprint != "ERROR")
			lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".deselect", id);

		if(comp->entity)
		{
			auto graph = ents.get_component<GraphicsComponent>(id);
			if(graph && graph->node)
			{ // Should always be non-null, but just to be sure.
				auto child = comp->entity->getParentSceneNode();
				if(child)
				{
					child->detachAllObjects();
					graph->node->removeChild(child);
					ents.get_scene_manager().destroySceneNode(child);
				}
				ents.get_scene_manager().destroyEntity(comp->entity);
				comp->entity = nullptr;
			}
		}
		return true;
	}
	return false;
}

void SelectionHelper::set_scale(EntitySystem& ents, tdt::uint id, Ogre::Vector3 val)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
	{
		comp->scale = val;
		if(comp->entity && comp->entity->getParentSceneNode())
			comp->entity->getParentSceneNode()->setScale(val);
	}
}

Ogre::Vector3 SelectionHelper::get_scale(EntitySystem& ents, tdt::uint id)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		return comp->scale;
	else
		return Ogre::Vector3{};
}

void SelectionHelper::set_marker_type(EntitySystem& ents, tdt::uint id, SELECTION_MARKER_TYPE type)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		comp->marker_type = type;
}

SELECTION_MARKER_TYPE SelectionHelper::get_marker_type(EntitySystem& ents, tdt::uint id)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		return comp->marker_type;
	else
		return SELECTION_MARKER_TYPE::CIRCLE;
}

void SelectionHelper::set_rotation(EntitySystem& ents, tdt::uint id, Ogre::Degree val)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		comp->rotation = val;
}

Ogre::Degree SelectionHelper::get_rotation(EntitySystem& ents, tdt::uint id)
{
	SelectionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SelectionComponent);
	if(comp)
		return comp->rotation;
	else
		return Ogre::Degree{};
}
