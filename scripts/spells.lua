-- Table that contains the individual spell tables.
-- Each spell table needs two fields: price (integer)
-- and cast (function that gets called when the spell is cast).
game.spell.spells = {
	-- Basic player spell, commands the miner with fewest tasks
	-- to mine every currently selected mineable entity.
	mine = {
		init = function()
			game.spell.set_type(game.enum.spell_type.global)
		end,

		pay_mana = function()
			-- NO COST.
			return true
		end,

		cast = function()
			game.command.mine()
			game.spell.stop_casting()
		end
	},

	-- Heals a friendly target to full health.
	heal = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(10)
		end,

		cast = function(target)
			if game.ai.get_faction(target) == game.enum.faction.friendly then
				game.health.heal(target)
			else
				game.spell.refund_(10)
			end
			game.spell.stop_casting()
		end
	},

	meteor = {
		init = function()
			game.spell.set_type(game.enum.spell_type.placing)
			game.entity.place("meteor")
		end,

		pay_mana = function()
			return game.player.sub_mana(40)
		end,

		cast = function(id)
			game.spell.stop_casting()
		end
	},

	healing_wave = {
		init = function()
			game.spell.set_type(game.enum.spell_type.placing)
			game.entity.place("healing_wave")
		end,

		pay_mana = function()
			return game.player.sub_mana(30)
		end,

		cast = function(id)
			game.spell.stop_casting()
		end,
	},

	spawn_imp = {
		init = function()
			game.spell.set_type(game.enum.spell_type.placing)
			game.entity.place("imp")
		end,

		pay_mana = function()
			return game.player.sub_mana(20)
		end,

		cast = function(id)
			local lifespan = game.lls.get_max_time(id)
			game.gui.log.print("\\[" .. id .. "\\] Imp spawned for " .. lifespan .. " seconds.")
			game.spell.stop_casting()
		end,
	},

	spawn_imp_gang = {
		init = function()
			game.spell.set_type(game.enum.spell_type.positional)
		end,

		pay_mana = function()
			return game.player.sub_mana(100)
		end,

		cast = function(x, y)
			local boss = game.entity.create("imp_gang_boss")
			local mem1 = game.entity.create("imp_gang_member")
			local mem2 = game.entity.create("imp_gang_member")
			local mem3 = game.entity.create("imp_gang_member")
			local mem4 = game.entity.create("imp_gang_member")
			local node = game.grid.get_node_from_position(x, y)

			local res = game.grid.distribute_to_adjacent_free_nodes(
					node, boss, mem1, mem2, mem3, mem4
			)

			if not res then
				game.spell.refund_(100)
				game.entity.destroy(boss)
				game.entity.destroy(mem1)
				game.entity.destroy(mem2)
				game.entity.destroy(mem3)
				game.entity.destroy(mem4)
			end
			game.spell.stop_casting()
		end,
	},

	chain_lightning = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(60)
		end,

		cast = function(target)
			if game.ai.get_faction(target) == game.enum.faction.friendly or
			   game.entity.has_component(target, game.enum.component.structure) then
				game.gui.log.print("\\[ERROR\\] Cannot cast that on that target.")
				game.spell.refund_(60)
				return
			end
			local x, y, z = game.physics.get_position(target)
			local bolt = game.entity.create("chain_lightning_projectile")
			game.physics.set_position(bolt, x, y + 1000, z)
			game.projectile.set_target(bolt, target)
			game.projectile.set_dmg(bolt, game.get_random(100, 2000))
			game.spell.stop_casting()
		end,
	},

	meteor_shower = {
		init = function()
			game.spell.set_type(game.enum.spell_type.global)
		end,

		pay_mana = function()
			return game.player.sub_mana(200)
		end,

		cast = function()
			local met1 = game.entity.create("meteor")
			local met2 = game.entity.create("meteor")
			local met3 = game.entity.create("meteor")
			local met4 = game.entity.create("meteor")
			local met5 = game.entity.create("meteor")

			game.grid.place_at_random_free_node(met1)
			game.grid.place_at_random_free_node(met2)
			game.grid.place_at_random_free_node(met3)
			game.grid.place_at_random_free_node(met4)
			game.grid.place_at_random_free_node(met5)
			game.spell.stop_casting()
		end,
	},

	slowing_wave = {
		init = function()
			game.spell.set_type(game.enum.spell_type.placing)
			game.entity.place("slowing_wave")
		end,

		pay_mana = function()
			return game.player.sub_mana(50)
		end,

		cast = function(id)
			game.spell.stop_casting()
		end,
	},

	freezing_wave = {
		init = function()
			game.spell.set_type(game.enum.spell_type.placing)
			game.entity.place("freezing_wave")
		end,

		pay_mana = function()
			return game.player.sub_mana(70)
		end,

		cast = function(id)
			game.spell.stop_casting()
		end,
	},

	slow = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(20)
		end,

		cast = function(target)
			if game.ai.get_faction(target) ~= game.enum.faction.friendly then
				game.combat.apply_slow_to(target, 5.0)
			else
				game.spell.refund_(20)
			end
			game.spell.stop_casting()
		end
	},

	freeze = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(40)
		end,

		cast = function(target)
			if game.ai.get_faction(target) ~= game.enum.faction.friendly then
				game.combat.apply_freeze_to(target, 5.0)
			else
				game.spell.refund_(40)
			end
			game.spell.stop_casting()
		end
	},

	teleport = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(100)
		end,

		cast = function(target)
			if game.ai.get_faction(target) ~= game.enum.faction.friendly then
				game.grid.place_at_random_free_node(target)
			else
				game.spell.refund_(100)
			end
			game.spell.stop_casting()
		end
	},

	portal = {
		init = function()
			game.spell.set_type(game.enum.spell_type.placing)
			game.entity.place("portal")
			game.spell.set_last_id(game.const.no_ent)
		end,

		pay_mana = function()
			return game.player.sub_mana(200)
		end,

		cast = function(id)
			local last = game.spell.get_last_id()
			if last == game.const.no_ent then
				game.spell.set_last_id(id)
				game.entity.place("portal")
			else
				local node_id = game.grid.get_node_from_position(game.physics.get_2d_position(id))
				local node_last = game.grid.get_node_from_position(game.physics.get_2d_position(last))
				game.trigger.set_linked_entity(id, last)
				game.grid.set_portal_neighbour(node_id, node_last)
				game.trigger.set_linked_entity(last, id)
				game.grid.set_portal_neighbour(node_last, node_id)

				game.spell.stop_casting()
				game.spell.set_last_id(game.const.no_ent)
			end
		end
	},
	
	-- Basic player spell, commands the combat unit with fewest tasks
	-- to attack the currently selected enemy entity.
	attack = {
		init = function()
			game.spell.set_type(game.enum.spell_type.global)
		end,

		pay_mana = function()
			-- NO COST.
			return true
		end,

		cast = function()
			game.command.attack()
			game.spell.stop_casting()
		end
	},
	
	-- Basic player spell, commands the unit with fewest tasks
	-- to go to the selected (clicked on) place.
	reposition = {
		init = function()
			game.spell.set_type(game.enum.spell_type.positional)
		end,

		pay_mana = function()
			-- NO COST.
			return true
		end,

		cast = function(x, y)
			game.command.reposition(x, y)
			game.spell.stop_casting()
		end
	},
	
	-- Commands all units that have gold on them to return it to the closest
	-- gold vault.
	return_gold = {
		init = function()
			game.spell.set_type(game.enum.spell_type.global)
		end,

		pay_mana = function()
			-- NO COST.
			return true
		end,

		cast = function()
			game.command.return_gold()
			game.spell.stop_casting()
		end
	},
	
	-- Commands all units spawned at a building to return to their spawners.
	fall_back = {
		init = function()
			game.spell.set_type(game.enum.spell_type.global)
		end,

		pay_mana = function()
			-- NO COST.
			return true
		end,

		cast = function()
			game.command.fall_back()
			game.spell.stop_casting()
		end
	},

	-- Destroys a neutral entity that can be mined.
	destroy_block = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(200)
		end,

		cast = function(id)
			if game.ai.get_faction(id) == game.enum.faction.neutral and
			   game.entity.has_component(id, game.enum.component.mine) then
				game.entity.kill(id, game.const.no_ent)
		   	else
				game.spell.refund_(200)
			end
		end
	},

	lightning = {
		init = function()
			game.spell.set_type(game.enum.spell_type.targeted)
		end,

		pay_mana = function()
			return game.player.sub_mana(20)
		end,

		cast = function(target)
			if game.ai.get_faction(target) == game.enum.faction.friendly or
			   game.entity.has_component(target, game.enum.component.structure) then
				game.gui.log.print("\\[ERROR\\] Cannot cast that on that target.")
				game.spell.refund_(20)
				return
			end
			local x, y, z = game.physics.get_position(target)
			local bolt = game.entity.create("lightning_projectile")
			game.physics.set_position(bolt, x, y + 1000, z)
			game.projectile.set_target(bolt, target)
			game.projectile.set_dmg(bolt, game.get_random(10, 1000))
			game.spell.stop_casting()
		end,
	},

	lightning_storm = {
		init = function()
			game.spell.set_type(game.enum.spell_type.global)
		end,

		pay_mana = function()
			return game.player.sub_mana(500)
		end,

		cast = function()
			local i = 0
			for _, enemy in ipairs(game.get_enemies()) do
				if game.get_random(0, 3) == 1 then
					local bolt = game.entity.create("chain_lightning_projectile")
					local x, y, z = game.physics.get_position(enemy)
					game.physics.set_position(bolt, x, y + game.get_random(600, 5000), z)
					game.projectile.set_target(bolt, enemy)
					game.projectile.set_dmg(bolt, game.get_random(10, 1000))
					i = i + 1

					if i == 30 then
						game.spell.stop_casting()
						return
					end
				end
			end
			game.spell.stop_casting()
		end
	},

	spawn_random = {
		init = function()
			game.spell.set_type(game.enum.spell_type.positional)
		end,

		pay_mana = function()
			return game.player.sub_mana(100)
		end,

		cast = function(x, y)
			local id = game.const.no_ent
			local tmp = game.get_random(0, 5)

			if tmp == 0 then
				id = game.entity.create("ogre_warrior")
			elseif tmp == 1 then
				id = game.entity.create("ogre_cleric")
			elseif tmp == 2 then
				id = game.entity.create("ogre_fire_mage")
			elseif tmp == 3 then
				id = game.entity.create("ogre_thunder_mage")
			elseif tmp == 4 then
				id = game.entity.create("ogre_ice_mage")
			else
				id = game.entity.create("ogre_chaos_mage")
			end

			game.entity.add_component(id, game.enum.component.lls)
			game.lls.set_max_time(id, 60)
			game.physics.set_2d_position(id, x, y)
			game.gui.log.print("\\[" .. id .. "\\] Random spawned for 60 seconds.")
			game.spell.stop_casting()
		end,
	}
}

-- Used to return mana to the player if a spell can't be used
-- for some reason.
-- Param: Amount of mana to return.
game.spell.refund_ = function(value)
	game.player.add_mana(value)
end

-- Testing function that unlocks all spells.
game.spell.unlock_all = function()
	for spell, _ in pairs(game.spell.spells) do
		game.spell.register_spell(spell)
	end
end

-- Spells the player starts with.
game.spell.register_spell("mine")
