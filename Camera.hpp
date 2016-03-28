#pragma once

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <tuple>
#include "Enums.hpp"
#include "Typedefs.hpp"

/**
 * Class wrapping the Ogre camera object, allowing RTS-like movement and switching
 * to free mode.
 */
class Camera
{
	friend class GameSerializer;
	friend class Game;
	public:
		/**
		 * Constructor.
		 */
		Camera() = default;

		/**
		 * Destructor.
		 */
		~Camera() = default;

		/**
		 * Brief: Initializes the wrapper with a camera object.
		 * Param: Camera to be wrapped.
		 */
		void init(Ogre::Camera*);

		/**
		 * Brief: Sets the 2D position of the camera (X and Z axes).
		 * Param: The new position.
		 */
		void set_position(const Ogre::Vector2&);

		/**
		 * Brief: Returns the 3D position of the camera (including height).
		 */
		const Ogre::Vector3& get_position() const;

		/**
		 * Brief: Changes the direction the camera is facing.
		 * Param: The new direction vector.
		 */
		void set_direction(const Ogre::Vector3&);

		/**
		 * Brief: Returns the direction the camera is facing.
		 */
		const Ogre::Vector3& get_direction() const;

		/**
		 * Brief: Makes the camera to look at a point on the ground.
		 * Param: 2D location of the point (X and Z axes).
		 */
		void look_at(const Ogre::Vector2&);

		/**
		 * Brief: Resets the camera's position and orientation.
		 */
		void reset();

		/**
		 * Brief: Sets the starting stats of the camera.
		 *        (Used upon reset.)
		 * Param: Starting position.
		 * Param: Starting point that camera is looking at.
		 * Param: Starting height of the camera.
		 */
		void set_start(const Ogre::Vector2&, const Ogre::Vector2&, tdt::real);

		/**
		 * Brief: Changes the movement mode of the camera.
		 * Param: If true, the camera will be in free mode,
		 *        otherwise it will return to RTS mode.
		 */
		void set_free_mode(bool);

		/**
		 * Brief: Returns true if the camera is in free mode,
		 *        false otherwise.
		 */
		bool get_free_mode() const;

		/**
		 * Brief: Updates the movement of the camera.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real);

		/**
		 * Brief: Moves the camera if a movement key was pressed.
		 * Param: Pressed key.
		 */
		void key_pressed(CEGUI::Key::Scan);

		/**
		 * Brief: Moves the camera if a movement key was released.
		 * Param: Released key.
		 */
		void key_released(CEGUI::Key::Scan);

		/**
		 * Brief: Moves the camera in a given direction, used for
		 *        mouse movement.
		 * Param: Direction of the movement.
		 * Param: Time since the last frame.
		 */
		void move(DIRECTION::VAL, tdt::real);

		/**
		 * Brief: Changes the height of the camera.
		 * Param: The new height.
		 */
		void set_height(tdt::real);

		/**
		 * Brief: Returns the height of the camera.
		 */
		tdt::real get_height() const;

		/**
		 * Brief: Rotates the camera around the side-to-side axis.
		 * Param: Amount of degrees to rotate by.
		 */
		void pitch(const Ogre::Degree&);

		/**
		 * Brief: Rotates the camera around the vertical axis.
		 * Param: Amount of degrees to rotate by.
		 */
		void yaw(const Ogre::Degree&);

	private:
		/**
		 * Ogre camera that is wrapped.
		 */
		Ogre::Camera* camera_;

		/**
		 * Starting stats of the camera, used when resetting.
		 */
		std::tuple<Ogre::Vector3, Ogre::Vector3> start_;

		/**
		 * Determines the mode of the camera, if true, it
		 * can fly around the level, if false, it can move
		 * in an RTS-like fashion.
		 */
		bool free_mode_;

		/**
		 * Direction vector of the free mode movement.
		 */
		Ogre::Vector3 movement_direction_;

		/**
		 * Speed modifier of the camera.
		 */
		tdt::real speed_;

		/**
		 * Y axis the camera is locked at when free mode
		 * is disabled.
		 */
		tdt::real height_;
};