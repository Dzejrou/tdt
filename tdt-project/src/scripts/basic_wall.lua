-- Destructible wall used by the level generators.
basic_wall = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.align,
		game.enum.component.mine,
		game.enum.component.exp_val,
		game.enum.component.name,
		game.enum.component.destructor
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
		scale_x = 50.0,
		scale_y = 50.0,
		scale_z = 50.0,
		query_flags = game.enum.entity_type.wall,
	},

	StructureComponent = {
		radius = 0
	},

	AlignComponent = {
		state_0 = {
			material = "colour/brown",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 25.0
		},

		state_1 = {
			material = "colour/brown",
			mesh = "cube-1.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_2 = {
			material = "colour/brown",
			mesh = "half_cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_3 = {
			material = "colour/brown",
			mesh = "cube-3.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_4 = {
			material = "colour/brown",
			mesh = "cube-4.mesh",
			position_offset_x = 0.0,
			position_offset_y = 50.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 51.0,
			scale_z = 50.0
		},

		state_5 = {
			material = "colour/brown",
			mesh = "cube-2-axis.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		}
	},

	ExperienceValueComponent = {
		value = 10
	},

	NameComponent = {
		name = "BASIC WALL"
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

if game then
	game.entity.register("basic_wall")
end
