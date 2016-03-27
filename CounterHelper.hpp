#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 *
 */
namespace CounterHelper
{
	/**
	 *
	 */
	bool increment(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	bool decrement(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_curr_value(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	tdt::uint get_curr_value(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_max_value(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	tdt::uint get_max_value(EntitySystem&, tdt::uint);
}