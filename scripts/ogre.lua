-- Testing Ogre entity.
ogre = {
	components = {
		-- type enums contained in core_utils.lua
		type.component.physics,
		type.component.health,
		type.component.ai,
		type.component.graphics,
		type.component.movement,
		type.component.combat,
		type.component.event
	},

	PhysicsComponent = {
		solid = true
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 1,
		defense = 8
	},

	AIComponent = {
		blueprint = "ogre",
		faction = 0
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "Ogre"
	},

	MovementComponent = {
		speed_modifier = 10,
	},

	CombatComponent = {
		range = 15,
		min_dmg = 50,
		max_dmg = 150,
		atk_1 = 1,
		atk_2 = 0
	},

	EventComponent = {
		curr_event_progress = 0,
		curr_event_length = 0,
		curr_event_type = 0
	},

	init = function(id)
		-- TODO:
	end,

	update = function(id)
		-- TODO:
	end,

	finnish = function(id)
		-- TODO:
	end
}