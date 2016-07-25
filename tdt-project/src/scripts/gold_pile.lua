-- Gets dropped by the gold deposits when they are killed, can be picked
-- up by miners.
gold_pile = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.gold,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/gold",
		visible = true,
		manual_scaling = true,
		scale_x = 15,
		scale_y = 10,
		scale_z = 15,
		query_flags = game.enum.entity_type.misc
	},

	GoldComponent = {
		curr = 100,
		max = 100
	},

	NameComponent = {
		name = "GOLD PILE"
	}
}

if game then
	game.entity.register("gold_pile")
end
