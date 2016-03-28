-- Default upgrade blueprint for miners, upgrades health and damage.
friendly_miner_upgrade = {
	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 500)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 20, max + 30)
	end
}

-- Default upgrade blueprint for warriors, upgrades health, defense
-- and damage.
friendly_warrior_upgrade = {
	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 250)
		game.health.add_defense(10)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 30, max + 30)
	end
}

-- Default upgrade blueprint for mages, upgrades health, defense,
-- mana and damage.
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
