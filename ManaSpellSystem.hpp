#pragma once

#include "System.hpp"
#include "Typedefs.hpp"
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
		 * Param: Entity system containing entities this system works with.
		 */
		ManaSpellSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~ManaSpellSystem() = default;

		/**
		 * Brief: Regenerates mana if necessary and performs entity spell
		 *        casting if off cooldown.
		 * Param: Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Sets the time period between mana regens.
		 * Param: The new time period.
		 */
		void set_regen_period(tdt::real);

		/**
		 * Brief: Returns the time period between mana regens.
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