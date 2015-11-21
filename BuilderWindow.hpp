#pragma once

#include <vector>
#include <string>
#include "GUIWindow.hpp"

class EntityPlacer;

/**
 * Class representing the building selection window, allows the player to place
 * registered (unlocked) buildings.
 */
class BuilderWindow : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		BuilderWindow();

		/**
		 * Destructor.
		 */
		~BuilderWindow() {}

		/**
		 * Brief: Appends a table name to the vector of all building tables.
		 * Param: Name of the table to register.
		 */
		void register_building(const std::string&);

		/**
		 * Brief: Sets the placer that is used to build.
		 * Param: The new entity placer.
		 */
		void set_placer(EntityPlacer*);
	protected:
		/**
		 * Brief: Initializes the window and subscribes events.
		 */
		void init_();
	private:
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
		const std::string& get_building_(std::size_t);

		/**
		 * Brief: Updates building names on the buttons.
		 */
		void update_selection_();

		/**
		 * Names of all registered buildings.
		 */
		std::vector<std::string> buildings_;

		/**
		 * Number of the current rightmost selection.
		 * The window shows buildings with indices <selection_number_ - 3, selection_number_>.
		 */
		std::size_t selection_number_;

		/**
		 * Placer used to build.
		 */
		EntityPlacer* placer_;
};