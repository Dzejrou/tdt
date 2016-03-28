-- Smart miner that mines on it's own, used for the intro dummy
-- level.
auto_ogre_miner = {
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
		blueprint = "auto_ogre_miner",
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
		if game.event.get_type(evt) == game.enum.event.gold_dropped then
			if game.gold.full(id) then
				game.gold.go_deposit(id)
			end

			task = game.task.create(game.event.get_target(evt), game.enum.task.go_pick_up_gold)
			game.task.add(id, task)
			return true
		end

		return true
	end,

	init = function(id)
	end,

	update = function(id)
		deposit = game.gold.get_closest_gold_deposit(id)
		if deposit ~= game.const.no_ent then
			game.gui.log.print("\\[#" .. id .."\\] Gonna mine deposit #" .. deposit .. ".")
			task = game.task.create(deposit, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end,

	on_hit = function(id, hitter)
	end,

	can_break = function(id, node)
		return true
	end,

	get_cost = function(id, node)
		resident = game.grid.get_resident(node)
		hp = game.health.get(resident)

		if hp <= 0 then
			return 1
		else
			return hp
		end
	end
}

if game then
	game.entity.register("auto_ogre_miner")
end
