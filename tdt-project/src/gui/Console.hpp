#pragma once

#include <string>
#include <CEGUI/CEGUI.h>
#include <Typedefs.hpp>
#include "GUIWindow.hpp"

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
		~Console() = default;

		/**
		 * \brief Changes the visibility and text capturing of the console window.
		 * \param The new visibility state.
		 */
		void set_visible(bool) override;

		/**
		 * \brief Event handler that is called by CEGUI whenever a text is entered.
		 * \param Reference to the CEGUI argument.
		 */
		bool handle_text(const CEGUI::EventArgs&);

		/**
		 * \brief Event handler that is called by CEGUI whenever the EXECUTE button is pressed.
		 * \param Reference to the CEGUI argument.
		 */
		bool execute(const CEGUI::EventArgs&);

		/**
		 * \brief Prints a given message into the console window.
		 * \param Message to be printed.
		 * \param Colour of the message text, defaults to white.
		 */
		void print_text(const std::string&, CEGUI::Colour = CEGUI::Colour{0xFFFFFFFF});

		/**
		 * \brief Scrolls the console output down one line, used so that messages from the outside can scroll
		 *        all the way down to the last line of the output.
		 * \param Amount of lines to scroll.
		 */
		void scroll_down(tdt::uint = 1);

		/**
		 * \brief Updates the FPS value next to the console name.
		 * \param Time since the last frame.
		 * \param The new framerate.
		 */
		void update_fps(tdt::real, tdt::real);

		/**
		 * \brief Sets the number of entries that will be shown in the console's history.
		 * \param The new entry count.
		 */
		void set_history(tdt::uint);

		/**
		 * \brief Returns the number of entries that will be shown in the console's history.
		 */
		tdt::uint get_history() const;

		/**
		 * \brief Clears the console log.
		 */
		void clear();

	protected:
		/**
		 * \brief Initializes the console and subscribes it to events.
		 */
		void init_() override;

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
		tdt::real time_since_last_fps_update_;

		/**
		 * Limits the number of console entries that will be shown in it's history.
		 */
		tdt::uint console_history_;
};