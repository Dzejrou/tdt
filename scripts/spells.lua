-- Table that contains the individual spell tables.
-- Each spell table needs two fields: price (integer)
-- and cast (function that gets called when the spell is cast).
game.spell.spells = {
	-- Basic player spell, commands the miner with fewest tasks
	-- to mine every currently selected mineable entity.
	mine = {
		price = 0,
		cast = function()
			game.command.mine()
		end
	},

	-- Heals a friendly target to full health.
	heal = {
		price = 10,
		cast = function()
			local target = game.get_selected_entity()
			if game.ai.get_faction(target) == game.enum.faction.friendly then
				game.health.heal(target)
			else
				game.spell.refund_("heal")
			end
		end
	}
}

-- Used to return mana to the player if a spell can't be used
-- for some reason.
-- Param: Name of the spell.
game.spell.refund_ = function(spell)
	game.player.add_mana(game.spell.spells[spell].price)
end

game.spell.register_spell("mine")
