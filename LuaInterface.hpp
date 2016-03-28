#pragma once

#include "lppscript/LppScript.hpp"
#include "Typedefs.hpp"
class EntitySystem;
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
		static int lua_kill_selected(lpp::Script::state);
		static int lua_list_components_of(lpp::Script::state);
		static int lua_load(lpp::Script::state);
		static int lua_reload_all(lpp::Script::state);
		static int lua_save_game(lpp::Script::state);
		static int lua_load_game(lpp::Script::state);
		static int lua_get_cursor_position(lpp::Script::state);
		static int lua_can_place_when_game_paused(lpp::Script::state);
		static int lua_toggle_placing_when_game_paused(lpp::Script::state);
		static int lua_new_game(lpp::Script::state);
		static int lua_create_empty_level(lpp::Script::state);
		static int lua_reset_unlocks(lpp::Script::state);
		static int lua_get_random(lpp::Script::state);
		static int lua_set_key_bind(lpp::Script::state);
		static int lua_get_first_selected(lpp::Script::state);
		static int lua_get_enemies(lpp::Script::state);
		static int lua_get_friends(lpp::Script::state);
		static int lua_set_throne_id(lpp::Script::state);
		static int lua_get_throne_id(lpp::Script::state);
		
		// Command.
		static int lua_command_to_mine(lpp::Script::state);
		static int lua_command_to_attack(lpp::Script::state);
		static int lua_command_to_reposition(lpp::Script::state);
		static int lua_command_to_return_gold(lpp::Script::state);
		static int lua_command_to_fall_back(lpp::Script::state);

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
		static int lua_rotate_x(lpp::Script::state);
		static int lua_rotate_y(lpp::Script::state);
		static int lua_rotate_z(lpp::Script::state);
		static int lua_collide(lpp::Script::state);
		static int lua_set_query_flags(lpp::Script::state);
		static int lua_get_query_flags(lpp::Script::state);
		static int lua_apply_scale(lpp::Script::state);
		static int lua_set_graphics_update_period(lpp::Script::state);
		static int lua_get_graphics_update_period(lpp::Script::state);

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
		static int lua_kill_entity(lpp::Script::state);
		static int lua_has_component(lpp::Script::state);
		static int lua_entity_reset_state(lpp::Script::state);

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
		static int lua_set_2d_position(lpp::Script::state);
		static int lua_get_2d_position(lpp::Script::state);

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
		static int lua_set_original_speed(lpp::Script::state);
		static int lua_get_original_speed(lpp::Script::state);
		static int lua_reset_speed(lpp::Script::state);

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

		// AI, factions & updating.
		static int lua_get_blueprint(lpp::Script::state);
		static int lua_get_state(lpp::Script::state);
		static int lua_get_faction(lpp::Script::state);
		static int lua_set_blueprint(lpp::Script::state);
		static int lua_set_state(lpp::Script::state);
		static int lua_set_faction(lpp::Script::state);
		static int lua_set_update_period(lpp::Script::state);
		static int lua_get_update_period(lpp::Script::state);
		static int lua_force_update(lpp::Script::state);
		static int lua_get_faction_name(lpp::Script::state);

		// Input handling.
		static int lua_set_input_handler(lpp::Script::state);
		static int lua_get_input_handler(lpp::Script::state);
		static int lua_toggle_first_person(lpp::Script::state);

		// Grid system & pathfinding.
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
		static int lua_set_pathfinding_blueprint(lpp::Script::state);
		static int lua_get_pathfinding_blueprint(lpp::Script::state);
		static int lua_create_graph(lpp::Script::state);
		static int lua_set_resident(lpp::Script::state);
		static int lua_get_resident(lpp::Script::state);
		static int lua_add_residences(lpp::Script::state);
		static int lua_add_residence(lpp::Script::state);
		static int lua_set_radius(lpp::Script::state);
		static int lua_set_walk_through(lpp::Script::state);
		static int lua_is_walk_throuth(lpp::Script::state);
		static int lua_place_at_random_free_node(lpp::Script::state);
		static int lua_distribute_to_adjacent_free_nodes(lpp::Script::state);
		static int lua_get_random_free_node(lpp::Script::state);
		static int lua_set_portal_neighbour(lpp::Script::state);
		static int lua_get_next_pathfinding_node(lpp::Script::state);
		static int lua_get_target_pathfinding_node(lpp::Script::state);
		static int lua_pathfinding_skip_next_node(lpp::Script::state);

		// Tasks & task handling.
		static int lua_add_task(lpp::Script::state);
		static int lua_add_priority_task(lpp::Script::state);
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
		static int lua_set_task_complete(lpp::Script::state);
		static int lua_is_task_complete(lpp::Script::state);
		static int lua_task_clear(lpp::Script::state);

		// Combat & homing projectiles.
		static int lua_set_combat_target(lpp::Script::state);
		static int lua_get_combat_target(lpp::Script::state);
		static int lua_set_range(lpp::Script::state);
		static int lua_get_range(lpp::Script::state);
		static int lua_set_dmg_range(lpp::Script::state);
		static int lua_get_dmg_range(lpp::Script::state);
		static int lua_get_dmg(lpp::Script::state);
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
		static int lua_closest_enemy_in_sight_thats_not(lpp::Script::state);
		static int lua_closest_friendly_in_sight_thats_not(lpp::Script::state);
		static int lua_closest_enemy_thats_not(lpp::Script::state);
		static int lua_closest_friendly_thats_not(lpp::Script::state);
		static int lua_in_sight(lpp::Script::state);
		static int lua_run_away_from(lpp::Script::state);
		static int lua_set_max_run_away_attempts(lpp::Script::state);
		static int lua_get_max_run_away_attempts(lpp::Script::state);
		static int lua_apply_heal_to_entities_in_range(lpp::Script::state);
		static int lua_apply_damage_to_entities_in_range(lpp::Script::state);
		static int lua_apply_slow_to_entities_in_range(lpp::Script::state);
		static int lua_apply_freeze_to_entities_in_range(lpp::Script::state);
		static int lua_in_range(lpp::Script::state);
		static int lua_set_projectile_blueprint(lpp::Script::state);
		static int lua_get_projectile_blueprint(lpp::Script::state);
		static int lua_apply_slow_to(lpp::Script::state);
		static int lua_apply_freeze_to(lpp::Script::state);
		static int lua_enemy_in_range(lpp::Script::state);
		static int lua_closest_friendly_structure(lpp::Script::state);
		static int lua_closest_enemy_structure(lpp::Script::state);
		static int lua_closest_friendly_structure_in_sight(lpp::Script::state);
		static int lua_closest_enemy_structure_in_sight(lpp::Script::state);

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
		static int lua_double_production(lpp::Script::state);
		static int lua_increase_production(lpp::Script::state);

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
		static int lua_gold_full(lpp::Script::state);
		static int lua_is_gold_vault(lpp::Script::state);
		static int lua_get_closest_gold_vault(lpp::Script::state);
		static int lua_get_closest_gold_vault_in_sight(lpp::Script::state);
		static int lua_get_closest_free_gold_vault(lpp::Script::state);
		static int lua_get_closest_free_gold_vault_in_sight(lpp::Script::state);
		static int lua_exists_free_gold_vault(lpp::Script::state);

		// GUI.
		static int lua_set_gui_visible(lpp::Script::state);
		static int lua_is_gui_visible(lpp::Script::state);
		static int lua_set_window_visible(lpp::Script::state);
		static int lua_is_window_visible(lpp::Script::state);
		static int lua_show_save_dialog(lpp::Script::state);
		static int lua_show_load_dialog(lpp::Script::state);

		// Log.
		static int lua_clear_log(lpp::Script::state);
		static int lua_print_to_log(lpp::Script::state);
		static int lua_set_log_history(lpp::Script::state);
		static int lua_get_log_history(lpp::Script::state);
		static int lua_set_log_visible(lpp::Script::state);
		static int lua_is_log_visible(lpp::Script::state);

		// Tracker.
		static int lua_set_tracked_entity(lpp::Script::state);
		static int lua_get_tracked_entity(lpp::Script::state);
		static int lua_update_tracking(lpp::Script::state);
		static int lua_clear_entity_tracker(lpp::Script::state);
		static int lua_set_tracker_visible(lpp::Script::state);
		static int lua_is_tracker_visible(lpp::Script::state);

		// Console.
		static int lua_console_scroll_down(lpp::Script::state);
		static int lua_set_console_history(lpp::Script::state);
		static int lua_get_console_history(lpp::Script::state);
		static int lua_set_console_visible(lpp::Script::state);
		static int lua_is_console_visible(lpp::Script::state);
		static int lua_clear_console(lpp::Script::state);

		// Builder.
		static int lua_set_builder_visible(lpp::Script::state);
		static int lua_is_builder_visible(lpp::Script::state);
		static int lua_register_building(lpp::Script::state);

		// Research.
		static int lua_research_show(lpp::Script::state);
		static int lua_free_research(lpp::Script::state);
		static int lua_research_all(lpp::Script::state);
		static int lua_dummy_unlock(lpp::Script::state);
		static int lua_research_reset(lpp::Script::state);

		// Player.
		static int lua_add_player_gold(lpp::Script::state);
		static int lua_sub_player_gold(lpp::Script::state);
		static int lua_add_player_mana(lpp::Script::state);
		static int lua_sub_player_mana(lpp::Script::state);
		static int lua_add_player_max_units(lpp::Script::state);
		static int lua_sub_player_max_units(lpp::Script::state);
		static int lua_add_player_curr_units(lpp::Script::state);
		static int lua_sub_player_curr_units(lpp::Script::state);
		static int lua_get_player_gold(lpp::Script::state);
		static int lua_get_player_mana(lpp::Script::state);
		static int lua_player_reset(lpp::Script::state);
		static int lua_nulify_player_stats(lpp::Script::state);
		static int lua_add_player_max_mana(lpp::Script::state);
		static int lua_sub_player_max_mana(lpp::Script::state);
		static int lua_get_player_max_mana(lpp::Script::state);
		static int lua_add_player_mana_regen(lpp::Script::state);
		static int lua_sub_player_mana_regen(lpp::Script::state);
		static int lua_get_player_mana_regen(lpp::Script::state);

		// Price.
		static int lua_set_price(lpp::Script::state);
		static int lua_get_price(lpp::Script::state);

		// Spells.
		static int lua_register_spell(lpp::Script::state);
		static int lua_spellcaster_set_type(lpp::Script::state);
		static int lua_spellcaster_get_type(lpp::Script::state);
		static int lua_spellcaster_set_spell(lpp::Script::state);
		static int lua_spellcaster_get_spell(lpp::Script::state);
		static int lua_spellcaster_get_last_type(lpp::Script::state);
		static int lua_spellcaster_get_last_spell(lpp::Script::state);
		static int lua_spellcaster_set_last_spell_id(lpp::Script::state);
		static int lua_spellcaster_get_last_spell_id(lpp::Script::state);
		static int lua_spellcaster_is_casting(lpp::Script::state);
		static int lua_spellcaster_stop_casting(lpp::Script::state);

		// Alignment.
		static int lua_align_set_material(lpp::Script::state);
		static int lua_align_get_material(lpp::Script::state);
		static int lua_align_set_mesh(lpp::Script::state);
		static int lua_align_get_mesh(lpp::Script::state);
		static int lua_align_set_position_offset(lpp::Script::state);
		static int lua_align_get_position_offset(lpp::Script::state);
		static int lua_align_set_scale(lpp::Script::state);
		static int lua_align_get_scale(lpp::Script::state);

		// Mana crystal.
		static int lua_mana_crystal_set_cap(lpp::Script::state);
		static int lua_mana_crystal_get_cap(lpp::Script::state);
		static int lua_mana_crystal_set_regen(lpp::Script::state);
		static int lua_mana_crystal_get_regen(lpp::Script::state);

		// OnHit.
		static int lua_on_hit_set_blueprint(lpp::Script::state);
		static int lua_on_hit_get_blueprint(lpp::Script::state);
		static int lua_on_hit_call(lpp::Script::state);
		static int lua_on_hit_set_cooldown(lpp::Script::state);
		static int lua_on_hit_get_cooldown(lpp::Script::state);

		// Constructor.
		static int lua_constructor_set_blueprint(lpp::Script::state);
		static int lua_constructor_get_blueprint(lpp::Script::state);
		static int lua_constructor_call(lpp::Script::state);

		// Trigger.
		static int lua_trigger_set_blueprint(lpp::Script::state);
		static int lua_trigger_get_blueprint(lpp::Script::state);
		static int lua_trigger_set_linked_entity(lpp::Script::state);
		static int lua_trigger_get_linked_entity(lpp::Script::state);
		static int lua_trigger_set_cooldown(lpp::Script::state);
		static int lua_trigger_get_cooldown(lpp::Script::state);
		static int lua_trigger_trigger(lpp::Script::state);
		static int lua_trigger_set_check_period(lpp::Script::state);
		static int lua_trigger_get_check_period(lpp::Script::state);
		static int lua_trigger_can_be_triggered_by(lpp::Script::state);
		static int lua_trigger_reset_timer(lpp::Script::state);
		static int lua_trigger_set_radius(lpp::Script::state);
		static int lua_trigger_get_radius(lpp::Script::state);

		// Upgrade.
		static int lua_upgrade_set_blueprint(lpp::Script::state);
		static int lua_upgrade_get_blueprint(lpp::Script::state);
		static int lua_upgrade_set_experience(lpp::Script::state);
		static int lua_upgrade_get_experience(lpp::Script::state);
		static int lua_upgrade_add_experience(lpp::Script::state);
		static int lua_upgrade_set_exp_needed(lpp::Script::state);
		static int lua_upgrade_get_exp_needed(lpp::Script::state);
		static int lua_upgrade_set_level(lpp::Script::state);
		static int lua_upgrade_get_level(lpp::Script::state);
		static int lua_upgrade_set_level_cap(lpp::Script::state);
		static int lua_upgrade_get_level_cap(lpp::Script::state);
		static int lua_upgrade_can_level_up(lpp::Script::state);
		static int lua_upgrade_upgrade(lpp::Script::state);
		static int lua_upgrade_all_level_up(lpp::Script::state);

		// Notification.
		static int lua_notification_set_cooldown(lpp::Script::state);
		static int lua_notification_get_cooldown(lpp::Script::state);
		static int lua_notification_reset(lpp::Script::state);
		static int lua_notification_notify(lpp::Script::state);
		static int lua_notification_get_curr_time(lpp::Script::state);
		static int lua_notification_advance_curr_time(lpp::Script::state);

		// Explosion.
		static int lua_explosion_set_delta(lpp::Script::state);
		static int lua_explosion_get_delta(lpp::Script::state);
		static int lua_explosion_set_max_radius(lpp::Script::state);
		static int lua_explosion_get_max_radius(lpp::Script::state);
		static int lua_explosion_get_curr_radius(lpp::Script::state);
		static int lua_explosion_increase_curr_radius(lpp::Script::state);

		// Limited life span.
		static int lua_lls_set_max_time(lpp::Script::state);
		static int lua_lls_get_max_time(lpp::Script::state);
		static int lua_lls_get_curr_time(lpp::Script::state);
		static int lua_lls_advance_curr_time(lpp::Script::state);

		// Name.
		static int lua_name_set(lpp::Script::state);
		static int lua_name_get(lpp::Script::state);

		// Experience value.
		static int lua_exp_val_set(lpp::Script::state);
		static int lua_exp_val_get(lpp::Script::state);
		static int lua_exp_val_inc(lpp::Script::state);
		static int lua_exp_val_dec(lpp::Script::state);

		// Mana and spell system.
		static int lua_mana_set_regen_period(lpp::Script::state);
		static int lua_mana_get_regen_period(lpp::Script::state);

		// Wave system.
		static int lua_wave_next_wave(lpp::Script::state);
		static int lua_wave_advance_countdown(lpp::Script::state);
		static int lua_wave_entity_died(lpp::Script::state);
		static int lua_wave_start(lpp::Script::state);
		static int lua_wave_pause(lpp::Script::state);
		static int lua_wave_set_entity_total(lpp::Script::state);
		static int lua_wave_get_entity_total(lpp::Script::state);
		static int lua_wave_set_wave_count(lpp::Script::state);
		static int lua_wave_get_wave_count(lpp::Script::state);
		static int lua_wave_add_spawn_node(lpp::Script::state);
		static int lua_wave_clear_spawn_nodes(lpp::Script::state);
		static int lua_wave_set_spawn_cooldown(lpp::Script::state);
		static int lua_wave_get_spawn_cooldown(lpp::Script::state);
		static int lua_wave_add_entity_blueprint(lpp::Script::state);
		static int lua_wave_set_table(lpp::Script::state);
		static int lua_wave_get_table(lpp::Script::state);
		static int lua_wave_set_curr_wave_number(lpp::Script::state);
		static int lua_wave_get_curr_wave_number(lpp::Script::state);
		static int lua_wave_set_countdown(lpp::Script::state);
		static int lua_wave_get_countdown(lpp::Script::state);
		static int lua_wave_set_state(lpp::Script::state);
		static int lua_wave_get_state(lpp::Script::state);
		static int lua_wave_update_label_text(lpp::Script::state);
		static int lua_wave_set_spawn_timer(lpp::Script::state);
		static int lua_wave_get_spawn_timer(lpp::Script::state);
		static int lua_wave_set_wave_entities(lpp::Script::state);
		static int lua_wave_get_wave_entities(lpp::Script::state);
		static int lua_wave_set_entities_spawned(lpp::Script::state);
		static int lua_wave_get_entities_spawned(lpp::Script::state);
		static int lua_wave_clear_entity_blueprints(lpp::Script::state);
		static int lua_wave_list(lpp::Script::state);
		static int lua_wave_set_endless_mode(lpp::Script::state);
		static int lua_wave_get_endless_mode(lpp::Script::state);
		static int lua_wave_turn_endless_on(lpp::Script::state);

		// Message to the player.
		static int lua_msg_to_plr_show(lpp::Script::state);
		static int lua_msg_to_plr_show_ok(lpp::Script::state);
		static int lua_msg_to_plr_show_yes_no(lpp::Script::state);
		static int lua_msg_set_butt_label(lpp::Script::state);
		static int lua_msg_reset_butt_labels(lpp::Script::state);

		// Mana.
		static int lua_mana_add(lpp::Script::state);
		static int lua_mana_sub(lpp::Script::state);
		static int lua_mana_set(lpp::Script::state);
		static int lua_mana_get(lpp::Script::state);
		static int lua_mana_set_max(lpp::Script::state);
		static int lua_mana_get_max(lpp::Script::state);
		static int lua_mana_set_regen(lpp::Script::state);
		static int lua_mana_get_regen(lpp::Script::state);

		// Entity spells.
		static int lua_ent_spell_set_blueprint(lpp::Script::state);
		static int lua_ent_spell_get_blueprint(lpp::Script::state);
		static int lua_ent_spell_set_cooldown(lpp::Script::state);
		static int lua_ent_spell_get_cooldown(lpp::Script::state);
		static int lua_ent_spell_advance_curr_time(lpp::Script::state);
		static int lua_ent_spell_set_curr_time(lpp::Script::state);
		static int lua_ent_spell_get_curr_time(lpp::Script::state);
		static int lua_ent_spell_cast(lpp::Script::state);

		// Light.
		static int lua_light_set_visible(lpp::Script::state);
		static int lua_light_toggle_visible(lpp::Script::state);
		static int lua_light_is_visible(lpp::Script::state);
		static int lua_light_init(lpp::Script::state);

		// Command.
		static int lua_command_set(lpp::Script::state);
		static int lua_command_test(lpp::Script::state);

		// Counter.
		static int lua_counter_increment(lpp::Script::state);
		static int lua_counter_decrement(lpp::Script::state);
		static int lua_counter_set_curr_value(lpp::Script::state);
		static int lua_counter_get_curr_value(lpp::Script::state);
		static int lua_counter_set_max_value(lpp::Script::state);
		static int lua_counter_get_max_value(lpp::Script::state);
};