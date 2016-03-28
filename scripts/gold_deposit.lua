-- Represents a mineable block containing gold in the game.
gold_deposit = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.destructor,
		game.enum.component.gold,
		game.enum.component.faction,
		game.enum.component.align,
		game.enum.component.mine,
		game.enum.component.exp_val,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = true
	},

	HealthComponent = {
		max_hp = 2000,
		regen = 0,
		defense = 13
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/gold",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 50,
		scale_z = 50,
		query_flags = game.enum.entity_type.wall
	},

	StructureComponent = {
		radius = 0
	},

	DestructorComponent = {
		blueprint = "drop_gold_destructor"
	},

	GoldComponent = {
		curr = 1500,
		max = 1500
	},

	FactionComponent = {
		faction = game.enum.faction.neutral
	},

	AlignComponent = {
		state_0 = {
			material = "colour/gold",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 25.0
		},

		state_1 = {
			material = "colour/gold",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 25.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_2 = {
			material = "colour/gold",
			mesh = "half_cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_3 = {
			material = "colour/gold",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		},

		state_4 = {
			material = "colour/gold",
			mesh = "cube.mesh",
			position_offset_x = 0.0,
			position_offset_y = 0.0,
			position_offset_z = 0.0,
			scale_x = 50.0,
			scale_y = 50.0,
			scale_z = 50.0
		}
	},

	ExperienceValueComponent = {
		value = 20
	},

	NameComponent = {
		name = "GOLD DEPOSIT"
	},
}

if game then
	game.entity.register("gold_deposit")
end
