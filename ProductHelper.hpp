#pragma once

#include <cstdlib>
class EntitySystem;

namespace ProductHelper
{
	void set_producer(EntitySystem&, std::size_t, std::size_t);

	std::size_t get_producer(EntitySystem&, std::size_t);
}