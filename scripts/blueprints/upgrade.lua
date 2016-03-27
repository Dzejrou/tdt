-- TODO:
friendly_miner_upgrade = {
	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 500)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 20, max + 30)
	end
}

-- TODO:
friendly_warrior_upgrade = {
	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 250)
		game.health.add_defense(10)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 30, max + 30)
	end
}

-- TODO:
friendly_mage_upgrade = {
	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 500)
		game.health.add_defense(id, 2)
		game.mana.set_max(id, game.mana.get_max(id) + 20)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 30, max + 30)
	end
}
