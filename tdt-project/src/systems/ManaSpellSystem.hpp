#pragma once

#include <Typedefs.hpp>
#include "System.hpp"
class EntitySystem;

/**
 * Regenerates mana to the player and all entities that have mana. Also
 * takes care of entity spell casting.
 */
class ManaSpellSystem : public System
{
	public:
		/**
		 * Constructor.
		 * \param Entity system containing entities this system works with.
		 */
		ManaSpellSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~ManaSpellSystem() = default;

		/**
		 * \brief Regenerates mana if necessary and performs entity spell
		 *        casting if off cooldown.
		 * \param Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * \brief Sets the time period between mana regens.
		 * \param The new time period.
		 */
		void set_regen_period(tdt::real);

		/**
		 * \brief Returns the time period between mana regens.
		 */
		tdt::real get_regen_period() const;

	private:
		/**
		 * Entity system containing entities that this system
		 * works with.
		 */
		EntitySystem& entities_;

		/**
		 * Allow for dynamic periods between mana regeneration
		 * updates.
		 */
		tdt::real regen_timer_, regen_period_;
};