show_msg("This is actually from Lua!")

board = {
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 2, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
}

get_block_id = function(x, y)
	return board[x][y]
end

programmer = {
	name = "Dzejrou",
	age = 23,
	history = {
		high_school = "Omska",
		university = "MMF UK"
	}
}

function sum(...)
	local s = 0
	for _, v in ipairs{...} do
		s = s + v
	end
	return s
end