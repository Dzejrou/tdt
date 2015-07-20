#pragma once

#include <Ogre.h>
#include <stdexcept>
#include <limits>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

/**
 * System handling movement related updates and containing movement & physics related methods.
 */
class MovementSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 */
		MovementSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~MovementSystem() {}

		/**
		 * Brief: Updates the movement of a single valid entity.
		 * Param: ID of the entity.
		 * Param: Time since the last frame.
		 */
		void update(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns true if a given entity is valid for this system's update, false otherwise.
		 *        (Should be tested before each update call.)
		 * Param: ID of the entity.
		 */
		bool is_valid(std::size_t) const;

		/**
		 * Brief: Returns true if a given entity is moving.
		 * Param: ID of the entity.
		 */
		bool is_moving(std::size_t) const;

		/**
		 * Brief: Returns true if a given entity is solid (i.e. is subject to collision detection).
		 * Param: ID of the entity.
		 */
		bool is_solid(std::size_t) const;

		/**
		 * Brief: Returns true if a given entity can move to a given point in space, false otherwise.
		 * Param: ID of the entity.
		 * Param: Target coordinate.
		 */
		bool can_move_to(std::size_t, Ogre::Vector3);

		/**
		 * Brief: Sets a given entity to move in a given direction, returns true if such movement is possible and
		 *        false otherwise. The move will then be applied in the update method.
		 * Param: ID of the entity.
		 * Param: Directional vector.
		 * Note: Every vector passed to this method should be normalised and the length of the move will be
		 *       increased by the entity's speed modifier. This is not enforced though.
		 */
		bool move(std::size_t, Ogre::Vector3);

		/**
		 * Brief: Moves a given entity to a given point in space (absolute movement).
		 * Param: ID of the entity.
		 * Param: Target coordinate.
		 */
		void move_to(std::size_t, Ogre::Vector3);

		/**
		 * Brief: Rotates a given entity by a given amount of radians.
		 * Param: ID of the entity.
		 * Param: Rotation angle in radians.
		 * Note: Ogre3D has conversion functions.
		 */
		void rotate(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns a given entity's bounding box.
		 * Param: ID of th entity.
		 * Note: The entity has to have a GraphicsComponent, because collision detection is
		 *       done using Ogre's bounding boxes.
		 */
		const Ogre::AxisAlignedBox& get_bounds(std::size_t) const;

		/**
		 * Brief: Returns true if two given entities collide, false otherwise.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 */
		bool collide(std::size_t, std::size_t) const;

		/**
		 * Brief: Returns the distance between two given entities.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 */
		Ogre::Real get_distance(std::size_t, std::size_t) const;

		/**
		 * Brief: Returns the position of a given entity.
		 * Param: ID of the entity.
		 */
		Ogre::Vector3 get_position(std::size_t) const;

		/**
		 * Brief: Returns the speed modifier of a given entity.
		 * Param: ID of the entity.
		 */
		Ogre::Real get_speed_modifier(std::size_t) const;

		/**
		 * Brief: Changes the speed modifier of a given entity to a given value.
		 * Param: ID of the entity.
		 * Param: New speed value.
		 */
		void set_speed_modifier(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns the ID of the closest enemy in a given radius around a given entity,
		 *        returns said entity's ID if no enemies are present in the radius.
		 * Param: ID of the entity.
		 * Param: The radius value.
		 */
		std::size_t enemy_in_radius(std::size_t, Ogre::Real) const;

		/**
		 * Brief: Returns the ID of an enemy that is closest to a given entity, or said entity's ID
		 *        if no enemies are around it.
		 * Param: ID of the entity.
		 */
		std::size_t closest_enemy(std::size_t) const;

		/**
		 * Brief: Returns the direction to the enemy that is closest (with optional maximal distance)
		 *        to a given entity.
		 * Param: ID of the entity.
		 * Param: Optional radius.
		 */
		Ogre::Vector3 dir_to_closest_enemy(std::size_t, Ogre::Real = std::numeric_limits<Ogre::Real>::max()) const;

		/**
		 * Brief: Returns the direction from a given entity to another given entity.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 */
		Ogre::Vector3 dir_to_enemy(std::size_t, std::size_t) const;

		/**
		 * Brief: Returns the direction a given entity is facing.
		 * Param: ID of the entity.
		 */
		Ogre::Vector3 get_dir(std::size_t) const;

		/**
		 * Brief: Returns the opposite direction to the direction a given entity is facing.
		 * Param: ID of the entity.
		 */
		Ogre::Vector3 get_dir_back(std::size_t) const;

		/**
		 * Brief: Returns the direction perpendicular to the direction a given entity is facing.
		 *        (To the left.)
		 * Param: ID of the entity.
		 */
		Ogre::Vector3 get_dir_left(std::size_t) const;

		/**
		 * Brief: Returns the direction perpendicular to the direction a given entity is facing.
		 *        (To the right.)
		 * Param: ID of the entity.
		 */
		Ogre::Vector3 get_dir_right(std::size_t) const;

		/**
		 * Brief: Returns the size of the angle bewteen two given vectors as Ogre::Real
		 *        which can then be used in Ogre::Radian constructor for conversion to Radians.
		 *        (The reason for this is that Lua does not have the notion of radians and as such
		 *        using floating point numbers is easier.)
		 * Param: Vector #1.
		 * Param: Vector #2.
		 */
		Ogre::Real get_angle(Ogre::Vector3, Ogre::Vector3) const;
	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
};