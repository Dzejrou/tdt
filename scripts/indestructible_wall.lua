indestructible_wall = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
	},

	PhysicsComponent = {
		solid = true
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/dark_gray",
		visible = true,
		manual_scaling = true,
		scale_x = 50.0,
		scale_y = 50.0,
		scale_z = 50.0,
		query_flags = game.enum.entity_type.wall,
	},

	StructureComponent = {
		radius = 0
	},
}

if game then
	game.entity.register("indestructible_wall")
end
