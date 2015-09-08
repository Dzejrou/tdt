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

-- INIT:
game = game or {}
game.utils = utils

if show_msg then
	game.show_msg = show_msg
elseif game.print then
	game.show_msg = game.print
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
