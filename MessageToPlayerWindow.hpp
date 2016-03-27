#pragma once

#include <string>
#include "GUIWindow.hpp"
#include "lppscript/LppScript.hpp"

/**
 * A window that can show the player a text message with 1, 2 or 3 buttons (custom labels)
 * that can call assigned functions.
 * Button names: (used for setting labels)
 *		1st on the left: NO
 *		2nd on the left: YES
 *		1st on the right: OK
 */
class MessageToPlayerWindow : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		MessageToPlayerWindow();

		/**
		 * Destructor.
		 */
		~MessageToPlayerWindow() = default;

		/**
		 * Brief: Shows a given text message to the player and assigns callbacks
		 *        to the buttons.
		 * Param: The message.
		 * Param: Callback for the OK button.
		 * Param: Callback for the YES button.
		 * Param: Callback for the NO button.
		 * Note: If a callback passes is "NONE", the assigned button will not be shown.
		 * Note: The callbacks are strings of names of the Lua functions that ought to be called
		 *       when the button is pressed.
		 */
		void show(const std::string& = "NONE", const std::string& = "NONE",
				  const std::string& = "NONE", const std::string& = "NONE");

		/**
		 * Brief: Sets the label of a given button.
		 * Param: The name of the button (OK, YES, NO).
		 * Param: The new label.
		 */
		void set_butt_label(const std::string&, const std::string&);

		/**
		 * Brief: Resets the button labels to their default values.
		 *        ("OK", "YES" and "NO")
		 */
		void reset_butt_labels();

	protected:
		/**
		 * Brief: Initializes this window.
		 */
		void init_();

	private:
		/**
		 * Reference to the scripting engine for easier use
		 * when calling Lua callbacks.
		 */
		lpp::Script& script_;

		/**
		 * Labels of the buttons.
		 */
		std::string ok_func_, yes_func_, no_func_;
};