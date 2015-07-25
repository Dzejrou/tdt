#include "Line.hpp"

// Static initialization.
int Line::line_count_ = 0;

Line::Line(const Ogre::Vector3& start_point, const Ogre::Vector3& end_point,
		   const Ogre::String& name, const std::string& material)
	: Ogre::ManualObject(name == "line_" ? name + std::to_string(line_count_++) : name),
	  start_{start_point}, end_{end_point}, material_{material}
{
	clear();
	begin(material_, Ogre::RenderOperation::OT_LINE_STRIP);
	position(start_);
	position(end_);
	end();
}