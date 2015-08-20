-- Represents C++ enums.
enum = {
	entity_type = {
		none = 0,
		wall = 1,
		minion = 2,
		enemy = 4,
		building = 8,
		misc = 16
	},
	
	component = {
		none = -1,
		physics = 0,
		health = 1,
		ai = 2,
		graphics = 3,
		movement = 4,
		combat = 5,
		event = 6,
		input = 7,
		time = 8,
		mana = 9,
		spell = 10,
		production = 11,
		grid_node = 12,
		product = 13,
		pathfinding = 14,
		task = 15,
		task_handler = 16,
		structure = 17,
		homing = 18
	},

	event = {
		-- TODO:
	},

	faction = {
		friendly = 0,
		enemy = 1,
		neutral = 2
	},

	input = {
		-- Will be set in InputSystem's constructor.
		key_up = 0,
		key_down = 1,
		key_left = 2,
		key_right = 3,
	},

	game_state = {
		running = 0,
		ended = 1,
		paused = 2,
		menu = 3
	},

	task = {
		none = 0,
		go_to = 1,
		go_near = 2,
		go_kill = 3,
		kill = 4,
		get_in_range = 5
	},

	atk_type = {
		none = 0,
		melee = 1,
		ranged = 2
	}
}

-- Contains auxiliary functions used for debugging and testing.
utils = {
	-- Returns an array of environment variables and their types.
	get_env = function()
		res = {}
		for k, v in pairs(_G) do
			res[#res + 1] = tostring(k) .. " : " .. type(v)
		end
		return res
	end,

	print_env = function()
		if game then
			for k, v in pairs(_G) do
				game.print(k .. " = " .. tostring(v))
			end
		end
	end,

	-- Returns a blueprint table of a given entity.
	get_blueprint_table = function(id)
		table_name = game.get_blueprint(id)
		return _G[table_name] -- _G contains all global variables.
	end
}

-- Add these tables into the main game table, also add aliases.
if game then
	game.enum = enum
	game.utils = utils

	if show_msg then
		game.show_msg = show_msg
	end

	game.quit = function()
		game.set_game_state(game.enum.game_state.ended)
	end

	game.pause = function()
		game.set_game_state(game.enum.game_state.paused)
	end

	game.unpause = function()
		game.set_game_state(game.enum.game_state.running)
	end

	-- Aliases: (Easier to create in lua than in C++)
	game.set_position = game.move_to
else
	show_msg("Game Lua table not loaded!")
end

-- Error entity blueprint, messages are for debug purposes, disallowing
-- undefined entities to leave the development process.
ERROR = {
	init = function()
		game.show_msg("Initializing an ERROR entity.")
	end,

	update = function()
		-- DUMMY BODY
	end,

	finnish = function()
		game.show_msg("Destroying an ERROR entity.")
	end,

	input_handler = function(id, key)
		game.show_msg("Trying to move an ERROR entity.")
	end
}


-- Helper commands executed on startup:
if game then
	game.toggle_camera_free_mode()
end
