-- A summonable imp with limited life span.
imp = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.lls,
		game.enum.component.name,
		game.enum.component.combat,
		game.enum.component.movement,
		game.enum.component.task_handler,
		game.enum.component.faction,
		game.enum.component.ai,
		game.enum.component.event_handler,
		game.enum.component.pathfinding
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 10,
		defense = 12
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	LimitedLifeSpanComponent = {
		max_time = 120.0
	},

	NameComponent = {
		name = "IMP"
	},

	CombatComponent = {
		range = 300,
		min_dmg = 50,
		max_dmg = 80,
		type = game.enum.atk_type.ranged,
		cooldown = 3,
		pursue = false,
		projectile_blueprint = "basic_projectile"
	},

	MovementComponent = {
		speed_modifier = 70
	},

	TaskHandlerComponent = {
		possible_tasks = {
			game.enum.task.go_to,
			game.enum.task.go_near,
			game.enum.task.go_kill,
			game.enum.task.kill,
			game.enum.task.get_in_range
		},
		blueprint = "default_task_handler"
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	AIComponent = {
		blueprint = "smart_friendly_combat_unit_ai"
	},

	EventHandlerComponent = {
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity,
			game.enum.event.meteor_falling
		}
	},

	PathfindingComponent = {
		blueprint = "cannot_break_blocks"
	}
}

-- A member of the summonable imp gang (with limited life span).
imp_gang_member = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.lls,
		game.enum.component.name,
		game.enum.component.combat,
		game.enum.component.movement,
		game.enum.component.task_handler,
		game.enum.component.faction,
		game.enum.component.ai,
		game.enum.component.event_handler,
		game.enum.component.pathfinding
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 10,
		defense = 20
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	LimitedLifeSpanComponent = {
		max_time = 60.0
	},

	NameComponent = {
		name = "IMP GANG MEMBER"
	},

	CombatComponent = {
		range = 300,
		min_dmg = 60,
		max_dmg = 90,
		type = game.enum.atk_type.ranged,
		cooldown = 3,
		pursue = true,
		projectile_blueprint = "basic_projectile"
	},

	MovementComponent = {
		speed_modifier = 65
	},

	TaskHandlerComponent = {
		possible_tasks = {
			game.enum.task.go_to,
			game.enum.task.go_near,
			game.enum.task.go_kill,
			game.enum.task.kill,
			game.enum.task.get_in_range
		},
		blueprint = "default_task_handler"
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	AIComponent = {
		blueprint = "smart_friendly_combat_unit_ai"
	},

	EventHandlerComponent = {
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity,
			game.enum.event.meteor_falling
		}
	},

	PathfindingComponent = {
		blueprint = "cannot_break_blocks"
	}
}

-- The leader of the summonable imp gang (with limited life span).
imp_gang_boss = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.lls,
		game.enum.component.name,
		game.enum.component.combat,
		game.enum.component.movement,
		game.enum.component.task_handler,
		game.enum.component.faction,
		game.enum.component.ai,
		game.enum.component.event_handler,
		game.enum.component.pathfinding
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1500,
		regen = 10,
		defense = 20
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	LimitedLifeSpanComponent = {
		max_time = 60.0
	},

	NameComponent = {
		name = "IMP GANG BOSS"
	},

	CombatComponent = {
		range = 350,
		min_dmg = 80,
		max_dmg = 120,
		type = game.enum.atk_type.ranged,
		cooldown = 3,
		pursue = true,
		projectile_blueprint = "basic_projectile"
	},

	MovementComponent = {
		speed_modifier = 60
	},

	TaskHandlerComponent = {
		possible_tasks = {
			game.enum.task.go_to,
			game.enum.task.go_near,
			game.enum.task.go_kill,
			game.enum.task.kill,
			game.enum.task.get_in_range
		},
		blueprint = "default_task_handler"
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	AIComponent = {
		blueprint = "smart_friendly_combat_unit_ai"
	},

	EventHandlerComponent = {
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity,
			game.enum.event.meteor_falling
		}
	},

	PathfindingComponent = {
		blueprint = "cannot_break_blocks"
	}
}

if game then
	game.entity.register("imp")
	game.entity.register("imp_gang_member")
	game.entity.register("imp_gang_boss")
end
