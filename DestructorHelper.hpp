#pragma once

#include <cstdlib>
#include <string>
#include "lppscript/LppScript.hpp"
class EntitySystem;

namespace DestructorHelper
{
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	const std::string& get_blueprint(EntitySystem&, std::size_t);

	void destroy(EntitySystem&, std::size_t);
}