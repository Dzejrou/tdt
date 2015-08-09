#include "EntityPlacer.hpp"

EntityPlacer::EntityPlacer(EntitySystem& ents, GridSystem& grid)
	: entities_{ents}, grid_{grid}, curr_position_{0, 0, 0},
	  placing_node_{}, visible_{false}, table_name_{},
	  half_height_{}, placing_structure_{false}, structure_radius_{0},
	  placed_id_{Component::NO_ENTITY}
{ /* DUMMY BODY */ }

EntityPlacer::~EntityPlacer()
{
	if(placed_id_ != Component::NO_ENTITY)
		entities_.destroy_entity(placed_id_);
}

void EntityPlacer::set_current_entity_table(const std::string& table_name)
{
	auto& script = lpp::Script::get_singleton();
	if(script.is_nil(table_name + ".GraphicsComponent.mesh"))
		return;

	if(!script.is_nil(table_name + ".StructureComponent"))
	{
		placing_structure_ = true;
		structure_radius_ = script.get<std::size_t>(table_name + ".StructureComponent.radius");
	}
	else
		placing_structure_ = false;

	if(entities_.get_registered_entities().count(table_name) != 0)
	{
		table_name_ = table_name;
		if(placed_id_ != Component::NO_ENTITY)
			entities_.destroy_entity(placed_id_);

		placed_id_ = entities_.create_entity(table_name);
		auto& comp = entities_.get_component<GraphicsComponent>(placed_id_);
		comp.entity->setQueryFlags(0); // Ignored by selection.
		placing_node_ = comp.node;

		if(comp.manual_scaling)
			half_height_ = comp.scale.y;
		else
			half_height_ = comp.entity->getBoundingBox().getHalfSize().y;
	}
}

void EntityPlacer::update_position(const Ogre::Vector3& pos)
{
	if(placing_structure_)
	{
		auto node_id = grid_.get_node_from_position(pos.x, pos.z);

		if(node_id == Component::NO_ENTITY)
			return;

		// Snap to grid.
		auto& node_pos = entities_.get_component<PhysicsComponent>(node_id).position;
		curr_position_ = Ogre::Vector3{node_pos.x, half_height_, node_pos.z};
	}
	else
		curr_position_ = Ogre::Vector3{pos.x, half_height_, pos.z};
	
	placing_node_->setPosition(curr_position_);
}

std::size_t EntityPlacer::place(Console& console)
{
	std::size_t id = entities_.create_entity(table_name_);

	if(entities_.has_component<PhysicsComponent>(id))
	{
		auto& comp = entities_.get_component<PhysicsComponent>(id);
		comp.position = Ogre::Vector3{curr_position_.x, comp.half_height, curr_position_.z};

		if(entities_.has_component<GraphicsComponent>(id))
			entities_.get_component<GraphicsComponent>(id).node->setPosition(curr_position_.x, comp.half_height,
																			 curr_position_.z);
	}

	if(placing_structure_)
		grid_.place_structure(id, grid_.get_node_from_position(curr_position_.x, curr_position_.z), structure_radius_);

	console.print_text("Placed entity #" + std::to_string(id) + " at (" + std::to_string(curr_position_.x)
					   + ", " + std::to_string(curr_position_.y) + ")\nTable: " + table_name_);
	console.scroll_down();
	return id;
}

void EntityPlacer::set_visible(bool on_off)
{
	visible_ = on_off;
	placing_node_->setVisible(on_off);

	if(!on_off)
		placing_structure_ = false;
}

bool EntityPlacer::is_visible() const
{
	return visible_;
}
