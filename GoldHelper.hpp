#pragma once

#include <cstdlib>
class EntitySystem;

namespace GoldHelper
{
	void set_curr_gold(EntitySystem&, std::size_t, std::size_t);

	std::size_t get_curr_gold(EntitySystem&, std::size_t);

	void set_max_gold(EntitySystem&, std::size_t, std::size_t);

	std::size_t get_max_gold(EntitySystem&, std::size_t);

	std::size_t add_gold(EntitySystem&, std::size_t, std::size_t);

	std::size_t sub_gold(EntitySystem&, std::size_t, std::size_t);

	std::size_t transfer_all_gold(EntitySystem&, std::size_t, std::size_t);
};