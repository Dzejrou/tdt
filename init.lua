-------------------------------------------------------------------------------
-- GAME INITIALIZATION --------------------------------------------------------
-- NOTE: IT'S INADVISED TO CHANGE THE FOLLOWING CODE! -------------------------
-------------------------------------------------------------------------------
require("config")
require("keybinds")

-- Loads the main script of each script directory.
for _, script_dir in ipairs(game.config.script_directories) do
	game.load(script_dir .. "/core.lua")
end

-- Sets all necessary game variables.
game.ai.set_update_period(game.config.ai_update_period)
game.graphics.set_update_period(game.config.graphics_update_period)
game.production.set_multiplier(game.config.production_multiplier)
game.time.set_multiplier(game.config.timer_multiplier)
game.event.set_multiplier(game.config.event_update_multiplier)
game.combat.set_max_run_away_attempts(game.config.max_run_away_attempts)
game.trigger.set_check_period(game.config.trigger_check_period)
game.mana.set_regen_period(game.config.mana_regen_period)
game.wave.set_table(game.config.default_wave_table)
game.gui.console.set_history(game.config.console_hitory)
game.gui.log.set_history(game.config.log_history)

-- Helper commands executed on startup:
--game.toggle_camera_free_mode()
--game.grid.create_graphics()
