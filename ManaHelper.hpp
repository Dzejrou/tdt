#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 *
 */
namespace ManaHelper
{
	/**
	 *
	 */
	void add_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	bool sub_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	void set_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	tdt::uint get_mana(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_max_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	tdt::uint get_max_mana(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 *
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);

}