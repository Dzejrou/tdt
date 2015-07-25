#pragma once

#include <Ogre.h>

#include <string>

class Line : public Ogre::ManualObject
{
	public:
		Line(const Ogre::Vector3&, const Ogre::Vector3&,
			 const Ogre::String& = "line_", const std::string& = "colour/blue");
		~Line() {}
	private:
		Ogre::Vector3 start_, end_;
		std::string material_;

		static int line_count_; // For easy line naming.
};