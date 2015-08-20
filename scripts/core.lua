-- Load all scripts:
scripts = {
	"core_utils.lua", "ogre.lua", "evil_ogre.lua", "basic_wall.lua", "basic_projectile.lua",
	"barracks.lua", "evil_barracks.lua"
}

if game then
	for _, s in ipairs(scripts) do
		game.load("scripts/" .. s)
	end
else
	show_msg("Game table not defined!")
end
