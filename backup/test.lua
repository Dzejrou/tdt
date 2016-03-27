kill_event = function(id, time)
	game.print("Creating kill event: #" .. tostring(id) .. " -> " .. tostring(time) .. " seconds.")
	evt = game.entity.create("")
	game.entity.add_component(evt, game.enum.component.event)
	game.event.set_type(evt, game.enum.event.kill_entity)
	game.event.set_handler(evt, id)
	game.event.set_radius(evt, 0.0)
	game.event.set_active(evt, false)

	timer = game.entity.create("")
	game.entity.add_component(timer, game.enum.component.time)
	game.time.set_limit(timer, time)
	game.time.set_target(timer, evt)
	game.time.set_type(timer, game.enum.time_event.start_event)

	return evt, timer
end

event_test1 = function()
	id = game.entity.create("ogre")
	evt, timer = kill_event(id, 10.0)
	game.save_game("evt_test")
	return id, evt, timer
end
