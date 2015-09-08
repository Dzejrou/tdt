-- Error entity blueprint, messages are for debug purposes, disallowing
-- undefined entities to leave the development process.
ERROR = {
	init = function()
		game.show_msg("Initializing an ERROR entity.")
	end,

	update = function()
		-- DUMMY BODY
	end,

	finnish = function()
		game.show_msg("Destroying an ERROR entity.")
	end,

	input_handler = function(id, key)
		game.show_msg("Trying to move an ERROR entity.")
	end
}
