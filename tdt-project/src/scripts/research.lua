-- Auxiliary function used to get the name of a research point
-- at the given spot in the research table.
-- Param: Row number.
-- Param: Column number.
game.gui.research.get_name = function(i, j)
	return game.gui.research.research_[(i - 1) * 7 + j].name
end

-- Auxiliary function used to get the price of a research point
-- at the given spot in the research table.
-- Param: Row number.
-- Param: Column number.
game.gui.research.get_price = function(i, j)
	return game.gui.research.research_[(i - 1) * 7 + j].price
end

-- Auxiliary function that unlocks a research point at the
-- given spot in the research table.
-- Param: Row number.
-- Param: Column number.
game.gui.research.unlock = function(i, j)
	game.gui.research.research_[(i - 1) * 7 + j].unlock()
end

-- Table containing info about the individual research points.
game.gui.research.research_ = {
	-- 1x1
	{
		name = "BARRACKS",
		price = 400,
		unlock = function()
			game.gui.builder.register_building("barracks")
		end
	},

	-- 1x2
	{
		name = "ATTACK",
		price = 400,
		unlock = function()
			game.spell.register_spell("attack")
		end
	},

	-- 1x3
	{
		name = "REPOSITION",
		price = 600,
		unlock = function()
			game.spell.register_spell("reposition")
		end
	},

	-- 1x4
	{
		name = "ICE TOWER",
		price = 800,
		unlock = function()
			game.gui.builder.register_building("ice_tower")
		end
	},

	-- 1x5
	{
		name = "THUNDER TOWER",
		price = 1000,
		unlock = function()
			game.gui.builder.register_building("thunder_tower")
		end
	},

	-- 1x6
	{
		name = "FIRE TOWER",
		price = 1500,
		unlock = function()
			game.gui.builder.register_building("fire_tower")
		end
	},

	-- 1x7
	{
		name = "KILL ALL ENEMIES",
		price = 2000,
		unlock = function()
			for _, enemy in ipairs(game.get_enemies()) do
				game.entity.kill(enemy, game.const.no_ent)
			end
		end
	},

	-- 2x1
	{
		name = "HEAL",
		price = 200,
		unlock = function()
			game.spell.register_spell("heal")
		end
	},

	-- 2x2
	{
		name = "RETURN GOLD",
		price = 400,
		unlock = function()
			game.spell.register_spell("return_gold")
		end
	},

	-- 2x3
	{
		name = "FALL BACK",
		price = 600,
		unlock = function()
			game.spell.register_spell("fall_back")
		end
	},

	-- 2x4
	{
		name = "HEALING WAVE",
		price = 800,
		unlock = function()
			game.spell.register_spell("healing_wave")
		end
	},

	-- 2x5
	{
		name = "INCREASE PROD.",
		price = 1000,
		unlock = function()
			game.production.increase_production()
		end
	},

	-- 2x6
	{
		name = "DOUBLE PROD.",
		price = 1500,
		unlock = function()
			game.production.double_production()
		end
	},

	-- 2x7
	{
		name = "CHURCH",
		price = 2000,
		unlock = function()
			game.gui.builder.register_building("church")
		end
	},

	-- 3x1
	{
		name = "MANA CRYSTAL",
		price = 200,
		unlock = function()
			game.gui.builder.register_building("mana_crystal")
		end
	},

	-- 3x2
	{
		name = "WALL",
		price = 400,
		unlock = function()
			game.gui.builder.register_building("wall")
		end
	},

	-- 3x3
	{
		name = "SPAWN RANDOM",
		price = 600,
		unlock = function()
			game.spell.register_spell("spawn_random")
		end
	},

	-- 3x4
	{
		name = "LIGHT MANA CRYS.",
		price = 800,
		unlock = function()
			game.gui.builder.register_building("light_mana_crystal")
		end
	},

	-- 3x5
	{
		name = "FORTIFIED WALL",
		price = 1000,
		unlock = function()
			game.gui.builder.register_building("fortified_wall")
		end
	},

	-- 3x6
	{
		name = "PORTAL",
		price = 1500,
		unlock = function()
			game.spell.register_spell("portal")
		end
	},

	-- 3x7
	{
		name = "CHAOS TOWER",
		price = 2000,
		unlock = function()
			game.gui.builder.register_building("chaos_tower")
		end
	},

	-- 4x1
	{
		name = "LIGHTNING",
		price = 200,
		unlock = function()
			game.spell.register_spell("lightning")
		end
	},

	-- 4x2
	{
		name = "CHAIN LIGHTNING",
		price = 400,
		unlock = function()
			game.spell.register_spell("chain_lightning")
		end
	},

	-- 4x3
	{
		name = "LEVEL UP",
		price = 600,
		unlock = function()
			game.upgrade.all_level_up()
		end
	},

	-- 4x4
	{
		name = "METEOR",
		price = 800,
		unlock = function()
			game.spell.register_spell("meteor")
		end
	},

	-- 4x5
	{
		name = "FREEZE TRAP",
		price = 1000,
		unlock = function()
			game.gui.builder.register_building("freeze_trap")
		end
	},

	-- 4x6
	{
		name = "LIGHTNING STORM",
		price = 1500,
		unlock = function()
			game.spell.register_spell("lightning_storm")
		end
	},

	-- 4x7
	{
		name = "METEOR SHOWER",
		price = 2000,
		unlock = function()
			game.spell.register_spell("meteor_shower")
		end
	},

	-- 5x1
	{
		name = "SPAWN IMP",
		price = 200,
		unlock = function()
			game.spell.register_spell("spawn_imp")
		end
	},

	-- 5x2
	{
		name = "TELEPORT TRAP",
		price = 400,
		unlock = function()
			game.gui.builder.register_building("teleport_trap")
		end
	},

	-- 5x3
	{
		name = "SPAWN IMP GANG",
		price = 600,
		unlock = function()
			game.spell.register_spell("spawn_imp_gang")
		end
	},

	-- 5x4
	{
		name = "DAMAGE TRAP",
		price = 800,
		unlock = function()
			game.gui.builder.register_building("damage_trap")
		end
	},

	-- 5x5
	{
		name = "DESTROY BLOCK",
		price = 1000,
		unlock = function()
			game.spell.register_spell("destroy_block")
		end
	},

	-- 5x6
	{
		name = "UBER THRONE",
		price = 1500,
		unlock = function()
			local id = game.get_throne_id()
			game.health.buff(id, 5000)
			game.health.add_defense(id, 50)
			game.health.heal(id)
		end
	},

	-- 5x7
	{
		name = "INSTANT PROD.",
		price = 2000,
		unlock = function()
			game.production.instant_production()
		end
	},

	-- 6x1
	{
		name = "SLOW",
		price = 200,
		unlock = function()
			game.spell.register_spell("slow")
		end
	},

	-- 6x2
	{
		name = "FREEZE",
		price = 400,
		unlock = function()
			game.spell.register_spell("freeze")
		end
	},

	-- 6x3
	{
		name = "SLOW TRAP",
		price = 600,
		unlock = function()
			game.gui.builder.register_building("slow_trap")
		end
	},

	-- 6x4
	{
		name = "SLOWING WAVE",
		price = 800,
		unlock = function()
			game.spell.register_spell("slowing_wave")
		end
	},

	-- 6x5
	{
		name = "FREEZING WAVE",
		price = 1000,
		unlock = function()
			game.spell.register_spell("freezing_wave")
		end
	},

	-- 6x6
	{
		name = "TELEPORT",
		price = 1500,
		unlock = function()
			game.spell.register_spell("teleport")
		end
	},

	-- 6x7
	{
		name = "KILL TRAP",
		price = 2000,
		unlock = function()
			game.gui.builder.register_building("kill_trap")
		end
	}
}
