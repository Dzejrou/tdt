#pragma once

#include <string>
#include <Typedefs.hpp>
#include <Enums.hpp>
class EntitySystem;

/**
 *
 */
namespace SelectionHelper
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
	void set_material(EntitySystem&, tdt::uint, const std::string&);

	/**
	 *
	 */
	const std::string& get_material(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	bool select(EntitySystem&, tdt::uint, bool);

	/**
	 *
	 */
	bool deselect(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_scale(EntitySystem&, tdt::uint, Ogre::Vector3);

	/**
	 *
	 */
	Ogre::Vector3 get_scale(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_marker_type(EntitySystem&, tdt::uint, SELECTION_MARKER_TYPE);

	/**
	 *
	 */
	SELECTION_MARKER_TYPE get_marker_type(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void set_rotation(EntitySystem&, tdt::uint, Ogre::Degree);

	/**
	 *
	 */
	Ogre::Degree get_rotation(EntitySystem&, tdt::uint);
}