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
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.physics)\n" 
		+ "game.physics.set_position(" + tbl_name + ", " + std::to_string(comp->position.x)
		+ ", " + std::to_string(comp->half_height) + ", " + std::to_string(comp->position.z) + ")\n"
		+ "game.physics.set_solid(" + tbl_name + ", " + (comp->solid ? "true" : "false") + ")\n"
		+ "game.physics.set_half_height(" + tbl_name + ", " + std::to_string(comp->half_height) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<HealthComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.health)\n"
		+ "game.health.buff(" + tbl_name + ", " + std::to_string(comp->max_hp) + ")\n"
		+ "game.health.sub(" + tbl_name + ", " + std::to_string(comp->max_hp - comp->curr_hp) + ")\n"
		+ "game.health.add_defense(" + tbl_name + ", " + std::to_string(comp->defense) + ")\n"
		+ "game.health.set_regen(" + tbl_name + ", " + std::to_string(comp->regen) + ")\n"
		+ "game.health.set_alive(" + tbl_name + ", " + (comp->alive ? "true" : "false") + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<AIComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<AIComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.ai)\n"
		+ "game.ai.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		+ "game.ai.set_state(" + tbl_name + ", " + std::to_string((int)comp->state) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<GraphicsComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<GraphicsComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.graphics)\n"
		+ "game.graphics.set_mesh(" + tbl_name + ", '" + comp->mesh + "')\n"
		+ "game.graphics.set_material(" + tbl_name + ", '" + comp->material + "')\n"
		+ "game.graphics.set_manual_scaling(" + tbl_name + ", " + (comp->manual_scaling ? "true" : "false") + ")\n"
		+ "game.graphics.set_visible(" + tbl_name + ", " + (comp->visible ? "true" : "false") + ")\n"
	};

	if(comp->manual_scaling)
	{
		comm.append(
			  "game.graphics.set_scale(" + tbl_name + ", " + std::to_string(comp->scale.x) + ", "
			+ std::to_string(comp->scale.y) + ", " + std::to_string(comp->scale.z) + ")\n"
		);
	}
	comm.append("game.entity.init_graphics_component(" + tbl_name + ")\n");
	if(comp->entity)
		comm.append("game.graphics.set_query_flags(" + tbl_name + ", " + std::to_string(comp->entity->getQueryFlags()) + ")\n");

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<MovementComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<MovementComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.movement)\n"
		+ "game.movement.set_speed(" + tbl_name + ", " + std::to_string(comp->speed_modifier) + ")\n"
	};
	
	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<CombatComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	std::string comm{ // NOTE: Attack target will be set via a task.
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.combat)\n"
		+ "game.combat.set_range(" + tbl_name + ", " + std::to_string(comp->range) + ")\n"
		+ "game.combat.set_dmg_range(" + tbl_name + ", " + std::to_string(comp->min_dmg) + ", " + std::to_string(comp->max_dmg) + ")\n"
		+ "game.combat.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.combat.set_atk_type(" + tbl_name + ", " + std::to_string((int)comp->atk_type) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<EventComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<EventComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.event)\n"
		+ "game.event.set_type(" + tbl_name + ", " + std::to_string((int)comp->event_type) + ")\n"
		+ "game.event.set_target(" + tbl_name + ", entity_" + std::to_string(comp->target) + ")\n"
		+ "game.event.set_radius(" + tbl_name + ", " + std::to_string(comp->radius) + ")\n"
		+ "game.event.set_active(" + tbl_name + ", " + (comp->active ? "true" : "false") + ")\n"
		+ "game.event.set_handler(" + tbl_name + ", " + std::to_string(comp->handler) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<InputComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<InputComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.input)\n"
		+ "game.input.set_handler(" + tbl_name + ", '" + comp->input_handler + "')\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<TimeComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TimeComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.time)\n"
		+ "game.time.advance_current(" + tbl_name + ", " + std::to_string(comp->curr_time) + ")\n"
		+ "game.time.set_limit(" + tbl_name + ", " + std::to_string(comp->time_limit) + ")\n"
		+ "game.time.set_target(" + tbl_name + ", entity_" + std::to_string(comp->target) + ")\n"
		+ "game.time.set_type(" + tbl_name + ", " + std::to_string((int)comp->event_type) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
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
	auto comp = entities_.get_component<ProductionComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.production)\n"
		+ "game.production.set_blueprint(" + tbl_name + ", '" + comp->product_blueprint + "')\n"
		+ "game.production.set_limit(" + tbl_name + ", " + std::to_string(comp->max_produced) + ")\n"
		+ "game.production.set_count(" + tbl_name + ", " + std::to_string(comp->curr_produced) + ")\n"
		+ "game.production.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.production.set_progress(" + tbl_name + ", " + std::to_string(comp->curr_cd) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<ProductComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<ProductComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.product)\n"
		+ "game.production.set_producer(" + tbl_name + ", " + std::to_string(comp->producer) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<PathfindingComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<PathfindingComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.pathfinding)\n"
		+ "game.path.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		// Every task that was being completed when saving will be executed again with new pathfinding.
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<TaskComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TaskComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.task)\n"
		+ "game.task.set_source(" + tbl_name + ", entity_" + std::to_string(comp->source) + ")\n"
		+ "game.task.set_target(" + tbl_name + ", entity_" + std::to_string(comp->target) + ")\n"
		+ "game.task.set_type(" + tbl_name + ", " + std::to_string((int)comp->task_type) + ")\n"
	};
	task_pairs_.emplace_back(std::make_pair(comp->source, id));

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<TaskHandlerComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.task_handler)\n"
		+ "game.task.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
	};

	for(std::size_t i = 0; i < comp->possible_tasks.size(); ++i)
	{
		if(comp->possible_tasks.test(i))
			comm.append("game.task.add_possible(" + tbl_name + ", " + std::to_string(i) + ")\n");
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<StructureComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<StructureComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.structure)\n"
		+ "game.grid.set_walk_through(" + tbl_name + ", true)\n"
		+ tbl_name + "_residences = { "
	};
	std::string set_residents{}; // This will ensure that the grid nodes will have their residents also set.

	for(std::size_t i = 0; i < comp->residences.size(); ++i)
	{
		comm.append("entity_" + std::to_string(comp->residences[i]) +
					(i == comp->residences.size() - 1 ? "" : ", "));
		set_residents.append("game.grid.set_resident(entity_" + std::to_string(comp->residences[i])
							 + ", " + tbl_name + ")\n"
							 + "game.grid.set_free(" + std::to_string(comp->residences[i]) + ", false)\n");
	}
	comm.append(" }\ngame.grid.add_residences(" + tbl_name + ", '" + tbl_name + "_residences')\n");

	save_components_.emplace_back(std::move(comm));
	save_components_.emplace_back(set_residents);
}

template<>
inline void GameSerializer::save_component<HomingComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<HomingComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.homing)\n"
		+ "game.projectile.set_source(" + tbl_name + ", " + std::to_string(comp->source) + ")\n"
		+ "game.projectile.set_target(" + tbl_name + ", " + std::to_string(comp->target) + ")\n"
		+ "game.projectile.set_dmg(" + tbl_name + ", " + std::to_string(comp->dmg) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<EventHandlerComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<EventHandlerComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.event_handler)\n"
		+ "game.event_handling.set_handler(" + tbl_name + ", '" + comp->handler + "')\n"
	};

	for(std::size_t i = 0; i < comp->possible_events.size(); ++i)
	{
		if(comp->possible_events.test(i))
			comm.append("game.event_handling.add_possible(" + tbl_name + ", " + std::to_string(i) + ")\n");
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<DestructorComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<DestructorComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.destructor)\n"
		+ "game.destructor.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<GoldComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<GoldComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.gold)\n"
		+ "game.gold.set_current(" + tbl_name + ", " + std::to_string(comp->curr_amount) + ")\n"
		+ "game.gold.set_max(" + tbl_name + ", " + std::to_string(comp->max_amount) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<FactionComponent>(std::size_t id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<FactionComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.faction)\n" 
		+ "game.ai.set_faction(" + tbl_name + ", " + std::to_string((int)comp->faction) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}