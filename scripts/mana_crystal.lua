mana_crystal = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.mana_crystal,
		game.enum.component.price,
		game.enum.component.faction
	},

	PhysicsComponent = {
		solid = true,
	},

	HealthComponent = {
		max_hp = 1500,
		regen = 0,
		defense = 20
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/light_blue",
		visible = true,
		manual_scaling = true,
		scale_x = 10.0,
		scale_y = 25.0,
		scale_z = 10.0,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0
	},

	PriceComponent = {
		price = 500
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	ManaCrystalComponent = {
		cap_increase = 20,
		regen_increase = 1
	}
}

if game then
	game.entity.register("mana_crystal")
end
