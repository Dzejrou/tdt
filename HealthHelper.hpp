#pragma once

#include "EntitySystem.hpp"

namespace HealthHelper
{
	void set_health(EntitySystem&, std::size_t, std::size_t);
	std::size_t get_health(EntitySystem&, std::size_t);

	void add_health(EntitySystem&, std::size_t, std::size_t);
	void sub_health(EntitySystem&, std::size_t, std::size_t, bool = false);

	void heal(EntitySystem&, std::size_t);
	void buff(EntitySystem&, std::size_t, std::size_t);
	void debuff(EntitySystem&, std::size_t, std::size_t);

	void set_regen(EntitySystem&, std::size_t, std::size_t);
	std::size_t get_regen(EntitySystem&, std::size_t);

	void set_alive(EntitySystem&, std::size_t, bool);
	bool is_alive(EntitySystem&, std::size_t);

	void set_defense(EntitySystem&, std::size_t, std::size_t);
	std::size_t get_defense(EntitySystem&, std::size_t);
	void add_defense(EntitySystem&, std::size_t, std::size_t);
	void sub_defense(EntitySystem&, std::size_t, std::size_t);

	void ubercharge(EntitySystem&, std::size_t);
}