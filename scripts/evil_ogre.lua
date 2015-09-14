-- Testing Ogre entity.
evil_ogre = {
	components = {
		-- Enums contained in core_utils.lua
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.pathfinding,
		game.enum.component.task_handler
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
		faction = game.enum.faction.enemy
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT", -- Material is in mesh.
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.enemy
	},

	MovementComponent = {
		speed_modifier = 0.5,
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
		blueprint = "evil_ogre"
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

	init = function(id)
		evil_ogre.stats.current_amount = evil_ogre.stats.current_amount + 1
		evil_ogre.stats.overall_amount = evil_ogre.stats.overall_amount + 1
	end,

	update = function(id)
		enemy = game.closest_enemy_in_sight(id)
		if enemy ~= game.const.no_ent then
			task = game.create_task(enemy, game.enum.task.go_kill)
			game.add_task(id, task)
			return
		end

		-- If failed, try enemy not in sight.
		enemy = game.closest_enemy(id)
		if enemy ~= game.const.no_ent then
			task = game.create_task(enemy, game.enum.task.go_kill)
			game.add_task(id, task)
			return
		end
	end,

	finnish = function(id)
		evil_ogre.stats.current_amount = evil_ogre.stats.current_amount - 1
	end,

	stats = {
		current_amount = 0,
		overall_amount = 0,
		default_blueprint = "evil_ogre"
	},

	can_break = function(id, node)
		return false
	end,

	get_cost = function(id, node)
		return 1
	end
}

if game then
	game.register_entity("evil_ogre")
end
