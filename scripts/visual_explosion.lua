visual_explosion = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.explosion
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/transparent_orange",
		visible = true,
		manual_scaling = true,
		scale_x = 0,
		scale_y = 0,
		scale_z = 0,
		query_flags = game.enum.entity_type.misc
	},

	ExplosionComponent = {
		delta = 20,
		radius = 150.0
	}
}

if game then
	game.entity.register("visual_explosion")
end
