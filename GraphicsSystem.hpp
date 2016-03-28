#pragma once

#include "System.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * System that performs all graphics related updates.
 */
class GraphicsSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: The game's entity system.
		 */
		GraphicsSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~GraphicsSystem() = default;

		/**
		 * Brief: Performs all graphics updates.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Sets the time period before the next update.
		 * Param: The new period.
		 */
		void set_update_period(tdt::real);

		/**
		 * Brief: Returns the time period between updates.
		 */
		tdt::real get_update_period() const;
	private:
		/**
		 * Entity system that contains entities this system is
		 * working with.
		 */
		EntitySystem& entities_;

		/**
		 * Used to avoid per frame updates and allows dynamic
		 * update periods.
		 */
		tdt::real update_timer_, update_period_;
};