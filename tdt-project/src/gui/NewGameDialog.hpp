#pragma once

#include <map>
#include <string>
#include <CEGUI/CEGUI.h>
#include "GUIWindow.hpp"

/**
 * A GUI window that is used as an interface for
 * level creation.
 */
class NewGameDialog : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		NewGameDialog();

		/**
		 * Destructor.
		 */
		~NewGameDialog() = default;

		/**
		 * \brief Registers a new wave table as a scenario.
		 * \param Name of the scenario.
		 * \param Name of the wave table.
		 */
		void register_scenario(const std::string&, const std::string&);

		/**
		 * \brief Returns the name of the wave table that belongs to the
		 *        selected scenario.
		 */
		const std::string& get_selected_scenario_table();

	protected:
		/**
		 * \brief Initializes the window and subscribes events.
		 */
		void init_() override;

	private:
		/**
		 * Pairs of scenario names and wave table names that belong
		 * together.
		 */
		std::map<std::string, std::string> scenarios_;

		/**
		 * List of scenario names displayed to the player.
		 */
		CEGUI::Listbox* scenario_list_;
};