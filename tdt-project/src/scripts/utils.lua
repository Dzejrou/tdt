-- Contains auxiliary functions used for debugging and testing.
utils = {
	-- Returns an array of environment variables and their types.
	get_env = function()
		local res = {}
		for k, v in pairs(_G) do
			res[#res + 1] = tostring(k) .. " : " .. type(v)
		end
		return res
	end,

	-- Lists all environment variables to the game console.
	print_env = function()
		if game then
			for k, v in pairs(_G) do
				game.print(k .. " = " .. tostring(v))
			end
		end
	end,

	-- Returns a blueprint table of a given entity.
	get_blueprint_table = function(id)
		local table_name = game.get_blueprint(id)
		return _G[table_name] -- _G contains all global variables.
	end,

	-- Returns true if a given value v has a type matching
	-- one of the type names passed as the remaining arguments.
	assert_types = function(v, ...)
		local res = false

		for _, t in ipairs{...} do
			if type(t) == "string" and type(v) == t then
				res = true
			end
		end

		return res
	end,

	-- Calls a function stored in an array.
	call_array_func = function(array, index, ...)
		if(type(array) == "function" and array[index] ~= nil) then
			array[index](...)
		end
	end,

	testing_stats = function()
		game.player.add_gold(1000000)
		game.player.add_max_mana(9999)
		game.player.add_mana(9900)
		game.player.add_mana_regen(1000)
	end
}

-- INIT:
game.utils = utils

-- HELPER FUNCTIONS:
game.print = function(msg)
	if(type(msg) == "boolean") then
		game.print_(tostring(msg))
	else
		game.print_(msg)
	end
end

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

game.gold.go_deposit = function(id, prio)
	prio = prio or false
	local vault = game.gold.closest_free_gold_vault(id)

	if vault ~= game.const.no_ent then
		local task = game.task.create(vault, game.enum.task.go_deposit_gold)
		if prio then
			game.task.add_priority(id, task)
		else
			game.task.add(id, task)
		end
	else
		game.notification.notify(id, "No free vaults!")
	end
end

game.combat.attack = function(id, target)
	local task = game.task.create(target, game.enum.task.go_kill)
	game.task.add(id, task)
end
