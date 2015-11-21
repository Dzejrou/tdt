gold_vault = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.destructor,
		game.enum.component.gold,
		game.enum.component.faction
	},

	PhysicsComponent = {
		solid = false
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
		scale_y = 5,
		scale_z = 50,
		query_flags = game.enum.entity_type.misc
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	DestructorComponent = {
		blueprint = "drop_gold_destructor"
	},

	GoldComponent = {
		curr = 0,
		max = 10000
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	}
}

if game then
	game.entity.register("gold_vault")
	game.gui.builder.register_building("gold_vault")
end
