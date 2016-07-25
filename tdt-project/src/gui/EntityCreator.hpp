#pragma once

#include <CEGUI/CEGUI.h>
#include <set>
#include <string>
#include "GUIWindow.hpp"
class EntitySystem;
class EntityPlacer;

/**
 * Class representing the debugging GUI window used to place and create entities
 * during runtime.
 */
class EntityCreator : public GUIWindow
{
	public:
		/**
		 * Constructor, loads the gui layout for this window and registers callbacks.
		 * \param Reference to the game's entity placer.
		 * \param Reference to the game's entity system.
		 */
		EntityCreator(EntityPlacer&, EntitySystem&);

		/**
		 * Destructor.
		 */
		~EntityCreator() {}

		/**
		 * \brief Function that is called when the player/developer presses the "place now"
		 *        button, sets the currently selected entity blueprint for placing.
		 * \param Reference to the CEGUI event arguments.
		 */
		bool place(const CEGUI::EventArgs&);

		/**
		 * \brief Function that is called when the player/developer presses the "place"
		 *        button, changing the creator to the placing mode.
		 * \param Reference to the CEGUI event arguments.
		 */
		bool change_to_place(const CEGUI::EventArgs&);

		/**
		 * \brief Function that is called when the player/developer presses the "create"
		 *        button, changing the creator to the creation mode.
		 * \param Reference to the CEGUI event arguments.
		 */
		bool change_to_create(const CEGUI::EventArgs&);

		/**
		 * \brief Function that is called when the player/developer presses the "actualize
		 *        list" button and displays the set of all selected entities to the
		 *        list box.
		 * \param Reference to the CEGUI event arguments.
		 */
		bool actualize_list(const CEGUI::EventArgs&);

	protected:
		/**
		 * \brief Initializes the EntityCreator.
		 */
		void init_() override;
	private:

		/**
		 * Reference to the game's entity placer, used to set the blueprint table and visibility mode
		 * when the player/developer presses the "place now" button.
		 */
		EntityPlacer& placer_;

		/**
		 * Reference to the list of all registered entity blueprint names used for updates.
		 */
		std::set<std::string>& registered_entities_;

		/**
		 * Auxiliary pointer to the list box sub window for easy access when updating the entity
		 * blueprint list.
		 */
		CEGUI::Listbox* list_box_;
};