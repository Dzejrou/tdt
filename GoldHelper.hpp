#pragma once

#include <cstdlib>
class EntitySystem;

namespace GoldHelper
{
	/**
	 * Brief: Sets the gold value a given entity has, does not check if
	 *        the new value is smalled than the limit, use add_gold if that's
	 *        needed.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new gold value.
	 */
	void set_curr_gold(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the gold value a given entity has.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_curr_gold(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the limit of gold that a given entity can have.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new limit.
	 */
	void set_max_gold(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the limit of gold that a given entity can have.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_max_gold(EntitySystem&, std::size_t);

	/**
	 * Brief: Adds a given gold value to a given entity up to it's
	 *        gold limit, returns the amount of gold that superceeded the gold
	 *        limit and thus wasn't added.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Amount of gold to add.
	 */
	std::size_t add_gold(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Removes a given amount of gold from a given entity, but
	 *        does not subtract past zero. Returns amount of gold
	 *        actually removed.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Amoung of gold to subtract.
	 */
	std::size_t sub_gold(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Transfers all gold of an entity to another entity while
	 *        keeping the (0, max) range in mind. Returns amount of gold
	 *        actually transfered.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the sender entity.
	 * Param: ID of the receiver entity.
	 */
	std::size_t transfer_all_gold(EntitySystem&, std::size_t, std::size_t);
};