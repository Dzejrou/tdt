#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the graphics component.
 */
namespace GraphicsHelper
{
	/**
	 * Enum representing the planes in a 3D space.
	 */
	enum class PLANE
	{
		X = 0, Y, Z
	};

	/**
	 * \brief Sets the model of a given entity.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 * \param Name of the new mesh.
	 * \note Requires a call to init_graphics_component to take effect.
	 */
	void set_mesh(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the mesh of a given entity.
	 * \param Reference to the entity system that contains components.
	 */
	const std::string& get_mesh(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the name of the material a given entity is using.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 * \param Name of the entity.
	 * \note Requires a call to init_graphcis_component to take effect.
	 */
	void set_material(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the material a given entity is using.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 */
	const std::string& get_material(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the visibility status of a given entity.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 * \param True for visible, false for invisible.
	 */
	void set_visible(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Returns true if a given entity is visible, false otherwise.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 */
	bool is_visible(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the manual scaling status of a given entity.
	 *        (i.e. if the model should use dimensions stored in the mesh file
	 *         or has them explicitly set.)
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 * \param True for manual scaling, false for using the scale of the mesh.
	 * \note Requires a call to init_graphics_component to take effect.
	 */
	void set_manual_scaling(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Returns true if a given entity's model has explicit dimensions
	 *        or false if the dimensions of it's mesh are used.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 */
	bool get_manual_scaling(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the dimensions of a given entity (requires
	 *        manual_scaling to be true).
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 * \param The new scale value.
	 * \note Requires a call to init_graphics_component to take effect.
	 */
	void set_scale(EntitySystem&, tdt::uint, const Ogre::Vector3&);

	/**
	 * \brief Returns the scale (the dimensions) of a given entity (requires
	 *        manual_scaling to be true).
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 */
	const Ogre::Vector3& get_scale(EntitySystem&, tdt::uint);

	/**
	 * \brief Rotates a given entity so that it faces another one.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the first entity.
	 * \param ID of the second entity.
	 */
	void look_at(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Rotates a given entity by a given amount of radians.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 * \param Rotation angle in radians.
	 * \note Ogre3D has conversion functions.
	 */
	void rotate(EntitySystem&, tdt::uint, tdt::real, PLANE = PLANE::Y);

	/**
	 * \brief Returns a given entity's bounding box.
	 * \param Reference to the entity system that contains components.
	 * \param ID of th entity.
	 * \note The entity has to have a GraphicsComponent, because collision detection is
	 *       done using Ogre's bounding boxes.
	 */
	const Ogre::AxisAlignedBox& get_bounds(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if two given entities collide, false otherwise.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the first entity.
	 * \param ID of the second entity.
	 */
	bool collide(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Initializes the graphics component of a manually created entity
	 *        by loading it's model into an Ogre::Entity and bounding it to a
	 *        scene node.
	 * \param Reference to the entity system that contains components.
	 * \param ID of the entity.
	 */
	void init_graphics_component(EntitySystem&, Ogre::SceneManager&, tdt::uint);

	/**
	 * \brief Sets the flags used for queries (like in CombatSystem::in_sight) of
	 *        a given entity.
	 * \param ID of the entity.
	 * \param The new query flags.
	 */
	void set_query_flags(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Return the flags used for queries (like in CombatSystem::in_sight) of
	 *        a given entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_query_flags(EntitySystem&, tdt::uint);

	/**
	 * \brief Applies scale to a given entity's Ogre::Node if the entity has
	 *        manual scaling enabled (the scale is a part of the component).
	 * \param ID of the entity.
	 */
	void apply_scale(EntitySystem&, tdt::uint);
}