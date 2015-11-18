-------------------------------------------------------------------------------
-- GAME INITIALIZATION --------------------------------------------------------
-- NOTE: IT'S INADVISED TO CHANGE THE FOLLOWING CODE! -------------------------
-------------------------------------------------------------------------------
require("config")

-- Loads the main script of each script directory.
for _, script_dir in ipairs(game.config.script_directories) do
	game.load(script_dir .. "/core.lua")
end

-- Sets all necessary game variables.
game.ai.set_update_period(game.config.ai_update_period)
game.production.set_multiplier(game.config.production_multiplier)
game.time.set_multiplier(game.config.timer_multiplier)
game.event.set_multiplier(game.config.event_update_multiplier)

-- Helper commands executed on startup:
game.toggle_camera_free_mode()
game.grid.create_graphics()
