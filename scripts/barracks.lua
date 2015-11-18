barracks = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/blue",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "ogre",
		limit = 1,
		cooldown = 5
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	}
}
if game then
	game.entity.register("barracks")
end
