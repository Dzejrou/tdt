#pragma once

#include "EntitySystem.hpp"

namespace AIHelper
{
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);
	const std::string& get_blueprint(EntitySystem&, std::size_t);

	void set_faction(EntitySystem&, std::size_t, FACTION);
	FACTION get_faction(EntitySystem&, std::size_t);

	void set_state(EntitySystem&, std::size_t, ENTITY_STATE);
	ENTITY_STATE get_state(EntitySystem&, std::size_t);
}