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
		speed_modifier = 0.7
	},

	HomingComponent = {
		source = game.const.no_ent,
		target = game.const.no_ent,
		damage = 0
	}
}

if game then
	game.entity.register("basic_projectile")
end
