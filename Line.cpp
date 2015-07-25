#include "Line.hpp"

/**
 * Static member initialization.
 */
std::size_t Line::line_count_ = 0;

Line::Line(const Ogre::Vector3& start_point, const Ogre::Vector3& end_point,
		   const Ogre::String& name, const std::string& material)
	: Ogre::ManualObject(name == "line_" ? name + std::to_string(line_count_++) : name),
	  start_{start_point}, end_{end_point}, material_{material}
{
	setQueryFlags(0);
	recreate();
}

Ogre::Vector3 Line::get_start() const
{
	return start_;
}

Ogre::Vector3 Line::get_end() const
{
	return end_;
}

void Line::reposition(const Ogre::Vector3& s, const Ogre::Vector3& e)
{
	start_ = s;
	end_ = e;
	recreate();
}

void Line::set_material(const std::string& new_mat)
{
	material_ = new_mat;
	recreate();
}

void Line::recreate()
{
	clear();
	begin(material_, Ogre::RenderOperation::OT_LINE_STRIP);
	position(start_);
	position(end_);
	end();
}
