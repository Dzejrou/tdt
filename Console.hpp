#pragma once

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Ogre.h>
#include <string>
#include "GUIWindow.hpp"
#include "lppscript/LppScript.hpp"

/**
 * Class representing the ingame developers console that allows for runtime
 * execution of Lua code.
 */
class Console : public GUIWindow
{
	public:
	static const CEGUI::Colour RED_TEXT, GREEN_TEXT, ORANGE_TEXT, BLUE_TEXT;
		/**
		 * Constructor.
		 */
		Console();

		/**
		 * Destructor.
		 */
		~Console() {}

		/**
		 * Brief: Changes the visibility and text capturing of the console window.
		 * Param: The new visibility state.
		 */
		void set_visible(bool);

		/**
		 * Brief: Event handler that is called by CEGUI whenever a text is entered.
		 * Param: Reference to the CEGUI argument.
		 */
		bool handle_text(const CEGUI::EventArgs&);

		/**
		 * Brief: Event handler that is called by CEGUI whenever the EXECUTE button is pressed.
		 * Param: Reference to the CEGUI argument.
		 */
		bool execute(const CEGUI::EventArgs&);

		/**
		 * Brief: Prints a given message into the console window.
		 * Param: Message to be printed.
		 * Param: Colour of the message text, defaults to white.
		 */
		void print_text(const std::string&, CEGUI::Colour = CEGUI::Colour{0xFFFFFFFF});

		/**
		 * Brief: Scrolls the console output down one line, used so that messages from the outside can scroll
		 *        all the way down to the last line of the output.
		 * Param: Amount of lines to scroll.
		 */
		void scroll_down(std::size_t = 1);

		/**
		 * Brief: Updates the FPS value next to the console name.
		 * Param: Time since the last frame.
		 * Param: The new framerate.
		 */
		void update_fps(Ogre::Real, Ogre::Real);

		/**
		 * Brief: Sets the number of entries that will be shown in the console's history.
		 * Param: The new entry count.
		 */
		void set_history(std::size_t);

		/**
		 * Brief: Returns the number of entries that will be shown in the console's history.
		 */
		std::size_t get_history() const;

		/**
		 * Brief: Clears the console log.
		 */
		void clear();
	protected:
		/**
		 * Brief: Initializes the console and subscribes it to events.
		 */
		void init_();
	private:
		/**
		 * Pointer to the CEGUI ListBox widget that serves as console output.
		 */
		CEGUI::Listbox* list_box_;

		/**
		 * String containing the current command, allows to append more statements
		 * to it until the EXECUTE button is pressed, which allows for multi-line 
		 * Lua code.
		 */
		std::string curr_command_;

		/**
		 * Monitors the time passed since the fps label was last updated, used
		 * to make sure the fps update won't slow down the game as it involves
		 * float to string conversion.
		 */
		Ogre::Real time_since_last_fps_update_;

		/**
		 * Limits the number of console entries that will be shown in it's history.
		 */
		std::size_t console_history_;
};