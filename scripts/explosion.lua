explosion = {
	components = {
		game.enum.component.physics,
		game.enum.component.graphics,
		game.enum.component.combat,
		game.enum.component.faction,
		game.enum.component.explosion,
		game.enum.component.constructor
	},

	PhysicsComponent = {
		solid = false
	},

	GraphicsComponent = {
		mesh = "sphere.mesh",
		material = "colour/transparent_orange",
		visible = true,
		manual_scaling = true,
		scale_x = 0,
		scale_y = 0,
		scale_z = 0,
		query_flags = game.enum.entity_type.misc
	},

	CombatComponent = {
		range = 200,
		min_dmg = 100,
		max_dmg = 600,
		type = game.enum.atk_type.melee,
		cooldown = 0.0,
		pursue = false
	},

	FactionComponent = {
		faction = game.enum.faction.friendly
	},

	ExplosionComponent = {
		delta = 20,
		radius = 150.0
	},

	ConstructorComponent = {
		blueprint = "damage_entities_constructor"
	}
}

if game then
	game.entity.register("explosion")
end
