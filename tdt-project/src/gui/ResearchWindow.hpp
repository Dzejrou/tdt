#pragma once

#include <array>
#include <Typedefs.hpp>
#include "GUIWindow.hpp"
namespace lpp
{
	class Script;
}

/**
 * Class that represents the research window in the game, which allows
 * the player to unlock new buildings and spells.
 * \note Because this class is so tightly bound to Lua, the indices have to
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
		 * \brief Unlocks a single research point at a given position
		 *        in the research table.
		 * \param Row number.
		 * \param Column number.
		 */
		void unlock(tdt::uint, tdt::uint);

		/**
		 * \brief Unlocks a single research point without activating it.
		 *        Used for serialization.
		 * \param Row number.
		 * \param Column number.
		 */
		void dummy_unlock(tdt::uint, tdt::uint);

		/**
		 * \brief Returns a reference to the unlock table, used
		 *        for serialization.
		 */
		const std::array<bool, 42>& get_unlocked() const;

		/**
		 * \brief Shows a single research point at a given position
		 *        in the research table.
		 * \param Row number.
		 * \param Column number.
		 * \param If true, shows the button, otherwise it hides it.
		 */
		void show(tdt::uint, tdt::uint, bool = true);

		/**
		 * \brief Cheat that changes the price of any research to 0.
		 */
		void free_research();

		/**
		 * \brief Cheat that unlocks all research points.
		 */
		void research_all();

		/**
		 * \brief Resets the research state so that all items
		 *        can be unlocked again.
		 */
		void reset_research();

	protected:
		/**
		 * \brief Initializes this window.
		 */
		void init_() override;

	private:
		/**
		 * \brief Returns the price in gold of a research point at the
		 *        given position in the research table.
		 * \param Row number.
		 * \param Column number.
		 */
		tdt::uint get_price_(tdt::uint, tdt::uint);

		/**
		 * \brief Returns true if the research point at the given position
		 *        is unlocked, false otherwise.
		 * \param Row number.
		 * \param Column number.
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