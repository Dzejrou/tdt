-- Testing Ogre entity.
ogre = {
	components = {
		-- types enums contained in core_utils.lua
		types.component.physics,
		types.component.health,
		types.component.ai,
		types.component.graphics,
		types.component.movement,
		types.component.combat,
		types.component.event
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
		curr_event_types = 0
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

id1 = create_entity("ogre")
show_msg("created ogre #" .. tostring(id1))
id2 = create_entity("ogre")
show_msg("created ogre #" .. tostring(id2))
