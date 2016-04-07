-- Main testing wave scenario.
game.wave.wave_test = {
	init = function()
		local w = game.wave
		w.clear_entity_blueprints()
		w.set_wave_count(3)
		w.set_curr_wave_number(0)
		w.set_countdown(300)
	end,

	wstart_0 = function()
		local w = game.wave
		w.set_entity_total(2)
		w.add_entity_blueprint("evil_ogre_warrior")
		w.add_entity_blueprint("evil_ogre_warrior")
		w.set_spawn_cooldown(15.0)
	end,

	wend_0 = function()
		local w = game.wave
		w.set_countdown(240)
	end,

	wstart_1 = function()
		local w = game.wave
		w.set_entity_total(4)
		w.add_entity_blueprint("evil_ogre_thunder_mage")
		w.add_entity_blueprint("evil_ogre_ice_mage")
		w.set_spawn_cooldown(10.0)
	end,

	wend_1 = function()
		local w = game.wave
		w.set_countdown(180)
	end,

	wstart_2 = function()
		local w = game.wave
		w.set_entity_total(6)
		w.add_entity_blueprint("evil_ogre_fire_mage")
		w.add_entity_blueprint("evil_ogre_cleric")
		w.set_spawn_cooldown(5.0)
	end,

	wend_2 = function()
		game.win()
	end,
}
