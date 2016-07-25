-- Standard blueprint for entities that can use destructive pathfinding.
can_break_blocks = {
	can_break = function(id, node)
		resident = game.grid.get_resident(node)
		return game.entity.has_component(resident,
				game.enum.component.mine)
	end,

	get_cost = function(id, node)
		resident = game.grid.get_resident(node)
		hp = game.health.get(resident)

		return hp
	end
}

-- Strandard blueprint for entities that can move over free
-- paths only.
cannot_break_blocks = {
	can_break = function(id, node)
		return false
	end,

	get_cost = function(id, node)
		resident = game.grid.get_resident(node)
		hp = game.health.get(resident)

		return hp
	end
}
