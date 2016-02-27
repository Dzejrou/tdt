#pragma once

#include <Ogre.h>
#include "System.hpp"
#include "EntitySystem.hpp"

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
		void update(Ogre::Real) override;

		/**
		 * Brief: Sets the time period between mana regens.
		 * Param: The new time period.
		 */
		void set_regen_period(Ogre::Real);

		/**
		 * Brief: Returns the time period between mana regens.
		 */
		Ogre::Real get_regen_period() const;
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
		Ogre::Real regen_timer_, regen_period_;
};