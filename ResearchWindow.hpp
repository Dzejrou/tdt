#pragma once

#include <array>
#include "GUIWindow.hpp"
#include "lppscript/LppScript.hpp"

/**
 * Class that represents the research window in the game, which allows
 * the player to unlock new buildings and spells.
 * Note: Because this class is so tightly bound to Lua, the indices have to
 *       be adjusted when accessing the prices_ and unlocked_ arrays, since
 *       Lua uses indices starting at one when handling arrays.
 */
class ResearchWindow : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		ResearchWindow();

		/**
		 * Destructor.
		 */
		~ResearchWindow() {}

		/**
		 * Brief: Unlocks a single research point at a given position
		 *        in the research table.
		 * Param: Row number.
		 * Param: Column number.
		 */
		void unlock(std::size_t, std::size_t);

		/**
		 * Brief: Shows a single research point at a given position
		 *        in the research table.
		 * Param: Row number.
		 * Param: Column number.
		 * Param: If true, shows the button, otherwise it hides it.
		 */
		void show(std::size_t, std::size_t, bool = true);

		/**
		 * Brief: Cheat that changes the price of any research to 0.
		 */
		void free_research();

		/**
		 * Brief: Cheat that unlocks all research points.
		 */
		void research_all();
	protected:
		/**
		 * Brief: Initializes this window.
		 */
		void init_();
	private:
		/**
		 * Brief: Returns the price in gold of a research point at the
		 *        given position in the research table.
		 * Param: Row number.
		 * Param: Column number.
		 */
		std::size_t get_price_(std::size_t, std::size_t);

		/**
		 * Brief: Returns true if the research point at the given position
		 *        is unlocked, false otherwise.
		 * Param: Row number.
		 * Param: Column number.
		 */
		bool is_unlocked_(std::size_t, std::size_t);

		/**
		 * Pointer to the Lua Script used for easier access.
		 */
		lpp::Script* script_;

		/**
		 * Number of rows that the research table has.
		 */
		const std::size_t rows_{6};

		/**
		 * Number of columns that the research table has.
		 */
		const std::size_t cols_{7};

		/**
		 * Contains prices of the individual research points.
		 * Used to avoid unnecessary Lua lookups.
		 */
		std::array<std::size_t, 42> prices_;

		/**
		 * Contains information about the lock status of the individual
		 * research points.
		 * Used to avoid unnecessary Lua lookups.
		 */
		std::array<bool, 42> unlocked_;
};