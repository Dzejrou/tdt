#pragma once

#include <CEGUI/CEGUI.h>

/**
 * Abstract class that custom GUI windows inherit from, prevents unnecessary
 * rewriting of common functions (like visibility setting and window_ assignment on init).
 */
class GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		GUIWindow();

		/**
		 * Destructor.
		 */
		virtual ~GUIWindow() {}

		/**
		 * Brief: Initializes the window_ variable and calls the protected
		 *        init_ function.
		 */
		void init(CEGUI::Window*);

		/**
		 * Brief: Sets the visibolity status of this window.
		 * Param: The new visibility status.
		 */
		virtual void set_visible(bool);

		/**
		 * Brief: Returns true if the window is visible,
		 *        false otherwise.
		 */
		bool is_visible() const;
	protected:
		/**
		 * Root window.
		 */
		CEGUI::Window* window_;

		/**
		 * Brief: Specific init function for each inheriting class.
		 */
		virtual void init_() = 0;
};