-- TODO:
smart_friendly_combat_unit_ai = {
	update = function(id)
		local enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		enemy = game.combat.closest_enemy(id)
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end
}

-- TODO:
dumb_friendly_combat_unit_ai = {
	update = function(id)
		local enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		enemy = game.combat.closest_enemy(id)
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end
}

-- TODO:
smart_enemy_combat_unit_ai = {
	update = function(id)
		local enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		enemy = game.combat.closest_enemy(id)
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		enemy = game.get_throne_id()
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end
}

-- TODO:
dumb_enemy_combat_unit_ai = {
	update = function(id)
		local enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		enemy = game.combat.closest_enemy(id)
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		enemy = game.get_throne_id()
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end
}
