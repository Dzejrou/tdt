-- TODO:
heal_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		game.combat.apply_heal_to_entities_in_range(id, range)
	end
}

-- TODO:
damage_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.apply_damage_to_entities_in_range(id, range,
							      min, max)
	end
}

-- TODO:
slow_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		game.combat.apply_slow_to_entities_in_range(id, range, 5.0)
	end
}

-- TODO:
freeze_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		game.combat.apply_freeze_to_entities_in_range(id, range, 5.0)
	end
}

-- TODO:
throne_constructor = {
	construct = function(id)
		game.set_throne_id(id)
	end
}
