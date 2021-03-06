-- Represents C++ enums.
game.enum = {
	entity_type = {
		none = 0,
		wall = 1,
		minion = 2,
		enemy = 4,
		building = 8,
		misc = 16
	},
	
	component = {
		none = -1,
		physics = 0,
		health = 1,
		ai = 2,
		graphics = 3,
		movement = 4,
		combat = 5,
		event = 6,
		input = 7,
		time = 8,
		mana = 9,
		spell = 10,
		production = 11,
		grid_node = 12,
		product = 13,
		pathfinding = 14,
		task = 15,
		task_handler = 16,
		structure = 17,
		homing = 18,
		event_handler = 19,
		destructor = 20,
		gold = 21,
		faction = 22,
		price = 23,
		align = 24,
		mine =25,
		mana_crystal = 26,
		on_hit = 27,
		constructor = 28,
		trigger = 29,
		upgrade = 30,
		notification = 31,
		explosion = 32,
		lls = 33,
		name = 34,
		exp_val = 35,
		light = 36,
		command = 37,
		counter = 38,
		portal = 39,
		animation = 40
	},

	animation = {
		walk = 0,
		idle = 1,
		hit = 2
	},

	event = {
		none = 0,
		kill_entity = 1,
		gold_dropped = 2,
		restore_speed = 3,
		meteor_falling = 4
	},

	faction = {
		friendly = 0,
		enemy = 1,
		neutral = 2
	},

	input = {
		-- Will be set in InputSystem's constructor.
		key_up = 0,
		key_down = 1,
		key_left = 2,
		key_right = 3,
	},

	game_state = {
		running = 0,
		ended = 1,
		paused = 2,
		menu = 3,
		intro_menu = 4
	},

	task = {
		none = 0,
		go_to = 1,
		go_near = 2,
		go_kill = 3,
		kill = 4,
		get_in_range = 5,
		go_pick_up_gold = 6,
		pick_up_gold = 7,
		go_deposit_gold = 8,
		deposit_gold = 9
	},

	atk_type = {
		none = 0,
		melee = 1,
		ranged = 2
	},

	time_event = {
		none = 0,
		start_event = 1,
		end_event = 2
	},

	direction = {
		up = 0,
		down = 1,
		left = 2,
		right = 3,
		up_left = 4,
		up_right = 5,
		down_left = 6,
		down_right = 7,
		portal = 8,
		none = 9
	},

	spell_type = {
		none = 0,
		targeted = 1,
		positional = 2,
		global = 3,
		placing = 4
	},

	command = {
		mine = 0,
		attack = 1,
		reposition = 2,
		return_gold = 3,
		fall_back = 4
	},

	wave_state = {
		active = 0,
		waiting = 1,
		inactive = 2
	}
}
