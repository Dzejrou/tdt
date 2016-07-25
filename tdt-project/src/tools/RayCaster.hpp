#pragma once

#include <OGRE/Ogre.h>
#include <vector>
#include <string>
#include <Typedefs.hpp>

/**
 * Manages polygon precise raycasting used with half walls that have empty spaces
 * in their bounding boxes.
 * \note Strongly inspired by http://www.ogre3d.org/tikiwiki/Raycasting+to+the+polygon+level from
 *       the official Ogre3D wiki, big thanks to all contributors.
 */
class RayCaster
{
	public:
		/**
		 * Constructor.
		 * \param Scene manager that is used to create the ray query.
		 */
		RayCaster(Ogre::SceneManager&);

		/**
		 * \brief Casts a ray that checks for polygon level collisions on it's way.
		 *        Returns a pair of a bool, signaling whether a hit was made and
		 *        a distance to the place of the collision, if any occured.
		 * \param Starting position of the ray.
		 * \param Direction of the ray.
		 * \param Name of the entity to be ignored (the target) if it's a wall.
		 */
		std::pair<bool, tdt::real> cast(const Ogre::Vector3&, const Ogre::Vector3&,
										const std::string& = "") const;

	private:
		/**
		 * Query used for the collision ray cast.
		 */
		Ogre::RaySceneQuery* query_;

		/**
		 * \brief Returns information about vertices of an entity by modifying it's size_t and
		 *        vector parameters.
		 * \param Entity to be checked.
		 * \param Number of vertices, will be set inside the function.
		 * \param Number of indices, will be set inside the function.
		 * \param Vector of vertex point positions, will be filled inside the function.
		 * \param Vector of indices of the vertex points inside the vertex vector above.
		 * \param Position of the entity.
		 * \param Orientation of the entity.
		 * \param Scale of the entity.
		 */
		void get_info(const Ogre::Entity&, tdt::uint&, tdt::uint&, std::vector<Ogre::Vector3>&,
					  std::vector<tdt::uint>&, const Ogre::Vector3&, const Ogre::Quaternion&,
					  const Ogre::Vector3&) const;
};