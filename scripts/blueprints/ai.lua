-- AI blueprint used by the player's smart combat units, tries to find an enemy
-- and attacks him (prefers enemies in sight).
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

-- AI blueprint used by the player's dumb combat units, tries to find an enemy
-- within range and in sight and attacks him.
dumb_friendly_combat_unit_ai = {
	update = function(id)
		local enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end
}

-- AI blueprint used by the smart enemy combat units, tries to find player's unit
-- and attacks it (prefers units in sight). If no unit is found, it attacks the
-- dungeon throne.
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

-- AI blueprint used by the dumb enemy combat units, tries to find player's unit
-- in range and in sight and attacks it. If no unit is found, it attacks the
-- dungeon throne.
dumb_enemy_combat_unit_ai = {
	update = function(id)
		local enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent and game.combat.in_range(id, enemy) then
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
