#include "LuaInterface.hpp"
#include "Game.hpp"

/**
 * Static member initialization, will be set in the
 * init method.
 */
Game* LuaInterface::lua_this = nullptr;

void LuaInterface::init(Game* game)
{
	lua_this = game;

	// Register all functions that will be used in Lua.
	lpp::Script& script = lpp::Script::get_singleton();
	lpp::Script::regs game_funcs[] = {
		// Core functions.
		{"get_avg_fps", LuaInterface::lua_get_avg_fps},
		{"get_fps", LuaInterface::lua_get_fps},
		{"print", LuaInterface::lua_print},
		{"set_game_state", LuaInterface::lua_set_game_state},
		{"toggle_bounding_boxes", LuaInterface::lua_toggle_bounding_boxes},
		{"toggle_camera_free_mode", LuaInterface::lua_toggle_camera_free_mode},
		{"toggle_entity_creator", LuaInterface::lua_toggle_entity_creator},
		{"list_selected", LuaInterface::lua_list_selected},
		{"destroy_selected", LuaInterface::lua_destroy_selected},
		{"list_components_of", LuaInterface::lua_list_components_of},
		{"load", LuaInterface::lua_load},
		{"reload_all", LuaInterface::lua_reload_all},
		{"save_game", LuaInterface::lua_save_game},
		{"load_game", LuaInterface::lua_load_game},

		// Ogre related functions.
		{"set_mesh", LuaInterface::lua_set_mesh},
		{"set_material", LuaInterface::lua_set_material},
		{"set_visible", LuaInterface::lua_set_visible},
		{"set_manual_scaling", LuaInterface::lua_set_manual_scaling},
		{"set_scale", LuaInterface::lua_set_scale},

		// Entity manipulation.
		{"create_entity", LuaInterface::lua_create_entity},
		{"destroy_entity", LuaInterface::lua_destroy_entity},
		{"add_component", LuaInterface::lua_add_component},
		{"delete_component", LuaInterface::lua_delete_component},
		{"init_graphics_component", LuaInterface::lua_init_graphics_component},
		{"list_entity_tables", LuaInterface::lua_list_entity_tables},
		{"place_entity", LuaInterface::lua_place_entity},
		{"register_entity", LuaInterface::lua_register_entity},

		// Movement system.
		{"move_to", LuaInterface::lua_move_to},
		{"move", LuaInterface::lua_move},
		{"rotate", LuaInterface::lua_rotate},
		{"is_moving", LuaInterface::lua_is_moving},
		{"is_solid", LuaInterface::lua_is_solid},
		{"can_move_to", LuaInterface::lua_can_move_to},
		{"collide", LuaInterface::lua_collide},
		{"get_distance", LuaInterface::lua_get_distance},
		{"get_position", LuaInterface::lua_get_position},
		{"get_speed", LuaInterface::lua_get_speed_modifier},
		{"set_speed", LuaInterface::lua_set_speed_modifier},
		{"enemy_in_radius", LuaInterface::lua_enemy_in_radius},
		{"dir_to_closest_enemy", LuaInterface::lua_dir_to_closest_enemy},
		{"dir_to_closest_enemy_in_radius", LuaInterface::lua_dir_to_closest_enemy_in_radius},
		{"dir_to_enemy", LuaInterface::lua_dir_to_enemy},
		{"get_dir", LuaInterface::lua_get_dir},
		{"get_dir_back", LuaInterface::lua_get_dir_back},
		{"get_dir_left", LuaInterface::lua_get_dir_left},
		{"get_dir_right", LuaInterface::lua_get_dir_right},
		{"get_angle", LuaInterface::lua_get_angle},
		{"get_angle_between", LuaInterface::lua_get_angle_between},
		{"look_at", LuaInterface::lua_look_at},
		{"set_solid", LuaInterface::lua_set_solid},
		{"set_half_height", LuaInterface::lua_set_half_height},

		// Health system.
		{"get_health", LuaInterface::lua_get_health},
		{"add_health", LuaInterface::lua_add_health},
		{"sub_health", LuaInterface::lua_sub_health},
		{"heal", LuaInterface::lua_heal},
		{"buff", LuaInterface::lua_buff},
		{"get_defense", LuaInterface::lua_get_defense},
		{"add_defense", LuaInterface::lua_add_defense},
		{"sub_defense", LuaInterface::lua_sub_defense},
		{"set_regen", LuaInterface::lua_set_regen},
		{"set_alive", LuaInterface::lua_set_alive},

		// AI system.
		{"is_friendly", LuaInterface::lua_is_friendly},
		{"is_neutral", LuaInterface::lua_is_neutral},
		{"is_inanimate", LuaInterface::lua_is_inanimate},
		{"get_blueprint", LuaInterface::lua_get_blueprint},
		{"get_state", LuaInterface::lua_get_state},
		{"get_faction", LuaInterface::lua_get_faction},
		{"set_blueprint", LuaInterface::lua_set_blueprint},
		{"set_state", LuaInterface::lua_set_state},
		{"set_faction", LuaInterface::lua_set_faction},

		// Input system.
		{"set_input_handler", LuaInterface::lua_set_input_handler},
		{"toggle_first_person", LuaInterface::lua_toggle_first_person},

		// Grid system.
		{"add_node", LuaInterface::lua_add_node},
		{"get_node", LuaInterface::lua_get_node},
		{"get_node_from_position", LuaInterface::lua_get_node_from_position},
		{"create_grid_graphics", LuaInterface::lua_create_grid_graphics},
		{"delete_grid_graphics", LuaInterface::lua_delete_grid_graphics},
		{"toggle_grid_visible", LuaInterface::lua_toggle_grid_visible},
		{"is_free", LuaInterface::lua_is_free},
		{"set_free", LuaInterface::lua_set_free},
		{"set_free_selected", LuaInterface::lua_set_free_selected},
		{"pathfind", LuaInterface::lua_pathfind},
		{"clear_path_colour", LuaInterface::lua_clear_path_colour},
		{"set_pathfinding_blueprint", LuaInterface::lua_set_pathfinding_blueprint},
		{"create_graph", LuaInterface::lua_create_graph},
		{"set_resident", LuaInterface::lua_set_resident},
		{"get_resident", LuaInterface::lua_get_resident},
		{"add_residences", LuaInterface::lua_add_residences},
		{"add_residence", LuaInterface::lua_add_residence},
		{"set_radius", LuaInterface::lua_set_radius},
		{"set_walk_through", LuaInterface::lua_set_walk_through},

		// Task system.
		{"add_task", LuaInterface::lua_add_task},
		{"cancel_task", LuaInterface::lua_cancel_task},
		{"create_task", LuaInterface::lua_create_task},
		{"list_tasks_of", LuaInterface::lua_list_tasks_of},
		{"task_possible", LuaInterface::lua_task_possible},
		{"clear_task_queue", LuaInterface::lua_clear_task_queue},
		{"set_task_source", LuaInterface::lua_set_task_source},
		{"set_task_target", LuaInterface::lua_set_task_target},
		{"set_task_type", LuaInterface::lua_set_task_type},
		{"add_possible_task", LuaInterface::lua_add_possible_task},
		{"delete_possible_task", LuaInterface::lua_delete_possible_task},

		// Combat system.
		{"set_range", LuaInterface::lua_set_range},
		{"get_range", LuaInterface::lua_get_range},
		{"set_dmg_range", LuaInterface::lua_set_dmg_range},
		{"get_dmg_range", LuaInterface::lua_get_dmg_range},
		{"set_cooldown", LuaInterface::lua_set_cooldown},
		{"get_cooldown", LuaInterface::lua_get_cooldown},
		{"set_atk_type", LuaInterface::lua_set_atk_type},
		{"get_atk_type", LuaInterface::lua_get_atk_type},
		{"set_homing_source", LuaInterface::lua_set_homing_source},
		{"set_homing_target", LuaInterface::lua_set_homing_target},
		{"set_homing_dmg", LuaInterface::lua_set_homing_dmg},
		{"closest_enemy_in_sight", LuaInterface::lua_closest_enemy_in_sight},
		{"closest_friendly_in_sight", LuaInterface::lua_closest_friendly_in_sight},
		{"closest_enemy", LuaInterface::lua_closest_enemy},
		{"closest_friendly", LuaInterface::lua_closest_friendly},

		// Production system.
		{"set_production_blueprint", LuaInterface::lua_set_production_blueprint},
		{"get_production_blueprint", LuaInterface::lua_get_production_blueprint},
		{"set_production_limit", LuaInterface::lua_set_production_limit},
		{"get_production_limit", LuaInterface::lua_get_production_limit},
		{"set_production_cooldown", LuaInterface::lua_set_production_cooldown},
		{"get_production_cooldown", LuaInterface::lua_get_production_cooldown},
		{"set_production_progress", LuaInterface::lua_set_production_progress},
		{"get_production_progress", LuaInterface::lua_get_production_progress},
		{"set_production_count", LuaInterface::lua_set_production_count},
		{"get_production_count", LuaInterface::lua_get_production_count},
		{"set_producer", LuaInterface::lua_set_producer},
		{"get_producer", LuaInterface::lua_get_producer},
		{"instant_production", LuaInterface::lua_instant_production},

		// Ending sentinel (required by Lua).
		{nullptr, nullptr}
	};
	luaL_newlib(script.get_state(), game_funcs);
	lua_setglobal(script.get_state(), "game");

	// Set some C++ constants.
	script.execute("game.const = {}");
	script.execute("game.const.no_ent = " + std::to_string(Component::NO_ENTITY));

	// Load all necessary scripts. TODO: Load all lua scripts!
	script.load("scripts/core.lua");

	// InputComponent related enums.
	script.set("game.enum.input.key_up", OIS::KC_W);
	script.set("game.enum.input.key_down", OIS::KC_S);
	script.set("game.enum.input.key_left", OIS::KC_A);
	script.set("game.enum.input.key_right", OIS::KC_D);
}

/**
 * Note: Function definitions below act as an interface between C++ and Lua, they all have
 *		 to have the signature int fname(lpp::Script::state) and return the number of results
 *       pushed onto the Lua stack (Lua allows to return multiple results if needed).
 * Important: These functions will have their arguments on the stack in REVERSED ORDER!
 *            (Because, you know, it's a stack...)
 */
#pragma region LUA
int LuaInterface::lua_get_avg_fps(lpp::Script::state L)
{
	auto res = lua_this->window_->getAverageFPS();
	lua_pushnumber(L, res);
	return 1;
}
int LuaInterface::lua_get_fps(lpp::Script::state L)
{
	auto res = lua_this->window_->getLastFPS();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_print(lpp::Script::state L)
{
	std::string msg = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lua_this->console_.print_text(msg, Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_set_game_state(lpp::Script::state L)
{
	GAME_STATE state = (GAME_STATE)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	lua_this->set_state(state);
	return 0;
}

int LuaInterface::lua_toggle_bounding_boxes(lpp::Script::state)
{
	lua_this->scene_mgr_->showBoundingBoxes(!lua_this->scene_mgr_->getShowBoundingBoxes());
	return 0;
}

int LuaInterface::lua_toggle_camera_free_mode(lpp::Script::state)
{
	lua_this->toggle_camera_free_mode();
	return 0;
}

int LuaInterface::lua_toggle_entity_creator(lpp::Script::state L)
{
	lua_this->entity_creator_->set_visible(!lua_this->entity_creator_->is_visible());
	return 0;
}

int LuaInterface::lua_list_selected(lpp::Script::state)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
	{
		lua_this->console_.print_text(std::to_string(ent), Console::ORANGE_TEXT);
	}

	return 0;
}

int LuaInterface::lua_destroy_selected(lpp::Script::state)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
	{
		lua_this->entity_system_->destroy_entity(ent);
	}
	lua_this->selection_box_->clear_selected_entities();

	return 0;
}

int LuaInterface::lua_list_components_of(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::string report{};
	auto& ent = lua_this->entity_system_->get_component_list().find(id);
	if(ent != lua_this->entity_system_->get_component_list().end())
	{
		for(std::size_t i = 0; i < ent->second.size(); ++i)
		{
			if(ent->second.test(i))
				report.append(std::to_string(i) + ", ");
		}
	}

	lua_this->console_.print_text(report, Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_load(lpp::Script::state L)
{
	std::string script = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lpp::Script::get_singleton().load(script);
	return 0;
}

int LuaInterface::lua_reload_all(lpp::Script::state L)
{
	lpp::Script::get_singleton().reload_all_scripts();
	return 0;
}

int LuaInterface::lua_save_game(lpp::Script::state L)
{
	if(lua_gettop(L) > 0)
	{
		std::string fname = luaL_checkstring(L, -1);
		lua_pop(L, 1);
		lua_this->game_serializer_->save_game(*lua_this, fname);
	}
	else
		lua_this->game_serializer_->save_game(*lua_this);

	return 0;
}

int LuaInterface::lua_load_game(lpp::Script::state L)
{
	if(lua_gettop(L) > 0)
	{
		std::string fname = luaL_checkstring(L, -1);
		lua_pop(L, 1);
		lua_this->game_serializer_->load_game(*lua_this, fname);
	}
	else
		lua_this->game_serializer_->load_game(*lua_this);

	return 0;
}

int LuaInterface::lua_set_mesh(lpp::Script::state L)
{
	std::string mesh = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto comp = lua_this->entity_system_->get_component<GraphicsComponent>(id);
	if(comp)
		comp->mesh = mesh;
	return 0;
}

int LuaInterface::lua_set_material(lpp::Script::state L)
{
	std::string mat = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto comp = lua_this->entity_system_->get_component<GraphicsComponent>(id);
	if(comp)
		comp->material = mat;
	return 0;
}

int LuaInterface::lua_set_visible(lpp::Script::state L)
{
	bool vis = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto comp = lua_this->entity_system_->get_component<GraphicsComponent>(id);
	if(comp)
		comp->node->setVisible(vis);
	return 0;
}

int LuaInterface::lua_set_manual_scaling(lpp::Script::state L)
{
	bool on_off = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto comp = lua_this->entity_system_->get_component<GraphicsComponent>(id);
	if(comp)
		comp->manual_scaling = on_off;
	return 0;
}

int LuaInterface::lua_set_scale(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	auto comp = lua_this->entity_system_->get_component<GraphicsComponent>(id);
	if(comp)
	{
		comp->scale = Ogre::Vector3{x, y, z};
		if(comp->node)
			comp->node->setScale(x, y, z);
		comp->node->setPosition(
				comp->node->getPosition().x,
				comp->entity->getWorldBoundingBox(true).getHalfSize().y,
				comp->node->getPosition().z
			);
		auto phys_comp = lua_this->entity_system_->get_component<PhysicsComponent>(id);
		if(phys_comp)
			phys_comp->half_height = comp->entity->getWorldBoundingBox(true).getHalfSize().y;
	}
	return 0;
}

int LuaInterface::lua_create_entity(lpp::Script::state L)
{
	std::string table_name{""};
	if(lua_gettop(L) >= 1)
	{
		table_name = luaL_checkstring(L, 1);
		lua_pop(L, 1);
	}

	std::size_t id = lua_this->entity_system_->create_entity(table_name);
	lua_pushinteger(L, id); // Return the new id.
	return 1;
}

int LuaInterface::lua_destroy_entity(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->entity_system_->destroy_entity(id);
	return 0;
}

int LuaInterface::lua_add_component(lpp::Script::state L)
{
	int comp = (int)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->entity_system_->add_component(id, comp);
	return 0;
}

int LuaInterface::lua_delete_component(lpp::Script::state L)
{
	int comp = (int)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->entity_system_->delete_component(id, comp);
	return 0;
}

int LuaInterface::lua_init_graphics_component(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->entity_system_->init_graphics_component(id);
	return 0;
}

int LuaInterface::lua_list_entity_tables(lpp::Script::state L)
{
	auto& ents = lua_this->entity_system_->get_registered_entities();

	if(!ents.empty())
	{
		for(const auto& ent : ents)
			lua_this->console_.print_text(ent, Console::ORANGE_TEXT);
	}
	else
		lua_this->console_.print_text("NO REGISTERED ENTITY TABLES.", Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_place_entity(lpp::Script::state L)
{
	std::string table_name = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lua_this->placer_->set_current_entity_table(table_name);
	lua_this->placer_->set_visible(true);
	return 0;
}

int LuaInterface::lua_register_entity(lpp::Script::state L)
{
	std::string table_name = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lua_this->entity_system_->register_entity(table_name);
	return 0;
}

int LuaInterface::lua_move_to(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	lua_this->movement_system_->move_to(id, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_move(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	bool res = lua_this->movement_system_->move(id, Ogre::Vector3{x, y, z});
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_rotate(lpp::Script::state L)
{
	Ogre::Real delta = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->rotate(id, delta);
	return 0;
}

int LuaInterface::lua_is_moving(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->movement_system_->is_moving(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_is_solid(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->movement_system_->is_solid(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_can_move_to(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	bool res = lua_this->movement_system_->can_move_to(id, Ogre::Vector3{x, y, z});
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_collide(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = lua_this->movement_system_->collide(id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_distance(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	Ogre::Real res = lua_this->movement_system_->get_distance(id1, id2);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_position(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	Ogre::Vector3 res = lua_this->movement_system_->get_position(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_speed_modifier(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	Ogre::Real res = lua_this->movement_system_->get_speed_modifier(id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_speed_modifier(lpp::Script::state L)
{
	Ogre::Real speed = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->set_speed_modifier(id, speed);
	return 0;
}

int LuaInterface::lua_enemy_in_radius(lpp::Script::state L)
{
	Ogre::Real radius = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->movement_system_->enemy_in_radius(id, radius);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_dir_to_closest_enemy(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->dir_to_closest_enemy(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_dir_to_closest_enemy_in_radius(lpp::Script::state L)
{
	Ogre::Real radius = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto res = lua_this->movement_system_->dir_to_closest_enemy(id, radius);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_dir_to_enemy(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto res = lua_this->movement_system_->dir_to_enemy(id1, id2);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_back(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir_back(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_left(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir_left(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_right(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir_right(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_angle(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	auto dir = lua_this->movement_system_->get_dir(id);
	auto res = lua_this->movement_system_->get_angle(dir, Ogre::Vector3{x, y, z});
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_angle_between(lpp::Script::state L)
{
	Ogre::Real z2 = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y2 = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x2 = (Ogre::Real)luaL_checknumber(L, -3);
	Ogre::Real z1 = (Ogre::Real)luaL_checknumber(L, -4);
	Ogre::Real y1 = (Ogre::Real)luaL_checknumber(L, -5);
	Ogre::Real x1 = (Ogre::Real)luaL_checknumber(L, -6);
	lua_pop(L, 6);

	auto res = lua_this->movement_system_->get_angle(Ogre::Vector3{x1, y1, z1}, Ogre::Vector3{x2, y2, z2});
	lua_pushnumber(L, res);
	return 3;
}

int LuaInterface::lua_look_at(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->look_at(id1, id2);
	return 0;
}

int LuaInterface::lua_set_solid(lpp::Script::state L)
{
	bool solid = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->set_solid(id, solid);
	return 0;
}

int LuaInterface::lua_set_half_height(lpp::Script::state L)
{
	Ogre::Real hh = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->set_half_height(id, hh);
	return 0;
}

int LuaInterface::lua_get_health(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = lua_this->health_system_->get_health(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_health(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->add_health(id, val);
	return 0;
}

int LuaInterface::lua_sub_health(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->sub_health(id, val);
	return 0;
}

int LuaInterface::lua_heal(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 2);

	lua_this->health_system_->heal(id);
	return 0;
}

int LuaInterface::lua_buff(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->buff(id, val);
	return 0;
}

int LuaInterface::lua_get_defense(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = (std::size_t)lua_this->health_system_->get_defense(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_defense(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->add_defense(id, val);
	return 0;
}

int LuaInterface::lua_sub_defense(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->sub_defense(id, val);
	return 0;
}

int LuaInterface::lua_set_regen(lpp::Script::state L)
{
	std::size_t regen = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->set_regen(id, regen);
	return 0;
}

int LuaInterface::lua_set_alive(lpp::Script::state L)
{
	bool alive = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->set_alive(id, alive);
	return 0;
}

int LuaInterface::lua_is_friendly(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = lua_this->ai_system_->is_friendly(id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_is_neutral(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->ai_system_->is_neutral(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_is_inanimate(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->ai_system_->is_inanimate(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_blueprint(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::string res = lua_this->ai_system_->get_blueprint(id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_get_state(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	int res = (int)lua_this->ai_system_->get_state(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_faction(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	int res = (int)lua_this->ai_system_->get_faction(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_blueprint(id, blueprint);
	return 0;
}

int LuaInterface::lua_set_state(lpp::Script::state L)
{
	ENTITY_STATE state = (ENTITY_STATE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_state(id, state);
	return 0;
}

int LuaInterface::lua_set_faction(lpp::Script::state L)
{
	FACTION faction = (FACTION)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_faction(id, faction);
	return 0;
}

int LuaInterface::lua_set_input_handler(lpp::Script::state L)
{
	std::string handler = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->input_system_->set_input_handler(id, handler);
	return 0;
}

int LuaInterface::lua_toggle_first_person(lpp::Script::state L)
{
	std::size_t id{Component::NO_ENTITY};
	if(lua_gettop(L) >= 1) // Allow for easy exit.
	{
		id = (std::size_t)luaL_checkinteger(L, -1);
		lua_pop(L, 1);
	}

	lua_this->input_system_->set_first_person(!lua_this->input_system_->is_first_person(), id);
	return 0;
}

int LuaInterface::lua_add_node(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	lua_pop(L, 3);

	std::size_t res = lua_this->grid_system_->add_node(x, y, z);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_node(lpp::Script::state L)
{
	std::size_t y = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t x = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->grid_system_->get_node(x, y);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_node_from_position(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->grid_system_->get_node_from_position(x, z);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_create_grid_graphics(lpp::Script::state L)
{
	lua_this->grid_system_->create_graphics();
	return 0;
}

int LuaInterface::lua_delete_grid_graphics(lpp::Script::state L)
{
	lua_this->grid_system_->delete_graphics();
	return 0;
}

int LuaInterface::lua_toggle_grid_visible(lpp::Script::state)
{
	lua_this->grid_system_->set_visible(!lua_this->grid_system_->is_visible());
	return 0;
}

int LuaInterface::lua_is_free(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->grid_system_->is_free(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_free(lpp::Script::state L)
{
	bool free = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_free(id, free);
	return 0;
}

int LuaInterface::lua_set_free_selected(lpp::Script::state L)
{
	bool free = lua_toboolean(L, -1) == 1;
	lua_pop(L, 1);

	lua_this->grid_system_->set_free_selected(*lua_this->selection_box_, free);
	return 0;
}

int LuaInterface::lua_pathfind(lpp::Script::state L)
{
	std::size_t end = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t start = (std::size_t)luaL_checkinteger(L, -2);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -3);
	lua_pop(L, 3);

	bool res = lua_this->grid_system_->perform_a_star(id, start, end);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_path_colour(lpp::Script::state L)
{
	lua_this->grid_system_->clear_path_colour();
	return 0;
}

int LuaInterface::lua_set_pathfinding_blueprint(lpp::Script::state L)
{
	std::string blueprint = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_pathfinding_blueprint(id, blueprint);
	return 0;
}

int LuaInterface::lua_create_graph(lpp::Script::state L)
{
	Ogre::Real start_y = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real start_x = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real dist = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t height = (std::size_t)luaL_checkinteger(L, -4);
	std::size_t width = (std::size_t)luaL_checkinteger(L, -5);
	lua_pop(L, 5);

	lua_this->grid_system_->create_graph(width, height, dist,
										 start_x, start_y);
	return 0;
}

int LuaInterface::lua_set_resident(lpp::Script::state L)
{
	std::size_t res_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_resident(ent_id, res_id);
	return 0;
}

int LuaInterface::lua_get_resident(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->grid_system_->get_resident(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_residences(lpp::Script::state L)
{
	std::string residences = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto nodes = lpp::Script::get_singleton().get_vector<std::size_t>(residences);
	lua_this->grid_system_->add_residences(id, nodes);
	return 0;
}

int LuaInterface::lua_add_residence(lpp::Script::state L)
{
	std::size_t res_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->add_residence(ent_id, res_id);
	return 0;
}

int LuaInterface::lua_set_radius(lpp::Script::state L)
{
	std::size_t radius = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_radius(id, radius);
	return 0;
}

int LuaInterface::lua_set_walk_through(lpp::Script::state L)
{
	bool on_off = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_walk_through(id, on_off);
	return 0;
}

int LuaInterface::lua_add_task(lpp::Script::state L)
{
	std::size_t task_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->add_task(ent_id, task_id);
	return 0;
}

int LuaInterface::lua_cancel_task(lpp::Script::state L)
{
	std::size_t task_id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->task_system_->cancel_task(task_id);
	return 0;
}

int LuaInterface::lua_create_task(lpp::Script::state L)
{
	TASK_TYPE task = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t target = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t id = lua_this->task_system_->create_task(target, task);
	lua_pushinteger(L, id);
	return 1;
}

int LuaInterface::lua_list_tasks_of(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	
	auto comp = lua_this->entity_system_->get_component<TaskHandlerComponent>(id);
	if(comp)
	{
		std::string report{};
		auto& task_queue = comp->task_queue;

		if(comp->curr_task != Component::NO_ENTITY)
		{ // Current task.
			auto curr = lua_this->entity_system_->get_component<TaskComponent>(comp->curr_task);
			if(curr)
			{
				report.append(std::to_string(comp->curr_task) + ": "
							  + lua_this->task_system_->get_task_name(curr->task_type)
							  + " (" + std::to_string(curr->source)
							  + " -> " + std::to_string(curr->target) + ").\n");
			}
		}

		// Other tasks.
		for(auto& task : task_queue)
		{
			report.append(std::to_string(task) + ": ");
			auto task_comp = lua_this->entity_system_->get_component<TaskComponent>(task);
			if(task_comp)
			{
				report.append(lua_this->task_system_->get_task_name(task_comp->task_type)
							  + " (" + std::to_string(task_comp->source)
							  + " -> " + std::to_string(task_comp->target) + ").\n");
			}
			else
				report.append(lua_this->task_system_->get_task_name(TASK_TYPE::NONE));
		}
		lua_this->console_.print_text(report, Console::ORANGE_TEXT);
	}
	else
		lua_this->console_.print_text("<FAIL> GIVEN ENTITY HAS NO TASKS.", Console::RED_TEXT);

	return 0;
}

int LuaInterface::lua_task_possible(lpp::Script::state L)
{
	std::size_t task_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = lua_this->task_system_->task_possible(ent_id, task_id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_task_queue(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->task_system_->clear_task_queue(id);
	return 0;
}

int LuaInterface::lua_set_task_source(lpp::Script::state L)
{
	std::size_t source = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->set_task_source(id, source);
	return 0;
}

int LuaInterface::lua_set_task_target(lpp::Script::state L)
{
	std::size_t target = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->set_task_target(id, target);
	return 0;
}

int LuaInterface::lua_set_task_type(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->set_task_type(id, type);
	return 0;
}

int LuaInterface::lua_add_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->add_possible_task(id, type);
	return 0;
}
int LuaInterface::lua_delete_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->delete_possible_task(id, type);
	return 0;
}

int LuaInterface::lua_set_range(lpp::Script::state L)
{
	Ogre::Real range = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->combat_system_->set_range(id, range);
	return 0;
}

int LuaInterface::lua_get_range(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_range(id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_dmg_range(lpp::Script::state L)
{
	std::size_t max = (std::size_t)luaL_checknumber(L, -1);
	std::size_t min = (std::size_t)luaL_checknumber(L, -2);
	std::size_t id = (std::size_t)luaL_checknumber(L, -3);
	lua_pop(L, 3);

	lua_this->combat_system_->set_dmg_range(id, min, max);
	return 0;
}

int LuaInterface::lua_get_dmg_range(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t min{}, max{};
	std::tie(min, max) = lua_this->combat_system_->get_dmg_range(id);
	lua_pushinteger(L, min);
	lua_pushinteger(L, max);
	return 2;
}

int LuaInterface::lua_set_cooldown(lpp::Script::state L)
{
	Ogre::Real cd = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->combat_system_->set_cooldown(id, cd);
	return 0;
}

int LuaInterface::lua_get_cooldown(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_cooldown(id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_atk_type(lpp::Script::state L)
{
	int atk_type = (int)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->combat_system_->set_atk_type(id, (ATTACK_TYPE)atk_type);
	return 0;
}

int LuaInterface::lua_get_atk_type(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_atk_type(id);
	lua_pushnumber(L, (int)res);
	return 1;
}

int LuaInterface::lua_set_homing_source(lpp::Script::state L)
{
	std::size_t source = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->combat_system_->set_homing_source(id, source);
	return 0;
}

int LuaInterface::lua_set_homing_target(lpp::Script::state L)
{
	std::size_t target = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->combat_system_->set_homing_target(id, target);
	return 0;
}

int LuaInterface::lua_set_homing_dmg(lpp::Script::state L)
{
	std::size_t dmg = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->combat_system_->set_homing_dmg(id, dmg);
	return 0;
}

int LuaInterface::lua_closest_enemy_in_sight(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_closest_entity(id, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly_in_sight(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_closest_entity(id, true, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_closest_entity(id, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->combat_system_->get_closest_entity(id, false, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_production_blueprint(lpp::Script::state L)
{
	std::string blueprint = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->production_system_->set_production_blueprint(id, blueprint);
	return 0;
}

int LuaInterface::lua_get_production_blueprint(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto& res = lua_this->production_system_->get_production_blueprint(id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_set_production_limit(lpp::Script::state L)
{
	std::size_t limit = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->production_system_->set_production_limit(id, limit);
	return 0;
}

int LuaInterface::lua_get_production_limit(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->production_system_->get_production_limit(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_production_cooldown(lpp::Script::state L)
{
	Ogre::Real cd = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->production_system_->set_production_cooldown(id, cd);
	return 0;
}

int LuaInterface::lua_get_production_cooldown(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->production_system_->get_production_cooldown(id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_production_progress(lpp::Script::state L)
{
	Ogre::Real prog = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->production_system_->set_production_progress(id, prog);
	return 0;
}

int LuaInterface::lua_get_production_progress(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	
	auto res = lua_this->production_system_->get_production_progress(id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_production_count(lpp::Script::state L)
{
	std::size_t prog = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->production_system_->set_production_count(id, prog);
	return 0;
}

int LuaInterface::lua_get_production_count(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->production_system_->get_production_count(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_producer(lpp::Script::state L)
{
	std::size_t producer = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->production_system_->set_producer(id, producer);
	return 0;
}

int LuaInterface::lua_get_producer(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->production_system_->get_producer(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_instant_production(lpp::Script::state L)
{
	for(auto& ent : lua_this->entity_system_->get_component_container<ProductionComponent>())
		ent.second.cooldown = 0;
	return 0;
}
#pragma endregion