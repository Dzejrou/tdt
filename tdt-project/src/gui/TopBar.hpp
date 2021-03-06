#pragma once

#include <ctime>
#include <chrono>
#include <Typedefs.hpp>
#include "GUIWindow.hpp"

/**
 * Class representing an info bar on the top of the screen displaying
 * the name of the game, player's gold, mana, units and the current time.
 */
class TopBar : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		TopBar();

		/**
		 * Destructor.
		 */
		~TopBar() = default;

		/**
		 * \brief Updates the current time on the top bar if a
		 *        second passed since the last time update.
		 * \param Time since the last frame.
		 */
		void update_time(tdt::real);

		/**
		 * \brief Sets the given label's text to the given string.
		 * \param Label to change.
		 * \param New text.
		 */
		void update_label(const std::string&, const std::string&);

	protected:
		/**
		 * \brief Initializes the top bar.
		 */
		void init_() override;

	private:
		/**
		 * Time since the last "Current Time" update.
		 */
		tdt::real tdelta_;
};