#pragma once

#include <Typedefs.hpp>
#include "GUIWindow.hpp"
class EntitySystem;

/**
 * A window that monitors the stats of the currently selected entity and
 * allows for it's upgrading once it has enough experience.
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
		~EntityTracker() = default;

		/**
		 * \brief Sets the new tracked entity and loads it's data.
		 * \param ID of the entity.
		 * \param EntitySystem that contains the entity.
		 */
		void set_tracked_entity(tdt::uint, EntitySystem&);

		/**
		 * \brief Returns the ID of the currently tracked entity.
		 */
		tdt::uint get_tracked_entity() const;

		/**
		 * \brief Updates a single stat of the entity tracker.
		 * \param Name of the stat label (e.g. "HP_LABEL", "GOLD_LABEL" etc).
		 * \param String with the new value.
		 * \note The value should have the form "[CURRENT_VALUE]/[MAX_VALUE]".
		 */
		void update_tracking(const std::string&, const std::string&);

		/**
		 * \brief Clears the entity tracker's window, that is sets all
		 *        values to 0/0 and the id to UNKNOWN.
		 */
		void clear();

		/**
		 * \brief Adds a callback to the UPGRADE button that upgrades an entity.
		 * \param Entity system containing entities that will be upgraded by this button.
		 */
		void init_upgrade_butt(EntitySystem*);

		/**
		 * \brief Sets the visibility status of the UPGRADE button.
		 * \param True for visible, false for invisible.
		 */
		void show_upgrade_butt(bool);

	protected:
		/**
		 * \brief Initializes the window and sets all event subscribers.
		 */
		void init_() override;

	private:
		/**
		 * ID of the currently tracked entity.
		 */
		tdt::uint curr_tracked_entity_;

		/**
		 * Used for upgrading.
		 */
		EntitySystem* entities_;
};