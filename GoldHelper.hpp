#pragma once

#include <cstdlib>
class EntitySystem;
struct GoldComponent;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the gold component.
 */
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
	 * Param: If false, the transaction won't be registered (used when called from Player);
	 */
	std::size_t sub_gold(EntitySystem&, std::size_t, std::size_t, bool = true);

	/**
	 * Brief: Transfers all gold of an entity to another entity while
	 *        keeping the (0, max) range in mind. Returns amount of gold
	 *        actually transfered.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the sender entity.
	 * Param: ID of the receiver entity.
	 */
	std::size_t transfer_all_gold(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns true if a given entity's gold storage is full, false
	 *        otherwise.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	bool gold_full(EntitySystem&, std::size_t);

	/**
	 *
	 */
	void register_transaction_(EntitySystem&, GoldComponent&, std::size_t, std::size_t, bool = true);
};