#pragma once

#include <string>
#include "GUIWindow.hpp"
namespace lpp
{
	class Script;
}

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
		 * \brief Shows a given text message to the player and assigns callbacks
		 *        to the buttons.
		 * \param The message.
		 * \param Callback for the OK button.
		 * \param Callback for the YES button.
		 * \param Callback for the NO button.
		 * \note If a callback passes is "NONE", the assigned button will not be shown.
		 * \note The callbacks are strings of names of the Lua functions that ought to be called
		 *       when the button is pressed.
		 */
		void show(const std::string& = "NONE", const std::string& = "NONE",
				  const std::string& = "NONE", const std::string& = "NONE");

		/**
		 * \brief Sets the label of a given button.
		 * \param The name of the button (OK, YES, NO).
		 * \param The new label.
		 */
		void set_butt_label(const std::string&, const std::string&);

		/**
		 * \brief Resets the button labels to their default values.
		 *        ("OK", "YES" and "NO")
		 */
		void reset_butt_labels();

	protected:
		/**
		 * \brief Initializes this window.
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