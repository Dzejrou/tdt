-- Trigger that teleports enemies to a random place in the level.
teleport_trap = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name,
		game.enum.component.trigger
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/brown",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 600
	},

	NameComponent = {
		name = "RANDOM TELEPORT TRAP"
	},

	TriggerComponent = {
		blueprint = "random_teleport_trigger",
		cooldown = 30.0,
		radius = 100
	}
}

-- Trigger that slows the enemies.
slow_trap = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name,
		game.enum.component.trigger
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/transparent_white",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 400
	},

	NameComponent = {
		name = "SLOWING TRAP"
	},

	TriggerComponent = {
		blueprint = "slow_trigger",
		cooldown = 30.0,
		radius = 100
	}
}

-- Trigger that freezes the enemies.
freeze_trap = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name,
		game.enum.component.trigger
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/light_blue",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 800
	},

	NameComponent = {
		name = "FREEZING TRAP"
	},

	TriggerComponent = {
		blueprint = "freeze_trigger",
		cooldown = 30.0,
		radius = 100
	}
}

-- Trigger that damages the enemies.
damage_trap = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name,
		game.enum.component.trigger
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/dark_brown",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 600
	},

	NameComponent = {
		name = "DAMAGING TRAP"
	},

	TriggerComponent = {
		blueprint = "damage_trigger",
		cooldown = 30.0,
		radius = 100
	}
}

-- Trigger that instantly kills the enemies.
kill_trap = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.price,
		game.enum.component.name,
		game.enum.component.trigger
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/dark_gray",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	PriceComponent = {
		price = 600
	},

	NameComponent = {
		name = "KILLING TRAP"
	},

	TriggerComponent = {
		blueprint = "kill_trigger",
		cooldown = 30.0,
		radius = 100
	}
}

-- Trigger placed in pairs that transports friendlies.
portal = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.trigger,
		game.enum.component.portal
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/pink",
		visible = true,
		manual_scaling = true,
		scale_x = 50,
		scale_y = 1,
		scale_z = 50,
		query_flags = game.enum.entity_type.building
	},

	StructureComponent = {
		radius = 0,
		walk_through = true
	},

	FactionComponent = {
		faction = game.enum.faction.neutral
	},

	NameComponent = {
		name = "PORTAL"
	},

	TriggerComponent = {
		blueprint = "portal_trigger",
		cooldown = 1.0,
		radius = 100
	}
}

if game then
	game.entity.register("teleport_trap")
	game.entity.register("slow_trap")
	game.entity.register("freeze_trap")
	game.entity.register("damage_trap")
	game.entity.register("kill_trap")
	game.entity.register("portal")
end
