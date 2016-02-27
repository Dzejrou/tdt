-- Load all scripts:
scripts = {
	"utils.lua", "enum.lua", "error.lua",
	"ogre.lua", "evil_ogre.lua",
	"basic_wall.lua", "basic_projectile.lua",
	"barracks.lua", "evil_barracks.lua", "test.lua",
	"gold_deposit.lua", "blueprints_destructor.lua",
	"gold_pile.lua", "ogre_miner.lua", "auto_ogre_miner.lua",
	"mine.lua", "blueprints_task_handler.lua", "gold_vault.lua",
	"research.lua", "spells.lua", "indestructible_wall.lua",
	"walkway.lua", "mana_crystal.lua", "explosion.lua",
	"lls_ogre.lua"
}

if game then
	for _, s in ipairs(scripts) do
		game.load("scripts/" .. s)
	end
else
	show_msg("Game table not defined!")
end
