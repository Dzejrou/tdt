#pragma once

#include <Ogre.h>
#include "Enums.hpp"
class EntitySystem;

namespace TimeHelper
{
	Ogre::Real get_curr_time(EntitySystem&, std::size_t);

	void advance_curr_time(EntitySystem&, std::size_t, Ogre::Real);

	void max_curr_time(EntitySystem&, std::size_t);

	void set_time_limit(EntitySystem&, std::size_t, Ogre::Real);

	Ogre::Real get_time_limit(EntitySystem&, std::size_t);

	void set_target(EntitySystem&, std::size_t, std::size_t);

	std::size_t get_target(EntitySystem&, std::size_t);

	void set_type(EntitySystem&, std::size_t, TIME_EVENT);

	TIME_EVENT get_type(EntitySystem&, std::size_t);
}