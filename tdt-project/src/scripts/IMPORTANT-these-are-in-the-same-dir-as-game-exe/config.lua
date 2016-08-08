-------------------------------------------------------------------------------
-- GAME CONFIGURATION ---------------------------------------------------------
-------------------------------------------------------------------------------

game.config = {
	-- GENERAL

	-- Scripting modules that will be loaded by the game, each of these
	-- are directories located in the root directory of the game and must
	-- contain a file names "core.lua" which will be executed.
	script_directories = { "scripts" },

	-- TIME PERIODS & MULTIPLIERS
    
	-- Time between AI function calls in seconds.
	ai_update_period = 0.5,

	-- Time between graphics updates, e.g. explosion expansion, in seconds.
	graphics_update_period = 0.1,

	-- A multiplicative modifier of the production timer.
	production_multiplier = 1.0,

	-- A multiplicative modifier of the TimeComponent, OnHitComponent,
	-- TriggerComponent, NotificationComponent and LimitedLifeSpanComponent
	-- timers.
	timer_multiplier = 1.0,

	-- A multiplicative modifier of the cooldown timer of the event system
	-- updates (i.e. persistent events are handler x times more often, where
	-- x is the value of this variable).
	event_update_multiplier = 1.0,

	-- Maximum amount of attempts to find a path when running away from
	-- an enemy, if this is reached, the entity that tries to run away
	-- assumes that no path exists and stands still.
	max_run_away_attempts = 50,

	-- Time between two consecutive checks for targets by triggers, e.g.
	-- traps checking for an entity stepping in them.
	trigger_check_period = 1.0,

	-- Time between mana regeneration applications.
	mana_regen_period = 5.0,

	-- Default enemy wave system definition table used in the game.
	default_wave_table = "game.wave.wave_test",

	-- Amount of lines kept in the dev console history.
	console_hitory = 500,

	-- Amount of lines kept in the game log history.
	log_history = 50,

	-- TABLE NAMES
	-- These are used by the default level generator when it places
	-- blocks in the level. E.g. the entity stored in default_wall_table
	-- is placed whenever the level generator tries to place a wall.
	default_wall_table = "basic_wall",
	default_gold_table = "gold_deposit",
	default_border_table = "indestructible_wall",
	default_walkway_table = "walkway",
	default_light_table = "light_crystal",
	default_throne_table = "dungeon_throne",
	default_vault_table = "gold_vault",
	default_mine_table = "mine",

	-- If true, the game will offer the testing mode button in the
	-- main menu
	testing_mode = true
}
