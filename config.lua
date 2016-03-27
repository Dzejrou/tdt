-------------------------------------------------------------------------------
-- GAME CONFIGURATION ---------------------------------------------------------
-------------------------------------------------------------------------------

game.config = {
	-- GENERAL
	script_directories = { "scripts" },

	-- TIME PERIODS & MULTIPLIERS
	ai_update_period = 0.5,
	graphics_update_period = 0.1,
	production_multiplier = 1.0,
	timer_multiplier = 1.0,
	event_update_multiplier = 1.0,
	max_run_away_attempts = 50,
	trigger_check_period = 1.0,
	mana_regen_period = 5.0,
	default_wave_table = "game.wave.wave_test",
	console_hitory = 500,
	log_history = 50,

	-- TABLE NAMES
	default_wall_table = "basic_wall",
	default_gold_table = "gold_deposit",
	default_border_table = "indestructible_wall",
	default_walkway_table = "walkway",
	default_light_table = "light_crystal",
	default_throne_table = "dungeon_throne"
}
