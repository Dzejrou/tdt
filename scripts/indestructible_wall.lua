-- Indestructible wall used by the level generators to create borders for the
-- level.
indestructible_wall = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.align,
		game.enum.component.name
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

	AlignComponent = {
		state_0 = {
			material = "colour/dark_gray",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 25.0
		},

		state_1 = {
			material = "colour/dark_gray",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_2 = {
			material = "colour/dark_gray",
			mesh = "half_cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_3 = {
			material = "colour/dark_gray",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_4 = {
			material = "colour/dark_gray",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		}

	},

	NameComponent = {
		name = "INDESTRUCTIBLE WALL"
	}
}

if game then
	game.entity.register("indestructible_wall")
end
