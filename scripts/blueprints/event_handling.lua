-- Event handler that collects dropped gold and avoids meteors.
smart_friendly_mining_unit_evt_handling = {
	handle_event = function(id, evt)
		local evt_type = game.event.get_type(evt)
		if evt_type == game.enum.event.gold_dropped then
			if game.gold.full(id) then
				game.gold.go_deposit(id)
			end

			task = game.task.create(game.event.get_target(evt), game.enum.task.go_pick_up_gold)
			game.task.add(id, task)
			return true
		elseif evt_type == game.enum.event.meteor_falling and
		       game.ai.get_faction(evt) == game.enum.faction.enemy then
			game.task.clear(id)
			game.combat.run_away_from(id, evt, 2)
			game.event.set_active(evt, false)
			return false
		end

		return false
	end
}

-- Event handler that avoids meteors.
smart_friendly_combat_unit_evt_handling = {
	handle_event = function(id, evt)
		local evt_type = game.event.get_type(evt)
		if evt_type == game.enum.event.meteor_falling and 
		   game.ai.get_faction(evt) == game.enum.faction.enemy then
			game.task.clear(id)
			game.combat.run_away_from(id, evt, 2)
			game.event.set_active(evt, false)
			return false
		end

		return false
	end
}

-- Dumb event handler that ignores events.
dumb_friendly_combat_unit_evt_handling = {
	handle_event = function(id, evt)
		return false
	end
}

-- Event handler that avoids meteors.
smart_enemy_combat_unit_evt_handling = {
	handle_event = function(id, evt)
		local evt_type = game.event.get_type(evt)
		if evt_type == game.enum.event.meteor_falling and
		   game.ai.get_faction(evt) == game.enum.faction.friendly then
			game.task.clear(id)
			game.combat.run_away_from(id, evt, 2)
			game.event.set_active(evt, false)
			return false
		end

		return false
	end
}

-- Dumb event handler that ignores events.
dumb_enemy_combat_unit_evt_handling = {
	handle_event = function(id, evt)
		return false
	end
}
