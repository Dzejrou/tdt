#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <set>
#include <string>

#include "EntityPlacer.hpp"
#include "EntitySystem.hpp"

/**
 * Class representing the debugging GUI window used to place and create entities
 * during runtime.
 * TODO: Entity creation mode (changing the layout and sub-window visibility).
 */
class EntityCreator
{
	public:
		/**
		 * Constructor, loads the gui layout for this window and registers callbacks.
		 * Param: Reference to the game's entity placer.
		 * Param: Reference to the game's entity system.
		 */
		EntityCreator(EntityPlacer&, EntitySystem&);

		/**
		 * Destructor.
		 */
		~EntityCreator() {}

		/**
		 * Brief: Function that is called when the player/developer presses the "place now"
		 *        button, sets the currently selected entity blueprint for placing.
		 * Param: Reference to the CEGUI event arguments.
		 */
		void place(const CEGUI::EventArgs&);

		/**
		 * Brief: Function that is called when the player/developer presses the "place"
		 *        button, changing the creator to the placing mode.
		 * Param: Reference to the CEGUI event arguments.
		 */
		void change_to_place(const CEGUI::EventArgs&);

		/**
		 * Brief: Function that is called when the player/developer presses the "create"
		 *        button, changing the creator to the creation mode.
		 * Param: Reference to the CEGUI event arguments.
		 */
		void change_to_create(const CEGUI::EventArgs&);

		/**
		 * Brief: Function that is called when the player/developer presses the "actualize
		 *        list" button and displays the set of all selected entities to the
		 *        list box.
		 * Param: Reference to the CEGUI event arguments.
		 */
		void actualize_list(const CEGUI::EventArgs&);

		/**
		 * Brief: Sets the visibility state of the creator's window (and recursively it's children windows).
		 * Param: True for visible, false for invisible state.
		 */
		void set_visible(bool);

		/**
		 * Brief: Returns true if the creator window is visible, false otherwise.
		 */
		bool is_visible() const;
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
		 * Pointer to the main window of the creator.
		 */
		CEGUI::Window* window_;

		/**
		 * Auxiliary pointer to the list box sub window for easy access when updating the entity
		 * blueprint list.
		 */
		CEGUI::Listbox* list_box_;
};