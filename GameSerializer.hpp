#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

// Forward declaration.
class Game;

class GameSerializer
{
	public:
		GameSerializer(EntitySystem&);
		~GameSerializer() {}

		void save_game(Game&, const std::string& = "quick_save");
		void load_game(Game&, const std::string& = "quick_save");
	private:
		void save_entity(std::size_t);

		template<typename COMP>
		void save_component(std::size_t, const std::string&);

		EntitySystem& entities_;
		lpp::Script& script_;
		std::vector<std::string> saved_entities_;
		std::ofstream file_;
};

template <typename COMP>
inline void GameSerializer::save_component(const std::string &)
{
}
