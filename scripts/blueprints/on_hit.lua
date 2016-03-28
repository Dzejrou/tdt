-- Runs away from the attacker if it has no path assigned
-- and notifies the player if possible.
run_away_on_hit_with_notification = {
	on_hit = function(id, hitter)
		game.notification.notify(id, "I'm under attack!")
		if game.path.empty(id) then
			game.task.clear(id)
			game.combat.run_away_from(id, hitter, 3)
		end
	end
}

-- Silently runs away from the attacker if it has no path
-- assigned.
run_away_on_hit_without_notification = {
	on_hit = function(id, hitter)
		game.notification.notify(id, "I'm under attack!")
		if game.path.empty(id) then
			game.task.clear(id)
			game.combat.run_away_from(id, hitter, 3)
		end
	end
}

-- Attacks any attacker back.
attack_on_hit = {
	on_hit = function(id, hitter)
		game.combat.attack(id, hitter)
	end
}
