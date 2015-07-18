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

	init = function(id)
		ogre.stats.current_amount = ogre.stats.current_amount + 1
		ogre.stats.overall_amount = ogre.stats.overall_amount + 1
	end,

	update = function(id)
		mov = false
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
		elseif id == 8 then
			x, y, z = game.dir_to_enemy(id, 7)
			mov = game.move(id, x, y, z)
		end

		if id % 2 == 0 then
			game.rotate(id, 0.01)
		else
			game.rotate(id, -0.01)
		end

		if not mov then
			game.destroy_entity(id)
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
		enemy = 1
	elseif key == game.enum.input.key_down then
		enemy = 2
	elseif key == game.enum.input.key_left then
		enemy = 3
	elseif key == game.enum.input.key_right then
		enemy = 4
	else
		enemy = -1
		show_msg("key_code: " .. tostring(key))
	end

	if enemy ~= -1 then
		x, y, z = game.dir_to_enemy(id, enemy)
		game.move(id, x, y, z)
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
game.move_to(id9, 300, 100, 200)
game.delete_component(id9, game.enum.component.ai)
game.add_component(id9, game.enum.component.input)
game.set_input_handler(id9, "ogre_handler")
