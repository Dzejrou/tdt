#pragma once

#include <CEGUI/CEGUI.h>
#include <string>
#include "EntitySystem.hpp"
#include "Console.hpp"
#ifdef WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

class Game;

/**
 * Represents the game's main graphical user interface (i.e. any windows except
 * for the development ones like the console or entity creator).
 */
class GUI
{
	public:
		/**
		 * Destructor.
		 */
		~GUI() {}

		/**
		 * Brief: Initializes the selection by loading the layout and registering
		 *        all event handlers.
		 * Param: Pointer to the game object, which is used by the event handlers
		 *        (like the quit button etc).
		 */
		void init(Game*);

		/**
		 * Brief: Set's the GUI's visibility status.
		 * Param: The new visibility status.
		 * TODO: Toggle GUI with a hotkey for screen capturing?
		 */
		void set_visible(bool);

		/**
		 * Brief: Returns true if the entire GUI is visible, false otherwise.
		 */
		bool is_visible() const;

		/**
		 * Brief: Set's the visibility status of a particular window.
		 * Param: Name (path) of the window, without the root window prefix.
		 *        (e.g. "TOOLS/TOOL_SELECTION/SPELL_SELECTION")
		 * Param: The new visibility status.
		 */
		void set_visible(const std::string&, bool);

		/**
		 * Brief: Returns the visibility status of a particular window.
		 * Param: Name (path) of the window, without the root window prefix.
		 */
		bool is_visible(const std::string&) const;

		/**
		 * Brief: Clears the game's log by deleting all it's entries.
		 */
		void clear_log();

		/**
		 * Brief: Prints a string to the game's log.
		 * Param: String to be printed.
		 */
		void print_to_log(const std::string&);

		/**
		 * Brief: Sets the new tracked entity and loads it's data.
		 * Param: ID of the entity.
		 * Param: EntitySystem that contains the entity.
		 */
		void set_tracked_entity(std::size_t, EntitySystem&);

		/**
		 * Brief: Returns the ID of the currently tracked entity.
		 */
		std::size_t get_tracked_entity() const;

		/**
		 * Brief: Updates a single stat of the entity tracker.
		 * Param: Name of the stat label (e.g. "HP_LABEL", "GOLD_LABEL" etc).
		 * Param: String with the new value.
		 * Note: The value should have the form "[CURRENT_VALUE]/[MAX_VALUE]".
		 */
		void update_tracking(const std::string&, const std::string&);

		/**
		 * Brief: Clears the entity tracker's window, that is sets all
		 *        values to 0/0 and the id to UNKNOWN.
		 */
		void clear_entity_view();

		/**
		 * Brief: Returns the singleton instance.
		 */
		static GUI& instance();

		/**
		 * Brief: Sets the amount of entries kept in the game's log.
		 * Param: The new log history.
		 */
		void set_log_history(std::size_t);

		/**
		 * Brief: Returns the amoung of entries kept in the game's log.
		 */
		std::size_t get_log_history() const;

		/**
		 * Brief: Shows the load/save dialog window.
		 * Param: Either "SAVE" or "LOAD", will determine the
		 *        functionality of the window.
		 */
		void show_load_save_dialog(const std::string&);

		/**
		 * Brief: Returns a reference to the game's dev console.
		 */
		Console& get_console();

		/**
		 * Note: Since VS2015 seems to have some problems with C++ standard
		 *       (generates default copy/move constructors and operators even
		 *        if default constructor is created), these constructors/operators
		 *        are explicitly deleted.
		 */
		GUI(const GUI&) = delete;
		GUI(GUI&&) = delete;
		GUI& operator=(const GUI&) = delete;
		GUI& operator=(GUI&&) = delete;
	private:
		/**
		 * Constructor, private because of the singleton pattern.
		 */
		GUI();

		/**
		 * Brief: Fills a given list box with the names of all files in a
		 *        given directory.
		 * Param: Name of the directory.
		 * Param: List box to be filled.
		 * Param: If true, the .lua extension will be cut from the file name
		 *        if present.
		 */
		void list_directory(const std::string&, CEGUI::Listbox&, bool = false);

		/**
		 * Pointer to the root window of the layout.
		 */
		CEGUI::Window* window_;

		/**
		 * Pointer to the log window for easy access (as it might get called quite
		 * often, this will avoid frequent lookups).
		 */
		CEGUI::Listbox* log_;

		/**
		 * Name of the current tool in the tools subwindow.
		 */
		std::string curr_tool_;

		/**
		 * Pointer to the game instance used by button event handlers.
		 */
		Game* game_;

		/**
		 * ID of the entity that is currently tracked by the entity viewer.
		 */
		std::size_t curr_tracked_entity_;

		/**
		 * Number of entires kept in the game log.
		 */
		std::size_t log_history_;

		/**
		 * Game's developer console.
		 */
		Console console_;
};