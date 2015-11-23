#pragma once

#include "GUIWindow.hpp"
#include <Ogre.h>
#include <ctime>
#include <chrono>

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
		~TopBar() {}

		/**
		 * Brief: Updates the current time on the top bar if a
		 *        second passed since the last time update.
		 * Param: Time since the last frame.
		 */
		void update_time(Ogre::Real);

		/**
		 * Brief: Sets the given label's text to the given string.
		 * Param: Label to change.
		 * Param: New text.
		 */
		void update_label(const std::string&, const std::string&);
	protected:
		/**
		 * Brief: Initializes the top bar.
		 */
		void init_();
	private:
		/**
		 * Time since the last "Current Time" update.
		 */
		Ogre::Real tdelta_;
};