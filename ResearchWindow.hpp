#pragma once

#include <array>
#include "GUIWindow.hpp"
#include "Typedefs.hpp"
namespace lpp
{
	class Script;
}

/**
 * Class that represents the research window in the game, which allows
 * the player to unlock new buildings and spells.
 * Note: Because this class is so tightly bound to Lua, the indices have to
 *       be adjusted when accessing the prices_ and unlocked_ arrays, since
 *       Lua uses indices starting at one when handling arrays.
 */
class ResearchWindow : public GUIWindow
{
	friend class GameSerializer;
	public:
		/**
		 * Constructor.
		 */
		ResearchWindow();

		/**
		 * Destructor.
		 */
		~ResearchWindow() = default;

		/**
		 * Brief: Unlocks a single research point at a given position
		 *        in the research table.
		 * Param: Row number.
		 * Param: Column number.
		 */
		void unlock(tdt::uint, tdt::uint);

		/**
		 * Brief: Unlocks a single research point without activating it.
		 *        Used for serialization.
		 * Param: Row number.
		 * Param: Column number.
		 */
		void dummy_unlock(tdt::uint, tdt::uint);

		/**
		 * Brief: Returns a reference to the unlock table, used
		 *        for serialization.
		 */
		const std::array<bool, 42>& get_unlocked() const;

		/**
		 * Brief: Shows a single research point at a given position
		 *        in the research table.
		 * Param: Row number.
		 * Param: Column number.
		 * Param: If true, shows the button, otherwise it hides it.
		 */
		void show(tdt::uint, tdt::uint, bool = true);

		/**
		 * Brief: Cheat that changes the price of any research to 0.
		 */
		void free_research();

		/**
		 * Brief: Cheat that unlocks all research points.
		 */
		void research_all();

		/**
		 * Brief: Resets the research state so that all items
		 *        can be unlocked again.
		 */
		void reset_research();

	protected:
		/**
		 * Brief: Initializes this window.
		 */
		void init_() override;

	private:
		/**
		 * Brief: Returns the price in gold of a research point at the
		 *        given position in the research table.
		 * Param: Row number.
		 * Param: Column number.
		 */
		tdt::uint get_price_(tdt::uint, tdt::uint);

		/**
		 * Brief: Returns true if the research point at the given position
		 *        is unlocked, false otherwise.
		 * Param: Row number.
		 * Param: Column number.
		 */
		bool is_unlocked_(tdt::uint, tdt::uint);

		/**
		 * Pointer to the Lua Script used for easier access.
		 */
		lpp::Script* script_;

		/**
		 * Number of rows that the research table has.
		 */
		const tdt::uint rows_{6};

		/**
		 * Number of columns that the research table has.
		 */
		const tdt::uint cols_{7};

		/**
		 * Contains prices of the individual research points.
		 * Used to avoid unnecessary Lua lookups.
		 */
		std::array<tdt::uint, 42> prices_;

		/**
		 * Contains information about the lock status of the individual
		 * research points.
		 * Used to avoid unnecessary Lua lookups.
		 */
		std::array<bool, 42> unlocked_;
};