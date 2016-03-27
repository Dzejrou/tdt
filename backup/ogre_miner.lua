ogre_miner = {
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
		game.enum.component.gold,
		game.enum.component.faction,
		game.enum.component.notification,
		game.enum.component.on_hit,
		game.enum.component.name,
		game.enum.component.upgrade,
		game.enum.component.command
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 1,
		defense = 8
	},

	AIComponent = {
		blueprint = "ogre_miner",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT", -- Material is in mesh.
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 45
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
		blueprint = "ogre_miner",
		exp_needed = 100,
		level_cap = 10
	},

	CommandComponent = {
		possible_commands = {
			game.enum.command.mine
		}
	},

	update = function(id)
		-- TODO: Check for damaged buildings?
		-- TODO: Check for dropped gold piles?
	end,

	upgrade = function(id)
		game.health.heal(id)
		game.health.buff(id, 500)
		min, max = game.combat.get_dmg_range(id)
		game.combat.set_dmg_range(id, min + 20, max + 30)
	end
}

if game then
	game.entity.register("ogre_miner")
end
