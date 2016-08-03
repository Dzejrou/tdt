-- Basic mining entity with no AI. Awaits for MINE commands
-- and runs away when attacked.
ogre_miner = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
		game.enum.component.gold,
		game.enum.component.faction,
		game.enum.component.notification,
		game.enum.component.on_hit,
		game.enum.component.name,
		game.enum.component.upgrade,
		game.enum.component.command,
		game.enum.component.animation
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 3000,
		regen = 10,
		defense = 30
	},

	GraphicsComponent = {
		mesh = "humanoid.mesh",
		material = "colour/blue",
		visible = true,
		manual_scaling = true,
		scale_x = 25.0,
		scale_y = 30.0,
		scale_z = 25.0,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 50
	},

	CombatComponent = {
		range = 300,
		min_dmg = 100,
		max_dmg = 200,
		type = game.enum.atk_type.ranged,
		cooldown = 2.0,
		pursue = true,
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
			game.enum.task.get_in_range,
			game.enum.task.go_pick_up_gold,
			game.enum.task.pick_up_gold,
			game.enum.task.go_deposit_gold,
			game.enum.task.deposit_gold
		},
		blueprint = "default_task_handler"
	},

	EventHandlerComponent = {
		handler = "smart_friendly_mining_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity,
			game.enum.event.gold_dropped,
			game.enum.event.meteor_falling
		}
	},

	GoldComponent = {
		curr = 0,
		max = 1000	
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	OnHitComponent = {
		blueprint = "run_away_on_hit_with_notification",
		cooldown = 1.0
	},

	NotificationComponent = {
		cooldown = 10.0
	},

	NameComponent = {
		name = "OGRE MINER"
	},

	UpgradeComponent = {
		blueprint = "friendly_miner_upgrade",
		exp_needed = 100,
		level_cap = 10
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.mine,
			game.enum.command.return_gold,
			game.enum.command.fall_back
		}
	},

	AnimationComponent = {
		possible_animations = {
			game.enum.animation.walk,
			game.enum.animation.hit
		}
	},

	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 500)
		min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 20, max + 30)
	end
}

-- Basic melee ogre warrior. Attacks enemies on sight
-- if they are accessible.
ogre_warrior = {
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
		game.enum.component.command,
		game.enum.component.upgrade
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
		blueprint = "dumb_friendly_combat_unit_ai",
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
		max_dmg = 250,
		type = game.enum.atk_type.melee,
		cooldown = 1.5,
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
		handler = "dumb_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "OGRE WARRIOR"
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.attack,
			game.enum.command.reposition,
			game.enum.command.fall_back
		}
	},

	UpgradeComponent = {
		blueprint = "friendly_warrior_upgrade",
		exp_needed = 100,
		level_cap = 10
	}
}

-- Mage that fires freezing projectiles and casts freezing waves
-- around him.
ogre_ice_mage = {
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
		game.enum.component.command,
		game.enum.component.upgrade
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
		blueprint = "smart_friendly_combat_unit_ai",
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
		max_dmg = 250,
		type = game.enum.atk_type.ranged,
		cooldown = 2.5,
		pursue = false,
		projectile_blueprint = "freezing_projectile"
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
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "OGRE ICE MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.friendly_freezing_wave",
		cooldown = 15.0
	},

	ManaComponent = {
		max_mana = 500,
		regen = 5
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.attack,
			game.enum.command.reposition,
			game.enum.command.fall_back
		}
	},

	UpgradeComponent = {
		blueprint = "friendly_mage_upgrade",
		exp_needed = 100,
		level_cap = 10
	}
}

-- Basic melee ogre warrior. Attacks enemies on sight
-- if they are accessible.
ogre_thunder_mage = {
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
		game.enum.component.command,
		game.enum.component.upgrade
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
		blueprint = "smart_friendly_combat_unit_ai",
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
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "OGRE THUNDER MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.chain_lightning",
		cooldown = 20.0
	},

	ManaComponent = {
		max_mana = 350,
		regen = 20
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.attack,
			game.enum.command.reposition,
		}
	},

	UpgradeComponent = {
		blueprint = "friendly_mage_upgrade",
		exp_needed = 100,
		level_cap = 10
	}
}

-- Mage that fires slowing projectiles and occasionally
-- spawns meteors at his enemies' position.
ogre_fire_mage = {
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
		game.enum.component.command,
		game.enum.component.upgrade
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
		blueprint = "smart_friendly_combat_unit_ai",
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
		cooldown = 3,
		pursue = false,
		projectile_blueprint = "slowing_projectile"
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
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "OGRE FIRE MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.friendly_meteor",
		cooldown = 10.0
	},

	ManaComponent = {
		max_mana = 400,
		regen = 15
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.attack,
			game.enum.command.reposition,
			game.enum.command.fall_back
		}
	},

	UpgradeComponent = {
		blueprint = "friendly_mage_upgrade",
		exp_needed = 100,
		level_cap = 10
	}
}

-- Healer that shoots basic projectiles and heals
-- his nearby allies with a healing wave.
ogre_cleric = {
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
		game.enum.component.command,
		game.enum.component.upgrade
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
		blueprint = "smart_friendly_combat_unit_ai",
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
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "OGRE CLERIC"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.friendly_healing_wave",
		cooldown = 25.0
	},

	ManaComponent = {
		max_mana = 600,
		regen = 15
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.attack,
			game.enum.command.reposition,
			game.enum.command.fall_back
		}
	},

	UpgradeComponent = {
		blueprint = "friendly_mage_upgrade",
		exp_needed = 100,
		level_cap = 10
	}
}

-- Mage that fires slowing projectiles and occasionally
-- casts a random spell to crush his enemies.
ogre_chaos_mage = {
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
		game.enum.component.command,
		game.enum.component.upgrade
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
		blueprint = "smart_friendly_combat_unit_ai",
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
		max_dmg = 400,
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
		handler = "smart_friendly_combat_unit_evt_handling",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "OGRE CHAOS MAGE"
	},

	SpellComponent = {
		blueprint = "game.entity_spells.friendly_random_spell",
		cooldown = 5.0
	},

	ManaComponent = {
		max_mana = 600,
		regen = 15
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.attack,
			game.enum.command.reposition,
			game.enum.command.fall_back
		}
	},

	UpgradeComponent = {
		blueprint = "friendly_mage_upgrade",
		exp_needed = 100,
		level_cap = 10
	}
}

if game then
	game.entity.register("ogre_miner")
	game.entity.register("ogre_warrior")
	game.entity.register("ogre_ice_mage")
	game.entity.register("ogre_thunder_mage")
	game.entity.register("ogre_fire_mage")
	game.entity.register("ogre_cleric")
	game.entity.register("ogre_chaos_mage")
end
