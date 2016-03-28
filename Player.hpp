#pragma once

#include <vector>
#include <string>
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary class representing the player's resources, since the nature
 * of the game does not allow creating player as an entity (only one player
 * can exist at a time) and it allows for easy GUI modifications when the amount
 * of these resources changes (had player been an entity, ever gold/mana addition would
 * require a check which would be true only in minimal number of cases).
 */
class Player
{
	public:
		/**
		 * Destructor.
		 */
		~Player() {}

		/**
		 * Brief: Adds gold to the player's gold stash.
		 * Param: Amount to add.
		 */
		void add_gold(tdt::uint);

		/**
		 * Brief: Removes gold from the player's gold stash if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_gold(tdt::uint);

		/**
		 *
		 * Brief: Adds mana to the player's mana pool.
		 * Param: Amount to add.
		 */
		void add_mana(tdt::uint);

		/**
		 * Brief: Removes mana from the player's mana pool if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_mana(tdt::uint);

		/**
		 * Breif: Increases the mana capacity of the player by a given
		 *        amount.
		 * Param: Amount to add.
		 */
		void add_max_mana(tdt::uint);

		/**
		 * Brief: Decreases the mana capacity of the player by a given amount
		 *        if possible. Returns true if the player has enough, false otherwise.
		 * Param: Amount to decrease by.
		 */
		bool sub_max_mana(tdt::uint);

		/**
		 * Brief: Increases the player's mana regeneration by a given amount.
		 * Param: Amount to increase by.
		 */
		void add_mana_regen(tdt::uint);

		/**
		 * Brief: Decreases the player's mana regeneration by a given amount
		 *        if possible. Returns true if the player has enough, false otherwise.
		 * Param: Amount to decrease by.
		 */
		bool sub_mana_regen(tdt::uint);

		/**
		 *
		 * Brief: Adds max units to the player's unit amount.
		 * Param: Amount to add.
		 */
		void add_max_unit(tdt::uint);

		/**
		 * Brief: Removes max units from the player's unit amount if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_max_unit(tdt::uint);

		/**
		 * Brief: Adds current units to the player's unit amount.
		 * Param: Amount to add.
		 */
		void add_curr_unit(tdt::uint);

		/**
		 * Brief: Removes current units from the player's unit amount if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_curr_unit(tdt::uint);

		/**
		 * Brief: Returns the amount of gold the player currently
		 *        has.
		 */
		tdt::uint get_gold() const;

		/**
		 * Brief: Returns the amount of mana the player currently
		 *        has.
		 */
		tdt::uint get_mana() const;

		/**
		 * Brief: Returns the mana capacity of the player.
		 */
		tdt::uint get_max_mana() const;

		/**
		 * Brief: Returns the value of the player's mana regeneration.
		 */
		tdt::uint get_mana_regen() const;

		/**
		 * Brief: Sets all of the player's stats to their default values.
		 */
		void reset();

		/**
		 * Brief: Sets all of the player's stats to zero (used for loading).
		 */
		void nulify_all_stats();

		/**
		 * Brief: Returns a reference to the singleton
		 *        instance.
		 */
		static Player& instance()
		{
			static Player inst{};
			return inst;
		}

		/**
		 * Brief: Initializes the player class.
		 * Param: EntitySystem used to get gold vaults to
		 *        subtract gold from.
		 */
		void init(EntitySystem*);

		/**
		 * Brief: Sets the spells and buildings that are unlocked from the start.
		 * Param: Spell unlocks.
		 * Param: Building unlocks.
		 */
		void set_initial_unlocks(const std::vector<std::string>&, const std::vector<std::string>&);

		/**
		 * Brief: Returns a vector of all spells that are unlocked at the start
		 *        of a new game.
		 */
		const std::vector<std::string>& get_initial_spells() const;

		/**
		 * Brief: Returns a vector of all buildings that are unlocked at the start
		 *        of a new game.
		 */
		const std::vector<std::string>& get_initial_buildings() const;

	private:
		/**
		 * Constructor.
		 */
		Player();

		/**
		 * Amount of total gold the player currently has to spend.
		 * Note: Only gold stored in vaults is counted, not that on units.
		 */
		tdt::uint gold_;

		/**
		 * Amount of mana the player currently has to spend.
		 */
		tdt::uint mana_;

		/**
		 * Max amount of mana the player can have.
		 */
		tdt::uint max_mana_;

		/**
		 * Amount of mana that is added to the player's mana pool
		 * on every regen tick.
		 */
		tdt::uint mana_regen_;

		/**
		 * Amount of currently alive units.
		 */
		tdt::uint units_curr_;

		/**
		 * Amount of all units (even those that are respawning).
		 */
		tdt::uint units_max_;

		/**
		 * Helper value for overflow checking, contains tdt::uint max value.
		 */
		const tdt::uint uint_max_;

		/**
		 * Used to subtract gold from gold vault so that player gold and
		 * vault gold is synchronized.
		 */
		EntitySystem* entities_;

		/**
		 * Holds the names of the spells that are available to the
		 * player from the beggining. (That is, they are unlocked
		 * in the Lua script they are defined.)
		 */
		std::vector<std::string> initial_spell_unlocks_;

		/**
		 * Holds the names of the buildings that are available to the
		 * player from the beggining. (That is, they are unlocked
		 * in the Lua script they are defined.)
		 */
		std::vector<std::string> initial_building_unlocks_;
};