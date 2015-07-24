#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <string>

#include "lppscript/LppScript.hpp"

/**
 * Class representing the ingame developers console that allows for runtime
 * execution of Lua code.
 */
class Console
{
	public:
		/**
		 * Constructor.
		 */
		Console();

		/**
		 * Destructor.
		 */
		~Console() {}

		/**
		 * Brief: Initializes the console from a predefined CEGUI layout XML file,
		 *        registers it to the gui system and also registers it's event handlers.
		 */
		void init();

		/**
		 * Brief: Changes the visibility and text capturing of the console window.
		 * Param: The new visibility state.
		 */
		void set_visible(bool);

		/**
		 * Brief: Returns true if the console window is visible, false otherwise.
		 */
		bool is_visible() const;

		/**
		 * Brief: Event handler that is called by CEGUI whenever a text is entered.
		 * Param: Reference to the CEGUI argument.
		 */
		void handle_text(const CEGUI::EventArgs&);

		/**
		 * Brief: Event handler that is called by CEGUI whenever the EXECUTE button is pressed.
		 * Param: Reference to the CEGUI argument.
		 */
		void execute(const CEGUI::EventArgs&);

		/**
		 * Brief: Prints a given message into the console window.
		 * Param: Message to be printed.
		 * Param: Colour of the message text, defaults to white.
		 */
		void print_text(const std::string&, CEGUI::Colour = CEGUI::Colour{0xFFFFFFFF});
	private:
		/**
		 * Pointer to the CEGUI widget representing this console.
		 */
		CEGUI::Window* window_;

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
};