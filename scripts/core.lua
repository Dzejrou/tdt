-- Load all scripts:
scripts = {
	"utils.lua", "enum.lua", "error.lua",
	"friendly_ogres.lua", "evil_ogres.lua",
	"basic_wall.lua", "projectiles.lua",
	"friendly_spawners.lua", "evil_spawners.lua",
	"gold_deposit.lua", "blueprints/destructors.lua",
	"gold_pile.lua", "auto_ogre_miner.lua",
	"mine.lua", "blueprints/task_handlers.lua", "gold_vault.lua",
	"research.lua", "spells.lua", "indestructible_wall.lua",
	"walkway.lua", "mana_crystal.lua", "explosion.lua",
	"imp.lua", "wave.lua", "fortified_wall.lua", "wall.lua",
	"blueprints/constructors.lua", "healing_wave.lua", "meteor.lua",
	"visual_explosion.lua", "blueprints/on_hit.lua", "blueprints/ai.lua",
	"blueprints/event_handling.lua", "blueprints/pathfinding.lua",
	"blueprints/triggers.lua", "traps.lua", "light_crystal.lua",
	"freezing_wave.lua", "slowing_wave.lua", "light_mana_crystal.lua",
	"entity_spells.lua", "dungeon_throne.lua", "blueprints/upgrade.lua"
}

if game then
	for _, s in ipairs(scripts) do
		game.load("scripts/" .. s)
	end
else
	show_msg("Game table not defined!")
end

-- Called when a new level is created, can be overriden to call a
-- custom level generator or any other function. If it returns true,
-- the default level generator is going to be called afterwards, otherwise
-- it will be ignored.
game.init_level = function(width, height)
	game.gui.console.print("New level created with dimensions: "
			       .. width .. "x" .. height .. ".")
	game.wave.set_table(game.config.default_wave_table)
	return true
end

-- Game WIN/LOSE functions:
game.msg_funcs_ = {
	win_ok = function()
		game.quit()
	end,

	win_yes = function()
		game.unpause()
		game.wave.pause(true)
		game.wave.set_state(game.enum.wave_state.inactive)
		game.wave.update_label_text()
	end,

	win_no = function()
		game.unpause()
		game.wave.turn_endless_mode_on()
	end,

	loss_ok = function()
		game.quit()
	end
}

-- Ends the game and shows the "YOU WON" message.
game.win = function()
	game.set_game_state(game.enum.game_state.menu)
	game.gui.message.set_butt_label("OK", "QUIT")
	game.gui.message.set_butt_label("YES", "SANDBOX")
	game.gui.message.set_butt_label("NO", "ENDLESS")
	game.gui.message.show(
		[[Congratulations!
		You have managed to defend your dungeon against those pesky heroes and now you and your 
		minions can live happily while planning world domination. If you'd like to continue 
		the game in a sandbox mode, click the "SANDBOX" button below, the "ENDLESS" button will 
		cause the wave system to repeat the last wave and the "QUIT" button will end the game. 
		(Clicking the menu button to the left bottom will allow you to play a new game.)]],
		"game.msg_funcs_.win_ok", "game.msg_funcs_.win_yes", "game.msg_funcs_.win_no"
	)
end

-- Ends the game and shows the "YOU LOST" message.
game.lose = function()
	game.set_game_state(game.enum.game_state.menu)
	game.gui.message.set_butt_label("OK", "QUIT")
	game.gui.message.show_ok(
		[[Sadly, the endless hordes of heroic opressors have managed to destroy 
		your majestic dungeon throne! Pressing the "OK" button below will end the game 
		and pressing the menu button to the bottom left will allow you to create a new game.]],
		"game.msg_funcs_.loss_ok"
	)
end
