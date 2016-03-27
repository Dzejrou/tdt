#pragma once

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <tuple>
#include "Enums.hpp"
#include "Typedefs.hpp"

/**
 *
 */
class Camera
{
	friend class GameSerializer;
	friend class Game;
	public:
		/**
		 *
		 */
		Camera() = default;

		/**
		 *
		 */
		~Camera() = default;

		/**
		 *
		 */
		void init(Ogre::Camera*);

		/**
		 *
		 */
		void set_position(const Ogre::Vector2&);

		/**
		 *
		 */
		const Ogre::Vector3& get_position() const;

		/**
		 *
		 */
		void set_direction(const Ogre::Vector3&);

		/**
		 *
		 */
		const Ogre::Vector3& get_direction() const;

		/**
		 *
		 */
		void look_at(const Ogre::Vector2&);

		/**
		 *
		 */
		void reset();

		/**
		 *
		 */
		void set_start(const Ogre::Vector2&, const Ogre::Vector2&, tdt::real);

		/**
		 *
		 */
		void set_free_mode(bool);

		/**
		 *
		 */
		bool get_free_mode() const;

		/**
		 *
		 */
		void update(tdt::real);

		/**
		 *
		 */
		void key_pressed(CEGUI::Key::Scan);

		/**
		 *
		 */
		void key_released(CEGUI::Key::Scan);

		/**
		 *
		 */
		void move(DIRECTION::VAL, tdt::real);

		/**
		 *
		 */
		void set_height(tdt::real);

		/**
		 *
		 */
		tdt::real get_height() const;

		/**
		 *
		 */
		void pitch(const Ogre::Degree&);

		/**
		 *
		 */
		void yaw(const Ogre::Degree&);

	private:
		/**
		 *
		 */
		Ogre::Camera* camera_;

		/**
		 *
		 */
		std::tuple<Ogre::Vector3, Ogre::Vector3> start_;

		/**
		 *
		 */
		bool free_mode_;

		/**
		 *
		 */
		Ogre::Vector3 movement_direction_;

		/**
		 *
		 */
		tdt::real speed_;

		/**
		 *
		 */
		tdt::real height_;
};