#include "EntityPlacer.hpp"
#include "EntitySystem.hpp"
#include "GridSystem.hpp"
#include "GUI.hpp"
#include "Helpers.hpp"

EntityPlacer::EntityPlacer(EntitySystem& ents, GridSystem& grid, Ogre::SceneManager& mgr)
	: entities_{ents}, grid_{grid}, curr_position_{0, 0, 0},
	  placing_node_{mgr.getRootSceneNode()->createChildSceneNode()}, visible_{false}, table_name_{},
	  half_height_{}, placing_structure_{false}, structure_radius_{0}, mgr_{mgr},
	  ent_{nullptr}, price_{0}
{ /* DUMMY BODY */ }

EntityPlacer::~EntityPlacer()
{
	if(placing_node_)
		mgr_.destroySceneNode(placing_node_);
	if(ent_)
		mgr_.destroyEntity(ent_);
}
void EntityPlacer::set_current_entity_table(const std::string& table_name, bool use_price)
{
	if(entities_.get_registered_entities().count(table_name) == 0)
		return;

	auto& script = lpp::Script::get_singleton();
	if(script.is_nil(table_name + ".GraphicsComponent"))
		return;

	table_name_ = table_name;
	std::string mesh = script.get<std::string>(table_name + ".GraphicsComponent.mesh");
	std::string mat = script.get<std::string>(table_name + ".GraphicsComponent.material");
	bool man_scaling = script.get<bool>(table_name + ".GraphicsComponent.manual_scaling");
	if(ent_)
	{ // Recreation of the entity is required by Ogre.
		mgr_.destroyEntity(ent_);
		placing_node_->detachAllObjects();
		placing_node_->setScale(1.f, 1.f, 1.f);
		price_ = 0;
	}
	ent_ = mgr_.createEntity(mesh);
	ent_->setQueryFlags(0);
	placing_node_->attachObject(ent_);

	if(mat != "NO_MAT")
		ent_->setMaterialName(mat);
	
	if(!script.is_nil(table_name + ".StructureComponent"))
	{
		placing_structure_ = true;
		structure_radius_ = script.get<tdt::uint>(table_name + ".StructureComponent.radius");
	}
	else
		placing_structure_ = false;

	if(use_price && !script.is_nil(table_name + ".PriceComponent"))
		price_ = script.get<tdt::uint>(table_name + ".PriceComponent.price");

	if(man_scaling)
	{
		tdt::real x, y, z;
		x = script.get<tdt::real>(table_name + ".GraphicsComponent.scale_x");
		y = script.get<tdt::real>(table_name + ".GraphicsComponent.scale_y");
		z = script.get<tdt::real>(table_name + ".GraphicsComponent.scale_z");
		placing_node_->setScale(x, y, z);
		half_height_ = y;
	}
	else
		half_height_ = ent_->getWorldBoundingBox(true).getHalfSize().y;
}

void EntityPlacer::update_position(const Ogre::Vector3& pos)
{
	if(placing_structure_)
	{
		auto node_id = Grid::instance().get_node_from_position(pos.x, pos.z);

		if(node_id == Component::NO_ENTITY)
			return;

		// Snap to grid.
		auto comp = entities_.get_component<PhysicsComponent>(node_id);
		if(comp)
		{
			auto& node_pos = comp->position;
			curr_position_ = Ogre::Vector3{node_pos.x, half_height_, node_pos.z};
		}
	}
	else
		curr_position_ = Ogre::Vector3{pos.x, half_height_, pos.z};
	
	placing_node_->setPosition(curr_position_);
}

tdt::uint EntityPlacer::place()
{
	if(!Player::instance().sub_gold(price_))
	{
		GUI::instance().get_log().print("\\[ERROR\\] Not enough gold to place that.");
		return Component::NO_ENTITY;
	}

	tdt::uint node_id = Grid::instance().get_node_from_position(curr_position_.x, curr_position_.z);
	if(placing_structure_ && !GridNodeHelper::area_free(entities_, node_id, structure_radius_))
		return Component::NO_ENTITY; // This will prohibit of wall/building stacking.

	auto position = Ogre::Vector3{curr_position_.x, 0.f, curr_position_.z}; // Used to trigger constrcutors.
	tdt::uint id = entities_.create_entity(table_name_, position);
	auto comp = entities_.get_component<PhysicsComponent>(id);
	if(comp)
	{
		comp->position = Ogre::Vector3{curr_position_.x,
									   comp->half_height,
									   curr_position_.z};
		
		auto graph_comp = entities_.get_component<GraphicsComponent>(id);
		if(graph_comp)
		{
			graph_comp->node->setPosition(curr_position_.x, comp->half_height,
										  curr_position_.z);
		}
	}

	if(placing_structure_)
		grid_.place_structure(id, node_id, structure_radius_);

	GUI::instance().get_console().print_text("Placed entity #" + std::to_string(id)
										   + " at (" + std::to_string(curr_position_.x)
										   + ", " + std::to_string(curr_position_.z)
										   + ")\nTable: " + table_name_);
	return id;
}

void EntityPlacer::set_visible(bool on_off)
{
	visible_ = on_off;
	if(placing_node_)
		placing_node_->setVisible(visible_);
	if(placing_structure_ && !on_off)
		placing_structure_ = false;
}

bool EntityPlacer::is_visible() const
{
	return visible_;
}

void EntityPlacer::toggle_placing_when_game_paused()
{
	can_place_when_game_paused_ = !can_place_when_game_paused_;
}

bool EntityPlacer::can_place_when_game_paused() const
{
	return can_place_when_game_paused_;
}
