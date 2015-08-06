#pragma once

#include <Ogre.h>

#include <string>

/**
 * Class representing a single coloured line in a 3D space used to display
 * pathfinding grids and other possible objects.
 */
class Line : public Ogre::ManualObject
{
	public:
		/**
		 * Constructor.
		 * Param: Coordinate of the starting point.
		 * Param: Coordinate of the ending point.
		 * Param: Name of the object (used by Ogre).
		 * Param: Material name.
		 */
		Line(const Ogre::Vector3&, const Ogre::Vector3&,
			 const Ogre::String& = "line_", const std::string& = "colour/blue");

		/**
		 * Destructor.
		 */
		~Line() {}

		/**
		 * Brief: Returns the coordinate of this line's starting point.
		 */
		Ogre::Vector3 get_start() const;

		/**
		 * Brief: Returns the coordinate of this line's ending point.
		 */
		Ogre::Vector3 get_end() const;

		/**
		 * Brief: Recreates this line between the given coordinates.
		 * Param: Coordinate of the new starting point.
		 * Param: Coordinate of the new ending point.
		 */
		void reposition(const Ogre::Vector3&, const Ogre::Vector3&);

		/**
		 * Brief: Changes the line's material and immedietly recreates
		 *        it for the change to take effect.
		 * Param: Name of the new material.
		 */
		void set_material(const std::string&);
	private:
		/**
		 * Brief: (Re)Creates this line through Ogre's facilities.
		 */
		void recreate();

		/**
		 * Coordinates of the starting and ending points.
		 */
		Ogre::Vector3 start_, end_;

		/**
		 * Name of the material (in most cases the colour) this line uses.
		 */
		std::string material_;

		/**
		 * Number of lines created so far, used for simple default naming.
		 */
		static std::size_t line_count_;
};