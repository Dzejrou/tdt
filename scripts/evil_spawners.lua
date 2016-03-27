-- A building that spawns one evil ogre warrior.
evil_barracks = {
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
		material = "colour/red",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	ProductionComponent = {
		blueprint = "evil_ogre_warrior",
		limit = 1,
		cooldown = 5
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	PriceComponent = {
		price = 1000
	},

	NameComponent = {
		name = "EVIL BARRACKS"
	}
}

-- A building that spawns one evil ogre fire mage.
evil_fire_tower = {
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
		blueprint = "evil_ogre_fire_mage",
		limit = 1,
		cooldown = 10
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	PriceComponent = {
		price = 1800
	},

	NameComponent = {
		name = "EVIL FIRE TOWER"
	}
}

-- A building that spawns one evil ogre ice mage.
evil_ice_tower = {
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
		blueprint = "evil_ogre_ice_mage",
		limit = 1,
		cooldown = 10
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	PriceComponent = {
		price = 1500
	},

	NameComponent = {
		name = "EVIL ICE TOWER"
	}
}

-- A building that spawns one evil ogre thunder mage.
evil_thunder_tower = {
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
		blueprint = "evil_ogre_thunder_mage",
		limit = 1,
		cooldown = 8
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	PriceComponent = {
		price = 1750
	},

	NameComponent = {
		name = "EVIL THUNDER TOWER"
	}
}

-- A building that spawns one evil ogre cleric.
evil_church = {
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
		blueprint = "evil_ogre_cleric",
		limit = 1,
		cooldown = 5
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	PriceComponent = {
		price = 2000
	},

	NameComponent = {
		name = "EVIL CHURCH"
	}
}

-- A building that spawns one evil ogre chaos mage.
evil_chaos_tower = {
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
		blueprint = "evil_ogre_chaos_mage",
		limit = 1,
		cooldown = 30
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	PriceComponent = {
		price = 5000
	},

	NameComponent = {
		name = "EVIL CHAOS TOWER"
	}
}

if game then
	game.entity.register("evil_barracks")
	game.entity.register("evil_fire_tower")
	game.entity.register("evil_ice_tower")
	game.entity.register("evil_thunder_tower")
	game.entity.register("evil_church")
	game.entity.register("evil_chaos_tower")
end
