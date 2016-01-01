#pragma once

#include <Ogre.h>
#include <vector>
#include <limits>

/**
 * Manages polygon precise raycasting used with half walls that have empty spaces
 * in their bounding boxes.
 * Note: Strongly inspired by http://www.ogre3d.org/tikiwiki/Raycasting+to+the+polygon+level from
 *       the official Ogre3D wiki, big thanks to all contributors.
 */
class RayCaster
{
	public:
		/**
		 *
		 */
		RayCaster(Ogre::SceneManager&);

		/**
		 *
		 */
		std::pair<bool, Ogre::Vector3> cast(const Ogre::Vector3&, const Ogre::Vector3&);
	private:
		/**
		 *
		 */
		Ogre::RaySceneQuery* query_;

		/**
		 *
		 */
		void get_info(const Ogre::Entity&, std::size_t&, std::size_t&, std::vector<Ogre::Vector3>&,
					  std::vector<std::size_t>&, const Ogre::Vector3&, const Ogre::Quaternion&,
					  const Ogre::Vector3&);
};