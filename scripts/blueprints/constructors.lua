-- Constructor that heals enemies in the constructed entity's range.
heal_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		game.combat.apply_heal_to_entities_in_range(id, range)
	end
}

-- Costructor that deals damage to enemies in the constructed
-- entity's range.
damage_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.apply_damage_to_entities_in_range(id, range,
							      min, max)
	end
}

-- Constructor that slows all entities in the constructed entity's range.
slow_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		game.combat.apply_slow_to_entities_in_range(id, range, 5.0)
	end
}

-- Constructor that freezes all entities in the constructed entity's range.
freeze_entities_constructor = {
	construct = function(id)
		local range = game.combat.get_range(id)
		game.combat.apply_freeze_to_entities_in_range(id, range, 5.0)
	end
}

-- Constructor that sets the constructed entity to be the dungeon throne.
-- (-> it will be the structure target of enemy entities.)
throne_constructor = {
	construct = function(id)
		game.set_throne_id(id)
	end
}
