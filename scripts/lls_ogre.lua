-- Testing Ogre entity with limited life span.
lls_ogre = {
	components = {
		-- Enums contained in core_utils.lua
		game.enum.component.physics,
		game.enum.component.health,
		game.enum.component.graphics,
		game.enum.component.lls,
		game.enum.component.name
	},

	PhysicsComponent = {
		solid = false
	},

	HealthComponent = {
		max_hp = 1000,
		regen = 1,
		defense = 8
	},

	GraphicsComponent = {
		mesh = "ogrehead.mesh",
		material = "NO_MAT", -- Material is in mesh.
		visible = true,
		manual_scaling = false,
		query_flags = game.enum.entity_type.minion
	},

	LimitedLifeSpanComponent = {
		max_time = 5.0
	},

	NameComponent = {
		name = "LLS Ogre TEST"
	}
}

if game then
	game.entity.register("lls_ogre")
end
