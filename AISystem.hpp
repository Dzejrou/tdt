#pragma once

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "lppscript\LppScript.hpp"

class AISystem : public System
{
	public:
		AISystem(EntitySystem&);
		~AISystem() {}

		void update(std::size_t, Ogre::Real);
		bool is_valid(std::size_t) const;
		bool is_friendly(std::size_t, std::size_t) const;
		bool is_neutral(std::size_t) const;
		bool is_inanimate(std::size_t) const;
		std::string get_blueprint(std::size_t) const;
		EntityState get_state(std::size_t) const;
		Faction get_faction(std::size_t) const;

	private:
		EntitySystem& entities_;
};