game.entity_spells = {
	-- Spawns a wave that freezes enemies in place at the caster location.
	friendly_freezing_wave = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 30) then
				local x, y = game.physics.get_2d_position(id)
				local wave = game.entity.create("freezing_wave")

				game.physics.set_2d_position(wave, x, y)
			end
		end
	},

	-- Spawns a wave that freezes enemies in place at the caster location.
	enemy_freezing_wave = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 30) then
				local x, y = game.physics.get_2d_position(id)
				local wave = game.entity.create("enemy_freezing_wave")

				game.physics.set_2d_position(wave, x, y)
			end
		end
	},

	-- Spawns a wave that slows enemies at the caster location.
	friendly_slowing_wave = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 25) then
				local x, y = game.physics.get_2d_position(id)
				local wave = game.entity.create("slowing_wave")

				game.physics.set_2d_position(wave, x, y)
			end
		end
	},

	-- Spawns a wave that slows enemies at the caster location.
	enemy_slowing_wave = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 25) then
				local x, y = game.physics.get_2d_position(id)
				local wave = game.entity.create("enemy_slowing_wave")

				game.physics.set_2d_position(wave, x, y)
			end
		end
	},

	-- Spawns a wave that heals friends at the caster location.
	friendly_healing_wave = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 35) then
				local x, y = game.physics.get_2d_position(id)
				local wave = game.entity.create("healing_wave")

				game.physics.set_2d_position(wave, x, y)
			end
		end
	},

	-- Spawns a wave that heals friends in place at the caster location.
	enemy_healing_wave = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 35) then
				local x, y = game.physics.get_2d_position(id)
				local wave = game.entity.create("enemy_healing_wave")

				game.physics.set_2d_position(wave, x, y)
			end
		end
	},

	-- Spawns a wave that freezes enemies in place at the caster location.
	friendly_meteor = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 30) then
			   	local target = game.combat.get_target(id)
				local x, y = game.physics.get_2d_position(target)
				local met = game.entity.create("meteor")

				game.physics.set_2d_position(met, x, y)
			end
		end
	},

	-- Spawns a wave that freezes enemies in place at the caster location.
	enemy_meteor = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 30) then
			   	local target = game.combat.get_target(id)
				local x, y = game.physics.get_2d_position(target)
				local met = game.entity.create("enemy_meteor")

				game.physics.set_2d_position(met, x, y)
			end
		end
	},

	-- Casts a random spell.
	friendly_random_spell = {
		cast = function(id)
			local tmp = game.get_random(0, 4)

			if tmp == 0 then
				game.entity_spells.friendly_freezing_wave.cast(id)
			elseif tmp == 1 then
				game.entity_spells.friendly_slowing_wave.cast(id)
			elseif tmp == 3 then
				game.entity_spells.friendly_meteor.cast(id)
			else
				game.entity_spells.friendly_healing_wave.cast(id)
			end
		end
	},

	-- Casts a random spell.
	enemy_random_spell = {
		cast = function(id)
			local tmp = game.get_random(0, 4)

			if tmp == 0 then
				game.entity_spells.enemy_freezing_wave.cast(id)
			elseif tmp == 1 then
				game.entity_spells.enemy_slowing_wave.cast(id)
			elseif tmp == 3 then
				game.entity_spells.enemy_meteor.cast(id)
			else
				game.entity_spells.enemy_healing_wave.cast(id)
			end
		end
	},

	-- Strikes the enemy and his allies with a powerful chain lightning bolt.
	chain_lightning = {
		cast = function(id)
			if game.combat.enemy_in_range(id) and
			   game.mana.sub(id, 25) then
			   	local target = game.combat.get_target(id)

				if target ~= game.const.no_ent and game.combat.in_range(id, target) and
				   not game.entity.has_component(target, game.enum.component.structure) then
					local counter = game.counter.get(id)
					local new_bolt = game.entity.create("chain_lightning_projectile")
					local x, y, z = game.physics.get_position(id)
					game.physics.set_position(new_bolt, x, y, z)
					game.counter.set(new_bolt, counter)
					game.projectile.set_target(new_bolt, target)
					game.projectile.set_source(new_bolt, id)
					game.projectile.set_dmg(new_bolt, game.projectile.get_dmg(id))
				end
			end
		end
	},
}
