-- Basic projectile that does damage.
basic_projectile = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.homing
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/red",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 10,
		scale_z = 10,
		query_flags = game.enum.entity_type.misc
	},

	MovementComponent = {
		speed_modifier = 10
	},

	HomingComponent = {
		source = game.const.no_ent,
		target = game.const.no_ent,
		damage = 0
	}
}

-- Yellow projectile that bounces to other targets
-- in range up to 6 times.
chain_lightning_projectile = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.homing,
		game.enum.component.destructor,
		game.enum.component.counter,
		game.enum.component.combat
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/yellow",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 10,
		scale_z = 10,
		query_flags = game.enum.entity_type.misc
	},

	MovementComponent = {
		speed_modifier = 10
	},

	HomingComponent = {
		source = game.const.no_ent,
		target = game.const.no_ent,
		damage = 0
	},

	DestructorComponent = {
		blueprint = "chain_destructor"
	},

	CounterComponent = {
		max_value = 7
	},

	CombatComponent = {
		range = 250,
		min_dmg = 0, -- Copied from caster.
		max_dmg = 0,
		type = game.enum.atk_type.melee,
		cooldown = 0,
		pursue = false
	}
}

-- Slows the target on impact.
slowing_projectile = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.homing,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/transparent_white",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 10,
		scale_z = 10,
		query_flags = game.enum.entity_type.misc
	},

	MovementComponent = {
		speed_modifier = 10
	},

	HomingComponent = {
		source = game.const.no_ent,
		target = game.const.no_ent,
		damage = 0
	},

	DestructorComponent = {
		blueprint = "apply_slow_destructor"
	}

}

-- Freezes the target in place on impact.
freezing_projectile = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.homing,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/light_blue",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 10,
		scale_z = 10,
		query_flags = game.enum.entity_type.misc
	},

	MovementComponent = {
		speed_modifier = 10
	},

	HomingComponent = {
		source = game.const.no_ent,
		target = game.const.no_ent,
		damage = 0
	},

	DestructorComponent = {
		blueprint = "apply_freeze_destructor"
	}

}

-- Yellow projectile that bounces to other targets
-- in range up to 1 times.
lightning_projectile = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.homing,
		game.enum.component.destructor,
		game.enum.component.counter,
		game.enum.component.combat
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/yellow",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 10,
		scale_z = 10,
		query_flags = game.enum.entity_type.misc
	},

	MovementComponent = {
		speed_modifier = 10
	},

	HomingComponent = {
		source = game.const.no_ent,
		target = game.const.no_ent,
		damage = 0
	},

	DestructorComponent = {
		blueprint = "lightning_destructor"
	},

	CounterComponent = {
		max_value = 2
	},

	CombatComponent = {
		range = 250,
		min_dmg = 0, -- Copied from caster.
		max_dmg = 0,
		type = game.enum.atk_type.melee,
		cooldown = 0,
		pursue = false
	}
}

if game then
	game.entity.register("basic_projectile")
	game.entity.register("chain_lightning_projectile")
	game.entity.register("slowing_projectile")
	game.entity.register("freezing_projectile")
	game.entity.register("lightning_projectile")
end
