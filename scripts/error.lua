-- Error entity blueprint, messages are for debug purposes, disallowing
-- undefined entities to leave the development process.
-- TODO: Finnish all components and blueprint.
ERROR = {
	update = function()
		-- DUMMY BODY
	end,

	input_handler = function(id, key)
		game.show_msg("Trying to move an ERROR entity.")
	end,

	construct = function(id)
		game.show_msg("Trying to construct an ERROR entity.")
	end,

	destroy = function(id, killer)
		game.show_msg("Trying to destroy an ERROR entity.")
	end,

	trigger = function(id, target)
		game.show_msg("Trying to trigger an ERROR entity.")
	end
}
