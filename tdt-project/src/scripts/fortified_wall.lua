-- Stronger wall that can be built by the player.
fortified_wall = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.align,
		game.enum.component.mine,
		game.enum.component.exp_val,
		game.enum.component.price,
		game.enum.component.faction,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = true
	},

	HealthComponent = {
		max_hp = 3500,
		regen = 1,
		defense = 20
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/dark_brown",
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
			material = "colour/dark_brown",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 25.0
		},

		state_1 = {
			material = "colour/dark_brown",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_2 = {
			material = "colour/dark_brown",
			mesh = "half_cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_3 = {
			material = "colour/dark_brown",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_4 = {
			material = "colour/dark_brown",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 50.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_5 = {
			material = "colour/dark_brown",
			mesh = "cube-2-axis.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		}
	},

	PriceComponent = {
		price = 600
	},

	ExperienceValueComponent = {
		value = 50
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "FORTIFIED WALL"
	}
}

if game then
	game.entity.register("fortified_wall")
end
