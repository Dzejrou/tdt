#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 *
 */
namespace LightHelper
{
	/**
	 *
	 */
	void set_visible(EntitySystem&, tdt::uint, bool);

	/**
	 *
	 */
	void toggle_visible(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	bool is_visible(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void init(EntitySystem&, tdt::uint);
}