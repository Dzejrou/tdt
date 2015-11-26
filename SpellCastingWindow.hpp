#pragma once
#pragma once

#include <vector>
#include <string>
#include "GUIWindow.hpp"
#include "lppscript/LppScript.hpp"

/**
* Class representing the spell selection window, allows the player to cast
* registered (unlocked) spells.
*/
class SpellCastingWindow : public GUIWindow
{
	public:
		/**
		* Constructor.
		*/
		SpellCastingWindow();

		/**
		* Destructor.
		*/
		~SpellCastingWindow() {}

		/**
		* Brief: Appends a table name to the vector of all spell tables.
		* Param: Name of the table to register.
		*/
		void register_spell(const std::string&);
	protected:
		/**
		* Brief: Initializes the window and subscribes events.
		*/
		void init_();
	private:
		/**
		 *
		 */
		void cast_(const std::string&);

		/**
		* Brief: Decrements selection_number_ by one and updates
		*        the window.
		*/
		void dec_selection_();

		/**
		* Brief: Increments selection_number_ by one and updates
		*        the window.
		*/
		void inc_selection_();

		/**
		* Brief: Range checked buildings_ index access, returns the name
		*        of the building at a given index or "UNKNOWN" if the
		*        index is out of bounds.
		* Param: Index of the building in the buildings_ vector.
		*/
		const std::string& get_spell_(std::size_t);

		/**
		* Brief: Updates building names on the buttons.
		*/
		void update_selection_();

		/**
		* Names of all registered buildings.
		*/
		std::vector<std::string> spells_;

		/**
		* Number of the current rightmost selection.
		* The window shows buildings with indices <selection_number_ - 3, selection_number_>.
		*/
		std::size_t selection_number_;

		/**
		 * Pointer to the scripting engine used for easier
		 * access.
		 */
		lpp::Script* script_;
};