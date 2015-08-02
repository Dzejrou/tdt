#include "EntityPlacer.hpp"

EntityPlacer::EntityPlacer(EntitySystem& ents, Ogre::SceneManager& mgr)
	: entities_{ents}, scene_mgr_{mgr}, curr_position_{0, 0, 0},
	  placing_node_{*mgr.getRootSceneNode()->createChildSceneNode()},
	  placed_entity_{nullptr}, visible_{false}, table_name_{},
	  half_height_{}
{ /* DUMMY BODY */ }

EntityPlacer::~EntityPlacer()
{
	if(placed_entity_)
	{
		scene_mgr_.destroyEntity(placed_entity_);
		placing_node_.detachAllObjects();
	}
	scene_mgr_.destroySceneNode(&placing_node_);
}

void EntityPlacer::set_current_entity_table(const std::string& table_name)
{
	auto& script = lpp::Script::get_singleton();
	if(script.is_nil(table_name + ".GraphicsComponent.mesh"))
		return;

	std::string mesh = script.get<std::string>(table_name + ".GraphicsComponent.mesh");
	if(entities_.get_registered_entities().count(table_name) != 0)
	{
		table_name_ = table_name;
		if(placed_entity_)
		{
			scene_mgr_.destroyEntity(placed_entity_);
			placing_node_.detachAllObjects();
		}
		placed_entity_ = scene_mgr_.createEntity(mesh);
		placing_node_.attachObject(placed_entity_);
		half_height_ = placed_entity_->getBoundingBox().getHalfSize().y;
	}
}

void EntityPlacer::update_position(const Ogre::Vector3& pos)
{
	curr_position_ = pos;
	placing_node_.setPosition(pos.x, half_height_, pos.y);
}

std::size_t EntityPlacer::place(Console& console)
{
	std::size_t id = entities_.create_entity(table_name_);

	if(entities_.has_component<PhysicsComponent>(id))
	{
		auto& comp = entities_.get_component<PhysicsComponent>(id);
		comp.position = Ogre::Vector3{curr_position_.x, comp.half_height, curr_position_.y};

		if(entities_.has_component<GraphicsComponent>(id))
			entities_.get_component<GraphicsComponent>(id).node->setPosition(curr_position_.x, comp.half_height,
																			 curr_position_.y);
	}

	console.print_text("Placed entity #" + std::to_string(id) + " at (" + std::to_string(curr_position_.x)
					   + ", " + std::to_string(curr_position_.y) + ")\nTable: " + table_name_);
	console.scroll_down();
	return id;
}

void EntityPlacer::set_visible(bool on_off)
{
	visible_ = on_off;
	placing_node_.setVisible(on_off);
}

bool EntityPlacer::is_visible() const
{
	return visible_;
}
