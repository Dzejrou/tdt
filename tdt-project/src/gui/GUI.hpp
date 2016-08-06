#pragma once

#include <CEGUI/CEGUI.h>
#include <string>
#include "Console.hpp"
#include "EntityTracker.hpp"
#include "GameLog.hpp"
#include "BuilderWindow.hpp"
#include "TopBar.hpp"
#include "ResearchWindow.hpp"
#include "SpellCastingWindow.hpp"
#include "MessageToPlayerWindow.hpp"
#include "OptionsWindow.hpp"
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
	friend void action::QUICK_LOAD();
	friend void action::QUICK_SAVE();
	friend void action::RESET_CAMERA();
	friend class OptionsWindow;
	public:
		/**
		 * Destructor.
		 */
		~GUI() {}

		/**
		 * \brief Initializes the selection by loading the layout and registering
		 *        all event handlers.
		 * \param Pointer to the game object, which is used by the event handlers
		 *        (like the quit button etc).
		 */
		void init(Game*);

		/**
		 * \brief Set's the GUI's visibility status.
		 * \param The new visibility status.
		 * TODO: Toggle GUI with a hotkey for screen capturing?
		 */
		void set_visible(bool);

		/**
		 * \brief Returns true if the entire GUI is visible, false otherwise.
		 */
		bool is_visible() const;

		/**
		 * \brief Set's the visibility status of a particular window.
		 * \param Name (path) of the window, without the root window prefix.
		 *        (e.g. "TOOLS/TOOL_SELECTION/SPELL_SELECTION")
		 * \param The new visibility status.
		 */
		void set_visible(const std::string&, bool);

		/**
		 * \brief Returns the visibility status of a particular window.
		 * \param Name (path) of the window, without the root window prefix.
		 */
		bool is_visible(const std::string&) const;

		/**
		 * \brief Returns the singleton instance.
		 */
		static GUI& instance();

		/**
		 * \brief Shows the load/save dialog window.
		 * \param Either "SAVE" or "LOAD", will determine the
		 *        functionality of the window.
		 */
		void show_load_save_dialog(const std::string&);

		/**
		 * \brief Returns a pointer to the root window.
		 */
		CEGUI::Window* get_window();

		/**
		 * \brief Returns a pointer to a given subwindow of
		 *        the root window.
		 * \param Name of the window.
		 */
		CEGUI::Window* get_window(const std::string&);

		/**
		 * \brief Returns a reference to the game's dev console.
		 */
		Console& get_console();

		/**
		 * \brief Returns a reference to the entity tracker.
		 */
		EntityTracker& get_tracker();

		/**
		 * \brief Returns a reference to the game's log.
		 */
		GameLog& get_log();

		/**
		 * \brief Returns a reference to the builder window.
		 */
		BuilderWindow& get_builder();

		/**
		 * \brief Returns a reference to the top bar.
		 */
		TopBar& get_top_bar();

		/**
		 * \brief Returns a reference to the research window.
		 */
		ResearchWindow& get_research();

		/**
		 * \brief Returns a reference to the spell casting window.
		 */
		SpellCastingWindow& get_spell_casting();

		/**
		 * \brief Returns a reference to the message to player window.
		 */
		MessageToPlayerWindow& get_message();

		/**
		 * \brief Returns a reference to the options window.
		 */
		OptionsWindow& get_options();

		/**
		 * \brief Notifies the GUI that the escape key was pressed so that
		 *        it can close windows if needed. Returns true if anything
		 *        has been closed, false otherwise.
		 * \note CEGUI event system does not seem to work properly :/
		 */
		bool escape_pressed();

		/**
		 * \brief Notifies the GUI that the mouse wheel was moved. Returns
		 *        true if the event has been handled, false otherwise.
		 * \param Mousewheel relative movement value.
		 */
		bool mouse_wheel_scrolled(int);

		/**
		 * \brief Sets the visibility status of the current tool window.
		 * \param The new visibility status.
		 */
		void set_curr_tool_visible(bool);

		/**
		 * \brief Sets the current tool window.
		 * \param The name of the tool. (MENU, SPELL, BUILD)
		 */
		void set_curr_tool(const std::string&);

		/**
		 * \brief Returns the name of the current tool window.
		 */
		const std::string& get_curr_tool();

		/**
		 * \note Since VS2015 seems to have some problems with C++ standard
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
		 * \brief Fills a given list box with the names of all files in a
		 *        given directory.
		 * \param Name of the directory.
		 * \param List box to be filled.
		 * \param If true, the .lua extension will be cut from the file name
		 *        if present.
		 */
		void list_directory(const std::string&, CEGUI::Listbox&, bool = false);

		/**
		 * Pointer to the root window of the layout.
		 */
		CEGUI::Window* window_;

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
		EntityTracker tracker_;

		/**
		 * Game's developer console.
		 */
		Console console_;

		/**
		 * Game's log, used to show messages to the player.
		 */
		GameLog log_;

		/**
		 * Allows the player to place buildings.
		 */
		BuilderWindow builder_;

		/**
		 * Shows game info at the top of the screen.
		 */
		TopBar top_bar_;

		/**
		 * Game's research window that allows the player to buy
		 * buildings, units and spells.
		 */
		ResearchWindow research_;

		/**
		 * Allows the player to cast spells.
		 */
		SpellCastingWindow spell_casting_;

		/**
		 * Allows easier access to the menu subwindow.
		 */
		CEGUI::Window* menu_;

		/**
		 * Allows the game to show a message to the player with any
		 * of the following buttons: OK, YES, NO.
		 */
		MessageToPlayerWindow message_;

		/**
		 * Allows to change the resolution, window mode and
		 * key bindings.
		 */
		OptionsWindow options_;
};