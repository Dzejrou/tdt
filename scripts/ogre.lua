-- Testing Ogre entity.
ogre = {
	components = {
		-- Enums contained in core_utils.lua
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.ai,
		game.enum.component.graphics,
		game.enum.component.movement,
		game.enum.component.combat,
		game.enum.component.event
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 1,
		defense = 8
	},

	AIComponent = {
		blueprint = "ogre",
		faction = game.enum.faction.friendly
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "Ogre",
		visible = true
	},

	MovementComponent = {
		speed_modifier = 0.01,
	},

	CombatComponent = {
		range = 15,
		min_dmg = 50,
		max_dmg = 150,
		atk_1 = 1,
		atk_2 = 0
	},

	EventComponent = {
		curr_event_progress = 0,
		curr_event_length = 0,
		curr_event_type = 0
	},

	InputComponent = {
		-- Won't get loaded, but serves as a blueprint if needed.
		input_handler = "ogre_handler"
	},

	init = function(id)
		ogre.stats.current_amount = ogre.stats.current_amount + 1
		ogre.stats.overall_amount = ogre.stats.overall_amount + 1
	end,

	update = function(id)
		mov = true
		if id == 0 then
			mov = game.move(id, 5, 0, -2)
		elseif id == 1 then
			mov = game.move(id, -5, 0, 2)
		elseif id == 2 then
			mov = game.move(id, -5, 0, -2)
		elseif id == 3 then
			mov = game.move(id, 5, 0, 2)
		elseif id == 4 then
			mov = game.move(id, 0, 5, 0)
		elseif id == 5 then
			mov = game.move(id6, 0, -5, 0)
		elseif id == 6 then
			mov = game.move(id, 0, 0, -5)
		elseif id == 7 then
			mov = game.move(id, 0, 0, 5)
		end

		if id % 2 == 0 then
			game.rotate(id, 0.01)
		elseif id ~= 9 then
			game.rotate(id, -0.01)
		end
	end,

	finnish = function(id)
		ogre.stats.current_amount = ogre.stats.current_amount - 1
		show_msg("Ogre #" .. tostring(id) .. " has been destroyed!\nCurrent: "
		         .. tostring(ogre.stats.current_amount) .. "\tOverall: "
			 .. tostring(ogre.stats.overall_amount))
	end,

	stats = {
		current_amount = 0,
		overall_amount = 0,
		default_blueprint = "ogre"
	}
}

ogre_handler = function(id, key)
	if key == game.enum.input.key_up then
		game.move(id, game.get_dir(id))
	elseif key == game.enum.input.key_down then
		game.move(id, game.get_dir_back(id))
	elseif key == game.enum.input.key_left then
		game.rotate(id, 0.01)
	elseif key == game.enum.input.key_right then
		game.rotate(id, -0.01)
	end
end

ogre.PhysicsComponent.solid = false

id1 = game.create_entity("ogre")
game.move_to(id1, 100, 100, 100)

id2 = game.create_entity("ogre")
game.move_to(id2, 100, 100, 100)

id3 = game.create_entity("ogre")
game.move_to(id3, 100, 100, 100)

id4 = game.create_entity("ogre")
game.move_to(id4, 100, 100, 100)

id5 = game.create_entity("ogre")
game.move_to(id5, 100, 100, 100)

id6 = game.create_entity("ogre")
game.move_to(id6, 100, 100, 100)

-- ogre.PhysicsComponent.solid = true
game.utils.get_blueprint_table(id6).PhysicsComponent.solid = true
id7 = game.create_entity("ogre")
game.move_to(id7, -200, 100, 400)


id8 = game.create_entity("ogre")
game.move_to(id8, -200, 100, 100)

ogre.PhysicsComponent.solid = false
ogre.MovementComponent.speed_modifier = 0.4
id9 = game.create_entity("ogre")
game.move_to(id9, -100, 30, 100)

id10 = game.create_entity("ogre")
game.move_to(id10, -100, 30, -100)