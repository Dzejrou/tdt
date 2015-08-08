basic_wall = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure
	},

	PhysicsComponent = {
		solid = true
	},

	HealthComponent = {
		max_hp = 2000,
		regen = 1,
		defense = 13
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/brown",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 50,
		scale_z = 50
	},

	StructureComponent = {
		radius = 1
	}
}

if game then
	game.register_entity("basic_wall")
end
