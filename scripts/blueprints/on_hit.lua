-- TODO:
run_away_on_hit_with_notification = {
	on_hit = function(id, hitter)
		game.notification.notify(id, "I'm under attack!")
		if game.path.empty(id) then
			game.task.clear(id)
			game.combat.run_away_from(id, hitter, 3)
		end
	end
}

-- TODO:
run_away_on_hit_without_notification = {
	on_hit = function(id, hitter)
		game.notification.notify(id, "I'm under attack!")
		if game.path.empty(id) then
			game.task.clear(id)
			game.combat.run_away_from(id, hitter, 3)
		end
	end
}

-- TODO:
attack_on_hit = {
	on_hit = function(id, hitter)
		game.combat.attack(id, hitter)
	end
}
