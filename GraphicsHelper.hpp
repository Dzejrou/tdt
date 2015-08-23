#pragma once

class GraphicsComponent;
class EntitySystem;

namespace GraphicsHelper
{
	/**
	 * Brief: Rotates a given entity so that it faces another one.
	 * Param: Reference to the entity system that contains components.
	 * Param: ID of the first entity.
	 * Param: ID of the second entity.
	 */
	void look_at(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Rotates a given entity by a given amount of radians.
	 * Param: Reference to the entity system that contains components.
	 * Param: ID of the entity.
	 * Param: Rotation angle in radians.
	 * Note: Ogre3D has conversion functions.
	 */
	void rotate(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns a given entity's bounding box.
	 * Param: Reference to the entity system that contains components.
	 * Param: ID of th entity.
	 * Note: The entity has to have a GraphicsComponent, because collision detection is
	 *       done using Ogre's bounding boxes.
	 */
	const Ogre::AxisAlignedBox& get_bounds(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns true if two given entities collide, false otherwise.
	 * Param: Reference to the entity system that contains components.
	 * Param: ID of the first entity.
	 * Param: ID of the second entity.
	 */
	bool collide(EntitySystem&, std::size_t, std::size_t);
}