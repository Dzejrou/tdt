-- Load all scripts:
scripts = {
	"core_utils.lua", "ogre.lua", "evil_ogre.lua", "basic_wall.lua", "basic_projectile.lua",
	"barracks.lua", "evil_barracks.lua", "test.lua", "gold_deposit.lua", "blueprints_destructor.lua",
	"gold_pile.lua", "ogre_miner.lua"
}

if game then
	for _, s in ipairs(scripts) do
		game.load("scripts/" .. s)
	end
else
	show_msg("Game table not defined!")
end

-- Returns true if a given value v has a type matching
-- one of the type names passed as remaining arguments.
assert_types = function(v, ...)
	res = false

	for _, t in ipairs{...} do
		if type(t) == "string" and type(v) == t then
			res = true
		end
	end

	return res
end
