-- Teleports the target to a random free node on the map.
random_teleport_trigger = {
	trigger = function(id, target)
		game.grid.place_at_random_free_node(target)
		game.task.clear(target)
		game.path.clear(target)
		game.gui.log.print("\\[#" .. id .. "\\] Teleported #" .. target .. " away!")
	end
}

-- Slows the target for 5 seconds.
slow_trigger = {
	trigger = function(id, target)
		game.combat.apply_slow_to(target, 5.0)
		game.gui.log.print("\\[#" .. id .. "\\] Slowed #" .. target .. " for 5 seconds!")
	end,
}

-- Freezes the target for 5 seconds.
freeze_trigger = {
	trigger = function(id, target)
		game.combat.apply_freeze_to(target, 5.0)
		game.gui.log.print("\\[#" .. id .. "\\] Frozen #" .. target .. " for 5 seconds!")
	end,
}

-- Damages the target for a random value from the range (200, 600).
damage_trigger = {
	trigger = function(id, target)
		local dmg = game.get_random(200, 600)
		game.health.sub(target, dmg)
		game.gui.log.print("\\[#" .. id .. "\\] Dealt " .. dmg .. " damage to #" .. target .. "!")
	end,
}

-- Kills the target instantly.
kill_trigger = {
	trigger = function(id, target)
		game.entity.kill(target)
		game.gui.log.print("\\[#" .. id .. "\\] Killed #" .. target .. "!")
	end,
}

-- Sends the target (that INTENTIONALLY steps on the trigger) to the linked entity,
-- acting as a portal.
portal_trigger = {
	trigger = function(id, target)
		local other = game.trigger.get_linked_entity(id)
		local next_node = game.path.next_node(target)
		local node = game.grid.get_node_from_position(game.physics.get_2d_position(id))

		if next_node == node then 
			next_node = game.path.after_next(target)
			if next_node == game.grid.get_node_from_position(game.physics.get_2d_position(other)) then
				game.path.skip(target)
				game.graphics.look_at(target, next_node)
				game.trigger.reset_timer(other)
				game.physics.set_2d_position(target, game.physics.get_2d_position(other))
				game.gui.log.print("\\[#" .. id .. "\\] Sent #" .. target .. " to portal #" .. other .."!")
			end
		end
	end,
}
