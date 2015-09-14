game = game or {}

-- GAME CONFIGURATION
game.config = {
	-- GENERAL
	script_directory = "scripts",

	-- TIME PERIODS & MULTIPLIERS
	ai_update_period = 0.5,
	production_multiplier = 1.0,
	timer_multiplier = 1.0,
	event_update_multiplier = 1.0
}

-- NOTE: IT'S INADVISED TO CHANGE THE FOLLOWING CODE!
game.set_update_period(game.config.ai_update_period)
game.set_production_multiplier(game.config.production_multiplier)
game.set_timer_multiplier(game.config.timer_multiplier)
game.set_event_update_multiplier(game.config.event_update_multiplier)

-- Helper commands executed on startup:
game.toggle_camera_free_mode()
game.create_grid_graphics()
