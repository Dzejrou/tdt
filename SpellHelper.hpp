#pragma once

#include <string>
#include "Typedefs.hpp"
class EntitySystem;

/**
 *
 */
namespace SpellHelper
{
	/**
	 *
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 *
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 *
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 *
	 */
	void set_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 *
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void cast(EntitySystem&, tdt::uint);
}