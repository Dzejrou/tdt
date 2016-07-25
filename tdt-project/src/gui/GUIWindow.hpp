#pragma once

namespace CEGUI
{
	class Window;
}

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
		virtual ~GUIWindow() = default;

		/**
		 * \brief Initializes the window_ variable and calls the protected
		 *        init_ function.
		 */
		void init(CEGUI::Window*);

		/**
		 * \brief Sets the visibolity status of this window.
		 * \param The new visibility status.
		 */
		virtual void set_visible(bool);

		/**
		 * \brief Returns true if the window is visible,
		 *        false otherwise.
		 */
		bool is_visible() const;

	protected:
		/**
		 * Root window.
		 */
		CEGUI::Window* window_;

		/**
		 * \brief Specific init function for each inheriting class.
		 */
		virtual void init_() = 0;
};