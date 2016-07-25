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
		~BuilderWindow() = default;

		/**
		 * \brief Appends a table name to the vector of all building tables.
		 * \param Name of the table to register.
		 */
		void register_building(const std::string&);

		/**
		 * \brief Sets the placer that is used to build.
		 * \param The new entity placer.
		 */
		void set_placer(EntityPlacer*);

		/**
		 * \brief Returns a vector containing all the names of the
		 *        registered buildings. (Used for serialization.)
		 */
		const std::vector<std::string>& get_buildings() const;

		/**
		 * \brief Removes all unlocked buildings.
		 */
		void clear_buildings();

		/**
		 * \brief Places the building on a given position.
		 * \param The button position. (1-4)
		 */
		void build(int);

		/**
		 * \brief Decrements selection_number_ by one and updates
		 *        the window.
		 */
		void dec_selection();

		/**
		 * \brief Increments selection_number_ by one and updates
		 *        the window.
		 */
		void inc_selection();

	protected:
		/**
		 * \brief Initializes the window and subscribes events.
		 */
		void init_() override;

	private:
		/**
		 * \brief Range checked buildings_ index access, returns the name
		 *        of the building at a given index or "UNKNOWN" if the
		 *        index is out of bounds.
		 * \param Index of the building in the buildings_ vector.
		 */
		const std::string& get_building_(std::size_t);

		/**
		 * \brief Updates building names on the buttons.
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