#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

namespace AlignHelper
{
	/**
	 * \brief Sets the material name of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 * \param New material name.
	 */
	void set_material(EntitySystem&, tdt::uint, tdt::uint, const std::string&);

	/**
	 * \brief Returns the material name of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 */
	const std::string& get_material(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the mesh name of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 * \param New mesh name.
	 */
	void set_mesh(EntitySystem&, tdt::uint, tdt::uint, const std::string&);

	/**
	 * \brief Returns the mesh name of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 */
	const std::string& get_mesh(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the position offset from the position of the residence node
	 *        of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 * \param New position offset vector.
	 */
	void set_position_offset(EntitySystem&, tdt::uint, tdt::uint, const Ogre::Vector3&);

	/**
	 * \brief Returns the position offset from the position of the residence node
	 *        of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 */
	const Ogre::Vector3& get_position_offset(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the scale of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 * \param New scale vector.
	 */
	void set_scale(EntitySystem&, tdt::uint, tdt::uint, const Ogre::Vector3&);

	/**
	 * \brief Returns the scale of a given entity in a given align state.
	 * \param Entity system containing the components of the given entity.
	 * \param ID of the entity.
	 * \param Number of the state.
	 */
	const Ogre::Vector3& get_scale(EntitySystem&, tdt::uint, tdt::uint);
}