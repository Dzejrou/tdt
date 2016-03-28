#pragma once

#include <random>
#include "Enums.hpp"
#include "DestructorHelper.hpp"
#include "Typedefs.hpp"
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
		IS_ENEMY(EntitySystem&, tdt::uint);

		/**
		 * Destructor.
		 */
		~IS_ENEMY() = default;

		/**
		 * Brief: Tests if a given entity is an enemy of the entity specified
		 *        in the constructor.
		 * Param: ID of the entity.
		 */
		bool operator()(tdt::uint);

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
		IS_FRIENDLY(EntitySystem&, tdt::uint);

		/**
		 * Destructor.
		 */
		~IS_FRIENDLY() = default;

		/**
		 * Brief: Tests if a given entity is a friend of the entity specified
		 *        in the constructor.
		 * Param: ID of the entity.
		 */
		bool operator()(tdt::uint);

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
		IS_FRIENDLY_OR_NEUTRAL(EntitySystem&, tdt::uint);

		/**
		 * Destructor.
		 */
		~IS_FRIENDLY_OR_NEUTRAL() = default;

		/**
		 * Brief: Tests if a given entity is a friend of or neutral to the entity specified
		 *        in the constructor.
		 * Param: ID of the entity.
		 */
		bool operator()(tdt::uint);

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
		 * Destructor.
		 */
		~HAS_GOLD() = default;

		/**
		 * Brief: Tests if a given entity has a gold component.
		 * Param: ID of the entity.
		 */
		bool operator()(tdt::uint);

		private:
			/**
			 * Entity system containing all tested entities.
			 */
			EntitySystem& entities_;
	};

	/**
	 * Tests if a given entity is of friendly faction,
	 * has structure component and has gold component
	 * (that is, it's a gold vault).
	 */
	struct IS_GOLD_VAULT
	{
		/**
		 * Constructor.
		 * Param: Entity system that contains all tested entities.
		 */
		IS_GOLD_VAULT(EntitySystem&);

		/**
		 * Destructor.
		 */
		~IS_GOLD_VAULT() = default;

		/**
		 * Brief: Tests a given entity.
		 * Param: ID of the entity.
		 */
		bool operator()(tdt::uint);

		private:
			/**
			 * Entity system that contains all tested entities.
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
		friend void DestructorHelper::destroy(EntitySystem&, tdt::uint, bool, tdt::uint);

		/**
		 * Brief: Destroy a given entity.
		 * Param: Entity system containing the entity.
		 * Param: ID of the entity.
		 */
		static void destroy(EntitySystem&, tdt::uint);
	};

	/**
	 * Brief: Returns the direction from a given entity to another given
	 *        entity in the form of the direction enum (8 directional).
	 * Param: EntitySystem containing both entities.
	 * Param: ID of the first entity.
	 * Param: ID of the second entity.
	 * Note: The direction is #1 -> #2.
	 */
	int get_enum_direction(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns a random number within a given range.
	 * Param: Lower bound of the range.
	 * Param: Upper bound of the range.
	 */
	tdt::uint get_random(tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the absolute value of a given integer.
	 * Param: The number we want absolute value of.
	 */
	tdt::uint abs(int);
}