#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <numeric>
#include "Enums.hpp"
class EntitySystem;

namespace EventHelper
{
	void set_event_type(EntitySystem&, std::size_t, EVENT_TYPE);

	EVENT_TYPE get_event_type(EntitySystem&, std::size_t);

	void set_target(EntitySystem&, std::size_t, std::size_t);

	std::size_t get_target(EntitySystem&, std::size_t);

	void set_radius(EntitySystem&, std::size_t, Ogre::Real);

	Ogre::Real get_radius(EntitySystem&, std::size_t);

	void set_active(EntitySystem&, std::size_t, bool = true);

	bool is_active(EntitySystem&, std::size_t);
}