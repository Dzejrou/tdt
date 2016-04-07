-- Simple destructor that awards the killer with experience equal
-- to the experience value of the destructed entity.
give_experience_destructor = {
	dtor = function(id, killer)
		local exp_val = game.exp_val.get(id)
		if exp_val > 0 then
			game.upgrade.add_experience(killer, exp_val)
		end
	end
}

-- Creates a pile of gold after an entity is killed, contains
-- all of the entity's gold. Also creates an event announcing
-- the appearance of a new gold pile on the ground so that minions
-- in range can pick it up.
drop_gold_destructor = {
	dtor = function(id, killer)
		give_experience_destructor.dtor(id, killer)

		local pile = game.entity.create("gold_pile")
		game.gold.set_current(pile, game.gold.get_current(id))
		game.gold.set_max(pile, game.gold.get_max(id))
		local x1, y1, z1 = game.physics.get_position(pile)
		local x2, y2, z2 = game.physics.get_position(id)
		game.movement.move_to(pile, x2, y1, z2)

		local evt = game.entity.create("")
		game.entity.add_component(evt, game.enum.component.event)
		game.event.set_target(evt, pile)
		game.event.set_type(evt, game.enum.event.gold_dropped)
		game.event.set_radius(evt, 3000.0)
		game.entity.add_component(evt, game.enum.component.physics)
		game.physics.set_position(evt, x2, y1, z2)

		if killer and killer ~= game.const.no_ent and
		   game.ai.get_faction(killer) == game.enum.faction.friendly then
			game.event.set_handler(evt, killer)
		end
	end
}

-- Destructor that drops the vault's gold on the floor and subtracts that amount
-- of gold from the player's gold reserves.
gold_vault_destructor = {
	dtor = function(id, killer)
		game.gui.log.print("\\[#" .. id .. "\\] Gold vault has been destroyed!")
		drop_gold_destructor.dtor(id)
		if not game.player.sub_gold(game.gold.get_current(id)) then
			game.print("\\[ERROR\\] Cannot remove gold that dropped from vault #" .. id .. "!")
		end
	end
}

-- Destructor used by entities in the wave system, it awards experience (if
-- possible) and tells the wave system that a wave entity has died.
wave_entity_destructor = {
	dtor = function(id, killer)
		give_experience_destructor.dtor(id, killer)

		game.wave.entity_died()
	end
}

-- Destructor that creates an explosion at the destroyed entity's
-- position and deals damage to enemies in range.
explosion_destructor = {
	dtor = function(id, killer)
		local range = game.combat.get_range(id)
		local min, max = game.combat.get_dmg_range(id)
		game.combat.apply_damage_to_entities_in_range(id, range,
							      min, max)

		local explosion = game.entity.create("visual_explosion")
		local x, y, z = game.physics.get_position(id)
		game.physics.set_position(explosion, x, y, z)
	end
}

-- Destructor that slows enemies within range of the destroyed entity.
apply_slow_destructor = {
	dtor = function(id, killer)
		game.combat.apply_slow_to(killer, 5.0)
	end
}

-- Destructor that freezes enemies within range of the destroyed entity.
apply_freeze_destructor = {
	dtor = function(id, killer)
		game.combat.apply_freeze_to(killer, 5.0)
	end
}

-- Destructor that increments the counter of the destroyed entity and if
-- it hasn't reached it's max value yet, creates it's clone and tries to
-- send it to a closest friend of the killer.
-- Chain lightning variant.
chain_destructor = {
	dtor = function(id, killer)
		if not game.counter.increment(id) then
			local source = game.projectile.get_source(id)
			local target = game.combat.closest_friendly_thats_not(killer, source)

			if target ~= game.const.no_ent and game.combat.in_range(id, target) and
			   not game.entity.has_component(target, game.enum.component.structure) then
				local counter = game.counter.get(id)
				local new_bolt = game.entity.create("chain_lightning_projectile")
				local x, y, z = game.physics.get_position(id)
				game.physics.set_position(new_bolt, x, y, z)
				game.counter.set(new_bolt, counter)
				game.projectile.set_target(new_bolt, target)
				game.projectile.set_source(new_bolt, killer)
				game.projectile.set_dmg(new_bolt, game.projectile.get_dmg(id))
			end
		end
	end
}

-- Destructor that increments the counter of the destroyed entity and if
-- it hasn't reached it's max value yet, creates it's clone and tries to
-- send it to a closest friend of the killer.
-- Lightning variant.
lightning_destructor = {
	dtor = function(id, killer)
		if not game.counter.increment(id) then
			local source = game.projectile.get_source(id)
			local target = game.combat.closest_friendly_thats_not(killer, source)

			if target ~= game.const.no_ent and game.combat.in_range(id, target) and
			   not game.entity.has_component(target, game.enum.component.structure) then
				local counter = game.counter.get(id)
				local new_bolt = game.entity.create("lightning_projectile")
				local x, y, z = game.physics.get_position(id)
				game.physics.set_position(new_bolt, x, y, z)
				game.counter.set(new_bolt, counter)
				game.projectile.set_target(new_bolt, target)
				game.projectile.set_source(new_bolt, killer)
				game.projectile.set_dmg(new_bolt, game.projectile.get_dmg(id))
			end
		end
	end
}

-- Destructor used by the dungeon throne, loses the game.
lose_game_destructor = {
	dtor = function(id, killer)
		game.lose()
	end
}
