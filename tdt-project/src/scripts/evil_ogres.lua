-- Basic melee ogre warrior. Attacks enemies on sight
-- if they are accessible.
evil_ogre_warrior = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 4250,
		regen = 20,
		defense = 60
	},

	AIComponent = {
		blueprint = "smart_enemy_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55
	},

	CombatComponent = {
		range = 100,
		min_dmg = 150,
		max_dmg = 300,
		type = game.enum.atk_type.melee,
		cooldown = 1.5,
		pursue = false,
		projectile_blueprint = "basic_projectile"
	},

	PathfindingComponent = {
		blueprint = "can_break_blocks"
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

	EventHandlerComponent = {
		handler = "dumb_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE WARRIOR"
	},

	ExperienceValueComponent = {
		value = 10
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

-- Mage that fires freezing projectiles and casts freezing waves
-- around him.
evil_ogre_ice_mage = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.spell,
		game.enum.component.mana,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 2500,
		regen = 15,
		defense = 40
	},

	AIComponent = {
		blueprint = "smart_enemy_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55
	},

	CombatComponent = {
		range = 400,
		min_dmg = 200,
		max_dmg = 300,
		type = game.enum.atk_type.ranged,
		cooldown = 2.5,
		pursue = false,
		projectile_blueprint = "freezing_projectile"
	},

	PathfindingComponent = {
		blueprint = "can_break_blocks"
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

	EventHandlerComponent = {
		handler = "smart_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE ICE MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.enemy_freezing_wave",
		cooldown = 15.0
	},

	ManaComponent = {
		max_mana = 500,
		regen = 5
	},

	ExperienceValueComponent = {
		value = 15
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

-- Basic melee ogre warrior. Attacks enemies on sight
-- if they are accessible.
evil_ogre_thunder_mage = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.spell,
		game.enum.component.mana,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 3000,
		regen = 18,
		defense = 35
	},

	AIComponent = {
		blueprint = "smart_enemy_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55
	},

	CombatComponent = {
		range = 400,
		min_dmg = 50,
		max_dmg = 600,
		type = game.enum.atk_type.ranged,
		cooldown = 1.5,
		pursue = false,
		projectile_blueprint = "lightning_projectile"
	},

	PathfindingComponent = {
		blueprint = "can_break_blocks"
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

	EventHandlerComponent = {
		handler = "smart_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE THUNDER MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.chain_lightning",
		cooldown = 10.0
	},

	ManaComponent = {
		max_mana = 350,
		regen = 20
	},

	ExperienceValueComponent = {
		value = 20
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

-- Mage that fires slowing projectiles and occasionally
-- spawns meteors at his enemies' position.
evil_ogre_fire_mage = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.spell,
		game.enum.component.mana,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 2250,
		regen = 13,
		defense = 55
	},

	AIComponent = {
		blueprint = "smart_enemy_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55
	},

	CombatComponent = {
		range = 400,
		min_dmg = 200,
		max_dmg = 400,
		type = game.enum.atk_type.ranged,
		cooldown = 3,
		pursue = false,
		projectile_blueprint = "slowing_projectile"
	},

	PathfindingComponent = {
		blueprint = "can_break_blocks"
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

	EventHandlerComponent = {
		handler = "smart_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE FIRE MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.enemy_meteor",
		cooldown = 10.0
	},

	ManaComponent = {
		max_mana = 400,
		regen = 15
	},

	ExperienceValueComponent = {
		value = 25
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

-- Healer that shoots basic projectiles and heals
-- his nearby allies with a healing wave.
evil_ogre_cleric = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.spell,
		game.enum.component.mana,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 3250,
		regen = 10,
		defense = 35
	},

	AIComponent = {
		blueprint = "smart_enemy_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 45
	},

	CombatComponent = {
		range = 500,
		min_dmg = 50,
		max_dmg = 100,
		type = game.enum.atk_type.ranged,
		cooldown = 1,
		pursue = false,
		projectile_blueprint = "basic_projectile"
	},

	PathfindingComponent = {
		blueprint = "cannot_break_blocks"
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

	EventHandlerComponent = {
		handler = "smart_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE CLERIC"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.enemy_healing_wave",
		cooldown = 30.0
	},

	ManaComponent = {
		max_mana = 600,
		regen = 15
	},

	ExperienceValueComponent = {
		value = 30
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

-- Mage that fires slowing projectiles and occasionally
-- casts a random spell to crush his enemies.
evil_ogre_chaos_mage = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.spell,
		game.enum.component.mana,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 3250,
		regen = 15,
		defense = 65
	},

	AIComponent = {
		blueprint = "smart_enemy_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 65
	},

	CombatComponent = {
		range = 450,
		min_dmg = 300,
		max_dmg = 450,
		type = game.enum.atk_type.ranged,
		cooldown = 1.5,
		pursue = false,
		projectile_blueprint = "slowing_projectile"
	},

	PathfindingComponent = {
		blueprint = "can_break_blocks"
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

	EventHandlerComponent = {
		handler = "smart_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE CHAOS MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.enemy_random_spell",
		cooldown = 5.0
	},

	ManaComponent = {
		max_mana = 600,
		regen = 15
	},

	ExperienceValueComponent = {
		value = 50
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	}
}

-- Testing dummy enemy.
evil_ogre_test = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.ai,
		game.enum.component.exp_val,
		game.enum.component.destructor
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1000000,
		regen = 100,
		defense = 0
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT",
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55
	},

	CombatComponent = {
		range = 100,
		min_dmg = 150,
		max_dmg = 300,
		type = game.enum.atk_type.melee,
		cooldown = 1.5,
		pursue = false,
		projectile_blueprint = "basic_projectile"
	},

	PathfindingComponent = {
		blueprint = "can_break_blocks"
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

	EventHandlerComponent = {
		handler = "dumb_enemy_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

	NameComponent = {
		name = "EVIL OGRE TEST DUMMY"
	},

	AIComponent = {
		blueprint = "evil_ogre_test",
	},

	ExperienceValueComponent = {
		value = 100
	},

	DestructorComponent = {
		blueprint = "give_experience_destructor"
	},

	update = function(id)
		-- DUMMY!
	end
}

if game then
	game.entity.register("evil_ogre_warrior")
	game.entity.register("evil_ogre_ice_mage")
	game.entity.register("evil_ogre_thunder_mage")
	game.entity.register("evil_ogre_fire_mage")
	game.entity.register("evil_ogre_cleric")
	game.entity.register("evil_ogre_chaos_mage")
	game.entity.register("evil_ogre_test")
end
