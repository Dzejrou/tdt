#pragma once

#include <OGRE/Ogre.h>
#include <CEGUI/CEGUI.h>
#include <tuple>
#include <Enums.hpp>
#include <Typedefs.hpp>

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
		Camera();

		/**
		 * Destructor.
		 */
		~Camera() = default;

		/**
		 * \brief Initializes the wrapper with a camera object.
		 * \param Camera to be wrapped.
		 * \param Point the camera is looking at.
		 */
		void init(Ogre::Camera*, const Ogre::Vector3&);

		/**
		 * \brief Sets the 2D position of the camera (X and Z axes).
		 * \param The new position.
		 */
		void set_position(const Ogre::Vector2&);

		/**
		 * \brief Returns the 3D position of the camera (including height).
		 */
		const Ogre::Vector3& get_position() const;

		/**
		 * \brief Changes the direction the camera is facing.
		 * \param The new direction vector.
		 */
		void set_direction(const Ogre::Vector3&);

		/**
		 * \brief Returns the direction the camera is facing.
		 */
		Ogre::Vector3 get_direction() const;

		/**
		 * \brief Makes the camera to look at a point on the ground.
		 * \param 2D location of the point (X and Z axes).
		 */
		void look_at(const Ogre::Vector2&);

		/**
		 * \brief Resets the camera's position and orientation.
		 */
		void reset();

		/**
		 * \brief Sets the starting stats of the camera.
		 *        (Used upon reset.)
		 * \param Starting position.
		 * \param Starting point that camera is looking at.
		 * \param Starting height of the camera.
		 */
		void set_start(const Ogre::Vector2&, const Ogre::Vector2&, tdt::real);

		/**
		 * \brief Changes the movement mode of the camera.
		 * \param If true, the camera will be in free mode,
		 *        otherwise it will return to RTS mode.
		 */
		void set_free_mode(bool);

		/**
		 * \brief Returns true if the camera is in free mode,
		 *        false otherwise.
		 */
		bool get_free_mode() const;

		/**
		 * \brief Updates the movement of the camera.
		 * \param Time since the last frame.
		 */
		void update(tdt::real);

		/**
		 * \brief Moves the camera if a movement key was pressed.
		 * \param Pressed key.
		 */
		void key_pressed(CEGUI::Key::Scan);

		/**
		 * \brief Moves the camera if a movement key was released.
		 * \param Released key.
		 */
		void key_released(CEGUI::Key::Scan);

		/**
		 * \brief Moves the camera in a given direction, used for
		 *        mouse movement.
		 * \param Direction of the movement.
		 * \param Time since the last frame.
		 */
		void move(DIRECTION::VAL, tdt::real);

		/**
		 * \brief Changes the height of the camera.
		 * \param The new height.
		 */
		void set_height(tdt::real);

		/**
		 * \brief Returns the height of the camera.
		 */
		tdt::real get_height() const;

		/**
		 * \brief Rotates the camera around the side-to-side axis.
		 * \param Amount of degrees to rotate by.
		 */
		void pitch(const Ogre::Degree&);

		/**
		 * \brief Rotates the camera around the vertical axis.
		 * \param Amount of degrees to rotate by.
		 */
		void yaw(const Ogre::Degree&);

		/**
		 * \brief Rotates the camera around the point it looks at when the mouse wheel is rotated.
		 * \param Value of the mouse wheel rotation.
		 */
		void rotate(int);

		/**
		 * \brief Zooms the camera in or out depending on the mouse wheel rotation.
		 * \param Value of the mouse wheel rotation.
		 */
		void zoom(int);

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

		/**
		 * Current zoom level.
		 */
		int zoom_;

		/**
		 * Zoom boundaries.
		 */
		const int zoom_min_, zoom_max_;

		/**
		 * Delta time saved in the last update.
		 */
		tdt::real last_delta_;

		/**
		 * Speed modifier for zooming in and out. (Normal speed is too slow.)
		 */
		tdt::real zoom_modifier_;

		/**
		 * Point in the game world the camera is looking at.
		 */
		Ogre::Vector3 target_;
};