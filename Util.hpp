#pragma once

#include <cstdlib>
#include <random>
#include "Enums.hpp"
#include "DestructorHelper.hpp"
class EntitySystem;

/**
 * The util namespace contains functors used as conditions in searches and other
 * helper structures/functions used throughout the code.
 */
namespace util
{
	/**
	 * Tests if if the entity it is called on is an enemy of the entity
	 * specified in it's constructor.
	 */
	struct IS_ENEMY
	{
		/**
		 * Constructor.
		 * Param: Entity system containing all tested entities.
		 * Param: ID of the entity towards which others are tested
		 *        for the enemy status.
		 */
		IS_ENEMY(EntitySystem&, std::size_t);

		/**
		 * Brief: Tests if a given entity is an enemy of the entity specified
		 *        in the constructor.
		 * Param: ID of the entity.
		 */
		bool operator()(std::size_t);

		private:
			/**
			 * Faction that is hostile towards the entity performing the search.
			 */
			FACTION enemy_faction_;

			/**
			 * Entity system containing all tested entities.
			 */
			EntitySystem& entities_;
	};

	/**
	 * Tests if if the entity it is called on is a friend of the entity
	 * specified in it's constructor.
	 */
	struct IS_FRIENDLY
	{
		/**
		 * Constructor.
		 * Param: Entity system containing all tested entities.
		 * Param: ID of the entity towards which others are tested
		 *        for the friendly status.
		 */
		IS_FRIENDLY(EntitySystem&, std::size_t);

		/**
		 * Brief: Tests if a given entity is a friend of the entity specified
		 *        in the constructor.
		 * Param: ID of the entity.
		 */
		bool operator()(std::size_t);

		private:
			/**
			 * Faction that is friendly towards the entity performing the search.
			 */
			FACTION faction_;

			/**
			 * Entity system containing all tested entities.
			 */
			EntitySystem& entities_;
	};

	/**
	 * Tests if if the entity it is called on is a friend of or neutral to the entity
	 * specified in it's constructor.
	 */
	struct IS_FRIENDLY_OR_NEUTRAL
	{
		/**
		 * Constructor.
		 * Param: Entity system containing all tested entities.
		 * Param: ID of the entity towards which others are tested
		 *        for the friendly/neutrality status.
		 */
		IS_FRIENDLY_OR_NEUTRAL(EntitySystem&, std::size_t);

		/**
		 * Brief: Tests if a given entity is a friend of or neutral to the entity specified
		 *        in the constructor.
		 * Param: ID of the entity.
		 */
		bool operator()(std::size_t);

		private:
			/**
			 * Faction that is friendly towards the entity performing the search.
			 */
			FACTION faction_;

			/**
			 * Entity system containing all tested entities.
			 */
			EntitySystem& entities_;
	};

	/**
	 * Tests if a given entity has a gold component.
	 */
	struct HAS_GOLD
	{
		/**
		 * Constructor.
		 * Param: Entity system containing all tested entities.
		 */
		HAS_GOLD(EntitySystem&);

		/**
		 * Brief: Tests if a given entity has a gold component.
		 * Param: ID of the entity.
		 */
		bool operator()(std::size_t);

		private:
			/**
			 * Entity system containing all tested entities.
			 */
			EntitySystem& entities_;
	};

	/**
	 * A structure providing the private method EntitySystem::destroy_entity to
	 * the DestructorHelper::destroy function. The reason for the existence of this
	 * struct is that it provides only this one method and keeps others private.
	 */
	class EntityDestroyer
	{
		friend void DestructorHelper::destroy(EntitySystem&, std::size_t, bool, std::size_t);

		/**
		 * Brief: Destroy a given entity.
		 * Param: Entity system containing the entity.
		 * Param: ID of the entity.
		 */
		static void destroy(EntitySystem&, std::size_t);
	};

	/**
	 * Brief: Returns the direction from a given entity to another given
	 *        entity in the form of the direction enum (8 directional).
	 * Param: EntitySystem containing both entities.
	 * Param: ID of the first entity.
	 * Param: ID of the second entity.
	 * Note: The direction is #1 -> #2.
	 */
	int get_enum_direction(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns a random number within a given range.
	 * Param: Lower bound of the range.
	 * Param: Upper bound of the range.
	 */
	std::size_t get_random(std::size_t, std::size_t);

	/**
	 * Brief: Returns the absolute value of a given integer.
	 * Param: The number we want absolute value of.
	 */
	std::size_t abs(int);
}