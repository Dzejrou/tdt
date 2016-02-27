#pragma once

#include "EntitySystem.hpp"
#include "GUIWindow.hpp"

/**
 *
 */
class EntityTracker : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		EntityTracker();

		/**
		 * Destructor.
		 */
		~EntityTracker() {}

		/**
		 * Brief: Sets the new tracked entity and loads it's data.
		 * Param: ID of the entity.
		 * Param: EntitySystem that contains the entity.
		 */
		void set_tracked_entity(std::size_t, EntitySystem&);

		/**
		 * Brief: Returns the ID of the currently tracked entity.
		 */
		std::size_t get_tracked_entity() const;

		/**
		 * Brief: Updates a single stat of the entity tracker.
		 * Param: Name of the stat label (e.g. "HP_LABEL", "GOLD_LABEL" etc).
		 * Param: String with the new value.
		 * Note: The value should have the form "[CURRENT_VALUE]/[MAX_VALUE]".
		 */
		void update_tracking(const std::string&, const std::string&);

		/**
		 * Brief: Clears the entity tracker's window, that is sets all
		 *        values to 0/0 and the id to UNKNOWN.
		 */
		void clear();

		/**
		 * Brief: Adds a callback to the UPGRADE button that upgrades an entity.
		 * Param: Entity system containing entities that will be upgraded by this button.
		 */
		void init_upgrade_butt(EntitySystem*);
	protected:
		/**
		 * Brief: Initializes the window and sets all event subscribers.
		 */
		void init_();
	private:
		/**
		 * ID of the currently tracked entity.
		 */
		std::size_t curr_tracked_entity_;

		/**
		 * Used for upgrading.
		 */
		EntitySystem* entities_;
};