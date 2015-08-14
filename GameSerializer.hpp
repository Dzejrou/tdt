#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

// Forward declaration.
class Game;

/**
 * Class that is used to save (by using Lua code generation)
 * and loading the game (by executing said code).
 */
class GameSerializer
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 */
		GameSerializer(EntitySystem&);

		/**
		 * Destructor.
		 */
		~GameSerializer() {}

		/**
		 * Brief: Creates a Lua script that is to be used as a save file by
		 *        serializing every entity into a sequence of commands that create
		 *        this entity from scratch when executed.
		 * Param: Reference to the Game object (to be able to save all necessary data).
		 * Param: Name of the save file.
		 */
		void save_game(Game&, const std::string& = "quick_save");

		/**
		 * Brief: Executes a given Lua script containing a serialized game, effectively
		 *        restoring the state of that game.
		 * Param: Reference to the game object (currently used for console entries,
		 *        but might be used more in the future).
		 * Param: Name of the save file to load.
		 */
		void load_game(Game&, const std::string& = "quick_save");
	private:
		/**
		 * Brief: Adds commands to the save file that assign all tasks (has to be done last).
		 */
		void save_tasks();

		/**
		 * Brief: Generates code that constructs a single component.
		 * Param: ID of the component to serialize (type specialized as template argument).
		 * Param: Name of the variable already in the save file that holds the new ID.
		 */
		template<typename COMP>
		void save_component(std::size_t, const std::string&);

		/**
		 * Reference to the game's entity system, used for component access.
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the lpp::Script singleton for easy use.
		 */
		lpp::Script& script_;

		/**
		 * Contains entity - task pairs that should be added in the save_tasks method.
		 */
		std::vector<std::pair<std::size_t, std::size_t>> task_pairs_;

		/**
		 * Main file stream (no need for ifstream, since loading is done through Lua).
		 */
		std::ofstream file_;

		/**
		 * Auxiliary vectors that allows to place entity creation at the top (so no entity
		 * variables are nil when loading a game) and component definitions at the bottom.
		 */
		std::vector<std::string> save_entities_, save_components_;
};

template <>
inline void GameSerializer::save_component<PhysicsComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<PhysicsComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.physics)\n" 
		+ "game.set_position(" + tbl_name + ", " + std::to_string(comp->position.x)
		+ ", " + std::to_string(comp->half_height) + ", " + std::to_string(comp->position.z) + ")\n"
		+ "game.set_solid(" + tbl_name + ", " + (comp->solid ? "true" : "false") + ")\n"
		+ "game.set_half_height(" + tbl_name + ", " + std::to_string(comp->half_height) + ")\n"
	};

	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<HealthComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.health)\n"
		+ "game.buff(" + tbl_name + ", " + std::to_string(comp->max_hp) + ")\n"
		+ "game.sub_health(" + tbl_name + ", " + std::to_string(comp->max_hp - comp->curr_hp) + ")\n"
		+ "game.add_defense(" + tbl_name + ", " + std::to_string(comp->defense) + ")\n"
		+ "game.set_regen(" + tbl_name + ", " + std::to_string(comp->regen) + ")\n"
		+ "game.set_alive(" + tbl_name + ", " + (comp->alive ? "true" : "false") + ")\n"
	};

	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<AIComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<AIComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.ai)\n"
		+ "game.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		+ "game.set_state(" + tbl_name + ", " + std::to_string((int)comp->state) + ")\n"
		+ "game.set_faction(" + tbl_name + ", " + std::to_string((int)comp->faction) + ")\n"
	};

	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<GraphicsComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<GraphicsComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.graphics)\n"
		+ "game.set_mesh(" + tbl_name + ", '" + comp->mesh + "')\n"
		+ "game.set_material(" + tbl_name + ", '" + comp->material + "')\n"
		+ "game.set_manual_scaling(" + tbl_name + ", " + (comp->manual_scaling ? "true" : "false") + ")\n"
		+ "game.init_graphics_component(" + tbl_name + ")\n"
		+ "game.set_visible(" + tbl_name + ", " + (comp->visible ? "true" : "false") + ")\n"
	};

	if(comp->manual_scaling)
	{
		comm.append(
			  "game.set_scale(" + tbl_name + ", " + std::to_string(comp->scale.x) + ", "
			+ std::to_string(comp->scale.y) + ", " + std::to_string(comp->scale.z) + ")\n"
		);
	}

	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<MovementComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<MovementComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.movement)\n"
		+ "game.set_speed(" + tbl_name + ", " + std::to_string(comp->speed_modifier) + ")\n"
	};
	
	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<CombatComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	std::string comm{ // NOTE: Attack target will be set via a task.
		  "game.add_component(" + tbl_name + ", game.enum.component.combat)\n"
		+ "game.set_range(" + tbl_name + ", " + std::to_string(comp->range) + ")\n"
		+ "game.set_atk_range(" + tbl_name + ", " + std::to_string(comp->min_dmg) + ", " + std::to_string(comp->max_dmg) + ")\n"
		+ "game.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.set_atk_type(" + tbl_name + ", " + std::to_string((int)comp->atk_type) + ")\n"
	};

	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<EventComponent>(std::size_t id, const std::string& tbl_name)
{
	// TODO:
}

template <>
inline void GameSerializer::save_component<InputComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<InputComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.input)\n"
		+ "game.set_input_handler(" + tbl_name + ", '" + comp->input_handler + "')\n"
	};

	save_components_.emplace_back(comm);
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
	auto comp = entities_.get_component<PathfindingComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.pathfinding)\n"
		+ "game.set_pathfinding_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		// Every task that was being comp->eted when saving will be executed again with new pathfinding.
	};

	save_components_.emplace_back(comm);
}

template <>
inline void GameSerializer::save_component<TaskComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TaskComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.task)\n"
		+ "game.set_task_source(" + tbl_name + ", entity_" + std::to_string(comp->source) + ")\n"
		+ "game.set_task_target(" + tbl_name + ", entity_" + std::to_string(comp->target) + ")\n"
		+ "game.set_task_type(" + tbl_name + ", " + std::to_string((int)comp->task_type) + ")\n"
	};
	task_pairs_.emplace_back(std::make_pair(comp->source, id));

	save_components_.emplace_back(comm);
}

template<>
inline void GameSerializer::save_component<TaskHandlerComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	std::string comm{
		"game.add_component(" + tbl_name + ", game.enum.component.task_handler)\n"
	};

	for(std::size_t i = 0; i < comp->possible_tasks.size(); ++i)
	{
		if(comp->possible_tasks.test(i))
			comm.append("game.add_possible_task(" + tbl_name + ", " + std::to_string(i) + ")\n");
	}

	save_components_.emplace_back(comm);
}

template<>
inline void GameSerializer::save_component<StructureComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<StructureComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.structure)\n"
		+ tbl_name + "_residences = { "
	};

	for(std::size_t i = 0; i < comp->residences.size(); ++i)
		comm.append("entity_" + std::to_string(comp->residences[i]) +
					(i == comp->residences.size() - 1 ? "" : ", "));
	comm.append(" }\ngame.add_residences(" + tbl_name + ", '" + tbl_name + "_residences')\n");

	save_components_.emplace_back(comm);
}

template<>
inline void GameSerializer::save_component<HomingComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<HomingComponent>(id);
	std::string comm{
		  "game.add_component(" + tbl_name + ", game.enum.component.homing)\n"
		+ "game.set_homing_source(" + tbl_name + ", " + std::to_string(comp->source) + ")\n"
		+ "game.set_homing_target(" + tbl_name + ", " + std::to_string(comp->target) + ")\n"
		+ "game.set_homing_dmg(" + tbl_name + ", " + std::to_string(comp->dmg) + ")\n"
	};

	save_components_.emplace_back(comm);
}