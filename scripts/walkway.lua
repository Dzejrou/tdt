-- Used to prevent the player from placing structure on some nodes, like
-- the wave spawning ones.
walkway = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/gray",
		visible = true,
		manual_scaling = true,
		scale_x = 50.0,
		scale_y = 0.2,
		scale_z = 50.0,
		query_flags = game.enum.entity_type.misc, -- Not selectable.
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},
}

if game then
	game.entity.register("walkway")
end
