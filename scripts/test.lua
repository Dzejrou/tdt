kill_event = function(id, time)
	game.print("Creating kill event: #" .. tostring(id) .. " -> " .. tostring(time) .. " seconds.")
	evt = game.create_entity("")
	game.add_component(evt, game.enum.component.event)
	game.set_event_type(evt, game.enum.event.kill_entity)
	game.set_event_target(evt, id)
	game.set_event_radius(evt, 0.0)
	game.set_event_active(evt, false)

	timer = game.create_entity("")
	game.add_component(timer, game.enum.component.time)
	game.set_time_limit(timer, time)
	game.set_timer_target(timer, evt)
	game.set_timer_type(timer, game.enum.time_event.start_event)

	return evt, timer
end

event_test1 = function()
	id = game.create_entity("ogre")
	evt, timer = kill_event(id, 10.0)
	game.save_game("evt_test")
	return id, evt, timer
end
