ogre = {
	PhysicsComponent = {
		x = 0,
		y = 0,
		z = 0
	},

	HealthComponent = {
		max_hp = 1000,
		curr_hp = 1000,
		regen = 1
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
		mov_x = 0,
		mov_y = 0,
		mov_z = 0,

		speed_x = 0,
		speed_y = 0,
		speed_z = 0,

		moving = false
	},

	CombatComponent = {
		range = 15,

		min_dmg = 50,
		max_dmg = 150
	},

	TaskComponent = {
		progress = 0,
		curr_task_length = 0,
		curr_task_type = 0
	}
}