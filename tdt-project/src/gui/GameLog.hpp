#pragma once

#include <Typedefs.hpp>
#include "GUIWindow.hpp"
namespace CEGUI
{
	class Listbox;
}

/**
 * Class representing the log window used to show messages to the player.
 * (No space for gold, enemies attacking etc.)
 * \note For debug/technical etc messages, see the Console class.
 */
class GameLog : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		GameLog();

		/**
		 * Destructor.
		 */
		~GameLog() = default;

		/**
		 * \brief Clears the game's log by deleting all it's entries.
		 */
		void clear();

		/**
		 * \brief Prints a string to the game's log.
		 * \param String to be printed.
		 */
		void print(const std::string&);

		/**
		 * \brief Sets the amount of entries kept in the game's log.
		 * \param The new log history.
		 */
		void set_history(tdt::uint);

		/**
		 * \brief Returns the amoung of entries kept in the game's log.
		 */
		tdt::uint get_history() const;

	protected:
		/**
		 * \brief Initializes the game log (called by parent's init).
		 */
		void init_() override;

	private:
		/**
		 * Number of entires kept in the game log.
		 */
		tdt::uint log_history_;

		/**
		 * Pointer to the log window for easy access (as it might get called quite
		 * often, this will avoid frequent lookups).
		 */
		CEGUI::Listbox* log_;
};