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
		game.enum.component.gold
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
		faction = game.enum.faction.friendly
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
		range = 60,
		min_dmg = 50,
		max_dmg = 75,
		type = game.enum.atk_type.melee,
		cooldown = 2
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
			game.enum.task.pick_up_gold
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

	handle_event = function(id, evt)
		if game.get_event_type(evt) == game.enum.event.gold_dropped then
		game.print("Handling: " .. tostring(evt))
			task = game.create_task(game.get_event_target(evt), game.task.go_pick_up_gold)
			game.add_task(id, task)
		end
	end,

	init = function(id)
	end,

	update = function(id)
		deposit = game.get_closest_gold_deposit(id)
		if deposit ~= game.const.no_ent then
			game.show_msg("Found deposit: " .. tostring(deposit))
			task = game.create_task(deposit, game.enum.task.go_kill)
			game.add_task(id, task)
			return
		end
	end,

	finnish = function(id)
	end,

	can_break = function(id, structure)
		return true
	end,

	get_cost = function(id, structure)
		return 1
	end
}

if game then
	game.register_entity("ogre_miner")
end
