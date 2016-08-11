#include <tools/Player.hpp>
#include <tools/Pathfinding.hpp>
#include <tools/PathfindingAlgorithms.hpp>
#include <tools/GameSerializer.hpp>
#include <tools/Grid.hpp>
#include <tools/Spellcaster.hpp>
#include <tools/SelectionBox.hpp>
#include <tools/EntityPlacer.hpp>
#include <helpers/Helpers.hpp>
#include <lppscript/LppScript.hpp>
#include <systems/EntitySystem.hpp>
#include <systems/CombatSystem.hpp>
#include <systems/WaveSystem.hpp>
#include <systems/GraphicsSystem.hpp>
#include <systems/MovementSystem.hpp>
#include <systems/AISystem.hpp>
#include <systems/TaskSystem.hpp>
#include <systems/TriggerSystem.hpp>
#include <systems/InputSystem.hpp>
#include <systems/HealthSystem.hpp>
#include <systems/ProductionSystem.hpp>
#include <systems/EventSystem.hpp>
#include <systems/TimeSystem.hpp>
#include <systems/ManaSpellSystem.hpp>
#include <systems/GridSystem.hpp>
#include <gui/GUI.hpp>
#include <gui/EntityCreator.hpp>
#include "Game.hpp"
#include "LuaInterface.hpp"

#define GET_REAL(state, position) ((tdt::real)luaL_checknumber(state, position))
#define GET_UINT(state, position) ((tdt::uint)luaL_checkinteger(state, position))
#define GET_SINT(state, position) ((int)luaL_checkinteger(state, position))
#define GET_BOOL(state, position) (lua_toboolean(state, position) == 1)
#define GET_STR(state, position)  (luaL_checkstring(state, position))

/**
 * Static member initialization, will be set in the
 * init method.
 */
Game* LuaInterface::lua_this{};
EntitySystem* LuaInterface::ents{};

void LuaInterface::init(Game* game)
{
	lua_this = game;
	ents = game->entity_system_.get();

	// Register all functions that will be used in Lua.
	lpp::Script& script = lpp::Script::instance();
	lpp::Script::regs game_funcs[] = {
		// Core functions.
		{"get_avg_fps", LuaInterface::lua_get_avg_fps},
		{"get_fps", LuaInterface::lua_get_fps},
		{"print_", LuaInterface::lua_print}, // Underscore added because it is wrapped in lua as game.print function.
		{"set_game_state", LuaInterface::lua_set_game_state},
		{"toggle_bounding_boxes", LuaInterface::lua_toggle_bounding_boxes},
		{"toggle_camera_free_mode", LuaInterface::lua_toggle_camera_free_mode},
		{"toggle_entity_creator", LuaInterface::lua_toggle_entity_creator},
		{"list_selected", LuaInterface::lua_list_selected},
		{"destroy_selected", LuaInterface::lua_destroy_selected},
		{"kill_selected", LuaInterface::lua_kill_selected},
		{"list_components_of", LuaInterface::lua_list_components_of},
		{"load", LuaInterface::lua_load},
		{"reload_all", LuaInterface::lua_reload_all},
		{"save_game", LuaInterface::lua_save_game},
		{"load_game", LuaInterface::lua_load_game},
		{"get_cursor_position", LuaInterface::lua_get_cursor_position},
		{"get_selected_entity", LuaInterface::lua_get_tracked_entity}, // Alias.
		{"get_enum_direction", LuaInterface::lua_get_enum_direction},
		{"get_node_in_dir", LuaInterface::lua_get_node_in_dir},
		{"can_place_when_game_paused", LuaInterface::lua_can_place_when_game_paused},
		{"toggle_placing_when_game_paused", LuaInterface::lua_toggle_placing_when_game_paused},
		{"new_game", LuaInterface::lua_new_game},
		{"create_empty_level", LuaInterface::lua_create_empty_level},
		{"reset_unlocks", LuaInterface::lua_reset_unlocks},
		{"get_random", LuaInterface::lua_get_random},
		{"set_key_bind", LuaInterface::lua_set_key_bind},
		{"get_first_selected", LuaInterface::lua_get_first_selected},
		{"get_enemies", LuaInterface::lua_get_enemies},
		{"get_friends", LuaInterface::lua_get_friends},
		{"set_throne_id", LuaInterface::lua_set_throne_id},
		{"get_throne_id", LuaInterface::lua_get_throne_id},
		{"register_scenario", LuaInterface::lua_register_scenario},
		{nullptr, nullptr}
	};

	lpp::Script::regs command_funcs[] = {
		// Commands.
		{"mine", LuaInterface::lua_command_to_mine},
		{"attack", LuaInterface::lua_command_to_attack},
		{"reposition", LuaInterface::lua_command_to_reposition},
		{"return_gold", LuaInterface::lua_command_to_return_gold},
		{"fall_back", LuaInterface::lua_command_to_fall_back},
		{"set", LuaInterface::lua_command_set},
		{"test", LuaInterface::lua_command_test},
		{nullptr, nullptr}
	};

	lpp::Script::regs graph_funcs[] = {
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
		{"rotate_x", LuaInterface::lua_rotate_x},
		{"rotate_y", LuaInterface::lua_rotate_y},
		{"rotate_z", LuaInterface::lua_rotate_z},
		{"collide", LuaInterface::lua_collide},
		{"look_at", LuaInterface::lua_look_at},
		{"set_query_flags", LuaInterface::lua_set_query_flags},
		{"get_query_flags", LuaInterface::lua_get_query_flags},
		{"apply_scale", LuaInterface::lua_apply_scale},
		{"set_update_period", LuaInterface::lua_set_graphics_update_period},
		{"get_update_period", LuaInterface::lua_get_graphics_update_period},
		{nullptr, nullptr}
	};

	lpp::Script::regs entity_funcs[] = {
		// Entity manipulation.
		{"create", LuaInterface::lua_create_entity},
		{"destroy", LuaInterface::lua_destroy_entity},
		{"add_component", LuaInterface::lua_add_component},
		{"delete_component", LuaInterface::lua_delete_component},
		{"init_graphics_component", LuaInterface::lua_init_graphics_component},
		{"list_tables", LuaInterface::lua_list_entity_tables},
		{"place", LuaInterface::lua_place_entity},
		{"register", LuaInterface::lua_register_entity},
		{"exists", LuaInterface::lua_exists},
		{"kill", LuaInterface::lua_kill_entity},
		{"has_component", LuaInterface::lua_has_component},
		{"reset", LuaInterface::lua_entity_reset_state},
		{nullptr, nullptr}
	};
	
	lpp::Script::regs phys_funcs[] = {
		// Physics.
		{"set_position", LuaInterface::lua_set_position},
		{"get_position", LuaInterface::lua_get_position},
		{"set_solid", LuaInterface::lua_set_solid},
		{"is_solid", LuaInterface::lua_is_solid},
		{"set_half_height", LuaInterface::lua_set_half_height},
		{"get_half_height", LuaInterface::lua_get_half_height},
		{"get_distance", LuaInterface::lua_get_distance},
		{"get_angle", LuaInterface::lua_get_angle},
		{"get_angle_between", LuaInterface::lua_get_angle_between},
		{"set_2d_position", LuaInterface::lua_set_2d_position},
		{"get_2d_position", LuaInterface::lua_get_2d_position},
		{nullptr, nullptr}
	};

	lpp::Script::regs mov_funcs[] = {
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
		{"set_original_speed", LuaInterface::lua_set_original_speed},
		{"get_original_speed", LuaInterface::lua_get_original_speed},
		{"reset_speed", LuaInterface::lua_reset_speed},
		{nullptr, nullptr}
	};

	lpp::Script::regs hp_funcs[] = {
		// Health & defense.
		{"set", LuaInterface::lua_set_health},
		{"get", LuaInterface::lua_get_health},
		{"add", LuaInterface::lua_add_health},
		{"sub", LuaInterface::lua_sub_health},
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
		{nullptr, nullptr}
	};

	lpp::Script::regs ai_funcs[] = {
		// AI & update.
		{"get_blueprint", LuaInterface::lua_get_blueprint},
		{"get_state", LuaInterface::lua_get_state},
		{"get_faction", LuaInterface::lua_get_faction},
		{"set_blueprint", LuaInterface::lua_set_blueprint},
		{"set_state", LuaInterface::lua_set_state},
		{"set_faction", LuaInterface::lua_set_faction},
		{"set_update_period", LuaInterface::lua_set_update_period},
		{"get_update_period", LuaInterface::lua_get_update_period},
		{"force_update", LuaInterface::lua_force_update},
		{"get_faction_name", LuaInterface::lua_get_faction_name},
		{nullptr, nullptr}
	};

	lpp::Script::regs input_funcs[] = {
		// Input handling.
		{"set_handler", LuaInterface::lua_set_input_handler},
		{"get_handler", LuaInterface::lua_get_input_handler},
		{"toggle_first_person", LuaInterface::lua_toggle_first_person},
		{nullptr, nullptr}
	};

	lpp::Script::regs grid_funcs[] = {
		// Grid system.
		{"add_node", LuaInterface::lua_add_node},
		{"get_node", LuaInterface::lua_get_node},
		{"get_node_from_position", LuaInterface::lua_get_node_from_position},
		{"create_graphics", LuaInterface::lua_create_grid_graphics},
		{"delete_graphics", LuaInterface::lua_delete_grid_graphics},
		{"toggle_visible", LuaInterface::lua_toggle_grid_visible},
		{"is_free", LuaInterface::lua_is_free},
		{"set_free", LuaInterface::lua_set_free},
		{"set_free_selected", LuaInterface::lua_set_free_selected},
		{"create", LuaInterface::lua_create_graph},
		{"set_resident", LuaInterface::lua_set_resident},
		{"get_resident", LuaInterface::lua_get_resident},
		{"add_residences", LuaInterface::lua_add_residences},
		{"add_residence", LuaInterface::lua_add_residence},
		{"set_radius", LuaInterface::lua_set_radius},
		{"set_walk_through", LuaInterface::lua_set_walk_through},
		{"is_walk_through", LuaInterface::lua_is_walk_throuth},
		{"place_at_random_free_node", LuaInterface::lua_place_at_random_free_node},
		{"distribute_to_adjacent_free_nodes", LuaInterface::lua_distribute_to_adjacent_free_nodes},
		{"get_random_free_node", LuaInterface::lua_get_random_free_node},
		{"set_portal_neighbour", LuaInterface::lua_set_portal_neighbour},
		{nullptr, nullptr}
	};

	lpp::Script::regs path_funcs[] = {
		// Pathfinding.
		{"pathfind", LuaInterface::lua_pathfind},
		{"pop_first", LuaInterface::lua_pop_first_path_node},
		{"pop_last", LuaInterface::lua_pop_last_path_node},
		{"empty", LuaInterface::lua_path_queue_empty},
		{"set_blueprint", LuaInterface::lua_set_pathfinding_blueprint},
		{"get_blueprint", LuaInterface::lua_get_pathfinding_blueprint},
		{"clear", LuaInterface::lua_clear_path},
		{"next_node", LuaInterface::lua_get_next_pathfinding_node},
		{"target", LuaInterface::lua_get_target_pathfinding_node},
		{"skip", LuaInterface::lua_pathfinding_skip_next_node},
		{"after_next", LuaInterface::lua_pathfinding_after_next_node},
		{nullptr, nullptr}
	};

	lpp::Script::regs task_funcs[] = {
		// Tasks & task handling.
		{"add", LuaInterface::lua_add_task},
		{"add_priority", LuaInterface::lua_add_priority_task},
		{"cancel", LuaInterface::lua_cancel_task},
		{"create", LuaInterface::lua_create_task},
		{"list", LuaInterface::lua_list_tasks_of},
		{"possible", LuaInterface::lua_task_possible},
		{"type_possible", LuaInterface::lua_task_type_possibe},
		{"clear_queue", LuaInterface::lua_clear_task_queue},
		{"set_source", LuaInterface::lua_set_task_source},
		{"get_source", LuaInterface::lua_get_task_source},
		{"set_target", LuaInterface::lua_set_task_target},
		{"get_target", LuaInterface::lua_get_task_target},
		{"set_type", LuaInterface::lua_set_task_type},
		{"get_type", LuaInterface::lua_get_task_type},
		{"add_possible", LuaInterface::lua_add_possible_task},
		{"delete_possible", LuaInterface::lua_delete_possible_task},
		{"set_blueprint", LuaInterface::lua_set_task_handling_blueprint},
		{"get_blueprint", LuaInterface::lua_get_task_handling_blueprint},
		{"set_complete", LuaInterface::lua_set_task_complete},
		{"is_complete", LuaInterface::lua_is_task_complete},
		{"clear", LuaInterface::lua_task_clear},
		{nullptr, nullptr}
	};

	lpp::Script::regs combat_funcs[] = {
		// Combat & homing projectiles.
		{"set_target", LuaInterface::lua_set_combat_target},
		{"get_target", LuaInterface::lua_get_combat_target},
		{"set_range", LuaInterface::lua_set_range},
		{"get_range", LuaInterface::lua_get_range},
		{"set_dmg_range", LuaInterface::lua_set_dmg_range},
		{"get_dmg_range", LuaInterface::lua_get_dmg_range},
		{"get_dmg", LuaInterface::lua_get_dmg},
		{"set_cooldown", LuaInterface::lua_set_cooldown},
		{"get_cooldown", LuaInterface::lua_get_cooldown},
		{"set_atk_type", LuaInterface::lua_set_atk_type},
		{"get_atk_type", LuaInterface::lua_get_atk_type},
		{"closest_enemy_in_sight", LuaInterface::lua_closest_enemy_in_sight},
		{"closest_friendly_in_sight", LuaInterface::lua_closest_friendly_in_sight},
		{"closest_enemy", LuaInterface::lua_closest_enemy},
		{"closest_friendly", LuaInterface::lua_closest_friendly},
		{"closest_enemy_in_sight_thats_not", LuaInterface::lua_closest_enemy_in_sight_thats_not},
		{"closest_friendly_in_sight_thats_not", LuaInterface::lua_closest_friendly_in_sight_thats_not},
		{"closest_enemy_thats_not", LuaInterface::lua_closest_enemy_thats_not},
		{"closest_friendly_thats_not", LuaInterface::lua_closest_friendly_thats_not},
		{"in_sight", LuaInterface::lua_in_sight},
		{"run_away_from", LuaInterface::lua_run_away_from},
		{"set_max_run_away_attempts", LuaInterface::lua_set_max_run_away_attempts},
		{"get_max_run_away_attempts", LuaInterface::lua_get_max_run_away_attempts},
		{"apply_heal_to_entities_in_range", LuaInterface::lua_apply_heal_to_entities_in_range},
		{"apply_damage_to_entities_in_range", LuaInterface::lua_apply_damage_to_entities_in_range},
		{"apply_slow_to_entities_in_range", LuaInterface::lua_apply_slow_to_entities_in_range},
		{"apply_freeze_to_entities_in_range", LuaInterface::lua_apply_freeze_to_entities_in_range},
		{"in_range", LuaInterface::lua_in_range},
		{"set_projectile_blueprint", LuaInterface::lua_set_projectile_blueprint},
		{"get_projectile_blueprint", LuaInterface::lua_get_projectile_blueprint},
		{"apply_slow_to", LuaInterface::lua_apply_slow_to},
		{"apply_freeze_to", LuaInterface::lua_apply_freeze_to},
		{"enemy_in_range", LuaInterface::lua_enemy_in_range},
		{"closest_friendly_structure", LuaInterface::lua_closest_friendly_structure},
		{"closest_enemy_structure", LuaInterface::lua_closest_enemy_structure},
		{"closest_friendly_structure_in_sight", LuaInterface::lua_closest_friendly_structure_in_sight},
		{"closest_enemy_structure_in_sight", LuaInterface::lua_closest_enemy_structure_in_sight},
		{nullptr, nullptr}
	};

	lpp::Script::regs proj_funcs[] = {
		// Homing projectile.
		{"set_source", LuaInterface::lua_set_homing_source},
		{"get_source", LuaInterface::lua_get_homing_source},
		{"set_target", LuaInterface::lua_set_homing_target},
		{"get_target", LuaInterface::lua_get_homing_target},
		{"set_dmg", LuaInterface::lua_set_homing_dmg},
		{"get_dmg", LuaInterface::lua_get_homing_dmg},
		{nullptr, nullptr}
	};

	lpp::Script::regs prod_funcs[] = {
		// Production & products.
		{"set_blueprint", LuaInterface::lua_set_production_blueprint},
		{"get_blueprint", LuaInterface::lua_get_production_blueprint},
		{"set_limit", LuaInterface::lua_set_production_limit},
		{"get_limit", LuaInterface::lua_get_production_limit},
		{"set_cooldown", LuaInterface::lua_set_production_cooldown},
		{"get_cooldown", LuaInterface::lua_get_production_cooldown},
		{"set_progress", LuaInterface::lua_set_production_progress},
		{"get_progress", LuaInterface::lua_get_production_progress},
		{"set_count", LuaInterface::lua_set_production_count},
		{"get_count", LuaInterface::lua_get_production_count},
		{"set_producer", LuaInterface::lua_set_producer},
		{"get_producer", LuaInterface::lua_get_producer},
		{"instant_production", LuaInterface::lua_instant_production},
		{"set_multiplier", LuaInterface::lua_set_production_multiplier},
		{"get_multiplier", LuaInterface::lua_get_production_multiplier},
		{"double_production", LuaInterface::lua_double_production},
		{"increase_production", LuaInterface::lua_increase_production},
		{nullptr, nullptr}
	};

	lpp::Script::regs time_funcs[] = {
		// Time & time system.
		{"get_current", LuaInterface::lua_get_curr_time},
		{"advance_current", LuaInterface::lua_advance_curr_time},
		{"max_current", LuaInterface::lua_max_curr_time},
		{"set_limit", LuaInterface::lua_set_time_limit},
		{"get_limit", LuaInterface::lua_get_time_limit},
		{"set_target", LuaInterface::lua_set_timer_target},
		{"get_target", LuaInterface::lua_get_timer_target},
		{"set_type", LuaInterface::lua_set_timer_type},
		{"get_type", LuaInterface::lua_get_timer_type},
		{"advance_all", LuaInterface::lua_advance_all_timers},
		{"advance_all_of_type", LuaInterface::lua_advance_all_timers_of_type},
		{"set_multiplier", LuaInterface::lua_set_timer_multiplier},
		{"get_multiplier", LuaInterface::lua_get_timer_multiplier},
		{nullptr, nullptr}
	};
	
	lpp::Script::regs event_funcs[] = {
		// Events & event handling.
		{"set_type", LuaInterface::lua_set_event_type},
		{"get_type", LuaInterface::lua_get_event_type},
		{"set_target", LuaInterface::lua_set_event_target},
		{"get_target", LuaInterface::lua_get_event_target},
		{"set_radius", LuaInterface::lua_set_event_radius},
		{"get_radius", LuaInterface::lua_get_event_radius},
		{"set_active", LuaInterface::lua_set_event_active},
		{"is_active", LuaInterface::lua_is_event_active},
		{"set_handler", LuaInterface::lua_set_handler_of_event},
		{"get_handler", LuaInterface::lua_get_handler_of_event},
		{"set_update_period", LuaInterface::lua_set_event_update_period},
		{"get_update_period", LuaInterface::lua_get_event_update_period},
		{"set_multiplier", LuaInterface::lua_set_event_update_multiplier},
		{"get_multiplier", LuaInterface::lua_get_event_update_multiplier},
		{nullptr, nullptr}
	};

	lpp::Script::regs handling_funcs[] = {
		// Event handling.
		{"set_handler", LuaInterface::lua_set_event_handler},
		{"get_handler", LuaInterface::lua_get_event_handler},
		{"can_handle", LuaInterface::lua_can_handle_event},
		{"add_possible", LuaInterface::lua_add_possible_event},
		{"delete_possible", LuaInterface::lua_delete_possible_event},
		{nullptr, nullptr}
	};
	
	lpp::Script::regs destr_funcs[] = {
		// Destructor.
		{"set_blueprint", LuaInterface::lua_set_destructor_blueprint},
		{"get_blueprint", LuaInterface::lua_get_destructor_blueprint},
		{nullptr, nullptr}
	};

	lpp::Script::regs gold_funcs[] = {
		// Gold.
		{"set_current", LuaInterface::lua_set_curr_gold},
		{"get_current", LuaInterface::lua_get_curr_gold},
		{"set_max", LuaInterface::lua_set_max_gold},
		{"get_max", LuaInterface::lua_get_max_gold},
		{"add", LuaInterface::lua_add_gold},
		{"sub", LuaInterface::lua_sub_gold},
		{"transfer_all", LuaInterface::lua_transfer_all_gold},
		{"get_closest_gold_deposit", LuaInterface::lua_get_closest_gold_deposit},
		{"get_closest_gold_deposit_in_sight", LuaInterface::lua_get_closest_gold_deposit_in_sight},
		{"full", LuaInterface::lua_gold_full},
		{"is_gold_vault", LuaInterface::lua_is_gold_vault},
		{"closest_gold_vault", LuaInterface::lua_get_closest_gold_vault},
		{"closest_gold_vault_in_sight", LuaInterface::lua_get_closest_gold_vault_in_sight},
		{"closest_free_gold_vault", LuaInterface::lua_get_closest_free_gold_vault},
		{"closest_free_gold_vault_in_sight", LuaInterface::lua_get_closest_free_gold_vault_in_sight},
		{"exists_free_gold_vault", LuaInterface::lua_exists_free_gold_vault},
		{nullptr, nullptr}
	};

	lpp::Script::regs player_funcs[] = {
		// Player stats.
		{"add_gold", LuaInterface::lua_add_player_gold},
		{"sub_gold", LuaInterface::lua_sub_player_gold},
		{"add_mana", LuaInterface::lua_add_player_mana},
		{"sub_mana", LuaInterface::lua_sub_player_mana},
		{"add_max_units", LuaInterface::lua_add_player_max_units},
		{"sub_max_units", LuaInterface::lua_sub_player_max_units},
		{"add_curr_units", LuaInterface::lua_add_player_curr_units},
		{"sub_max_units", LuaInterface::lua_sub_player_max_units},
		{"get_gold", LuaInterface::lua_get_player_gold},
		{"get_mana", LuaInterface::lua_get_player_mana},
		{"reset", LuaInterface::lua_player_reset},
		{"nulify_stats", LuaInterface::lua_nulify_player_stats},
		{"add_max_mana", LuaInterface::lua_add_player_max_mana},
		{"sub_max_mana", LuaInterface::lua_sub_player_max_mana},
		{"get_max_mana", LuaInterface::lua_get_player_max_mana},
		{"add_mana_regen", LuaInterface::lua_add_player_mana_regen},
		{"sub_mana_regen", LuaInterface::lua_sub_player_mana_regen},
		{"get_mana_regen", LuaInterface::lua_get_player_mana_regen},
		{nullptr, nullptr}
	};

	lpp::Script::regs price_funcs[] = {
		// Price.
		{"set", LuaInterface::lua_set_price},
		{"get", LuaInterface::lua_get_price},
		{nullptr, nullptr}
	};

	lpp::Script::regs gui_funcs[] = {
		// GUI.
		{"set_visible", LuaInterface::lua_set_gui_visible},
		{"is_visible", LuaInterface::lua_is_gui_visible},
		{"set_window_visible", LuaInterface::lua_set_window_visible},
		{"is_window_visible", LuaInterface::lua_is_window_visible},
		{"show_load_dialog", LuaInterface::lua_show_load_dialog},
		{"show_save_dialog", LuaInterface::lua_show_save_dialog},
		{nullptr, nullptr}
	};

	lpp::Script::regs log_funcs[] = {
		// Game log.
		{"clear", LuaInterface::lua_clear_log},
		{"print", LuaInterface::lua_print_to_log},
		{"set_history", LuaInterface::lua_set_log_history},
		{"get_history", LuaInterface::lua_get_log_history},
		{"set_visible", LuaInterface::lua_set_log_visible},
		{"is_visible", LuaInterface::lua_is_log_visible},
		{nullptr, nullptr}
	};

	lpp::Script::regs track_funcs[] = {
		// Entity tracker.
		{"clear", LuaInterface::lua_clear_entity_tracker},
		{"get_id", LuaInterface::lua_get_tracked_entity},
		{"set_id", LuaInterface::lua_set_tracked_entity},
		{"update", LuaInterface::lua_update_tracking},
		{"set_visible", LuaInterface::lua_set_tracker_visible},
		{"is_visible", LuaInterface::lua_is_tracker_visible},
		{nullptr, nullptr}
	};

	lpp::Script::regs console_funcs[] = {
		// Dev console.
		{"scroll_down", LuaInterface::lua_console_scroll_down},
		{"set_history", LuaInterface::lua_set_console_history},
		{"get_history", LuaInterface::lua_get_console_history},
		{"clear", LuaInterface::lua_clear_console},
		{"set_visible", LuaInterface::lua_set_console_visible},
		{"is_visible", LuaInterface::lua_is_console_visible},
		{"print", LuaInterface::lua_print},
		{nullptr, nullptr}
	};

	lpp::Script::regs builder_funcs[] = {
		// Builder window.
		{"set_visible", LuaInterface::lua_set_builder_visible},
		{"is_visible", LuaInterface::lua_is_builder_visible},
		{"register_building", LuaInterface::lua_register_building},
		{nullptr, nullptr}
	};

	lpp::Script::regs research_funcs[] = {
		// Research window.
		{"show", LuaInterface::lua_research_show},
		{"free_research", LuaInterface::lua_free_research},
		{"research_all", LuaInterface::lua_research_all},
		{"dummy_unlock", LuaInterface::lua_dummy_unlock},
		{"reset", LuaInterface::lua_research_reset},
		{nullptr, nullptr}
	};

	lpp::Script::regs align_funcs[] = {
		// Alignment.
		{"set_material", LuaInterface::lua_align_set_material},
		{"get_material", LuaInterface::lua_align_get_material},
		{"set_mesh", LuaInterface::lua_align_set_mesh},
		{"get_mesh", LuaInterface::lua_align_get_mesh},
		{"set_offset", LuaInterface::lua_align_set_position_offset},
		{"get_offset", LuaInterface::lua_align_get_position_offset},
		{"set_scale", LuaInterface::lua_align_set_scale},
		{"get_scale", LuaInterface::lua_align_get_scale},
		{nullptr, nullptr}
	};

	lpp::Script::regs spell_funcs[] = {
		// Spells.
		{"register_spell", LuaInterface::lua_register_spell},
		{"set_type", LuaInterface::lua_spellcaster_set_type},
		{"get_type", LuaInterface::lua_spellcaster_get_type},
		{"set_spell", LuaInterface::lua_spellcaster_set_spell},
		{"get_spell", LuaInterface::lua_spellcaster_get_type},
		{"get_last_type", LuaInterface::lua_spellcaster_get_last_type},
		{"get_last_spell", LuaInterface::lua_spellcaster_get_last_spell},
		{"set_last_id", LuaInterface::lua_spellcaster_set_last_spell_id},
		{"get_last_id", LuaInterface::lua_spellcaster_get_last_spell_id},
		{"is_casting", LuaInterface::lua_spellcaster_is_casting},
		{"stop_casting", LuaInterface::lua_spellcaster_stop_casting},
		{nullptr, nullptr}
	};

	lpp::Script::regs mana_crystal_funcs[] = {
		// Mana crystal.
		{"set_capacity", LuaInterface::lua_mana_crystal_set_cap},
		{"get_capacity", LuaInterface::lua_mana_crystal_get_cap},
		{"set_regen", LuaInterface::lua_mana_crystal_set_regen},
		{"get_regen", LuaInterface::lua_mana_crystal_get_regen},
		{nullptr, nullptr}
	};

	lpp::Script::regs on_hit_funcs[] = {
		// On hit.
		{"set_blueprint", LuaInterface::lua_on_hit_set_blueprint},
		{"get_blueprint", LuaInterface::lua_on_hit_get_blueprint},
		{"call", LuaInterface::lua_on_hit_call},
		{"set_cooldown", LuaInterface::lua_on_hit_set_cooldown},
		{"get_cooldown", LuaInterface::lua_on_hit_get_cooldown},
		{nullptr, nullptr}
	};

	lpp::Script::regs constructor_funcs[] = {
		// Constructor.
		{"set_blueprint", LuaInterface::lua_constructor_set_blueprint},
		{"get_blueprint", LuaInterface::lua_constructor_get_blueprint},
		{"call", LuaInterface::lua_constructor_call},
		{nullptr, nullptr}
	};

	lpp::Script::regs trigger_funcs[] = {
		// Trigger.
		{"set_blueprint", LuaInterface::lua_trigger_set_blueprint},
		{"get_blueprint", LuaInterface::lua_trigger_get_blueprint},
		{"set_linked_entity", LuaInterface::lua_trigger_set_linked_entity},
		{"get_linked_entity", LuaInterface::lua_trigger_get_linked_entity},
		{"set_cooldown", LuaInterface::lua_trigger_set_cooldown},
		{"get_cooldown", LuaInterface::lua_trigger_get_cooldown},
		{"trigger", LuaInterface::lua_trigger_trigger},
		{"set_check_period", LuaInterface::lua_trigger_set_check_period},
		{"get_check_period", LuaInterface::lua_trigger_get_check_period},
		{"can_be_triggered_by", LuaInterface::lua_trigger_can_be_triggered_by},
		{"reset_timer", LuaInterface::lua_trigger_reset_timer},
		{"set_radius", LuaInterface::lua_trigger_set_radius},
		{"get_radius", LuaInterface::lua_trigger_get_radius},
		{nullptr, nullptr}
	};

	lpp::Script::regs upgrade_funcs[] = {
		// Upgrade.
		{"set_blueprint", LuaInterface::lua_upgrade_set_blueprint},
		{"get_blueprint", LuaInterface::lua_upgrade_get_blueprint},
		{"set_experience", LuaInterface::lua_upgrade_set_experience},
		{"get_experience", LuaInterface::lua_upgrade_get_experience},
		{"add_experience", LuaInterface::lua_upgrade_add_experience},
		{"set_exp_needed", LuaInterface::lua_upgrade_set_exp_needed},
		{"get_exp_needed", LuaInterface::lua_upgrade_get_exp_needed},
		{"set_level", LuaInterface::lua_upgrade_set_level},
		{"get_level", LuaInterface::lua_upgrade_get_level},
		{"set_level_cap", LuaInterface::lua_upgrade_set_level_cap},
		{"get_level_cap", LuaInterface::lua_upgrade_get_level_cap},
		{"can_level_up", LuaInterface::lua_upgrade_can_level_up},
		{"upgrade", LuaInterface::lua_upgrade_upgrade},
		{"all_level_up", LuaInterface::lua_upgrade_all_level_up},
		{nullptr, nullptr}
	};

	lpp::Script::regs notification_funcs[] = {
		// Notification.
		{"set_cooldown", LuaInterface::lua_notification_set_cooldown},
		{"get_cooldown", LuaInterface::lua_notification_get_cooldown},
		{"reset", LuaInterface::lua_notification_reset},
		{"notify", LuaInterface::lua_notification_notify},
		{"get_curr_time", LuaInterface::lua_notification_get_curr_time},
		{"advance_curr_time", LuaInterface::lua_notification_advance_curr_time},
		{nullptr, nullptr}
	};

	lpp::Script::regs explosion_funcs[] = {
		// Explosion.
		{"set_delta", LuaInterface::lua_explosion_set_delta},
		{"get_delta", LuaInterface::lua_explosion_get_delta},
		{"set_max_radius", LuaInterface::lua_explosion_set_max_radius},
		{"get_max_radius", LuaInterface::lua_explosion_get_max_radius},
		{"get_curr_radius", LuaInterface::lua_explosion_get_curr_radius},
		{"increase_curr_radius", LuaInterface::lua_explosion_increase_curr_radius},
		{nullptr, nullptr}
	};

	lpp::Script::regs lls_funcs[] = {
		// Limited life span.
		{"set_max_time", LuaInterface::lua_lls_set_max_time},
		{"get_max_time", LuaInterface::lua_lls_get_max_time},
		{"get_curr_time", LuaInterface::lua_lls_get_curr_time},
		{"advance_curr_time", LuaInterface::lua_lls_advance_curr_time},
		{nullptr, nullptr}
	};

	lpp::Script::regs name_funcs[] = {
		// Name.
		{"set", LuaInterface::lua_name_set},
		{"get", LuaInterface::lua_name_get},
		{nullptr, nullptr}
	};

	lpp::Script::regs exp_val_funcs[] = {
		// Experience value.
		{"set", LuaInterface::lua_exp_val_set},
		{"get", LuaInterface::lua_exp_val_get},
		{"increase", LuaInterface::lua_exp_val_inc},
		{"decrease", LuaInterface::lua_exp_val_dec},
		{nullptr, nullptr}
	};

	lpp::Script::regs mana_funcs[] = {
		// Mana.
		{"set_regen_period", LuaInterface::lua_mana_set_regen_period},
		{"get_regen_period", LuaInterface::lua_mana_get_regen_period},
		{"add", LuaInterface::lua_mana_add},
		{"sub", LuaInterface::lua_mana_sub},
		{"set", LuaInterface::lua_mana_set},
		{"get", LuaInterface::lua_mana_get},
		{"set_max", LuaInterface::lua_mana_set_max},
		{"get_max", LuaInterface::lua_mana_get_max},
		{"set_regen", LuaInterface::lua_mana_set_regen},
		{"get_regen", LuaInterface::lua_mana_get_regen},
		{nullptr, nullptr}
	};

	lpp::Script::regs wave_funcs[] = {
		// Wave system.
		{"next", LuaInterface::lua_wave_next_wave},
		{"advance_countdown", LuaInterface::lua_wave_advance_countdown},
		{"entity_died", LuaInterface::lua_wave_entity_died},
		{"start", LuaInterface::lua_wave_start},
		{"pause", LuaInterface::lua_wave_pause},
		{"set_entity_total", LuaInterface::lua_wave_set_entity_total},
		{"get_entity_total", LuaInterface::lua_wave_get_entity_total},
		{"set_wave_count", LuaInterface::lua_wave_set_wave_count},
		{"get_wave_count", LuaInterface::lua_wave_get_wave_count},
		{"add_spawn_node", LuaInterface::lua_wave_add_spawn_node},
		{"clear_spawn_nodes", LuaInterface::lua_wave_clear_spawn_nodes},
		{"set_spawn_cooldown", LuaInterface::lua_wave_set_spawn_cooldown},
		{"get_spawn_cooldown", LuaInterface::lua_wave_get_spawn_cooldown},
		{"add_entity_blueprint", LuaInterface::lua_wave_add_entity_blueprint},
		{"set_table", LuaInterface::lua_wave_set_table},
		{"get_table", LuaInterface::lua_wave_get_table},
		{"set_curr_wave_number", LuaInterface::lua_wave_set_curr_wave_number},
		{"get_curr_wave_number", LuaInterface::lua_wave_get_curr_wave_number},
		{"set_countdown", LuaInterface::lua_wave_set_countdown},
		{"get_countdown", LuaInterface::lua_wave_get_countdown},
		{"set_state", LuaInterface::lua_wave_set_state},
		{"get_state", LuaInterface::lua_wave_get_state},
		{"update_label_text", LuaInterface::lua_wave_update_label_text},
		{"set_spawn_timer", LuaInterface::lua_wave_set_spawn_timer},
		{"get_spawn_timer", LuaInterface::lua_wave_get_spawn_timer},
		{"set_wave_entities", LuaInterface::lua_wave_set_wave_entities},
		{"get_wave_entities", LuaInterface::lua_wave_get_wave_entities},
		{"set_entities_spawned", LuaInterface::lua_wave_set_entities_spawned},
		{"get_entities_spawned", LuaInterface::lua_wave_get_entities_spawned},
		{"clear_entity_blueprints", LuaInterface::lua_wave_clear_entity_blueprints},
		{"list", LuaInterface::lua_wave_list},
		{"set_endless_mode", LuaInterface::lua_wave_set_endless_mode},
		{"get_endless_mode", LuaInterface::lua_wave_get_endless_mode},
		{"turn_endless_mode_on", LuaInterface::lua_wave_turn_endless_on},
		{nullptr, nullptr}
	};

	lpp::Script::regs msg_funcs[] = {
		// Message to the player.
		{"show", LuaInterface::lua_msg_to_plr_show},
		{"show_ok", LuaInterface::lua_msg_to_plr_show_ok},
		{"show_yes_no", LuaInterface::lua_msg_to_plr_show_yes_no},
		{"set_butt_label", LuaInterface::lua_msg_set_butt_label},
		{"reset_butt_labels", LuaInterface::lua_msg_reset_butt_labels},
		{nullptr, nullptr}
	};

	lpp::Script::regs ent_spell_funcs[] = {
		// Entity spells.
		{"set_blueprint", LuaInterface::lua_ent_spell_set_blueprint},
		{"get_blueprint", LuaInterface::lua_ent_spell_get_blueprint},
		{"set_cooldown", LuaInterface::lua_ent_spell_set_cooldown},
		{"get_cooldown", LuaInterface::lua_ent_spell_get_cooldown},
		{"advance_curr_time", LuaInterface::lua_ent_spell_advance_curr_time},
		{"set_curr_time", LuaInterface::lua_ent_spell_set_curr_time},
		{"get_curr_time", LuaInterface::lua_ent_spell_get_curr_time},
		{"cast", LuaInterface::lua_ent_spell_cast},
		{nullptr, nullptr}
	};

	lpp::Script::regs light_funcs[] = {
		// Light.
		{"set_visible", LuaInterface::lua_light_set_visible},
		{"toggle_visible", LuaInterface::lua_light_toggle_visible},
		{"is_visible", LuaInterface::lua_light_is_visible},
		{"init", LuaInterface::lua_light_init},
		{nullptr, nullptr}
	};

	lpp::Script::regs counter_funcs[] = {
		// Counter.
		{"increment", LuaInterface::lua_counter_increment},
		{"decrement", LuaInterface::lua_counter_decrement},
		{"set", LuaInterface::lua_counter_set_curr_value},
		{"get", LuaInterface::lua_counter_get_curr_value},
		{"set_max", LuaInterface::lua_counter_set_max_value},
		{"get_max", LuaInterface::lua_counter_get_max_value},
		{nullptr, nullptr}
	};

	lpp::Script::regs animation_funcs[] = {
		// Animation.
		{"play", LuaInterface::lua_animation_play},
		{"stop", LuaInterface::lua_animation_stop},
		{"add_possible", LuaInterface::lua_animation_add_possible},
		{"delete_possible", LuaInterface::lua_animation_delete_possible},
		{"is_possible", LuaInterface::lua_animation_is_possible},
		{"set_stop", LuaInterface::lua_animation_set_stop},
		{"get_stop", LuaInterface::lua_animation_get_stop},
		{nullptr, nullptr}
	};

	lpp::Script::regs selection_funcs[] = {
		// Selection.
		{"set_blueprint", LuaInterface::lua_selection_set_blueprint},
		{"get_blueprint", LuaInterface::lua_selection_get_blueprint},
		{"set_material", LuaInterface::lua_selection_set_material},
		{"get_material", LuaInterface::lua_selection_get_material},
		{"select", LuaInterface::lua_selection_select},
		{"deselect", LuaInterface::lua_selection_deselect},
		{"set_scale", LuaInterface::lua_selection_set_scale},
		{"get_scale", LuaInterface::lua_selection_get_scale},
		{"set_marker_type", LuaInterface::lua_selection_set_marker_type},
		{"get_marker_type", LuaInterface::lua_selection_get_marker_type},
		{"set_rotation", LuaInterface::lua_selection_set_rotation},
		{"get_rotation", LuaInterface::lua_selection_get_rotation},
		{nullptr, nullptr}
	};

	lpp::Script::regs activation_funcs[] = {
		// Activation.
		{"set_blueprint", LuaInterface::lua_activation_set_blueprint},
		{"get_blueprint", LuaInterface::lua_activation_get_blueprint},
		{"activate", LuaInterface::lua_activation_activate},
		{"deactivate", LuaInterface::lua_activation_deactivate},
		{"is_activated", LuaInterface::lua_activation_is_activated},
		{nullptr, nullptr}
	};

	auto state = script.get_state();
	luaL_newlib(state, game_funcs);
	lua_setglobal(state, "game");

	// Set all subtables.
	lua_getglobal(state, "game");
	luaL_newlib(state, command_funcs);
	lua_setfield(state, -2, "command");
	luaL_newlib(state, graph_funcs);
	lua_setfield(state, -2, "graphics");
	luaL_newlib(state, entity_funcs);
	lua_setfield(state, -2, "entity");
	luaL_newlib(state, phys_funcs);
	lua_setfield(state, -2, "physics");
	luaL_newlib(state, mov_funcs);
	lua_setfield(state, -2, "movement");
	luaL_newlib(state, hp_funcs);
	lua_setfield(state, -2, "health");
	luaL_newlib(state, ai_funcs);
	lua_setfield(state, -2, "ai");
	luaL_newlib(state, input_funcs);
	lua_setfield(state, -2, "input");
	luaL_newlib(state, grid_funcs);
	lua_setfield(state, -2, "grid");
	luaL_newlib(state, path_funcs);
	lua_setfield(state, -2, "path");
	luaL_newlib(state, task_funcs);
	lua_setfield(state, -2, "task");
	luaL_newlib(state, combat_funcs);
	lua_setfield(state, -2, "combat");
	luaL_newlib(state, proj_funcs);
	lua_setfield(state, -2, "projectile");
	luaL_newlib(state, prod_funcs);
	lua_setfield(state, -2, "production");
	luaL_newlib(state, time_funcs);
	lua_setfield(state, -2, "time");
	luaL_newlib(state, event_funcs);
	lua_setfield(state, -2, "event");
	luaL_newlib(state, handling_funcs);
	lua_setfield(state, -2, "event_handling");
	luaL_newlib(state, destr_funcs);
	lua_setfield(state, -2, "destructor");
	luaL_newlib(state, gold_funcs);
	lua_setfield(state, -2, "gold");
	luaL_newlib(state, player_funcs);
	lua_setfield(state, -2, "player");
	luaL_newlib(state, price_funcs);
	lua_setfield(state, -2, "price");
	luaL_newlib(state, spell_funcs);
	lua_setfield(state, -2, "spell");
	luaL_newlib(state, align_funcs);
	lua_setfield(state, -2, "align");
	luaL_newlib(state, mana_crystal_funcs);
	lua_setfield(state, -2, "mana_crystal");
	luaL_newlib(state, on_hit_funcs);
	lua_setfield(state, -2, "on_hit");
	luaL_newlib(state, constructor_funcs);
	lua_setfield(state, -2, "constructor");
	luaL_newlib(state, trigger_funcs);
	lua_setfield(state, -2, "trigger");
	luaL_newlib(state, upgrade_funcs);
	lua_setfield(state, -2, "upgrade");
	luaL_newlib(state, notification_funcs);
	lua_setfield(state, -2, "notification");
	luaL_newlib(state, explosion_funcs);
	lua_setfield(state, -2, "explosion");
	luaL_newlib(state, lls_funcs);
	lua_setfield(state, -2, "lls");
	luaL_newlib(state, name_funcs);
	lua_setfield(state, -2, "name");
	luaL_newlib(state, exp_val_funcs);
	lua_setfield(state, -2, "exp_val");
	luaL_newlib(state, mana_funcs);
	lua_setfield(state, -2, "mana");
	luaL_newlib(state, wave_funcs);
	lua_setfield(state, -2, "wave");
	luaL_newlib(state, ent_spell_funcs);
	lua_setfield(state, -2, "ent_spell");
	luaL_newlib(state, light_funcs);
	lua_setfield(state, -2, "light");
	luaL_newlib(state, counter_funcs);
	lua_setfield(state, -2, "counter");
	luaL_newlib(state, animation_funcs);
	lua_setfield(state, -2, "animation");
	luaL_newlib(state, selection_funcs);
	lua_setfield(state, -2, "selection");
	luaL_newlib(state, activation_funcs);
	lua_setfield(state, -2, "activation");

	// GUI subtable has it's own subtables.
	luaL_newlib(state, gui_funcs);
	lua_setfield(state, -2, "gui");
	lua_getfield(state, -1, "gui");
	luaL_newlib(state, log_funcs);
	lua_setfield(state, -2, "log");
	luaL_newlib(state, track_funcs);
	lua_setfield(state, -2, "tracker");
	luaL_newlib(state, console_funcs);
	lua_setfield(state, -2, "console");
	luaL_newlib(state, builder_funcs);
	lua_setfield(state, -2, "builder");
	luaL_newlib(state, research_funcs);
	lua_setfield(state, -2, "research");
	luaL_newlib(state, msg_funcs);
	lua_setfield(state, -2, "message");

	// Pop the residual tables.
	lua_pop(state, 2);
	
	// Set some C++ constants.
	script.execute("game.const = {}");
	script.execute("game.const.no_ent = " + std::to_string(Component::NO_ENTITY));

	// Load all necessary scripts.
	script.load("init.lua");

	// InputComponent related enums.
	script.set("game.enum.input.key_up", OIS::KC_W);
	script.set("game.enum.input.key_down", OIS::KC_S);
	script.set("game.enum.input.key_left", OIS::KC_A);
	script.set("game.enum.input.key_right", OIS::KC_D);

	auto testing = lpp::Script::instance().get<bool>("game.config.testing_mode");
	if(testing)
		GUI::instance().get_window("MAIN_MENU/TESTING_MODE")->setVisible(true);
}

/**
 * \note Function definitions below act as an interface between C++ and Lua, they all have
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
	std::string msg = GET_STR(L, -1);

	GUI::instance().get_console().print_text(msg, Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_set_game_state(lpp::Script::state L)
{
	GAME_STATE state = (GAME_STATE)luaL_checkinteger(L, -1);

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

int LuaInterface::lua_list_selected(lpp::Script::state L)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
	{
		GUI::instance().get_console().print_text(std::to_string(ent), Console::ORANGE_TEXT);
	}

	return 0;
}

int LuaInterface::lua_destroy_selected(lpp::Script::state L)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
		DestructorHelper::destroy(*ents, ent, true);
	lua_this->selection_box_->clear_selected_entities();

	return 0;
}

int LuaInterface::lua_kill_selected(lpp::Script::state L)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
		DestructorHelper::destroy(*ents, ent, false);
	lua_this->selection_box_->clear_selected_entities();

	return 0;
}

int LuaInterface::lua_list_components_of(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	std::string report{};
	auto& ent = lua_this->entity_system_->get_component_list().find(id);
	if(ent != lua_this->entity_system_->get_component_list().end())
	{
		for(tdt::uint i = 0; i < ent->second.size(); ++i)
		{
			if(ent->second.test(i))
				report.append(std::to_string(i) + ", ");
		}
	}

	GUI::instance().get_console().print_text(report, Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_load(lpp::Script::state L)
{
	std::string script = GET_STR(L, -1);

	lpp::Script::instance().load(script);
	return 0;
}

int LuaInterface::lua_reload_all(lpp::Script::state L)
{
	lpp::Script::instance().reload_all_scripts();
	return 0;
}

int LuaInterface::lua_save_game(lpp::Script::state L)
{
	if(lua_gettop(L) > 0)
	{
		std::string fname = GET_STR(L, -1);
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
		std::string fname = GET_STR(L, -1);
		lua_this->game_serializer_->load_game(*lua_this, fname);
	}
	else
		lua_this->game_serializer_->load_game(*lua_this);

	return 0;
}

int LuaInterface::lua_get_cursor_position(lpp::Script::state L)
{
	auto pos = lua_this->mouse_position_;

	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);
	return 2;
}

int LuaInterface::lua_can_place_when_game_paused(lpp::Script::state L)
{
	auto res = lua_this->placer_->can_place_when_game_paused();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_toggle_placing_when_game_paused(lpp::Script::state L)
{
	lua_this->placer_->toggle_placing_when_game_paused();
	return 0;
}

int LuaInterface::lua_new_game(lpp::Script::state L)
{
	tdt::uint height = GET_UINT(L, -1);
	tdt::uint width  = GET_UINT(L, -2);

	lua_this->new_game(width, height);
	return 0;
}

int LuaInterface::lua_create_empty_level(lpp::Script::state L)
{
	tdt::uint height = GET_UINT(L, -1);
	tdt::uint width  = GET_UINT(L, -2);

	lua_this->create_empty_level(width, height);
	return 0;
}

int LuaInterface::lua_reset_unlocks(lpp::Script::state L)
{
	lua_this->reset_unlocks();
	return 0;
}

int LuaInterface::lua_get_random(lpp::Script::state L)
{
	tdt::uint ub = GET_UINT(L, -1);
	tdt::uint lb = GET_UINT(L, -2);

	auto res = util::get_random(lb, ub);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_key_bind(lpp::Script::state L)
{
	CEGUI::Key::Scan key        =     (CEGUI::Key::Scan)GET_SINT(L, -1);
	KEY_BIND_ACTION::VAL action = (KEY_BIND_ACTION::VAL)GET_SINT(L, -2);

	GUI::instance().get_options().set_key_bind(action, key);
	return 0;
}

int LuaInterface::lua_get_first_selected(lpp::Script::state L)
{
	if(!lua_this->selection_box_->get_selected_entities().empty())
	{
		lua_pushinteger(L, lua_this->selection_box_->get_selected_entities()[0]);
		return 1;
	}
	else
		return 0;
}

int LuaInterface::lua_get_enemies(lpp::Script::state L)
{
	std::vector<tdt::uint> res{};
	for(auto& ent : ents->get_component_container<FactionComponent>())
	{
		if(ent.second.faction == FACTION::ENEMY)
			res.emplace_back(ent.first);
	}

	lua_createtable(L, res.size(), 0);
	int table = lua_gettop(L);
	int i = 1;
	for(const auto& ent : res)
	{
		lua_pushinteger(L, ent);
		lua_rawseti(L, table, i);
		++i;
	}
	return 1;
}

int LuaInterface::lua_get_friends(lpp::Script::state L)
{
	std::vector<tdt::uint> res{};
	for(auto& ent : ents->get_component_container<FactionComponent>())
	{
		if(ent.second.faction == FACTION::FRIENDLY)
			res.emplace_back(ent.first);
	}

	lua_createtable(L, res.size(), 0);
	int table = lua_gettop(L);
	int i = 1;
	for(const auto& ent : res)
	{
		lua_pushinteger(L, ent);
		lua_rawseti(L, table, i);
		++i;
	}
	return 1;
}

int LuaInterface::lua_set_throne_id(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	lua_this->set_throne_id(id);
	return 0;
}

int LuaInterface::lua_get_throne_id(lpp::Script::state L)
{
	auto res = lua_this->get_throne_id();
	
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_register_scenario(lpp::Script::state L)
{
	std::string table = GET_STR(L, -1);
	std::string scenario = GET_STR(L, -2);

	GUI::instance().get_new_game().register_scenario(scenario, table);
	return 0;
}

int LuaInterface::lua_command_to_mine(lpp::Script::state L)
{
	CommandHelper::command_to_mine(*ents, *lua_this->selection_box_);
	return 0;
}

int LuaInterface::lua_command_to_attack(lpp::Script::state L)
{
	CommandHelper::command_to_attack(*ents, *lua_this->selection_box_);
	return 0;
}

int LuaInterface::lua_command_to_reposition(lpp::Script::state L)
{
	tdt::real y = GET_REAL(L, -1);
	tdt::real x = GET_REAL(L, -2);

	CommandHelper::command_to_reposition(*ents, x, y);
	return 0;
}

int LuaInterface::lua_command_to_return_gold(lpp::Script::state L)
{
	CommandHelper::command_to_return_gold(*ents, *lua_this->combat_system_);
	return 0;
}

int LuaInterface::lua_command_to_fall_back(lpp::Script::state L)
{
	CommandHelper::command_to_fall_back(*ents);
	return 0;
}

int LuaInterface::lua_get_enum_direction(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint source = GET_UINT(L, -2);

	auto res = util::get_enum_direction(*ents, source, target);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_node_in_dir(lpp::Script::state L)
{
	int dir          = GET_SINT(L, -1);
	tdt::uint source = GET_UINT(L, -2);

	auto res = GridNodeHelper::get_node_in_dir(*ents, source, dir);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_mesh(lpp::Script::state L)
{
	std::string mesh = GET_STR(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	GraphicsHelper::set_mesh(*ents, id, mesh);
	return 0;
}

int LuaInterface::lua_set_material(lpp::Script::state L)
{
	std::string mat = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	GraphicsHelper::set_material(*ents, id, mat);
	return 0;
}

int LuaInterface::lua_set_visible(lpp::Script::state L)
{
	bool vis     = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	GraphicsHelper::set_visible(*ents, id, vis);
	return 0;
}

int LuaInterface::lua_set_manual_scaling(lpp::Script::state L)
{
	bool val     = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	GraphicsHelper::set_manual_scaling(*ents, id, val);
	return 0;
}

int LuaInterface::lua_set_scale(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	GraphicsHelper::set_scale(*ents, id, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_get_mesh(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = GraphicsHelper::get_mesh(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_get_material(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = GraphicsHelper::get_material(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_is_visible(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GraphicsHelper::is_visible(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_manual_scaling(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GraphicsHelper::get_manual_scaling(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_scale(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = GraphicsHelper::get_scale(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_collide(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);

	bool res = GraphicsHelper::collide(*ents, id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_query_flags(lpp::Script::state L)
{
	tdt::uint flags = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	GraphicsHelper::set_query_flags(*ents, id, flags);
	return 0;
}

int LuaInterface::lua_get_query_flags(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GraphicsHelper::get_query_flags(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_apply_scale(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	GraphicsHelper::apply_scale(*ents, id);
	return 0;
}

int LuaInterface::lua_set_graphics_update_period(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);

	lua_this->graphics_system_->set_update_period(val);
	return 0;
}

int LuaInterface::lua_get_graphics_update_period(lpp::Script::state L)
{
	auto res = lua_this->graphics_system_->get_update_period();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_look_at(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);

	GraphicsHelper::look_at(*ents, id1, id2);
	return 0;
}

int LuaInterface::lua_create_entity(lpp::Script::state L)
{
	std::string table_name{""};
	if(lua_gettop(L) >= 1)
		table_name = GET_STR(L, -1);

	tdt::uint id = lua_this->entity_system_->create_entity(table_name);
	lua_pushinteger(L, id); // Return the new id.
	return 1;
}

int LuaInterface::lua_destroy_entity(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	DestructorHelper::destroy(*ents, id, true);
	return 0;
}

int LuaInterface::lua_add_component(lpp::Script::state L)
{
	int comp     = GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	lua_this->entity_system_->add_component(id, comp);
	return 0;
}

int LuaInterface::lua_delete_component(lpp::Script::state L)
{
	int comp     = GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	lua_this->entity_system_->delete_component(id, comp);
	return 0;
}

int LuaInterface::lua_init_graphics_component(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	GraphicsHelper::init_graphics_component(*ents, *lua_this->scene_mgr_, id);
	return 0;
}

int LuaInterface::lua_list_entity_tables(lpp::Script::state L)
{
	auto& ents = lua_this->entity_system_->get_registered_entities();

	if(!ents.empty())
	{
		for(const auto& ent : ents)
			GUI::instance().get_console().print_text(ent, Console::ORANGE_TEXT);
	}
	else
		GUI::instance().get_console().print_text("NO REGISTERED ENTITY TABLES.", Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_place_entity(lpp::Script::state L)
{
	std::string table_name = GET_STR(L, -1);

	lua_this->placer_->set_current_entity_table(table_name);
	lua_this->placer_->set_visible(true);
	return 0;
}

int LuaInterface::lua_register_entity(lpp::Script::state L)
{
	std::string table_name = GET_STR(L, -1);

	lua_this->entity_system_->register_entity(table_name);
	return 0;
}

int LuaInterface::lua_exists(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->entity_system_->exists(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_kill_entity(lpp::Script::state L)
{
	tdt::uint killer = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	DestructorHelper::destroy(*ents, id, false, killer);
	return 0;
}

int LuaInterface::lua_has_component(lpp::Script::state L)
{
	tdt::uint type = GET_UINT(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	auto res = ents->has_component(id, type);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_entity_reset_state(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto comp = ents->get_component<TaskHandlerComponent>(id);
	if(comp)
	{
		TaskHelper::cancel_task(*ents, comp->curr_task);
		comp->curr_task = Component::NO_ENTITY;
		for(const auto& task : comp->task_queue)
		{
			TaskHelper::cancel_task(*ents, task);
		}
		comp->task_queue.clear();
		comp->busy = false;
	}

	auto path = ents->get_component<PathfindingComponent>(id);
	if(path)
	{
		path->path_queue.clear();
		path->target_id = Component::NO_ENTITY;
		path->last_id = Component::NO_ENTITY;
	}
	return 0;
}

int LuaInterface::lua_move_to(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	PhysicsHelper::move_to(*ents, id, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_move(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	bool res = lua_this->movement_system_->move(id, Ogre::Vector3{x, y, z});
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_rotate_x(lpp::Script::state L)
{
	tdt::real delta = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	GraphicsHelper::rotate(*ents, id, delta, GraphicsHelper::PLANE::X);
	return 0;
}

int LuaInterface::lua_rotate_y(lpp::Script::state L)
{
	tdt::real delta = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	GraphicsHelper::rotate(*ents, id, delta, GraphicsHelper::PLANE::Y);
	return 0;
}

int LuaInterface::lua_rotate_z(lpp::Script::state L)
{
	tdt::real delta = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	GraphicsHelper::rotate(*ents, id, delta, GraphicsHelper::PLANE::Z);
	return 0;
}

int LuaInterface::lua_is_solid(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	bool res = PhysicsHelper::is_solid(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_can_move_to(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	bool res = lua_this->movement_system_->can_move_to(id, Ogre::Vector3{x, y, z});
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_distance(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);

	tdt::real res = PhysicsHelper::get_distance(*ents, id1, id2);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_position(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	Ogre::Vector3 res = PhysicsHelper::get_position(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_speed_modifier(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	tdt::real res = MovementHelper::get_speed_modifier(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_speed_modifier(lpp::Script::state L)
{
	tdt::real speed = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	MovementHelper::set_speed_modifier(*ents, id, speed);
	return 0;
}

int LuaInterface::lua_dir_to(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);

	auto res = MovementHelper::dir_to(*ents, id1, id2);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = MovementHelper::get_dir(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_back(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = MovementHelper::get_dir_back(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_left(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = MovementHelper::get_dir_left(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_get_dir_right(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = MovementHelper::get_dir_right(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_set_original_speed(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	MovementHelper::set_original_speed(*ents, id, val);
	return 0;
}

int LuaInterface::lua_get_original_speed(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = MovementHelper::get_original_speed(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_reset_speed(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	MovementHelper::reset_speed(*ents, id);
	return 0;
}

int LuaInterface::lua_get_angle(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	auto dir = MovementHelper::get_dir(*ents, id);
	auto res = PhysicsHelper::get_angle(dir, Ogre::Vector3{x, y, z});
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_angle_between(lpp::Script::state L)
{
	tdt::real z2 = GET_REAL(L, -1);
	tdt::real y2 = GET_REAL(L, -2);
	tdt::real x2 = GET_REAL(L, -3);
	tdt::real z1 = GET_REAL(L, -4);
	tdt::real y1 = GET_REAL(L, -5);
	tdt::real x1 = GET_REAL(L, -6);

	auto res = PhysicsHelper::get_angle(Ogre::Vector3{x1, y1, z1}, Ogre::Vector3{x2, y2, z2});
	lua_pushnumber(L, res);
	return 3;
}

int LuaInterface::lua_set_2d_position(lpp::Script::state L)
{
	tdt::real y  = GET_REAL(L, -1);
	tdt::real x  = GET_REAL(L, -2);
	tdt::uint id = GET_UINT(L, -3);

	PhysicsHelper::set_2d_position(*ents, id, Ogre::Vector2{x, y});
	return 0;
}

int LuaInterface::lua_get_2d_position(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = PhysicsHelper::get_2d_position(*ents, id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	return 2;
}

int LuaInterface::lua_set_solid(lpp::Script::state L)
{
	bool solid   = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	PhysicsHelper::set_solid(*ents, id, solid);
	return 0;
}

int LuaInterface::lua_set_half_height(lpp::Script::state L)
{
	tdt::real hh = GET_REAL(L, -1);
	tdt::uint id = GET_UINT(L, -2);
	
	PhysicsHelper::set_half_height(*ents, id, hh);
	return 0;
}

int LuaInterface::lua_get_half_height(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = PhysicsHelper::get_half_height(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_position(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	PhysicsHelper::set_position(*ents, id, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_set_health(lpp::Script::state L)
{
	tdt::uint hp = GET_UINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	HealthHelper::set_health(*ents, id, hp);
	return 0;
}

int LuaInterface::lua_get_health(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	tdt::uint res = HealthHelper::get_health(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_health(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HealthHelper::add_health(*ents, id, val);
	return 0;
}

int LuaInterface::lua_sub_health(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HealthHelper::sub_health(*ents, id, val);
	return 0;
}

int LuaInterface::lua_heal(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	HealthHelper::heal(*ents, id);
	return 0;
}

int LuaInterface::lua_buff(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HealthHelper::buff(*ents, id, val);
	return 0;
}

int LuaInterface::lua_debuff(lpp::Script::state L)
{
	tdt::uint hp = GET_UINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	HealthHelper::debuff(*ents, id, hp);
	return 0;
}

int LuaInterface::lua_set_defense(lpp::Script::state L)
{
	tdt::uint def = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HealthHelper::set_defense(*ents, id, def);
	return 0;
}

int LuaInterface::lua_get_defense(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	tdt::uint res = HealthHelper::get_defense(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_defense(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HealthHelper::add_defense(*ents, id, val);
	return 0;
}

int LuaInterface::lua_sub_defense(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HealthHelper::sub_defense(*ents, id, val);
	return 0;
}

int LuaInterface::lua_set_regen(lpp::Script::state L)
{
	tdt::uint regen = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	HealthHelper::set_regen(*ents, id, regen);
	return 0;
}

int LuaInterface::lua_get_regen(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = HealthHelper::get_regen(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_alive(lpp::Script::state L)
{
	bool alive   = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	HealthHelper::set_alive(*ents, id, alive);
	return 0;
}

int LuaInterface::lua_is_alive(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = HealthHelper::is_alive(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_ubercharge(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	HealthHelper::ubercharge(*ents, id);
	return 0;
}

int LuaInterface::lua_set_regen_period(lpp::Script::state L)
{
	tdt::real t = GET_REAL(L, -1);

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
	tdt::uint id = GET_UINT(L, -1);

	std::string res = AIHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_get_state(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	int res = (int)AIHelper::get_state(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_faction(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	int res = (int)FactionHelper::get_faction(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	AIHelper::set_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_set_state(lpp::Script::state L)
{
	ENTITY_STATE::VAL state = (ENTITY_STATE::VAL)luaL_checkinteger(L, -1);
	tdt::uint id       = GET_UINT(L, -2);

	AIHelper::set_state(*ents, id, state);
	return 0;
}

int LuaInterface::lua_set_faction(lpp::Script::state L)
{
	FACTION faction = (FACTION)luaL_checkinteger(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	FactionHelper::set_faction(*ents, id, faction);
	return 0;
}

int LuaInterface::lua_set_update_period(lpp::Script::state L)
{
	tdt::real t = GET_REAL(L, -1);

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

int LuaInterface::lua_get_faction_name(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);
	auto& res = FactionHelper::get_faction_name(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_set_input_handler(lpp::Script::state L)
{
	std::string handler = GET_STR(L, -1);
	tdt::uint id        = GET_UINT(L, -2);

	InputHelper::set_input_handler(*ents, id, handler);
	return 0;
}

int LuaInterface::lua_get_input_handler(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = InputHelper::get_input_handler(*ents, id);
	lua_pushstring(L, res.c_str());
	return 0;
}

int LuaInterface::lua_toggle_first_person(lpp::Script::state L)
{
	tdt::uint id{Component::NO_ENTITY};
	if(lua_gettop(L) >= 1) // Allow for easy exit.
		id = GET_UINT(L, -1);

	lua_this->input_system_->set_first_person(!lua_this->input_system_->is_first_person(), id);
	return 0;
}

int LuaInterface::lua_add_node(lpp::Script::state L)
{
	tdt::real z = GET_REAL(L, -1);
	tdt::real x = GET_REAL(L, -2);

	auto res = Grid::instance().add_node(*ents, Ogre::Vector2{x, z});
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_get_node(lpp::Script::state L)
{
	tdt::uint y = GET_UINT(L, -1);
	tdt::uint x = GET_UINT(L, -2);

	tdt::uint res = Grid::instance().get_node(x, y);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_node_from_position(lpp::Script::state L)
{
	tdt::real z = GET_REAL(L, -1);
	tdt::real x = GET_REAL(L, -2);

	tdt::uint res = Grid::instance().get_node_from_position(x, z);
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
	tdt::uint id = GET_UINT(L, -1);

	bool res = GridNodeHelper::is_free(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_free(lpp::Script::state L)
{
	bool free    = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	GridNodeHelper::set_free(*ents, id, free);
	return 0;
}

int LuaInterface::lua_set_free_selected(lpp::Script::state L)
{
	bool free = GET_BOOL(L, -1);

	GridNodeHelper::set_free_selected(*ents, *lua_this->selection_box_, free);
	return 0;
}

int LuaInterface::lua_pathfind(lpp::Script::state L)
{
	tdt::uint end = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	bool res = util::pathfind<util::DEFAULT_PATHFINDING_ALGORITHM>(*ents, id, end, util::DEFAULT_HEURISTIC{*ents});
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_pop_first_path_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& path = PathfindingHelper::get_path(*ents, id);
	if(!path.empty())
		path.pop_front();
	return 0;
}

int LuaInterface::lua_pop_last_path_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& path = PathfindingHelper::get_path(*ents, id);
	if(!path.empty())
		path.pop_back();
	return 0;
}

int LuaInterface::lua_path_queue_empty(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = PathfindingHelper::get_path(*ents, id).empty();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_path(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& queue = PathfindingHelper::get_path(*ents, id);
	if(!queue.empty())
		queue.clear();
	return 0;
}

int LuaInterface::lua_set_pathfinding_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	PathfindingHelper::set_pathfinding_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_get_pathfinding_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = PathfindingHelper::get_pathpfinding_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 0;
}

int LuaInterface::lua_create_graph(lpp::Script::state L)
{
	tdt::real start_y = GET_REAL(L, -1);
	tdt::real start_x = GET_REAL(L, -2);
	tdt::real dist    = GET_REAL(L, -3);
	tdt::uint height  = GET_UINT(L, -4);
	tdt::uint width   = GET_UINT(L, -5);

	Grid::instance().create_graph(*ents, Ogre::Vector2{start_x, start_y}, width, height, dist);
	return 0;
}

int LuaInterface::lua_set_resident(lpp::Script::state L)
{
	tdt::uint res_id = GET_UINT(L, -1);
	tdt::uint ent_id = GET_UINT(L, -2);

	GridNodeHelper::set_resident(*ents, ent_id, res_id);
	return 0;
}

int LuaInterface::lua_get_resident(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GridNodeHelper::get_resident(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_residences(lpp::Script::state L)
{
	std::string residences = GET_STR(L, -1);
	tdt::uint id           = GET_UINT(L, -2);

	auto nodes = lpp::Script::instance().get_vector<tdt::uint>(residences);
	StructureHelper::add_residences(*ents, id, nodes);
	return 0;
}

int LuaInterface::lua_add_residence(lpp::Script::state L)
{
	tdt::uint res_id = GET_UINT(L, -1);
	tdt::uint ent_id = GET_UINT(L, -2);

	StructureHelper::add_residence(*ents, ent_id, res_id);
	return 0;
}

int LuaInterface::lua_set_radius(lpp::Script::state L)
{
	tdt::uint radius = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	StructureHelper::set_radius(*ents, id, radius);
	return 0;
}

int LuaInterface::lua_set_walk_through(lpp::Script::state L)
{
	bool val     = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	StructureHelper::set_walk_through(*ents, id, val);
	return 0;
}

int LuaInterface::lua_is_walk_throuth(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = StructureHelper::is_walk_through(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_place_at_random_free_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);
	auto res = Grid::instance().place_at_random_free_node(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_distribute_to_adjacent_free_nodes(lpp::Script::state L)
{
	int stack_size = lua_gettop(L);
	int stack_idx = 1;
	bool res{false};
	std::vector<tdt::uint> ids{};

	if(stack_size > 1)
	{
		tdt::uint id = GET_UINT(L, stack_idx++);
		for(; stack_idx <= stack_size; ++stack_idx)
		{
			ids.push_back(GET_UINT(L, stack_idx));
		}

		res = Grid::instance().distribute_to_adjacent_free_nodes(*ents, id, ids);
	}

	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_random_free_node(lpp::Script::state L)
{
	auto res = Grid::instance().get_random_free_node();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_portal_neighbour(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	GridNodeHelper::set_portal_neighbour(*ents, id, val);
	return 0;
}

int LuaInterface::lua_get_next_pathfinding_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	tdt::uint res{Component::NO_ENTITY};
	auto comp = ents->get_component<PathfindingComponent>(id);
	if(comp && !comp->path_queue.empty())
		res = comp->path_queue[0];

	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_target_pathfinding_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	tdt::uint res{Component::NO_ENTITY};
	auto comp = ents->get_component<PathfindingComponent>(id);
	if(comp && !comp->path_queue.empty())
		res = comp->path_queue[comp->path_queue.size() - 1];

	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_pathfinding_skip_next_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto comp = ents->get_component<PathfindingComponent>(id);
	if(comp && !comp->path_queue.empty())
		comp->path_queue.pop_front();
	return 0;
}

int LuaInterface::lua_pathfinding_after_next_node(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto comp = ents->get_component<PathfindingComponent>(id);
	tdt::uint res{Component::NO_ENTITY};
	if(comp && comp->path_queue.size() > 1)
		res = comp->path_queue[1];
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_task(lpp::Script::state L)
{
	tdt::uint task_id = GET_UINT(L, -1);
	tdt::uint ent_id  = GET_UINT(L, -2);

	TaskHelper::add_task(*ents, ent_id, task_id);
	return 0;
}

int LuaInterface::lua_add_priority_task(lpp::Script::state L)
{
	tdt::uint task_id = GET_UINT(L, -1);
	tdt::uint ent_id  = GET_UINT(L, -2);

	TaskHelper::add_task(*ents, ent_id, task_id, true);
	return 0;
}

int LuaInterface::lua_cancel_task(lpp::Script::state L)
{
	tdt::uint task_id = GET_UINT(L, -1);

	TaskHelper::cancel_task(*ents, task_id);
	return 0;
}

int LuaInterface::lua_create_task(lpp::Script::state L)
{
	TASK_TYPE task   = (TASK_TYPE)luaL_checkinteger(L, -1);
	tdt::uint target = GET_UINT(L, -2);

	auto id = TaskHelper::create_task(*ents, target, task);
	lua_pushinteger(L, id);
	return 1;
}

int LuaInterface::lua_list_tasks_of(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);
	
	auto comp = lua_this->entity_system_->get_component<TaskHandlerComponent>(id);
	if(comp)
	{
		std::string report{};
		auto& task_queue = comp->task_queue;
		int task_count{};

		report.append(comp->busy ? "State: BUSY\n" : "State: FREE\n");
		if(comp->curr_task != Component::NO_ENTITY)
		{ // Current task.
			++task_count;
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
			++task_count;
			report.append(std::to_string(task) + ": ");
			auto task_comp = lua_this->entity_system_->get_component<TaskComponent>(task);
			if(task_comp)
			{
				report.append(lua_this->task_system_->get_task_name(task_comp->task_type)
							  + " (" + std::to_string(task_comp->source)
							  + " -> " + std::to_string(task_comp->target) + ").\n");
			}
			else
				report.append(lua_this->task_system_->get_task_name(TASK_TYPE::NONE) + "\n");
		}
		GUI::instance().get_console().print_text(report, Console::ORANGE_TEXT);
		GUI::instance().get_console().scroll_down(task_count);
	}
	else
		GUI::instance().get_console().print_text("<FAIL> GIVEN ENTITY HAS NO TASKS.", Console::RED_TEXT);

	return 0;
}

int LuaInterface::lua_task_possible(lpp::Script::state L)
{
	tdt::uint task_id = GET_UINT(L, -1);
	tdt::uint ent_id  = GET_UINT(L, -2);

	bool res = TaskHandlerHelper::task_possible(*ents, ent_id, task_id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_task_type_possibe(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	auto res = TaskHandlerHelper::task_possible(*ents, id, type);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_task_queue(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	TaskHandlerHelper::clear_task_queue(*ents, id);
	return 0;
}

int LuaInterface::lua_set_task_source(lpp::Script::state L)
{
	tdt::uint source = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	TaskHelper::set_task_source(*ents, id, source);
	return 0;
}

int LuaInterface::lua_get_task_source(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TaskHelper::get_task_source(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_task_target(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	TaskHelper::set_task_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_get_task_target(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TaskHelper::get_task_target(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_task_type(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	TaskHelper::set_task_type(*ents, id, type);
	return 0;
}

int LuaInterface::lua_get_task_type(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TaskHelper::get_task_type(*ents, id);
	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_add_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	TaskHandlerHelper::add_possible_task(*ents, id, type);
	return 0;
}
int LuaInterface::lua_delete_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	TaskHandlerHelper::delete_possible_task(*ents, id, type);
	return 0;
}

int LuaInterface::lua_set_task_handling_blueprint(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	TaskHandlerHelper::set_blueprint(*ents, id, val);
	return 0;
}

int LuaInterface::lua_get_task_handling_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TaskHandlerHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_set_task_complete(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	TaskHelper::set_complete(*ents, id);
	return 0;
}

int LuaInterface::lua_is_task_complete(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TaskHelper::is_complete(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_task_clear(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto comp = ents->get_component<TaskHandlerComponent>(id);
	if(comp)
	{
		TaskHelper::cancel_task(*ents, comp->curr_task);
		comp->curr_task = Component::NO_ENTITY;
		for(const auto& task : comp->task_queue)
		{
			TaskHelper::cancel_task(*ents, task);
		}
		comp->task_queue.clear();
	}
	return 0;
}

int LuaInterface::lua_set_combat_target(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	CombatHelper::set_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_get_combat_target(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CombatHelper::get_target(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_range(lpp::Script::state L)
{
	tdt::real range = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	CombatHelper::set_range(*ents, id, range);
	return 0;
}

int LuaInterface::lua_get_range(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CombatHelper::get_range(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_dmg_range(lpp::Script::state L)
{
	tdt::uint max = GET_UINT(L, -1);
	tdt::uint min = GET_UINT(L, -2);
	tdt::uint id  = GET_UINT(L, -3);

	CombatHelper::set_dmg_range(*ents, id, min, max);
	return 0;
}

int LuaInterface::lua_get_dmg_range(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	tdt::uint min{}, max{};
	std::tie(min, max) = CombatHelper::get_dmg_range(*ents, id);
	lua_pushinteger(L, min);
	lua_pushinteger(L, max);
	return 2;
}

int LuaInterface::lua_get_dmg(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);
	tdt::uint min{}, max{};

	std::tie(min, max) = CombatHelper::get_dmg_range(*ents, id);
	auto res = CombatHelper::get_dmg(min, max);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_cooldown(lpp::Script::state L)
{
	tdt::real cd = GET_REAL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	CombatHelper::set_cooldown(*ents, id, cd);
	return 0;
}

int LuaInterface::lua_get_cooldown(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CombatHelper::get_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_atk_type(lpp::Script::state L)
{
	int atk_type = GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	CombatHelper::set_atk_type(*ents, id, (ATTACK_TYPE)atk_type);
	return 0;
}

int LuaInterface::lua_get_atk_type(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CombatHelper::get_atk_type(*ents, id);
	lua_pushnumber(L, (int)res);
	return 1;
}

int LuaInterface::lua_set_homing_source(lpp::Script::state L)
{
	tdt::uint source = GET_UINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	HomingHelper::set_source(*ents, id, source);
	return 0;
}

int LuaInterface::lua_get_homing_source(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = HomingHelper::get_source(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_homing_target(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	HomingHelper::set_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_get_homing_target(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = HomingHelper::get_target(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_homing_dmg(lpp::Script::state L)
{
	tdt::uint dmg = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	HomingHelper::set_dmg(*ents, id, dmg);
	return 0;
}

int LuaInterface::lua_get_homing_dmg(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = HomingHelper::get_dmg(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_entity(id, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_entity(id, true, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_entity(id, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_entity(id, false, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy_in_sight_thats_not(lpp::Script::state L)
{
	tdt::uint ignored = GET_UINT(L, -1);
	tdt::uint id      = GET_UINT(L, -2);

	auto res = lua_this->combat_system_->get_closest_entity_thats_not(id, ignored, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly_in_sight_thats_not(lpp::Script::state L)
{
	tdt::uint ignored = GET_UINT(L, -1);
	tdt::uint id      = GET_UINT(L, -2);

	auto res = lua_this->combat_system_->get_closest_entity_thats_not(id, ignored, true, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy_thats_not(lpp::Script::state L)
{
	tdt::uint ignored = GET_UINT(L, -1);
	tdt::uint id      = GET_UINT(L, -2);

	auto res = lua_this->combat_system_->get_closest_entity_thats_not(id, ignored, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly_thats_not(lpp::Script::state L)
{
	tdt::uint ignored = GET_UINT(L, -1);
	tdt::uint id      = GET_UINT(L, -2);

	auto res = lua_this->combat_system_->get_closest_entity_thats_not(id, ignored, false, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_in_sight(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);

	auto res = lua_this->combat_system_->in_sight(id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_run_away_from(lpp::Script::state L)
{
	tdt::uint min_node_count = GET_UINT(L, -1);
	tdt::uint from_id        = GET_UINT(L, -2);
	tdt::uint id             = GET_UINT(L, -3);

	lua_this->combat_system_->run_away_from(id, from_id, min_node_count);
	return 0;
}

int LuaInterface::lua_set_max_run_away_attempts(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->combat_system_->set_max_run_away_attempts(val);
	return 0;
}

int LuaInterface::lua_get_max_run_away_attempts(lpp::Script::state L)
{
	auto res = lua_this->combat_system_->get_max_run_away_attempts();

	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_apply_heal_to_entities_in_range(lpp::Script::state L)
{
	tdt::real range = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	lua_this->combat_system_->apply_heal_to_entities_in_range(id, range);
	return 0;
}

int LuaInterface::lua_apply_damage_to_entities_in_range(lpp::Script::state L)
{
	tdt::uint max   = GET_UINT(L, -1);
	tdt::uint min   = GET_UINT(L, -2);
	tdt::real range = GET_REAL(L, -3);
	tdt::uint id    = GET_UINT(L, -4);

	lua_this->combat_system_->apply_damage_to_entities_in_range(id, range, min, max);
	return 0;
}

int LuaInterface::lua_apply_slow_to_entities_in_range(lpp::Script::state L)
{
	tdt::real time  = GET_REAL(L, -1);
	tdt::real range = GET_REAL(L, -2);
	tdt::uint id    = GET_UINT(L, -3);

	lua_this->combat_system_->apply_slow_to_entities_in_range(id, range, time);
	return 0;
}

int LuaInterface::lua_apply_freeze_to_entities_in_range(lpp::Script::state L)
{
	tdt::real time  = GET_REAL(L, -1);
	tdt::real range = GET_REAL(L, -2);
	tdt::uint id    = GET_UINT(L, -3);

	lua_this->combat_system_->apply_freeze_to_entities_in_range(id, range, time);
	return 0;
}

int LuaInterface::lua_in_range(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);
	auto res = CombatHelper::in_range(*ents, id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_projectile_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	CombatHelper::set_projectile_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_get_projectile_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = CombatHelper::get_projectile_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_apply_slow_to(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	lua_this->combat_system_->apply_slow_to(id, val);
	return 0;
}

int LuaInterface::lua_apply_freeze_to(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	lua_this->combat_system_->apply_freeze_to(id, val);
	return 0;
}

int LuaInterface::lua_enemy_in_range(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->enemy_in_range(id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly_structure(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_structure(id, false, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy_structure(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_structure(id, false, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_friendly_structure_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_structure(id, true, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_closest_enemy_structure_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_structure(id, true, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_production_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	ProductionHelper::set_production_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_get_production_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = ProductionHelper::get_production_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_set_production_limit(lpp::Script::state L)
{
	tdt::uint limit = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	ProductionHelper::set_production_limit(*ents, id, limit);
	return 0;
}

int LuaInterface::lua_get_production_limit(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ProductionHelper::get_production_limit(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_production_cooldown(lpp::Script::state L)
{
	tdt::real cd = GET_REAL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	ProductionHelper::set_production_cooldown(*ents, id, cd);
	return 0;
}

int LuaInterface::lua_get_production_cooldown(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ProductionHelper::get_production_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_production_progress(lpp::Script::state L)
{
	tdt::real prog = GET_REAL(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	ProductionHelper::set_production_progress(*ents, id, prog);
	return 0;
}

int LuaInterface::lua_get_production_progress(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);
	
	auto res = ProductionHelper::get_production_progress(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_production_count(lpp::Script::state L)
{
	tdt::uint prog = GET_UINT(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	ProductionHelper::set_production_count(*ents, id, prog);
	return 0;
}

int LuaInterface::lua_get_production_count(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ProductionHelper::get_production_count(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_producer(lpp::Script::state L)
{
	tdt::uint producer = GET_UINT(L, -1);
	tdt::uint id       = GET_UINT(L, -2);

	ProductHelper::set_producer(*ents, id, producer);
	return 0;
}

int LuaInterface::lua_get_producer(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

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

int LuaInterface::lua_set_production_multiplier(lpp::Script::state L)
{
	tdt::real multiplier = GET_REAL(L, -1);

	lua_this->production_system_->set_time_multiplier(multiplier);
	return 0;
}

int LuaInterface::lua_get_production_multiplier(lpp::Script::state L)
{
	auto res = lua_this->production_system_->get_time_multiplier();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_double_production(lpp::Script::state L)
{
	tdt::uint added{};
	for(auto& ent : ents->get_component_container<ProductionComponent>())
	{
		if(FactionHelper::get_faction(*ents, ent.first) == FACTION::FRIENDLY)
		{
			added += ent.second.max_produced;
			ent.second.max_produced *= 2;
		}
	}

	Player::instance().add_max_unit(added);
	return 0;
}

int LuaInterface::lua_increase_production(lpp::Script::state L)
{
	tdt::uint added{};
	for(auto& ent : ents->get_component_container<ProductionComponent>())
	{
		if(FactionHelper::get_faction(*ents, ent.first) == FACTION::FRIENDLY)
		{
			++added;
			ent.second.max_produced += 1;
		}
	}

	Player::instance().add_max_unit(added);
	return 0;
}

int LuaInterface::lua_get_curr_time(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TimeHelper::get_curr_time(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_advance_curr_time(lpp::Script::state L)
{
	tdt::real time = GET_REAL(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	TimeHelper::advance_curr_time(*ents, id, time);
	return 0;
}

int LuaInterface::lua_max_curr_time(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	TimeHelper::max_curr_time(*ents, id);
	return 0;
}

int LuaInterface::lua_set_time_limit(lpp::Script::state L)
{
	tdt::real limit = GET_REAL(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	TimeHelper::set_time_limit(*ents, id, limit);
	return 0;
}

int LuaInterface::lua_get_time_limit(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TimeHelper::get_time_limit(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_timer_target(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	TimeHelper::set_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_get_timer_target(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TimeHelper::get_target(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_timer_type(lpp::Script::state L)
{
	TIME_EVENT type = (TIME_EVENT)luaL_checkinteger(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	TimeHelper::set_type(*ents, id, type);
	return 0;
}

int LuaInterface::lua_get_timer_type(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TimeHelper::get_type(*ents, id);
	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_advance_all_timers(lpp::Script::state L)
{
	tdt::real time = GET_REAL(L, -1);

	lua_this->time_system_->advance_all_timers(time);
	return 0;
}

int LuaInterface::lua_advance_all_timers_of_type(lpp::Script::state L)
{
	TIME_EVENT type = (TIME_EVENT)luaL_checkinteger(L, -1);
	tdt::real time  = GET_REAL(L, -2);

	lua_this->time_system_->advance_all_timers_of_type(time, type);
	return 0;
}

int LuaInterface::lua_set_timer_multiplier(lpp::Script::state L)
{
	tdt::real multiplier = GET_REAL(L, -1);

	lua_this->time_system_->set_time_multiplier(multiplier);
	return 0;
}

int LuaInterface::lua_get_timer_multiplier(lpp::Script::state L)
{
	auto res = lua_this->time_system_->get_time_multiplier();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_event_type(lpp::Script::state L)
{
	EVENT_TYPE type = (EVENT_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	EventHelper::set_event_type(*ents, id, type);
	return 0;
}

int LuaInterface::lua_get_event_type(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = EventHelper::get_event_type(*ents, id);
	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_set_event_target(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	EventHelper::set_target(*ents, id, target);
	return 0;
}

int LuaInterface::lua_get_event_target(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = EventHelper::get_target(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_event_radius(lpp::Script::state L)
{
	tdt::real radius = GET_REAL(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	EventHelper::set_radius(*ents, id, radius);
	return 0;
}

int LuaInterface::lua_get_event_radius(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = EventHelper::get_radius(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_event_active(lpp::Script::state L)
{
	bool active  = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	EventHelper::set_active(*ents, id, active);
	return 0;
}

int LuaInterface::lua_is_event_active(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = EventHelper::is_active(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_handler_of_event(lpp::Script::state L)
{
	tdt::uint handler = GET_UINT(L, -1);
	tdt::uint evt     = GET_UINT(L, -2);

	EventHelper::set_event_handler(*ents, evt, handler);
	return 0;
}

int LuaInterface::lua_get_handler_of_event(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = EventHelper::get_event_handler(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_event_handler(lpp::Script::state L)
{
	std::string handler = GET_STR(L, -1);
	tdt::uint id        = GET_UINT(L, -2);

	EventHandlerHelper::set_handler(*ents, id, handler);
	return 0;
}

int LuaInterface::lua_get_event_handler(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = EventHandlerHelper::get_handler(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_can_handle_event(lpp::Script::state L)
{
	EVENT_TYPE type = (EVENT_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	auto res = EventHandlerHelper::can_handle(*ents, id, type);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_add_possible_event(lpp::Script::state L)
{
	EVENT_TYPE type = (EVENT_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	EventHandlerHelper::add_possible_event(*ents, id, type);
	return 0;
}

int LuaInterface::lua_delete_possible_event(lpp::Script::state L)
{
	EVENT_TYPE type = (EVENT_TYPE)luaL_checkinteger(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	EventHandlerHelper::delete_possible_event(*ents, id, type);
	return 0;
}

int LuaInterface::lua_set_event_update_period(lpp::Script::state L)
{
	tdt::real t = GET_REAL(L, -1);

	lua_this->event_system_->set_update_period(t);
	return 0;
}

int LuaInterface::lua_get_event_update_period(lpp::Script::state L)
{
	auto res = lua_this->event_system_->get_update_period();
	lua_pushnumber(L, res);
	return 1;
}
int LuaInterface::lua_set_event_update_multiplier(lpp::Script::state L)
{
	tdt::real multiplier = GET_REAL(L, -1);

	lua_this->event_system_->set_update_time_multiplier(multiplier);
	return 0;
}

int LuaInterface::lua_get_event_update_multiplier(lpp::Script::state L)
{
	auto res = lua_this->event_system_->get_update_time_multiplier();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_set_destructor_blueprint(lpp::Script::state L)
{
	std::string  blueprint = GET_STR(L, -1);
	tdt::uint id           = GET_UINT(L, -2);

	DestructorHelper::set_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_get_destructor_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = DestructorHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_set_curr_gold(lpp::Script::state L)
{
	tdt::uint gold = GET_UINT(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	GoldHelper::set_curr_gold(*ents, id, gold);
	return 0;
}

int LuaInterface::lua_get_curr_gold(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GoldHelper::get_curr_gold(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_max_gold(lpp::Script::state L)
{
	tdt::uint gold = GET_UINT(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	GoldHelper::set_max_gold(*ents, id, gold);
	return 0;
}

int LuaInterface::lua_get_max_gold(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GoldHelper::get_max_gold(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_gold(lpp::Script::state L)
{
	tdt::uint gold = GET_UINT(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	GoldHelper::add_gold(*ents, id, gold);
	return 0;
}

int LuaInterface::lua_sub_gold(lpp::Script::state L)
{
	tdt::uint gold = GET_UINT(L, -1);
	tdt::uint id   = GET_UINT(L, -2);

	GoldHelper::sub_gold(*ents, id, gold);
	return 0;
}

int LuaInterface::lua_transfer_all_gold(lpp::Script::state L)
{
	tdt::uint id2 = GET_UINT(L, -1);
	tdt::uint id1 = GET_UINT(L, -2);

	GoldHelper::transfer_all_gold(*ents, id1, id2);
	return 0;
}

int LuaInterface::lua_get_closest_gold_deposit(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_deposit(id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_closest_gold_deposit_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_deposit(id, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_gold_full(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = GoldHelper::gold_full(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_is_gold_vault(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ents->has_component<StructureComponent>(id) &&
		       ents->has_component<GoldComponent>(id) &&
			   FactionHelper::get_faction(*ents, id) == FACTION::FRIENDLY;
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_closest_gold_vault(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_vault(id, false, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_closest_gold_vault_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_vault(id, true, false);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_closest_free_gold_vault(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_vault(id, false, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_closest_free_gold_vault_in_sight(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_vault(id, true, true);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_exists_free_gold_vault(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = lua_this->combat_system_->get_closest_gold_vault(id, true, true);
	lua_pushinteger(L, res != Component::NO_ENTITY);
	return 1;
}

int LuaInterface::lua_set_gui_visible(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	GUI::instance().set_visible(val);
	return 0;
}

int LuaInterface::lua_is_gui_visible(lpp::Script::state L)
{
	auto res = GUI::instance().is_visible();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_window_visible(lpp::Script::state L)
{
	bool val        = GET_BOOL(L, -1);
	std::string win = GET_STR(L, -2);

	GUI::instance().set_visible(win, val);
	return 0;
}

int LuaInterface::lua_is_window_visible(lpp::Script::state L)
{
	std::string win = GET_STR(L, -1);

	auto res = GUI::instance().is_visible(win);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_log(lpp::Script::state L)
{
	GUI::instance().get_log().clear();
	return 0;
}

int LuaInterface::lua_print_to_log(lpp::Script::state L)
{
	std::string msg = GET_STR(L, -1);

	GUI::instance().get_log().print(msg);
	return 0;
}

int LuaInterface::lua_set_tracked_entity(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	GUI::instance().get_tracker().set_tracked_entity(id, *ents);
	return 0;
}

int LuaInterface::lua_get_tracked_entity(lpp::Script::state L)
{
	auto res = GUI::instance().get_tracker().get_tracked_entity();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_update_tracking(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	std::string nam = GET_STR(L, -2);

	GUI::instance().get_tracker().update_tracking(nam, val);
	return 0;
}

int LuaInterface::lua_clear_entity_tracker(lpp::Script::state L)
{
	GUI::instance().get_tracker().clear();
	return 0;
}

int LuaInterface::lua_set_log_history(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	GUI::instance().get_log().set_history(val);
	return 0;
}

int LuaInterface::lua_get_log_history(lpp::Script::state L)
{
	auto res = GUI::instance().get_log().get_history();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_show_save_dialog(lpp::Script::state L)
{
	GUI::instance().show_load_save_dialog("SAVE");
	return 0;
}

int LuaInterface::lua_show_load_dialog(lpp::Script::state L)
{
	GUI::instance().show_load_save_dialog("LOAD");
	return 0;
}

int LuaInterface::lua_console_scroll_down(lpp::Script::state L)
{
	GUI::instance().get_console().scroll_down();
	return 0;
}

int LuaInterface::lua_set_console_history(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	GUI::instance().get_console().set_history(val);
	return 0;
}

int LuaInterface::lua_get_console_history(lpp::Script::state L)
{
	auto res = GUI::instance().get_console().get_history();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_console_visible(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	GUI::instance().get_console().set_visible(val);
	return 0;
}

int LuaInterface::lua_is_console_visible(lpp::Script::state L)
{
	auto res = GUI::instance().get_console().is_visible();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_clear_console(lpp::Script::state L)
{
	GUI::instance().get_console().clear();
	return 0;
}

int LuaInterface::lua_set_builder_visible(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	GUI::instance().get_builder().set_visible(val);
	return 0;
}

int LuaInterface::lua_is_builder_visible(lpp::Script::state L)
{
	auto res = GUI::instance().get_builder().is_visible();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_register_building(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);

	GUI::instance().get_builder().register_building(val);
	return 0;
}

int LuaInterface::lua_research_show(lpp::Script::state L)
{
	tdt::uint j = GET_UINT(L, -1);
	tdt::uint i = GET_UINT(L, -2);

	GUI::instance().get_research().show(i, j);
	return 0;
}

int LuaInterface::lua_free_research(lpp::Script::state)
{
	GUI::instance().get_research().free_research();
	return 0;
}

int LuaInterface::lua_research_all(lpp::Script::state)
{
	GUI::instance().get_research().research_all();
	return 0;
}

int LuaInterface::lua_dummy_unlock(lpp::Script::state L)
{
	tdt::uint j = GET_UINT(L, -1);
	tdt::uint i = GET_UINT(L, -2);

	GUI::instance().get_research().dummy_unlock(i, j);
	return 0;
}

int LuaInterface::lua_research_reset(lpp::Script::state L)
{
	GUI::instance().get_research().reset_research();
	return 0;
}

int LuaInterface::lua_add_player_gold(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	Player::instance().add_gold(val);
	return 0;
}

int LuaInterface::lua_sub_player_gold(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	auto res = Player::instance().sub_gold(val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_add_player_mana(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	Player::instance().add_mana(val);
	return 0;
}

int LuaInterface::lua_sub_player_mana(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	auto res = Player::instance().sub_mana(val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_add_player_max_units(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	Player::instance().add_max_unit(val);
	return 0;
}

int LuaInterface::lua_sub_player_max_units(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	auto res = Player::instance().sub_max_unit(val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_add_player_curr_units(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	Player::instance().add_curr_unit(val);
	return 0;
}

int LuaInterface::lua_sub_player_curr_units(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	auto res = Player::instance().sub_curr_unit(val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_player_gold(lpp::Script::state L)
{
	auto res = Player::instance().get_gold();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_get_player_mana(lpp::Script::state L)
{
	auto res = Player::instance().get_mana();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_player_reset(lpp::Script::state L)
{
	Player::instance().reset();
	return 0;
}

int LuaInterface::lua_nulify_player_stats(lpp::Script::state L)
{
	Player::instance().nulify_all_stats();
	return 0;
}

int LuaInterface::lua_add_player_max_mana(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	Player::instance().add_max_mana(val);
	return 0;
}

int LuaInterface::lua_sub_player_max_mana(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	auto res = Player::instance().sub_max_mana(val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_player_max_mana(lpp::Script::state L)
{
	auto res = Player::instance().get_max_mana();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_add_player_mana_regen(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	Player::instance().add_mana_regen(val);
	return 0;
}

int LuaInterface::lua_sub_player_mana_regen(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	auto res = Player::instance().sub_mana_regen(val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_get_player_mana_regen(lpp::Script::state L)
{
	auto res = Player::instance().get_mana_regen();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_set_price(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	PriceHelper::set_price(*ents, id, val);
	return 0;
}

int LuaInterface::lua_get_price(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = PriceHelper::get_price(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_register_spell(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);

	GUI::instance().get_spell_casting().register_spell(val);
	return 0;
}

int LuaInterface::lua_spellcaster_set_type(lpp::Script::state L)
{
	SPELL_TYPE val = (SPELL_TYPE)GET_SINT(L, -1);

	lua_this->spell_caster_->set_spell_type(val);
	return 0;
}

int LuaInterface::lua_spellcaster_get_type(lpp::Script::state L)
{
	auto res = lua_this->spell_caster_->get_spell_type();
	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_spellcaster_set_spell(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);

	lua_this->spell_caster_->set_spell(val);
	return 0;
}

int LuaInterface::lua_spellcaster_get_spell(lpp::Script::state L)
{
	auto& res = lua_this->spell_caster_->get_spell();
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_spellcaster_get_last_type(lpp::Script::state L)
{
	auto res = lua_this->spell_caster_->get_last_spell_type();
	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_spellcaster_get_last_spell(lpp::Script::state L)
{
	auto& res = lua_this->spell_caster_->get_last_spell();
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_spellcaster_set_last_spell_id(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->spell_caster_->set_last_spell_id(val);
	return 0;
}

int LuaInterface::lua_spellcaster_get_last_spell_id(lpp::Script::state L)
{
	auto res = lua_this->spell_caster_->get_last_spell_id();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_spellcaster_is_casting(lpp::Script::state L)
{
	auto res = lua_this->spell_caster_->is_casting();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_spellcaster_stop_casting(lpp::Script::state L)
{
	lua_this->spell_caster_->stop_casting();
	return 0;
}

int LuaInterface::lua_align_set_material(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint state = GET_UINT(L, -2);
	tdt::uint id    = GET_UINT(L, -3);

	AlignHelper::set_material(*ents, id, state, val);
	return 0;
}

int LuaInterface::lua_align_get_material(lpp::Script::state L)
{
	tdt::uint state = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	const std::string& res = AlignHelper::get_material(*ents, id, state);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_align_set_mesh(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint state = GET_UINT(L, -2);
	tdt::uint id    = GET_UINT(L, -3);

	AlignHelper::set_mesh(*ents, id, state, val);
	return 0;
}

int LuaInterface::lua_align_get_mesh(lpp::Script::state L)
{
	tdt::uint state = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	const std::string& res = AlignHelper::get_mesh(*ents, id, state);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_align_set_position_offset(lpp::Script::state L)
{
	tdt::real z     = GET_REAL(L, -1);
	tdt::real y     = GET_REAL(L, -2);
	tdt::real x     = GET_REAL(L, -3);
	tdt::uint state = GET_UINT(L, -4);
	tdt::uint id    = GET_UINT(L, -5);

	AlignHelper::set_position_offset(*ents, id, state, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_align_get_position_offset(lpp::Script::state L)
{
	tdt::uint state = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	const Ogre::Vector3& res = AlignHelper::get_position_offset(*ents, id, state);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_align_set_scale(lpp::Script::state L)
{
	tdt::real z     = GET_REAL(L, -1);
	tdt::real y     = GET_REAL(L, -2);
	tdt::real x     = GET_REAL(L, -3);
	tdt::uint state = GET_UINT(L, -4);
	tdt::uint id    = GET_UINT(L, -5);

	AlignHelper::set_scale(*ents, id, state, Ogre::Vector3{x, y, z});
	return 0;
}

int LuaInterface::lua_align_get_scale(lpp::Script::state L)
{
	tdt::uint state = GET_UINT(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	const Ogre::Vector3& res = AlignHelper::get_scale(*ents, id, state);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_mana_crystal_set_cap(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ManaCrystalHelper::set_capacity(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_crystal_get_cap(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ManaCrystalHelper::get_capacity(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_mana_crystal_set_regen(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ManaCrystalHelper::set_regen(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_crystal_get_regen(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ManaCrystalHelper::get_regen(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_on_hit_set_blueprint(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	OnHitHelper::set_blueprint(*ents, id, val);
	return 0;
}

int LuaInterface::lua_on_hit_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = OnHitHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_on_hit_call(lpp::Script::state L)
{
	tdt::uint hitter = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	OnHitHelper::call(*ents, id, hitter);
	return 0;
}

int LuaInterface::lua_on_hit_set_cooldown(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	OnHitHelper::set_cooldown(*ents, id, val);
	return 0;
}

int LuaInterface::lua_on_hit_get_cooldown(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = OnHitHelper::get_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_constructor_set_blueprint(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	ConstructorHelper::set_blueprint(*ents, id, val);
	return 0;
}

int LuaInterface::lua_constructor_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = ConstructorHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_constructor_call(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	ConstructorHelper::call(*ents, id);
	return 0;
}

int LuaInterface::lua_trigger_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	TriggerHelper::set_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_trigger_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = TriggerHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_trigger_set_linked_entity(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	TriggerHelper::set_linked_entity(*ents, id, target);
	return 0;
}

int LuaInterface::lua_trigger_get_linked_entity(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TriggerHelper::get_linked_entity(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_trigger_set_cooldown(lpp::Script::state L)
{
	tdt::real cd = GET_REAL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	TriggerHelper::set_cooldown(*ents, id, cd);
	return 0;
}

int LuaInterface::lua_trigger_get_cooldown(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TriggerHelper::get_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_trigger_trigger(lpp::Script::state L)
{
	tdt::uint target = GET_UINT(L, -1);
	tdt::uint id     = GET_UINT(L, -2);

	TriggerHelper::trigger(*ents, id, target);
	return 0;
}

int LuaInterface::lua_trigger_set_check_period(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);

	lua_this->trigger_system_->set_check_period(val);
	return 0;
}

int LuaInterface::lua_trigger_get_check_period(lpp::Script::state L)
{
	auto res = lua_this->trigger_system_->get_check_period();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_trigger_can_be_triggered_by(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	auto res = TriggerHelper::can_be_triggered_by(*ents, id, val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_trigger_reset_timer(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	TriggerHelper::reset_timer(*ents, id);
	return 0;
}

int LuaInterface::lua_trigger_set_radius(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	TriggerHelper::set_radius(*ents, id, val);
	return 0;
}

int LuaInterface::lua_trigger_get_radius(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = TriggerHelper::get_radius(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	UpgradeHelper::set_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_upgrade_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = UpgradeHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_upgrade_set_experience(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	auto res = UpgradeHelper::set_experience(*ents, id, val);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_get_experience(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = UpgradeHelper::get_experience(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_add_experience(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	auto res = UpgradeHelper::add_experience(*ents, id, val);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_set_exp_needed(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	UpgradeHelper::set_exp_needed(*ents, id, val);
	return 0;
}

int LuaInterface::lua_upgrade_get_exp_needed(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = UpgradeHelper::get_exp_needed(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_set_level(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	UpgradeHelper::set_level(*ents, id, val);
	return 0;
}

int LuaInterface::lua_upgrade_get_level(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = UpgradeHelper::get_level(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_set_level_cap(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	UpgradeHelper::set_level_cap(*ents, id, val);
	return 0;
}

int LuaInterface::lua_upgrade_get_level_cap(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = UpgradeHelper::get_level_cap(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_can_level_up(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = UpgradeHelper::can_level_up(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_upgrade_upgrade(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	UpgradeHelper::upgrade(*ents, id);
	return 0;
}

int LuaInterface::lua_upgrade_all_level_up(lpp::Script::state L)
{
	for(auto& ent : ents->get_component_container<UpgradeComponent>())
		ent.second.experience = ent.second.exp_needed;

	return 0;
}

int LuaInterface::lua_notification_set_cooldown(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	NotificationHelper::set_cooldown(*ents, id, val);
	return 0;
}

int LuaInterface::lua_notification_get_cooldown(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = NotificationHelper::get_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_notification_reset(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	NotificationHelper::reset(*ents, id);
	return 0;
}

int LuaInterface::lua_notification_notify(lpp::Script::state L)
{
	std::string msg = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	auto res = NotificationHelper::notify(*ents, id, msg);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_notification_get_curr_time(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = NotificationHelper::get_curr_time(*ents, id);
	lua_pushnumber(L, -1);
	return 1;
}

int LuaInterface::lua_notification_advance_curr_time(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	NotificationHelper::advance_curr_time(*ents, id, val);
	return 0;
}

int LuaInterface::lua_explosion_set_delta(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ExplosionHelper::set_delta(*ents, id, val);
	return 0;
}

int LuaInterface::lua_explosion_get_delta(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ExplosionHelper::get_delta(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_explosion_set_max_radius(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ExplosionHelper::set_max_radius(*ents, id, val);
	return 0;
}

int LuaInterface::lua_explosion_get_max_radius(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ExplosionHelper::get_max_radius(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_explosion_get_curr_radius(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ExplosionHelper::get_curr_radius(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_explosion_increase_curr_radius(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ExplosionHelper::increase_curr_radius(*ents, id, val);
	return 0;
}

int LuaInterface::lua_lls_set_max_time(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	LimitedLifeSpanHelper::set_max_time(*ents, id, val);
	return 0;
}

int LuaInterface::lua_lls_get_max_time(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = LimitedLifeSpanHelper::get_max_time(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_lls_get_curr_time(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = LimitedLifeSpanHelper::get_curr_time(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_lls_advance_curr_time(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	LimitedLifeSpanHelper::advance_curr_time(*ents, id, val);
	return 0;
}

int LuaInterface::lua_name_set(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	NameHelper::set_name(*ents, id, val);
	return 0;
}

int LuaInterface::lua_name_get(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = NameHelper::get_name(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_exp_val_set(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ExperienceValueHelper::set(*ents, id, val);
	return 0;
}

int LuaInterface::lua_exp_val_get(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ExperienceValueHelper::get(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_exp_val_inc(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ExperienceValueHelper::increase(*ents, id, val);
	return 0;
}

int LuaInterface::lua_exp_val_dec(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ExperienceValueHelper::decrease(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_set_regen_period(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);

	lua_this->mana_spell_system_->set_regen_period(val);
	return 0;
}

int LuaInterface::lua_mana_get_regen_period(lpp::Script::state L)
{
	auto res = lua_this->mana_spell_system_->get_regen_period();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_wave_next_wave(lpp::Script::state L)
{
	lua_this->wave_system_->next_wave();
	return 0;
}

int LuaInterface::lua_wave_advance_countdown(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->wave_system_->advance_wave_countdown(val);
	return 0;
}

int LuaInterface::lua_wave_entity_died(lpp::Script::state L)
{
	lua_this->wave_system_->wave_entity_died();
	return 0;
}

int LuaInterface::lua_wave_start(lpp::Script::state L)
{
	lua_this->wave_system_->start();
	return 0;
}

int LuaInterface::lua_wave_pause(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	lua_this->wave_system_->pause(val);
	return 0;
}

int LuaInterface::lua_wave_set_entity_total(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->wave_system_->set_entity_total(val);
	return 0;
}

int LuaInterface::lua_wave_get_entity_total(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_entity_total();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_wave_set_wave_count(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->wave_system_->set_wave_count(val);
	return 0;
}

int LuaInterface::lua_wave_get_wave_count(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_wave_count();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_wave_add_spawn_node(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->wave_system_->add_spawn_node(val);
	return 0;
}

int LuaInterface::lua_wave_clear_spawn_nodes(lpp::Script::state L)
{
	lua_this->wave_system_->clear_spawn_nodes();
	return 0;
}

int LuaInterface::lua_wave_set_spawn_cooldown(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);

	lua_this->wave_system_->set_spawn_cooldown(val);
	return 0;
}

int LuaInterface::lua_wave_get_spawn_cooldown(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_spawn_cooldown();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_wave_add_entity_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);

	lua_this->wave_system_->add_entity_blueprint(blueprint);
	return 0;
}

int LuaInterface::lua_wave_set_table(lpp::Script::state L)
{
	std::string table = GET_STR(L, -1);

	lua_this->wave_system_->set_wave_table(table);
	return 0;
}

int LuaInterface::lua_wave_get_table(lpp::Script::state L)
{
	auto& res = lua_this->wave_system_->get_wave_table();
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_wave_set_curr_wave_number(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	
	lua_this->wave_system_->set_curr_wave_number(val);
	return 0;
}

int LuaInterface::lua_wave_get_curr_wave_number(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_curr_wave_number();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_wave_set_countdown(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->wave_system_->set_countdown_value(val);
	return 0;
}

int LuaInterface::lua_wave_get_countdown(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_countdown_value();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_wave_set_state(lpp::Script::state L)
{
	int val = GET_SINT(L, -1);

	lua_this->wave_system_->set_state((WAVE_STATE)val);
	return 0;
}

int LuaInterface::lua_wave_get_state(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_state();
	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_wave_update_label_text(lpp::Script::state L)
{
	lua_this->wave_system_->update_label_text();
	return 0;
}

int LuaInterface::lua_wave_set_spawn_timer(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);

	lua_this->wave_system_->set_spawn_timer(val);
	return 0;
}

int LuaInterface::lua_wave_get_spawn_timer(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_spawn_timer();
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_wave_set_wave_entities(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);

	lua_this->wave_system_->set_wave_entities(val);
	return 0;
}

int LuaInterface::lua_wave_get_wave_entities(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_wave_entities();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_wave_set_entities_spawned(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	
	lua_this->wave_system_->set_entities_spawned(val);
	return 0;
}

int LuaInterface::lua_wave_get_entities_spawned(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_entities_spawned();
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_wave_clear_entity_blueprints(lpp::Script::state L)
{
	lua_this->wave_system_->clear_entity_blueprints();
	return 0;
}

int LuaInterface::lua_wave_list(lpp::Script::state L)
{
	auto& console = GUI::instance().get_console();
	for(const auto& ent : lua_this->wave_system_->get_entity_blueprints())
		console.print_text(ent, Console::ORANGE_TEXT);
	return 0;
}

int LuaInterface::lua_wave_set_endless_mode(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	lua_this->wave_system_->set_endless_mode(val);
	return 0;
}

int LuaInterface::lua_wave_get_endless_mode(lpp::Script::state L)
{
	auto res = lua_this->wave_system_->get_endless_mode();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_wave_turn_endless_on(lpp::Script::state L)
{
	lua_this->wave_system_->set_endless_mode(true);
	return 0;
}

int LuaInterface::lua_msg_to_plr_show(lpp::Script::state L)
{
	std::string no  = GET_STR(L, -1);
	std::string yes = GET_STR(L, -2);
	std::string ok  = GET_STR(L, -3);
	std::string msg = GET_STR(L, -4);

	GUI::instance().get_message().show(msg, ok, yes, no);
	return 0;
}

int LuaInterface::lua_msg_to_plr_show_ok(lpp::Script::state L)
{
	std::string ok  = GET_STR(L, -1);
	std::string msg = GET_STR(L, -2);

	GUI::instance().get_message().show(msg, ok);
	return 0;
}

int LuaInterface::lua_msg_to_plr_show_yes_no(lpp::Script::state L)
{
	std::string no  = GET_STR(L, -1);
	std::string yes = GET_STR(L, -2);
	std::string msg = GET_STR(L, -3);

	GUI::instance().get_message().show(msg, "NONE", yes, no);
	return 0;
}

int LuaInterface::lua_msg_set_butt_label(lpp::Script::state L)
{
	std::string val  = GET_STR(L, -1);
	std::string butt = GET_STR(L, -2);

	GUI::instance().get_message().set_butt_label(butt, val);
	return 0;
}

int LuaInterface::lua_msg_reset_butt_labels(lpp::Script::state L)
{
	GUI::instance().get_message().reset_butt_labels();
	return 0;
}

int LuaInterface::lua_mana_add(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ManaHelper::add_mana(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_sub(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	auto res = ManaHelper::sub_mana(*ents, id, val);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_mana_set(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ManaHelper::set_mana(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_get(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ManaHelper::get_mana(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_mana_set_max(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ManaHelper::set_max_mana(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_get_max(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ManaHelper::get_max_mana(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_mana_set_regen(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	ManaHelper::set_regen(*ents, id, val);
	return 0;
}

int LuaInterface::lua_mana_get_regen(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ManaHelper::get_regen(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_ent_spell_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	SpellHelper::set_blueprint(*ents, id, blueprint);
	return 0;
}

int LuaInterface::lua_ent_spell_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = SpellHelper::get_blueprint(*ents, id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_ent_spell_set_cooldown(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	SpellHelper::set_cooldown(*ents, id, val);
	return 0;
}

int LuaInterface::lua_ent_spell_get_cooldown(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = SpellHelper::get_cooldown(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_ent_spell_advance_curr_time(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	SpellHelper::advance_curr_time(*ents, id, val);
	return 0;
}

int LuaInterface::lua_ent_spell_set_curr_time(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	SpellHelper::set_curr_time(*ents, id, val);
	return 0;
}

int LuaInterface::lua_ent_spell_get_curr_time(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = SpellHelper::get_curr_time(*ents, id);
	lua_pushnumber(L, res);
	return 1;
}

int LuaInterface::lua_ent_spell_cast(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	SpellHelper::cast(*ents, id);
	return 0;
}

int LuaInterface::lua_light_set_visible(lpp::Script::state L)
{
	bool val     = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	LightHelper::set_visible(*ents, id, val);
	return 0;
}

int LuaInterface::lua_light_toggle_visible(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	LightHelper::toggle_visible(*ents, id);
	return 0;
}

int LuaInterface::lua_light_is_visible(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = LightHelper::is_visible(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_light_init(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	LightHelper::init(*ents, id);
	return 0;
}

int LuaInterface::lua_command_set(lpp::Script::state L)
{
	bool val          = GET_BOOL(L, -1);
	COMMAND_TYPE comm = (COMMAND_TYPE)GET_SINT(L, -2);
	tdt::uint id      = GET_UINT(L, -3);

	CommandHelper::set_command(*ents, id, comm, val);
	return 0;
}

int LuaInterface::lua_command_test(lpp::Script::state L)
{
	COMMAND_TYPE comm = (COMMAND_TYPE)GET_SINT(L, -1);
	tdt::uint id      = GET_UINT(L, -2);

	auto res = CommandHelper::test_command(*ents, id, comm);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_counter_increment(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CounterHelper::increment(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_counter_decrement(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CounterHelper::decrement(*ents, id);
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_counter_set_curr_value(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	CounterHelper::set_curr_value(*ents, id, val);
	return 0;
}

int LuaInterface::lua_counter_get_curr_value(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CounterHelper::get_curr_value(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_counter_set_max_value(lpp::Script::state L)
{
	tdt::uint val = GET_UINT(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	CounterHelper::set_max_value(*ents, id, val);
	return 0;
}

int LuaInterface::lua_counter_get_max_value(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = CounterHelper::get_max_value(*ents, id);
	lua_pushinteger(L, res);
	return 1;
}

int LuaInterface::lua_animation_play(lpp::Script::state L)
{
	bool stop    = GET_BOOL(L, -1);
	bool loop    = GET_BOOL(L, -2);
	int type     = GET_SINT(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	AnimationHelper::play(*ents, id, (ANIMATION_TYPE::VAL)type, loop, stop);

	return 0;
}

int LuaInterface::lua_animation_stop(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	AnimationHelper::stop(*ents, id);

	return 0;
}

int LuaInterface::lua_animation_add_possible(lpp::Script::state L)
{
	int type     = GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	AnimationHelper::add_possible(*ents, id, (ANIMATION_TYPE::VAL)type);

	return 0;
}

int LuaInterface::lua_animation_delete_possible(lpp::Script::state L)
{
	int type     = GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	AnimationHelper::delete_possible(*ents, id, (ANIMATION_TYPE::VAL)type);

	return 0;
}

int LuaInterface::lua_animation_is_possible(lpp::Script::state L)
{
	int type     = GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	auto res = AnimationHelper::is_possible(*ents, id, (ANIMATION_TYPE::VAL)type);

	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_animation_set_stop(lpp::Script::state L)
{
	bool val     = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	AnimationHelper::set_stop_current_animation(*ents, id, val);
	
	return 0;
}

int LuaInterface::lua_animation_get_stop(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = AnimationHelper::get_stop_current_animation(*ents, id);

	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_selection_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = GET_STR(L, -1);
	tdt::uint id          = GET_UINT(L, -2);

	SelectionHelper::set_blueprint(*ents, id, blueprint);

	return 0;
}

int LuaInterface::lua_selection_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = SelectionHelper::get_blueprint(*ents, id);

	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_selection_set_material(lpp::Script::state L)
{
	std::string material = GET_STR(L, -1);
	tdt::uint id         = GET_UINT(L, -2);

	SelectionHelper::set_material(*ents, id, material);

	return 0;
}

int LuaInterface::lua_selection_get_material(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = SelectionHelper::get_material(*ents, id);

	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_selection_select(lpp::Script::state L)
{
	bool first   = GET_BOOL(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	auto res = SelectionHelper::select(*ents, id, first);

	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_selection_deselect(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = SelectionHelper::deselect(*ents, id);

	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_selection_set_scale(lpp::Script::state L)
{
	tdt::real z  = GET_REAL(L, -1);
	tdt::real y  = GET_REAL(L, -2);
	tdt::real x  = GET_REAL(L, -3);
	tdt::uint id = GET_UINT(L, -4);

	SelectionHelper::set_scale(*ents, id, Ogre::Vector3{x, y, z});

	return 0;
}

int LuaInterface::lua_selection_get_scale(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = SelectionHelper::get_scale(*ents, id);

	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int LuaInterface::lua_selection_set_marker_type(lpp::Script::state L)
{
	auto val     = (SELECTION_MARKER_TYPE)GET_SINT(L, -1);
	tdt::uint id = GET_UINT(L, -2);

	SelectionHelper::set_marker_type(*ents, id, val);

	return 0;
}

int LuaInterface::lua_selection_get_marker_type(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = SelectionHelper::get_marker_type(*ents, id);

	lua_pushinteger(L, (int)res);
	return 1;
}

int LuaInterface::lua_selection_set_rotation(lpp::Script::state L)
{
	tdt::real val = GET_REAL(L, -1);
	tdt::uint id  = GET_UINT(L, -2);

	SelectionHelper::set_rotation(*ents, id, Ogre::Degree{val});

	return 0;
}

int LuaInterface::lua_selection_get_rotation(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = SelectionHelper::get_rotation(*ents, id);

	lua_pushnumber(L, res.valueDegrees());
	return 1;
}

int LuaInterface::lua_activation_set_blueprint(lpp::Script::state L)
{
	std::string val = GET_STR(L, -1);
	tdt::uint id    = GET_UINT(L, -2);

	ActivationHelper::set_blueprint(*ents, id, val);

	return 0;
}

int LuaInterface::lua_activation_get_blueprint(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto& res = ActivationHelper::get_blueprint(*ents, id);

	lua_pushstring(L, res.c_str());
	return 1;
}

int LuaInterface::lua_activation_activate(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	ActivationHelper::activate(*ents, id);

	return 0;
}

int LuaInterface::lua_activation_deactivate(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	ActivationHelper::deactivate(*ents, id);

	return 0;
}

int LuaInterface::lua_activation_is_activated(lpp::Script::state L)
{
	tdt::uint id = GET_UINT(L, -1);

	auto res = ActivationHelper::is_activated(*ents, id);
	
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_tracker_visible(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	GUI::instance().get_tracker().set_visible(val);
	return 0;
}

int LuaInterface::lua_is_tracker_visible(lpp::Script::state L)
{
	auto res = GUI::instance().get_tracker().is_visible();
	lua_pushboolean(L, res);
	return 1;
}

int LuaInterface::lua_set_log_visible(lpp::Script::state L)
{
	bool val = GET_BOOL(L, -1);

	GUI::instance().get_log().set_visible(val);
	return 0;
}

int LuaInterface::lua_is_log_visible(lpp::Script::state L)
{
	auto res = GUI::instance().get_log().is_visible();
	lua_pushboolean(L, res);
	return 1;
}
#pragma endregion