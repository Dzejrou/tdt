#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <string>
class EntitySystem;

namespace AlignHelper
{
	/**
	 * Brief: Sets the material name of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 * Param: New material name.
	 */
	void set_material(EntitySystem&, std::size_t, std::size_t, const std::string&);

	/**
	 * Brief: Returns the material name of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 */
	const std::string& get_material(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the mesh name of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 * Param: New mesh name.
	 */
	void set_mesh(EntitySystem&, std::size_t, std::size_t, const std::string&);

	/**
	 * Brief: Returns the mesh name of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 */
	const std::string& get_mesh(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the position offset from the position of the residence node
	 *        of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 * Param: New position offset vector.
	 */
	void set_position_offset(EntitySystem&, std::size_t, std::size_t, const Ogre::Vector3&);

	/**
	 * Brief: Returns the position offset from the position of the residence node
	 *        of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 */
	const Ogre::Vector3& get_position_offset(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the scale of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 * Param: New scale vector.
	 */
	void set_scale(EntitySystem&, std::size_t, std::size_t, const Ogre::Vector3&);

	/**
	 * Brief: Returns the scale of a given entity in a given align state.
	 * Param: Entity system containing the components of the given entity.
	 * Param: ID of the entity.
	 * Param: Number of the state.
	 */
	const Ogre::Vector3& get_scale(EntitySystem&, std::size_t, std::size_t);
}