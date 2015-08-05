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
		std::vector<std::pair<std::size_t, std::size_t>> task_pairs_;
		std::ofstream file_;
};

template <>
inline void GameSerializer::save_component<PhysicsComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<PhysicsComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.physics)\n" 
		+ "game.set_position(" + tbl_name + std::to_string(comp.position.x)
		+ ", " + std::to_string(comp.position.y) + ", " + std::to_string(comp.position.z) + ")\n"
		+ "game.set_solid(" + tbl_name + ", " + (comp.solid ? "true" : "false") + ")\n"
		+ "game.set_half_height(" + tbl_name + ", " + std::to_string(comp.half_height) + ")\n"
	};

	file_ << comm;
}

template <>
inline void GameSerializer::save_component<HealthComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<HealthComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.health)\n"
		+ "game.buff(" + tbl_name + ", " + std::to_string(comp.max_hp) + ")\n"
		+ "game.sub_health(" + tbl_name + ", " + std::to_string(comp.max_hp - comp.curr_hp) + ")\n"
		+ "game.add_defense(" + tbl_name + ", " + std::to_string(comp.defense) + ")\n"
		+ "game.set_regen(" + tbl_name + ", " + std::to_string(comp.regen) + ")\n"
		+ "game.set_alive(" + tbl_name + ", " + (comp.alive ? "true" : "false") + ")\n"
	};

	file_ << comm;
}

template <>
inline void GameSerializer::save_component<AIComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<AIComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.ai)\n"
		+ "game.set_blueprint(" + tbl_name + ", " + comp.blueprint + ")\n"
		+ "game.set_state(" + tbl_name + ", " + std::to_string((int)comp.state) + ")\n"
		+ "game.set_faction(" + tbl_name + ", " + std::to_string((int)comp.faction) + ")\n"
	};

	file_ << comm;
}

template <>
inline void GameSerializer::save_component<GraphicsComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<GraphicsComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.graphics)\n"
		+ "game.set_mesh(" + tbl_name + ", " + comp.mesh + ")\n"
		+ "game.set_material(" + tbl_name + ", " + comp.material + ")\n"
		+ "game.init_graphics_component(" + tbl_name + ")\n"
		+ "game.set_visible(" + tbl_name + ", " + (comp.visible ? "true" : "false") ")\n"
	};

	file_ << comm;
}

template <>
inline void GameSerializer::save_component<MovementComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<MovementComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.movement)\n"
		+ "game.set_speed(" + tbl_name + ", " + std::to_string(comp.speed_modifier) + ")\n"
	};
}

template <>
inline void GameSerializer::save_component<>(std::size_t id, const std::string& tbl_name)
{
}

template <>
inline void GameSerializer::save_component<>(std::size_t id, const std::string& tbl_name)
{
}