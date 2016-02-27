-- Auxiliary function used to get the name of a research point
-- at the given spot in the research table.
-- Param: Row number.
-- Param: Column number.
game.gui.research.get_name = function(i, j)
	return game.gui.research.research_[(i - 1) * 7 + j].name
end

-- Auxiliary function used to get the price of a research point
-- at the given spot in the research table.
-- Param: Row number.
-- Param: Column number.
game.gui.research.get_price = function(i, j)
	return game.gui.research.research_[(i - 1) * 7 + j].price
end

-- Auxiliary function that unlocks a research point at the
-- given spot in the research table.
-- Param: Row number.
-- Param: Column number.
game.gui.research.unlock = function(i, j)
	game.gui.research.research_[(i - 1) * 7 + j].unlock()
end

-- Table containing info about the individual research points.
game.gui.research.research_ = {
	-- 1x1
	{
		name = "BARRACKS",
		price = 400,
		unlock = function()
			game.gui.builder.register_building("barracks")
		end
	},

	-- 1x2
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 1x3
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 1x4
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 1x5
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 1x6
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 1x7
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 2x1
	{
		name = "HEAL",
		price = 200,
		unlock = function()
			game.spell.register_spell("heal")
		end
	},

	-- 2x2
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 2x3
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 2x4
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 2x5
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 2x6
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 2x7
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 3x1
	{
		name = "MANA CRYSTAL",
		price = 400,
		unlock = function()
			game.gui.builder.register_building("mana_crystal")
		end
	},

	-- 3x2
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 3x3
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 3x4
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 3x5
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 3x6
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 3x7
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x1
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x2
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x3
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x4
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x5
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x6
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 4x7
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x1
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x2
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x3
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x4
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x5
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x6
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 5x7
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x1
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x2
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x3
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x4
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x5
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x6
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	},

	-- 6x7
	{
		name = "TODO",
		price = 0,
		unlock = function()
			-- TODO:
		end
	}
}
