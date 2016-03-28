#pragma once

#include "Typedefs.hpp"
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
	void set_curr_gold(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the gold value a given entity has.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_curr_gold(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the limit of gold that a given entity can have.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new limit.
	 */
	void set_max_gold(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the limit of gold that a given entity can have.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_max_gold(EntitySystem&, tdt::uint);

	/**
	 * Brief: Adds a given gold value to a given entity up to it's
	 *        gold limit, returns the amount of gold that superceeded the gold
	 *        limit and thus wasn't added.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Amount of gold to add.
	 */
	tdt::uint add_gold(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Removes a given amount of gold from a given entity, but
	 *        does not subtract past zero. Returns amount of gold
	 *        that could not be removed (remainder from the given amount
	 *        after subtracting).
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Amount of gold to subtract.
	 * Param: If false, the transaction won't be registered (used when called from Player);
	 */
	tdt::uint sub_gold(EntitySystem&, tdt::uint, tdt::uint, bool = true);

	/**
	 * Brief: Transfers all gold of an entity to another entity while
	 *        keeping the (0, max) range in mind. Returns amount of gold
	 *        actually transfered.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the sender entity.
	 * Param: ID of the receiver entity.
	 */
	tdt::uint transfer_all_gold(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns true if a given entity's gold storage is full, false
	 *        otherwise.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	bool gold_full(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void register_transaction_(EntitySystem&, GoldComponent&, tdt::uint, tdt::uint, bool = true);
};