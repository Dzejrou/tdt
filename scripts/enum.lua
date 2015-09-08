-- Represents C++ enums.
enum = {
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
		gold = 21
	},

	event = {
		none = 0,
		kill_entity = 1,
		gold_dropped = 2
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
		menu = 3
	},

	task = {
		none = 0,
		go_to = 1,
		go_near = 2,
		go_kill = 3,
		kill = 4,
		get_in_range = 5,
		go_pick_up_gold = 6,
		pick_up_gold = 7
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
		none = 8
	}
}

-- INIT:
game = game or {}
game.enum = enum
