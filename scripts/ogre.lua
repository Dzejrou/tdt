-- Testing Ogre entity.
ogre = {
	components = {
		-- Enums contained in core_utils.lua
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler,
		game.enum.component.event_handler,
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
		blueprint = "ogre",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT", -- Material is in mesh.
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55,
	},

	CombatComponent = {
		range = 800,
		min_dmg = 15,
		max_dmg = 30,
		type = game.enum.atk_type.ranged,
		cooldown = 3
	},

	EventComponent = {
		curr_event_progress = 0,
		curr_event_length = 0,
		curr_event_type = 0
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
			game.enum.task.get_in_range
		},
		blueprint = "default_task_handler"
	},

	InputComponent = {
		-- Won't get loaded, but serves as a blueprint if needed.
		input_handler = "ogre_handler"
	},

	EventHandlerComponent = {
		handler = "ogre",
		possible_events = {
			game.enum.event.kill_entity
		}
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	handle_event = function(id, evt)
		-- TODO:
	end,

	init = function(id)
		ogre.stats.current_amount = ogre.stats.current_amount + 1
		ogre.stats.overall_amount = ogre.stats.overall_amount + 1
	end,

	update = function(id)
		enemy = game.combat.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end

		-- If failed, try enemy not in sight.
		enemy = game.combat.closest_enemy(id)
		if enemy ~= game.const.no_ent then
			task = game.task.create(enemy, game.enum.task.go_kill)
			game.task.add(id, task)
			return
		end
	end,

	finnish = function(id)
		ogre.stats.current_amount = ogre.stats.current_amount - 1
	end,

	stats = {
		current_amount = 0,
		overall_amount = 0,
		default_blueprint = "ogre"
	},

	can_break = function(id, node)
		return true
	end,

	get_cost = function(id, node)
		resident = game.grid.get_resident(node)
		hp = game.health.get(resident)

		if hp == 0 then
			return 1
		else
			return hp
		end
	end
}

ogre_handler = {
	handle = function(id, key)
		if key == game.enum.input.key_up then
			game.movement.move(id, game.movement.get_dir(id))
		elseif key == game.enum.input.key_down then
			game.movement.move(id, game.movement.get_dir_back(id))
		elseif key == game.enum.input.key_left then
			game.graphics.rotate(id, 0.01)
		elseif key == game.enum.input.key_right then
			game.graphics.rotate(id, -0.01)
		end
	end
end

if game then
	game.entity.register("ogre")
end
