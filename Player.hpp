#pragma once

#include <cstdlib>

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
		 * Brief: Returns a reference to the singleton
		 *        instance.
		 */
		static Player& instance()
		{
			static Player inst{};
			return inst;
		}
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
};