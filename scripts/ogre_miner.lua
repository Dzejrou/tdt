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
		game.enum.component.faction
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
		speed_modifier = 0.5,
	},

	CombatComponent = {
		range = 300,
		min_dmg = 100,
		max_dmg = 200,
		type = game.enum.atk_type.melee,
		cooldown = 2.0
	},

	PathfindingComponent = {
		blueprint = "ogre"
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
		handler = "ogre",
		possible_events = {
			game.enum.event.kill_entity,
			game.enum.event.gold_dropped
		}
	},

	GoldComponent = {
		curr = 0,
		max = 1000	
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	handle_event = function(id, evt)
		if game.get_event_type(evt) == game.enum.event.gold_dropped then
			task = game.create_task(game.get_event_target(evt), game.task.go_pick_up_gold)
			game.add_task(id, task)
			return true
		end
	end,

	init = function(id)
	end,

	update = function(id)
		deposit = game.get_closest_gold_deposit(id)
		if deposit ~= game.const.no_ent then
			task = game.create_task(deposit, game.enum.task.go_kill)
			game.add_task(id, task)
			return
		end
	end,

	can_break = function(id, node)
		return true
	end,

	get_cost = function(id, node)
		resident = game.get_resident(node)
		hp = game.get_health(resident)

		if hp <= 0 then
			return 1
		else
			return hp
		end
	end
}

if game then
	game.register_entity("ogre_miner")
end
