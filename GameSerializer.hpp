#pragma once

#include <string>

#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

class GameSerializer
{
	public:
		GameSerializer(EntitySystem&);
		~GameSerializer() {}

		void save_game(const std::string&);
		void load_game(const std::string&);
	private:
		void save_entity(std::size_t);

		template<typename COMP>
		void save_component(const std::string&);

		EntitySystem& entities_;
		lpp::Script& script_;
};