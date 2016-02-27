#pragma once

#include <cstdlib>
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
		void add_gold(std::size_t);

		/**
		 * Brief: Removes gold from the player's gold stash if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_gold(std::size_t);

		/**
		 *
		 * Brief: Adds mana to the player's mana pool.
		 * Param: Amount to add.
		 */
		void add_mana(std::size_t);

		/**
		 * Brief: Removes mana from the player's mana pool if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_mana(std::size_t);

		/**
		 * Breif: Increases the mana capacity of the player by a given
		 *        amount.
		 * Param: Amount to add.
		 */
		void add_max_mana(std::size_t);

		/**
		 * Brief: Decreases the mana capacity of the player by a given amount
		 *        if possible. Returns true if the player has enough, false otherwise.
		 * Param: Amount to decrease by.
		 */
		bool sub_max_mana(std::size_t);

		/**
		 * Brief: Increases the player's mana regeneration by a given amount.
		 * Param: Amount to increase by.
		 */
		void add_mana_regen(std::size_t);

		/**
		 * Brief: Decreases the player's mana regeneration by a given amount
		 *        if possible. Returns true if the player has enough, false otherwise.
		 * Param: Amount to decrease by.
		 */
		bool sub_mana_regen(std::size_t);

		/**
		 *
		 * Brief: Adds max units to the player's unit amount.
		 * Param: Amount to add.
		 */
		void add_max_unit(std::size_t);

		/**
		 * Brief: Removes max units from the player's unit amount if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_max_unit(std::size_t);

		/**
		 * Brief: Adds current units to the player's unit amount.
		 * Param: Amount to add.
		 */
		void add_curr_unit(std::size_t);

		/**
		 * Brief: Removes current units from the player's unit amount if possible,
		 *		  returns true if the player has enough, false otherwise.
		 * Param: Amount to remove.
		 */
		bool sub_curr_unit(std::size_t);

		/**
		 * Brief: Returns the amount of gold the player currently
		 *        has.
		 */
		std::size_t get_gold() const;

		/**
		 * Brief: Returns the amount of mana the player currently
		 *        has.
		 */
		std::size_t get_mana() const;

		/**
		 * Brief: Returns the mana capacity of the player.
		 */
		std::size_t get_max_mana() const;

		/**
		 * Brief: Returns the value of the player's mana regeneration.
		 */
		std::size_t get_mana_regen() const;

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
	private:
		/**
		 * Constructor.
		 */
		Player();

		/**
		 * Amount of total gold the player currently has to spend.
		 * Note: Only gold stored in vaults is counted, not that on units.
		 */
		std::size_t gold_;

		/**
		 * Amount of mana the player currently has to spend.
		 */
		std::size_t mana_;

		/**
		 * Max amount of mana the player can have.
		 */
		std::size_t max_mana_;

		/**
		 * Amount of mana that is added to the player's mana pool
		 * on every regen tick.
		 */
		std::size_t mana_regen_;

		/**
		 * Amount of currently alive units.
		 */
		std::size_t units_curr_;

		/**
		 * Amount of all units (even those that are respawning).
		 */
		std::size_t units_max_;

		/**
		 * Helper value for overflow checking, contains std::size_t max value.
		 */
		const std::size_t uint_max_;

		/**
		 * Used to subtract gold from gold vault so that player gold and
		 * vault gold is synchronized.
		 */
		EntitySystem* entities_;
};