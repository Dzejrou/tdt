#pragma once

#include "GUIWindow.hpp"

/**
 * Class representing the log window used to show messages to the player.
 * (No space for gold, enemies attacking etc.)
 * Note: For debug/technical etc messages, see the Console class.
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
		~GameLog() {}

		/**
		 * Brief: Clears the game's log by deleting all it's entries.
		 */
		void clear();

		/**
		 * Brief: Prints a string to the game's log.
		 * Param: String to be printed.
		 */
		void print(const std::string&);

		/**
		 * Brief: Sets the amount of entries kept in the game's log.
		 * Param: The new log history.
		 */
		void set_history(std::size_t);

		/**
		 * Brief: Returns the amoung of entries kept in the game's log.
		 */
		std::size_t get_history() const;
	protected:
		/**
		 * Brief: Initializes the game log (called by parent's init).
		 */
		void init_();
	private:
		/**
		 * Number of entires kept in the game log.
		 */
		std::size_t log_history_;

		/**
		 * Pointer to the log window for easy access (as it might get called quite
		 * often, this will avoid frequent lookups).
		 */
		CEGUI::Listbox* log_;
};