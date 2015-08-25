#include "LuaInterface.hpp"
#include "Game.hpp"

/**
 * Static member initialization, will be set in the
 * init method.
 */
Game* LuaInterface::lua_this = nullptr;
EntitySystem* LuaInterface::ents = nullptr;

void LuaInterface::init(Game* game)
{
	lua_this = game;
	ents = game->entity_system_.get();

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

		// Graphics.
		{"set_mesh", LuaInterface::lua_set_mesh},
		{"set_material", LuaInterface::lua_set_material},
		{"set_visible", LuaInterface::lua_set_visible},
		{"set_manual_scaling", LuaInterface::lua_set_manual_scaling},
		{"set_scale", LuaInterface::lua_set_scale},
		{"get_mesh", LuaInterface::lua_get_mesh},
		{"get_material", LuaInterface::lua_get_material},
		{"is_visible", LuaInterface::lua_is_visible},
		{"get_manual_scaling", LuaInterface::lua_get_manual_scaling},
		{"get_scale", LuaInterface::lua_get_scale},
		{"rotate", LuaInterface::lua_rotate},
		{"collide", LuaInterface::lua_collide},
		{"look_at", LuaInterface::lua_look_at},

		// Entity manipulation.
		{"create_entity", LuaInterface::lua_create_entity},
		{"destroy_entity", LuaInterface::lua_destroy_entity},
		{"add_component", LuaInterface::lua_add_component},
		{"delete_component", LuaInterface::lua_delete_component},
		{"init_graphics_component", LuaInterface::lua_init_graphics_component},
		{"list_entity_tables", LuaInterface::lua_list_entity_tables},
		{"place_entity", LuaInterface::lua_place_entity},
		{"register_entity", LuaInterface::lua_register_entity},

		// Physics.
		{"set_position", LuaInterface::lua_set_position}
		{"get_position", LuaInterface::lua_get_position},
		{"set_solid", LuaInterface::lua_set_solid},
		{"is_solid", LuaInterface::lua_is_solid},
		{"set_half_height", LuaInterface::lua_set_half_height},
		{"get_half_height", LuaInterface::lua_get_half_height},
		{"get_distance", LuaInterface::lua_get_distance},
		{"get_angle", LuaInterface::lua_get_angle},
		{"get_angle_between", LuaInterface::lua_get_angle_between},

		// Movement.
		{"move_to", LuaInterface::lua_move_to},
		{"move", LuaInterface::lua_move},
		{"can_move_to", LuaInterface::lua_can_move_to},
		{"get_speed", LuaInterface::lua_get_speed_modifier},
		{"set_speed", LuaInterface::lua_set_speed_modifier},
		{"get_dir", LuaInterface::lua_get_dir},
		{"get_dir_back", LuaInterface::lua_get_dir_back},
		{"get_dir_left", LuaInterface::lua_get_dir_left},
		{"get_dir_right", LuaInterface::lua_get_dir_right},

		// Health system.
		{"set_health", LuaInterface::lua_set_health}
		{"get_health", LuaInterface::lua_get_health},
		{"add_health", LuaInterface::lua_add_health},
		{"sub_health", LuaInterface::lua_sub_health},
		{"heal", LuaInterface::lua_heal},
		{"buff", LuaInterface::lua_buff},
		{"debuff", LuaInterface::lua_debuff},
		{"get_defense", LuaInterface::lua_get_defense},
		{"add_defense", LuaInterface::lua_add_defense},
		{"sub_defense", LuaInterface::lua_sub_defense},
		{"set_regen", LuaInterface::lua_set_regen},
		{"get_regen", LuaInterface::lua_get_regen},
		{"set_alive", LuaInterface::lua_set_alive},
		{"is_alive", LuaInterface::lua_is_alive},
		{"ubercharge", LuaInterface::lua_ubercharge},
		{"set_regen_period", LuaInterface::lua_set_regen_period},
		{"get_regen_period", LuaInterface::lua_get_regen_period},

		// AI system.
		{"get_blueprint", LuaInterface::lua_get_blueprint},
		{"get_state", LuaInterface::lua_get_state},
		{"get_faction", LuaInterface::lua_get_faction},
		{"set_blueprint", LuaInterface::lua_set_blueprint},
		{"set_state", LuaInterface::lua_set_state},
		{"set_faction", LuaInterface::lua_set_faction},
		{"set_update_period", LuaInterface::lua_set_update_period},
		{"get_update_period", LuaInterface::lua_get_update_period},
		{"force_update", LuaInterface::lua_force_update},

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

	GraphicsHelper::set_mesh(*ents, id, mesh);
	return 0;
}

int LuaInterface::lua_set_material(lpp::Script::state L)
{
	std::string mat = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	GraphicsHelper::set_material(*ents, id, mat);
	return 0;
}

int LuaInterface::lua_set_visible(lpp::Script::state L)
{
	bool vis = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	GraphicsHelper::set_visible(*ents, id, vis);
	return 0;
}

int LuaInterface::lua_set_manual_scaling(lpp::Script::state L)
{
	bool on_off = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	GraphicsHelper::set_manual_scaling(*ents, id, on_off);
	return 0;
}

int LuaInterface::lua_set_scale(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	GraphicsHelper::set_scale(*ents, id, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_get_mesh(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto& res = GraphicsHelper::get_mesh(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_get_material(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto& res = GraphicsHelper::get_material(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_is_visible(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = GraphicsHelper::is_visible(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_manual_scaling(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = GraphicsHelper::get_manual_scaling(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_scale(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto& res = GraphicsHelper::get_scale(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_collide(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = GraphicsHelper::collide(*ents, id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_look_at(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	GraphicsHelper::look_at(*ents, id1, id2);
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

	GraphicsHelper::init_graphics_component(*ents, *lua_this->scene_mgr_, id);
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

	PhysicsHelper::move_to(*ents, id, Ogre::Vector3{x, y, z});
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

	GraphicsHelper::rotate(*ents, id, delta);
	return 0;
}

int LuaInterface::lua_is_solid(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = PhysicsHelper::is_solid(*ents, id);
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

int LuaInterface::lua_get_distance(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	Ogre::Real res = PhysicsHelper::get_distance(*ents, id1, id2);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_position(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	Ogre::Vector3 res = PhysicsHelper::get_position(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_speed_modifier(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	Ogre::Real res = MovementHelper::get_speed_modifier(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_speed_modifier(lpp::Script::state L)
{
	Ogre::Real speed = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	MovementHelper::set_speed_modifier(*ents, id, speed);
	return 0;
}

int LuaInterface::lua_dir_to(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto res = MovementHelper::dir_to(*ents, id1, id2);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = MovementHelper::get_dir(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_back(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = MovementHelper::get_dir_back(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_left(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = MovementHelper::get_dir_left(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_right(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = MovementHelper::get_dir_right(*ents, id);
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

	auto dir = MovementHelper::get_dir(*ents, id);
	auto res = PhysicsHelper::get_angle(dir, Ogre::Vector3{x, y, z});
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

	auto res = PhysicsHelper::get_angle(Ogre::Vector3{x1, y1, z1}, Ogre::Vector3{x2, y2, z2});
	lua_pushnumber(L, res);
	return 3;
}

int LuaInterface::lua_set_solid(lpp::Script::state L)
{
	bool solid = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	PhysicsHelper::set_solid(*ents, id, solid);
	return 0;
}

int LuaInterface::lua_set_half_height(lpp::Script::state L)
{
	Ogre::Real hh = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);
	
	PhysicsHelper::set_half_height(*ents, id, hh);
	return 0;
}

int LuaInterface::lua_get_half_height(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = PhysicsHelper::get_half_height(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_position(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	PhysicsHelper::set_position(*ents, id, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_set_health(lpp::Script::state L)
{
	std::size_t hp = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::set_health(*ents, id, hp);
	return 0;
}

int LuaInterface::lua_get_health(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = HealthHelper::get_health(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_health(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::add_health(*ents, id, val);
	return 0;
}

int LuaInterface::lua_sub_health(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::sub_health(*ents, id, val);
	return 0;
}

int LuaInterface::lua_heal(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 2);

	HealthHelper::heal(*ents, id);
	return 0;
}

int LuaInterface::lua_buff(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::buff(*ents, id, val);
	return 0;
}

int LuaInterface::lua_debuff(lpp::Script::state L)
{
	std::size_t hp = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);

	HealthHelper::debuff(*ents, id, hp);
	return 0;
}

int LuaInterface::lua_set_defense(lpp::Script::state L)
{
	std::size_t def = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);

	HealthHelper::set_defense(*ents, id, def);
	return 0;
}

int LuaInterface::lua_get_defense(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = HealthHelper::get_defense(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_defense(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::add_defense(*ents, id, val);
	return 0;
}

int LuaInterface::lua_sub_defense(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::sub_defense(*ents, id, val);
	return 0;
}

int LuaInterface::lua_set_regen(lpp::Script::state L)
{
	std::size_t regen = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::set_regen(*ents, id, regen);
	return 0;
}

int LuaInterface::lua_get_regen(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = HealthHelper::get_regen(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_alive(lpp::Script::state L)
{
	bool alive = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HealthHelper::set_alive(*ents, id, alive);
	return 0;
}

int LuaInterface::lua_is_alive(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = HealthHelper::is_alive(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_ubercharge(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	HealthHelper::ubercharge(*ents, id);
	return 0;
}

int LuaInterface::lua_set_regen_period(lpp::Script::state L)
{
	Ogre::Real t = (Ogre::Real)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_this->health_system_->set_regen_period(t);
	return 0;
}

int LuaInterface::lua_get_regen_period(lpp::Script::state L)
{
	auto res = lua_this->health_system_->get_regen_period();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_blueprint(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::string res = AIHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_get_state(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	int res = (int)AIHelper::get_state(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_faction(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	int res = (int)AIHelper::get_faction(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	AIHelper::set_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_set_state(lpp::Script::state L)
{
	ENTITY_STATE state = (ENTITY_STATE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	AIHelper::set_state(*ents, id, state);
	return 0;
}

int LuaInterface::lua_set_faction(lpp::Script::state L)
{
	FACTION faction = (FACTION)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	AIHelper::set_faction(*ents, id, faction);
	return 0;
}

int LuaInterface::lua_set_update_period(lpp::Script::state L)
{
	Ogre::Real t = (Ogre::Real)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_this->ai_system_->set_update_period(t);
	return 0;
}

int LuaInterface::lua_get_update_period(lpp::Script::state L)
{
	auto res = lua_this->ai_system_->get_update_period();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_force_update(lpp::Script::state L)
{
	lua_this->ai_system_->force_update();
	return 0;
}

int LuaInterface::lua_set_input_handler(lpp::Script::state L)
{
	std::string handler = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	InputHelper::set_input_handler(*ents, id, handler);
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

	PathfindingHelper::set_pathfinding_blueprint(*ents, id, blueprint);
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
	StructureHelper::add_residences(*ents, id, nodes);
	return 0;
}

int LuaInterface::lua_add_residence(lpp::Script::state L)
{
	std::size_t res_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	StructureHelper::add_residence(*ents, ent_id, res_id);
	return 0;
}

int LuaInterface::lua_set_radius(lpp::Script::state L)
{
	std::size_t radius = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	StructureHelper::set_radius(*ents, id, radius);
	return 0;
}

int LuaInterface::lua_set_walk_through(lpp::Script::state L)
{
	bool on_off = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	StructureHelper::set_walk_through(*ents, id, on_off);
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

	bool res = TaskHandlerHelper::task_possible(*ents, ent_id, task_id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_task_queue(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	TaskHandlerHelper::clear_task_queue(*ents, id);
	return 0;
}

int LuaInterface::lua_set_task_source(lpp::Script::state L)
{
	std::size_t source = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	TaskHelper::set_task_source(*ents, id, source);
	return 0;
}

int LuaInterface::lua_set_task_target(lpp::Script::state L)
{
	std::size_t target = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	TaskHelper::set_task_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_set_task_type(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	TaskHelper::set_task_type(*ents, id, type);
	return 0;
}

int LuaInterface::lua_add_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	TaskHandlerHelper::add_possible_task(*ents, id, type);
	return 0;
}
int LuaInterface::lua_delete_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	TaskHandlerHelper::delete_possible_task(*ents, id, type);
	return 0;
}

int LuaInterface::lua_set_range(lpp::Script::state L)
{
	Ogre::Real range = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	CombatHelper::set_range(*ents, id, range);
	return 0;
}

int LuaInterface::lua_get_range(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = CombatHelper::get_range(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_dmg_range(lpp::Script::state L)
{
	std::size_t max = (std::size_t)luaL_checknumber(L, -1);
	std::size_t min = (std::size_t)luaL_checknumber(L, -2);
	std::size_t id = (std::size_t)luaL_checknumber(L, -3);
	lua_pop(L, 3);

	CombatHelper::set_dmg_range(*ents, id, min, max);
	return 0;
}

int LuaInterface::lua_get_dmg_range(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t min{}, max{};
	std::tie(min, max) = CombatHelper::get_dmg_range(*ents, id);
	lua_pushinteger(L, min);
	lua_pushinteger(L, max);
	return 2;
}

int LuaInterface::lua_set_cooldown(lpp::Script::state L)
{
	Ogre::Real cd = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	CombatHelper::set_cooldown(*ents, id, cd);
	return 0;
}

int LuaInterface::lua_get_cooldown(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = CombatHelper::get_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_atk_type(lpp::Script::state L)
{
	int atk_type = (int)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	CombatHelper::set_atk_type(*ents, id, (ATTACK_TYPE)atk_type);
	return 0;
}

int LuaInterface::lua_get_atk_type(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = CombatHelper::get_atk_type(*ents, id);
	lua_pushnumber(L, (int)res);
	return 1;
}

int LuaInterface::lua_set_homing_source(lpp::Script::state L)
{
	std::size_t source = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HomingHelper::set_source(*ents, id, source);
	return 0;
}

int LuaInterface::lua_set_homing_target(lpp::Script::state L)
{
	std::size_t target = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HomingHelper::set_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_set_homing_dmg(lpp::Script::state L)
{
	std::size_t dmg = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	HomingHelper::set_dmg(*ents, id, dmg);
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

	ProductionHelper::set_production_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_get_production_blueprint(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto& res = ProductionHelper::get_production_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_set_production_limit(lpp::Script::state L)
{
	std::size_t limit = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	ProductionHelper::set_production_limit(*ents, id, limit);
	return 0;
}

int LuaInterface::lua_get_production_limit(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = ProductionHelper::get_production_limit(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_production_cooldown(lpp::Script::state L)
{
	Ogre::Real cd = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	ProductionHelper::set_production_cooldown(*ents, id, cd);
	return 0;
}

int LuaInterface::lua_get_production_cooldown(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = ProductionHelper::get_production_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_production_progress(lpp::Script::state L)
{
	Ogre::Real prog = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	ProductionHelper::set_production_progress(*ents, id, prog);
	return 0;
}

int LuaInterface::lua_get_production_progress(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	
	auto res = ProductionHelper::get_production_progress(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_production_count(lpp::Script::state L)
{
	std::size_t prog = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	ProductionHelper::set_production_count(*ents, id, prog);
	return 0;
}

int LuaInterface::lua_get_production_count(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = ProductionHelper::get_production_count(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_producer(lpp::Script::state L)
{
	std::size_t producer = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	ProductHelper::set_producer(*ents, id, producer);
	return 0;
}

int LuaInterface::lua_get_producer(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = ProductHelper::get_producer(*ents, id);
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