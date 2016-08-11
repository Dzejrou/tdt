#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 *
 */
namespace ActivationHelper
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
	void activate(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void deactivate(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	bool is_activated(EntitySystem&, tdt::uint);
}