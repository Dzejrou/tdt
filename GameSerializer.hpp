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
		void save_tasks();

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
		+ "game.set_position(" + tbl_name + ", " + std::to_string(comp.position.x)
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
		+ "game.set_visible(" + tbl_name + ", " + (comp.visible ? "true" : "false") + ")\n"
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
inline void GameSerializer::save_component<CombatComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<EventComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<InputComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<InputComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.input)\n"
		+ "game.set_input_handler(" + tbl_name + ", " + comp.input_handler + ")\n"
	};

	file_ << comm;
}

template <>
inline void GameSerializer::save_component<TimeComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<ManaComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<SpellComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<ProductionComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<PathfindingComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<PathfindingComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.pathfinding)\n"
		+ "game.set_pathfind_blueprint(" + tbl_name + ", " + comp.blueprint + ")\n"
		+ "game.pathfind(" + tbl_name + ", " + std::to_string(comp.target_id) + ")\n"
	};

	file_ << comm;
}

template <>
inline void GameSerializer::save_component<TaskComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<TaskComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.task)\n"
		+ "game.set_task_source(" + tbl_name + ", " + std::to_string(comp.source) + ")\n"
		+ "game.set_task_target(" + tbl_name + ", " + std::to_string(comp.target) + ")\n"
		+ "game.set_task_type(" + tbl_name + ", " + std::to_string((int)comp.task_type) + ")\n"
	};
	task_pairs_.emplace_back(std::make_pair(comp.source, id));

	file_ << comm;
}

template<>
inline void GameSerializer::save_component<TaskHandlerComponent>(std::size_t id, const std::string& tbl_name)
{
	auto& comp = entities_.get_component<TaskHandlerComponent>(id);
	std::string comm{
		"game.add_component(" + tbl_name + ", game.enum.component.task_handler)\n"
	};

	for(std::size_t i = 0; i < comp.possible_tasks.size(); ++i)
	{
		if(comp.possible_tasks.test(i))
			comm.append("game.add_possible_task(" + tbl_name + ", " + std::to_string(i) + ")\n");
	}

	file_ << comm;
}