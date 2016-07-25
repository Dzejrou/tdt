-- A building that spawns one ogre warrior.
barracks = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name
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
		blueprint = "ogre_warrior",
		limit = 1,
		cooldown = 5
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 1000
	},

	NameComponent = {
		name = "BARRACKS"
	}
}

-- A building that spawns one ogre fire mage.
fire_tower = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/orange",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 75,
		scale_z = 10,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "ogre_fire_mage",
		limit = 1,
		cooldown = 10
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 1800
	},

	NameComponent = {
		name = "FIRE TOWER"
	}
}

-- A building that spawns one ogre ice mage.
ice_tower = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/light_blue",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 75,
		scale_z = 10,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "ogre_ice_mage",
		limit = 1,
		cooldown = 10
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 1500
	},

	NameComponent = {
		name = "ICE TOWER"
	}
}

-- A building that spawns one ogre thunder mage.
thunder_tower = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/transparent_yellow",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 75,
		scale_z = 10,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "ogre_thunder_mage",
		limit = 1,
		cooldown = 8
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 1750
	},

	NameComponent = {
		name = "THUNDER TOWER"
	}
}

-- A building that spawns one ogre cleric.
church = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/transparent_white",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 55,
		scale_z = 10,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "ogre_cleric",
		limit = 1,
		cooldown = 5
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 2000
	},

	NameComponent = {
		name = "CHURCH"
	}
}

-- A building that spawns one ogre chaos mage.
chaos_tower = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.production,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/transparent_pink",
		visible = true,
		manual_scaling = true,
		scale_x = 10,
		scale_y = 75,
		scale_z = 10,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "ogre_chaos_mage",
		limit = 1,
		cooldown = 30
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 5000
	},

	NameComponent = {
		name = "CHAOS TOWER"
	}
}

if game then
	game.entity.register("barracks")
	game.entity.register("fire_tower")
	game.entity.register("ice_tower")
	game.entity.register("thunder_tower")
	game.entity.register("church")
	game.entity.register("chaos_tower")
end
