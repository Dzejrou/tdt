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
		game.enum.component.task_handler,
		game.enum.component.faction,
		game.enum.component.evt_handler
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
		blueprint = "evil_ogre",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT", -- Material is in mesh.
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.enemy
	},

	MovementComponent = {
		speed_modifier = 55,
	},

	CombatComponent = {
		range = 800,
		min_dmg = 15,
		max_dmg = 30,
		type = game.enum.atk_type.ranged,
		cooldown = 3,
		pursue = true,
		projectile_blueprint = "basic_projectile"
	},

	EventHandlerComponent = {
		handler = "evil_ogre",
		possible_events = {
			game.enum.event.kill_entity,
			game.enum.event.restore_speed
		}
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

	FactionComponent = {
		faction = game.enum.faction.enemy
	},

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

	on_hit = function(id, hitter)
	end,

	can_break = function(id, node)
		resident = game.grid.get_resident(node)
		return game.entity.has_component(resident,
				game.enum.component.mine)
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
	game.entity.register("evil_ogre")
end
