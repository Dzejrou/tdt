-- Creates a pile of gold after an entity is killed, contains
-- all of the entity's gold. Also creates an event announcing
-- the appearance of a new gold pile on the ground so that minions
-- in range can pick it up.
drop_gold_destructor = {
	dtor = function(id, killer)
		-- TODO: Add experience to the killer?

		local pile = game.create_entity("gold_pile")
		game.set_curr_gold(pile, game.get_curr_gold(id))
		game.set_max_gold(pile, game.get_max_gold(id))
		local x1, y1, z1 = game.get_position(pile)
		local x2, y2, z2 = game.get_position(id)
		game.move_to(pile, x2, y1, z2)

		local evt = game.create_entity("")
		game.add_component(evt, game.enum.component.event)
		game.set_event_target(evt, pile)
		game.set_event_type(evt, game.enum.event.gold_dropped)
		game.set_event_radius(evt, 300.0)

		if killer and killer ~= game.const.no_ent then
			game.set_handler_of_event(evt, killer)
		end
	end
}
