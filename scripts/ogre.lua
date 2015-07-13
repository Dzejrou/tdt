ogre = {
	components = {0, 1, 2, 3, 4, 5, 6},

	PhysicsComponent = {
		solid = true
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 1,
		defense = 8
	},

	AIComponent = {
		script_name = "ogre.lua",
		state = 0,
		faction = 0
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "Ogre"
	},

	MovementComponent = {
		speed = 10,
	},

	CombatComponent = {
		range = 15,
		min_dmg = 50,
		max_dmg = 150
	},

	EventComponent = {
		curr_event_progress = 0,
		curr_event_length = 0,
		curr_event_type = 0
	}
}