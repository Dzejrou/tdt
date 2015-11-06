#pragma once

#include <CEGUI/CEGUI.h>
#include <string>

class Game;

/**
 *
 */
class GUI
{
	public:
		/**
		 *
		 */
		GUI(Game&);

		/**
		 *
		 */
		~GUI() {}

		/**
		 *
		 */
		void init();

		/**
		 *
		 */
		void set_visible(bool);

		/**
		 *
		 */
		void is_visible() const;

		/**
		 *
		 */
		void set_visible(const std::string&, bool);

		/**
		 *
		 */
		void is_visible(const std::string&) const;
	private:
		/**
		 *
		 */
		CEGUI::Window* window_;

		/**
		 *
		 */
		std::string curr_tool_;

		/**
		 *
		 */
		Game& game_;
};