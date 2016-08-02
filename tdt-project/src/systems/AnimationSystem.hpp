#pragma once

#include <Typedefs.hpp>
#include "System.hpp"
class EntitySystem;

/**
 *
 */
class AnimationSystem : public System
{
	public:
		/**
		 * Constructor.
		 * \param Reference to the game's entity system.
		 */
		AnimationSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~AnimationSystem() = default;

		/**
		 *
		 */
		void update(tdt::real) override;

	private:
		/**
		 *
		 */
		EntitySystem& entities_;
};