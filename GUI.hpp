#pragma once

#include <CEGUI/CEGUI.h>
#include <string>
#include "EntitySystem.hpp"
#ifdef WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

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
		~GUI() {}

		/**
		 *
		 */
		void init(Game*);

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

		/**
		 *
		 */
		void clear_log();

		/**
		 *
		 */
		void print_to_log(const std::string&);

		/**
		 *
		 */
		void set_tracked_entity(std::size_t, EntitySystem&);

		/**
		 *
		 */
		std::size_t get_tracked_entity() const;

		/**
		 *
		 */
		void update_tracking(const std::string&, const std::string&);

		/**
		 *
		 */
		void clear_entity_view();

		/**
		 *
		 */
		static GUI& instance();

		void set_log_history(std::size_t);
		std::size_t get_log_history() const;
		GUI(const GUI&) = delete;
		GUI(GUI&&) = delete;
		GUI& operator=(const GUI&) = delete;
		GUI& operator=(GUI&&) = delete;
	private:
		/**
		 *
		 */
		GUI();

		/**
		 *
		 */
		void list_directory(const std::string&, CEGUI::Listbox&, bool = false);

		/**
		 *
		 */
		CEGUI::Window* window_;

		/**
		 *
		 */
		CEGUI::Listbox* log_;

		/**
		 *
		 */
		std::string curr_tool_;

		/**
		 *
		 */
		Game* game_;

		/**
		 *
		 */
		std::size_t curr_tracked_entity_;

		/**
		 *
		 */
		std::size_t log_history_;
};