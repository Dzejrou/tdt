-- Testing Ogre entity.
ogre_warrior = {
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
		game.enum.component.faction,
		game.enum.component.name
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
		blueprint = "smart_friendly_combat_unit_ai",
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT", -- Material is in mesh.
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	MovementComponent = {
		speed_modifier = 55
	},

	CombatComponent = {
		range = 400,
		min_dmg = 15,
		max_dmg = 30,
		type = game.enum.atk_type.ranged,
		cooldown = 3,
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
		name = "OGRE WARRIOR"
	},
}

if game then
	game.entity.register("ogre_warrior")
end
