-- Building representing the player's life, it's death ends the game.
dungeon_throne = {
	components = {
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.structure,
		game.enum.component.destructor,
		game.enum.component.faction,
		game.enum.component.name,
		game.enum.component.constructor,
		game.enum.component.mine
	},

	PhysicsComponent = {
		solid = true
	},

	HealthComponent = {
		max_hp = 10000,
		regen = 1,
		defense = 50
	},

	GraphicsComponent = {
		mesh = "cube.mesh",
		material = "colour/dark_gray",
		visible = true,
		manual_scaling = true,
		scale_x = 45,
		scale_y = 30,
		scale_z = 45,
		query_flags = game.enum.entity_type.wall
	},

	StructureComponent = {
		radius = 0,
		walk_through = false
	},

	DestructorComponent = {
		blueprint = "lose_game_destructor"
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	NameComponent = {
		name = "THE DUNGEON THRONE"
	},

	ConstructorComponent = {
		blueprint = "throne_constructor"
	}
}

if game then
	game.entity.register("dungeon_throne")
end
