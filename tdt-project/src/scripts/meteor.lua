-- Used by the meteor spell, spawns a projectile that impacts it, triggering
-- the explosion destructor that damages enemies.
meteor = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.combat,
		game.enum.component.faction,
		game.enum.component.event,
		game.enum.component.constructor,
		game.enum.component.destructor,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 100000,
		regen = 0,
		defense = 0
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/orange",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.misc
	},

	CombatComponent = {
		range = 200,
		min_dmg = 200,
		max_dmg = 800,
		type = game.enum.atk_type.melee,
		cooldown = 0.0,
		pursue = false
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	EventComponent = {
		type = game.enum.event.meteor_falling,
		target = game.const.no_ent,
		radius = 300,
		active = true
	},

	ConstructorComponent = {
		blueprint = "meteor"
	},

	DestructorComponent = {
		blueprint = "explosion_destructor"
	},

	NameComponent = {
		name = "METEOR"
	},

	construct = function(id)
		local proj = game.entity.create("basic_projectile")
		game.graphics.set_material(proj, "colour/orange")


		local x, y, z = game.physics.get_position(id)
		local health = game.health.get(id)
		local height = game.get_random(4000, 6000)
		game.physics.set_position(proj, x + 3000, y + height, z + 3000)
		game.movement.set_speed(proj, 10)
		game.graphics.set_scale(proj, 30, 30, 30)
		game.graphics.apply_scale(proj)
		game.projectile.set_source(proj, id)
		game.projectile.set_target(proj, id)
		game.projectile.set_dmg(proj, health)
	end
}

-- Used by the meteor spell, spawns a projectile that impacts it, triggering
-- the explosion destructor that damages friendlies.
enemy_meteor = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.combat,
		game.enum.component.faction,
		game.enum.component.event,
		game.enum.component.constructor,
		game.enum.component.destructor,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 100000,
		regen = 0,
		defense = 0
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/orange",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.misc
	},

	CombatComponent = {
		range = 200,
		min_dmg = 200,
		max_dmg = 800,
		type = game.enum.atk_type.melee,
		cooldown = 0.0,
		pursue = false
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	EventComponent = {
		type = game.enum.event.meteor_falling,
		target = game.const.no_ent,
		radius = 300,
		active = true
	},

	ConstructorComponent = {
		blueprint = "meteor"
	},

	DestructorComponent = {
		blueprint = "explosion_destructor"
	},

	NameComponent = {
		name = "ENEMY METEOR"
	},

	construct = function(id)
		local proj = game.entity.create("basic_projectile")
		game.graphics.set_material(proj, "colour/orange")


		local x, y, z = game.physics.get_position(id)
		local health = game.health.get(id)
		game.physics.set_position(proj, x + 3000, y + 4500, z + 3000)
		game.movement.set_speed(proj, 10)
		game.graphics.set_scale(proj, 30, 30, 30)
		game.graphics.apply_scale(proj)
		game.projectile.set_source(proj, id)
		game.projectile.set_target(proj, id)
		game.projectile.set_dmg(proj, health)
	end
}

if game then
	game.entity.register("meteor")
	game.entity.register("enemy_meteor")
end
