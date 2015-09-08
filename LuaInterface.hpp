#pragma once

#include <Ogre.h>
#include <cstdlib>

#include "lppscript/LppScript.hpp"
#include "Helpers.hpp"
#include "EntitySystem.hpp"

/**
 * Forward declaration required as LuaInterface is included in Game.hpp
 * so that the Game class can call the LuaInterface::init method.
 */
class Game;

/**
 * Class that creates an interface between engine (C++) and
 * logic (Lua) code.
 */
class LuaInterface
{
	public:
		/**
		 * This is a static class, so all constructors are deleted.
		 */
		LuaInterface() = delete;
		LuaInterface(const LuaInterface&) = delete;
		LuaInterface(LuaInterface&&) = delete;

		/**
		 * Brief: Sets the lua_this pointer and registers all C++ API functions
		 *        to Lua.
		 * Param: Pointer to the game object that provides the game data to Lua.
		 */
		static void init(Game*);
	private:
		/**
		 * Lua requires all functions registered in it to be static
		 * (because it doesn't know anything about C++).
		 */
		static Game* lua_this;
		static EntitySystem* ents;

		// Core functions.
		static int lua_get_avg_fps(lpp::Script::state);
		static int lua_get_fps(lpp::Script::state);
		static int lua_print(lpp::Script::state);
		static int lua_set_game_state(lpp::Script::state);
		static int lua_toggle_bounding_boxes(lpp::Script::state);
		static int lua_toggle_camera_free_mode(lpp::Script::state);
		static int lua_toggle_entity_creator(lpp::Script::state);
		static int lua_list_selected(lpp::Script::state);
		static int lua_destroy_selected(lpp::Script::state);
		static int lua_list_components_of(lpp::Script::state);
		static int lua_load(lpp::Script::state);
		static int lua_reload_all(lpp::Script::state);
		static int lua_save_game(lpp::Script::state);
		static int lua_load_game(lpp::Script::state);

		// Util.
		static int lua_get_enum_direction(lpp::Script::state);
		static int lua_get_node_in_dir(lpp::Script::state);

		// Graphics.
		static int lua_set_mesh(lpp::Script::state);
		static int lua_set_material(lpp::Script::state);
		static int lua_set_visible(lpp::Script::state);
		static int lua_set_manual_scaling(lpp::Script::state);
		static int lua_set_scale(lpp::Script::state);
		static int lua_get_mesh(lpp::Script::state);
		static int lua_get_material(lpp::Script::state);
		static int lua_is_visible(lpp::Script::state);
		static int lua_get_manual_scaling(lpp::Script::state);
		static int lua_get_scale(lpp::Script::state);
		static int lua_look_at(lpp::Script::state);
		static int lua_rotate(lpp::Script::state);
		static int lua_collide(lpp::Script::state);

		// Entity system.
		static int lua_create_entity(lpp::Script::state);
		static int lua_destroy_entity(lpp::Script::state);
		static int lua_add_component(lpp::Script::state);
		static int lua_delete_component(lpp::Script::state);
		static int lua_init_graphics_component(lpp::Script::state);
		static int lua_list_entity_tables(lpp::Script::state);
		static int lua_place_entity(lpp::Script::state);
		static int lua_register_entity(lpp::Script::state);
		static int lua_exists(lpp::Script::state);

		// Physics.
		static int lua_set_position(lpp::Script::state);
		static int lua_get_position(lpp::Script::state);
		static int lua_is_solid(lpp::Script::state);
		static int lua_set_solid(lpp::Script::state);
		static int lua_set_half_height(lpp::Script::state);
		static int lua_get_half_height(lpp::Script::state);
		static int lua_get_distance(lpp::Script::state);
		static int lua_get_angle(lpp::Script::state);
		static int lua_get_angle_between(lpp::Script::state);

		// Movement.
		static int lua_move_to(lpp::Script::state);
		static int lua_move(lpp::Script::state);
		static int lua_can_move_to(lpp::Script::state);
		static int lua_get_speed_modifier(lpp::Script::state);
		static int lua_set_speed_modifier(lpp::Script::state);
		static int lua_dir_to(lpp::Script::state);
		static int lua_get_dir(lpp::Script::state);
		static int lua_get_dir_back(lpp::Script::state);
		static int lua_get_dir_left(lpp::Script::state);
		static int lua_get_dir_right(lpp::Script::state);

		// Health & defense.
		static int lua_set_health(lpp::Script::state);
		static int lua_get_health(lpp::Script::state);
		static int lua_add_health(lpp::Script::state);
		static int lua_sub_health(lpp::Script::state);
		static int lua_heal(lpp::Script::state);
		static int lua_buff(lpp::Script::state);
		static int lua_debuff(lpp::Script::state);
		static int lua_set_defense(lpp::Script::state);
		static int lua_get_defense(lpp::Script::state);
		static int lua_add_defense(lpp::Script::state);
		static int lua_sub_defense(lpp::Script::state);
		static int lua_set_regen(lpp::Script::state);
		static int lua_get_regen(lpp::Script::state);
		static int lua_set_alive(lpp::Script::state);
		static int lua_is_alive(lpp::Script::state);
		static int lua_ubercharge(lpp::Script::state);
		static int lua_set_regen_period(lpp::Script::state);
		static int lua_get_regen_period(lpp::Script::state);

		// AI & updating.
		static int lua_get_blueprint(lpp::Script::state);
		static int lua_get_state(lpp::Script::state);
		static int lua_get_faction(lpp::Script::state);
		static int lua_set_blueprint(lpp::Script::state);
		static int lua_set_state(lpp::Script::state);
		static int lua_set_faction(lpp::Script::state);
		static int lua_set_update_period(lpp::Script::state);
		static int lua_get_update_period(lpp::Script::state);
		static int lua_force_update(lpp::Script::state);

		// Input handling.
		static int lua_set_input_handler(lpp::Script::state);
		static int lua_get_input_handler(lpp::Script::state);
		static int lua_toggle_first_person(lpp::Script::state);

		// Grid system.
		static int lua_add_node(lpp::Script::state);
		static int lua_get_node(lpp::Script::state);
		static int lua_get_node_from_position(lpp::Script::state);
		static int lua_create_grid_graphics(lpp::Script::state);
		static int lua_delete_grid_graphics(lpp::Script::state);
		static int lua_toggle_grid_visible(lpp::Script::state);
		static int lua_is_free(lpp::Script::state);
		static int lua_set_free(lpp::Script::state);
		static int lua_set_free_selected(lpp::Script::state);
		static int lua_pathfind(lpp::Script::state);
		static int lua_pop_first_path_node(lpp::Script::state);
		static int lua_pop_last_path_node(lpp::Script::state);
		static int lua_path_queue_empty(lpp::Script::state);
		static int lua_clear_path(lpp::Script::state);
		static int lua_clear_path_colour(lpp::Script::state);
		static int lua_set_pathfinding_blueprint(lpp::Script::state);
		static int lua_create_graph(lpp::Script::state);
		static int lua_set_resident(lpp::Script::state);
		static int lua_get_resident(lpp::Script::state);
		static int lua_add_residences(lpp::Script::state);
		static int lua_add_residence(lpp::Script::state);
		static int lua_set_radius(lpp::Script::state);
		static int lua_set_walk_through(lpp::Script::state);
		static int lua_is_walk_throuth(lpp::Script::state);

		// Tasks & task handling.
		static int lua_add_task(lpp::Script::state);
		static int lua_cancel_task(lpp::Script::state);
		static int lua_create_task(lpp::Script::state);
		static int lua_list_tasks_of(lpp::Script::state);
		static int lua_task_possible(lpp::Script::state);
		static int lua_task_type_possibe(lpp::Script::state);
		static int lua_clear_task_queue(lpp::Script::state);
		static int lua_set_task_source(lpp::Script::state);
		static int lua_get_task_source(lpp::Script::state);
		static int lua_set_task_target(lpp::Script::state);
		static int lua_get_task_target(lpp::Script::state);
		static int lua_set_task_type(lpp::Script::state);
		static int lua_get_task_type(lpp::Script::state);
		static int lua_add_possible_task(lpp::Script::state);
		static int lua_delete_possible_task(lpp::Script::state);
		static int lua_set_task_handling_blueprint(lpp::Script::state);
		static int lua_get_task_handling_blueprint(lpp::Script::state);

		// Combat & homing projectiles.
		static int lua_set_combat_target(lpp::Script::state);
		static int lua_get_combat_target(lpp::Script::state);
		static int lua_set_range(lpp::Script::state);
		static int lua_get_range(lpp::Script::state);
		static int lua_set_dmg_range(lpp::Script::state);
		static int lua_get_dmg_range(lpp::Script::state);
		static int lua_set_cooldown(lpp::Script::state);
		static int lua_get_cooldown(lpp::Script::state);
		static int lua_set_atk_type(lpp::Script::state);
		static int lua_get_atk_type(lpp::Script::state);
		static int lua_set_homing_source(lpp::Script::state);
		static int lua_get_homing_source(lpp::Script::state);
		static int lua_set_homing_target(lpp::Script::state);
		static int lua_get_homing_target(lpp::Script::state);
		static int lua_set_homing_dmg(lpp::Script::state);
		static int lua_get_homing_dmg(lpp::Script::state);
		static int lua_closest_enemy_in_sight(lpp::Script::state);
		static int lua_closest_friendly_in_sight(lpp::Script::state);
		static int lua_closest_enemy(lpp::Script::state);
		static int lua_closest_friendly(lpp::Script::state);
		static int lua_in_sight(lpp::Script::state);

		// Production & products.
		static int lua_set_production_blueprint(lpp::Script::state);
		static int lua_get_production_blueprint(lpp::Script::state);
		static int lua_set_production_limit(lpp::Script::state);
		static int lua_get_production_limit(lpp::Script::state);
		static int lua_set_production_cooldown(lpp::Script::state);
		static int lua_get_production_cooldown(lpp::Script::state);
		static int lua_set_production_progress(lpp::Script::state);
		static int lua_get_production_progress(lpp::Script::state);
		static int lua_set_production_count(lpp::Script::state);
		static int lua_get_production_count(lpp::Script::state);
		static int lua_set_producer(lpp::Script::state);
		static int lua_get_producer(lpp::Script::state);
		static int lua_instant_production(lpp::Script::state);
		static int lua_set_production_multiplier(lpp::Script::state);
		static int lua_get_production_multiplier(lpp::Script::state);

		// Timers and time system.
		static int lua_get_curr_time(lpp::Script::state);
		static int lua_advance_curr_time(lpp::Script::state);
		static int lua_max_curr_time(lpp::Script::state);
		static int lua_set_time_limit(lpp::Script::state);
		static int lua_get_time_limit(lpp::Script::state);
		static int lua_set_timer_target(lpp::Script::state);
		static int lua_get_timer_target(lpp::Script::state);
		static int lua_set_timer_type(lpp::Script::state);
		static int lua_get_timer_type(lpp::Script::state);
		static int lua_advance_all_timers(lpp::Script::state);
		static int lua_advance_all_timers_of_type(lpp::Script::state);
		static int lua_set_timer_multiplier(lpp::Script::state);
		static int lua_get_timer_multiplier(lpp::Script::state);

		// Events & event handling.
		static int lua_set_event_type(lpp::Script::state);
		static int lua_get_event_type(lpp::Script::state);
		static int lua_set_event_target(lpp::Script::state);
		static int lua_get_event_target(lpp::Script::state);
		static int lua_set_event_radius(lpp::Script::state);
		static int lua_get_event_radius(lpp::Script::state);
		static int lua_set_event_active(lpp::Script::state);
		static int lua_is_event_active(lpp::Script::state);
		static int lua_set_handler_of_event(lpp::Script::state);
		static int lua_get_handler_of_event(lpp::Script::state);
		static int lua_set_event_handler(lpp::Script::state);
		static int lua_get_event_handler(lpp::Script::state);
		static int lua_can_handle_event(lpp::Script::state);
		static int lua_add_possible_event(lpp::Script::state);
		static int lua_delete_possible_event(lpp::Script::state);
		static int lua_set_event_update_period(lpp::Script::state);
		static int lua_get_event_update_period(lpp::Script::state);
		static int lua_set_event_update_multiplier(lpp::Script::state);
		static int lua_get_event_update_multiplier(lpp::Script::state);

		// Destructor.
		static int lua_set_destructor_blueprint(lpp::Script::state);
		static int lua_get_destructor_blueprint(lpp::Script::state);

		// Gold.
		static int lua_set_curr_gold(lpp::Script::state);
		static int lua_get_curr_gold(lpp::Script::state);
		static int lua_set_max_gold(lpp::Script::state);
		static int lua_get_max_gold(lpp::Script::state);
		static int lua_add_gold(lpp::Script::state);
		static int lua_sub_gold(lpp::Script::state);
		static int lua_transfer_all_gold(lpp::Script::state);
		static int lua_get_closest_gold_deposit(lpp::Script::state);
		static int lua_get_closest_gold_deposit_in_sight(lpp::Script::state);
};