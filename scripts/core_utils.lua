-- Represents C++ enums.
enum = {
	entity = {
		none = 0,
		ogre = 1
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
		producton = 11
	},

	event = {
	
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

	-- Returns a blueprint table of a given entity.
	get_blueprint_table = function(id)
		table_name = game.get_blueprint(id)
		return _G[table_name] -- _G contains all global variables.
	end
}

-- Add these tables into the main game table.
if game then
	game.enum = enum
	game.utils = utils
end

-- Error entity blueprint, messages are for debug purposes, disallowing
-- undefined entities to leave the development process.
ERROR = {
	init = function()
		show_msg("Initializing an ERROR entity.")
	end,

	update = function()
		-- DUMMY BODY
	end,

	finnish = function()
		show_msg("Destroying an ERROR entity.")
	end,

	input_handler = function(id, key)
	end
}