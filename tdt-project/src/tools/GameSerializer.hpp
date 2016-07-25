#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <array>
#include <Components.hpp>
#include <Typedefs.hpp>
#include <systems/EntitySystem.hpp>

// Forward declaration.
class Game;
namespace lpp
{
	class Script;
}

/**
 * Class that is used to save (by using Lua code generation)
 * and loading the game (by executing said code).
 */
class GameSerializer
{
	typedef void (GameSerializer::*SerializerFuncPtr)(tdt::uint, const std::string&);
	public:
		/**
		 * Constructor.
		 * \param Reference to the game's entity system.
		 */
		GameSerializer(EntitySystem&);

		/**
		 * Destructor.
		 */
		~GameSerializer() {}

		/**
		 * \brief Creates a Lua script that is to be used as a save file by
		 *        serializing every entity into a sequence of commands that create
		 *        this entity from scratch when executed.
		 * \param Reference to the Game object (to be able to save all necessary data).
		 * \param Name of the save file.
		 */
		void save_game(Game&, const std::string& = "quick_save");

		/**
		 * \brief Executes a given Lua script containing a serialized game, effectively
		 *        restoring the state of that game.
		 * \param Reference to the game object (currently used for console entries,
		 *        but might be used more in the future).
		 * \param Name of the save file to load.
		 */
		void load_game(Game&, const std::string& = "quick_save");

	private:
		/**
		 * \brief Adds commands to the save file that assign all tasks (has to be done last).
		 */
		void save_tasks();

		/**
		 * \brief Returns a string containing commands that will restore
		 *        the wave system to it's current state.
		 * \param Reference to the game object that contains the wave system.
		 */
		std::string save_wave_system(Game&);

		/**
		 * \brief Returns a string containing commands that will restore
		 *        the unlock system to it's current state.
		 */
		std::string save_unlocks();

		/**
		 * \brief Generates code that constructs a single component.
		 * \param ID of the component to serialize (type specialized as template argument).
		 * \param Name of the variable already in the save file that holds the new ID.
		 */
		template<typename COMP>
		void save_component(tdt::uint, const std::string&);

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
		std::vector<std::pair<tdt::uint, tdt::uint>> task_pairs_;

		/**
		 * Main file stream (no need for ifstream, since loading is done through Lua).
		 */
		std::ofstream file_;

		/**
		 * Auxiliary vectors that allows to place entity creation at the top (so no entity
		 * variables are nil when loading a game) and component definitions at the bottom.
		 */
		std::vector<std::string> save_entities_, save_components_;

		/**
		 * Pointers to the different save_component instances allowing for easy runtime
		 * differencing between components.
		 */
		std::array<SerializerFuncPtr, Component::count> serializers_;
};

template <>
inline void GameSerializer::save_component<PhysicsComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<HealthComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<AIComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<GraphicsComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<MovementComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<MovementComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.movement)\n"
		+ "game.movement.set_speed(" + tbl_name + ", " + std::to_string(comp->speed_modifier) + ")\n"
		+ "game.movement.set_original_speed(" + tbl_name + ", " + std::to_string(comp->original_speed) + ")\n"
	};
	
	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<CombatComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	std::string comm{ // NOTE: Attack target will be set via a task.
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.combat)\n"
		+ "game.combat.set_range(" + tbl_name + ", " + std::to_string(comp->range) + ")\n"
		+ "game.combat.set_dmg_range(" + tbl_name + ", " + std::to_string(comp->min_dmg) + ", " + std::to_string(comp->max_dmg) + ")\n"
		+ "game.combat.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.combat.set_atk_type(" + tbl_name + ", " + std::to_string((int)comp->atk_type) + ")\n"
		+ "game.combat.set_projectile_blueprint(" + tbl_name + ", '" + comp->projectile_blueprint + "')\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<EventComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<InputComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<InputComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.input)\n"
		+ "game.input.set_handler(" + tbl_name + ", '" + comp->input_handler + "')\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<TimeComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<ManaComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<ManaComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.mana)\n"
		+ "game.mana.set_max(" + tbl_name + ", " + std::to_string(comp->max_mana) + ")\n"
		+ "game.mana.set(" + tbl_name + ", " + std::to_string(comp->curr_mana) + ")\n"
		+ "game.mana.set_regen(" + tbl_name + ", " + std::to_string(comp->mana_regen) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<SpellComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<SpellComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.spell)\n"
		+ "game.ent_spell.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		+ "game.ent_spell.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.ent_spell.set_curr_time(" + tbl_name + ", " + std::to_string(comp->cd_time) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<ProductionComponent>(tdt::uint id, const std::string& tbl_name)
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

	if(FactionHelper::get_faction(entities_, id) == FACTION::FRIENDLY)
	{
		comm += "game.player.add_max_units(" + std::to_string(comp->max_produced)
			  + ")\ngame.player.add_curr_units(" + std::to_string(comp->curr_produced) + ")\n";
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<ProductComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<ProductComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.product)\n"
		+ "game.production.set_producer(" + tbl_name + ", entity_" + std::to_string(comp->producer) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template <>
inline void GameSerializer::save_component<PathfindingComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<TaskComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TaskComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.task)\n"
		+ "game.task.set_source(" + tbl_name + ", entity_" + std::to_string(comp->source) + ")\n"
		+ "game.task.set_target(" + tbl_name + ", entity_" + std::to_string(comp->target) + ")\n"
		+ "game.task.set_type(" + tbl_name + ", " + std::to_string((int)comp->task_type) + ")\n"
	};
	task_pairs_.emplace_back(comp->source, id);

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<TaskHandlerComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.task_handler)\n"
		+ "game.task.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
	};

	for(tdt::uint i = 0; i < comp->possible_tasks.size(); ++i)
	{
		if(comp->possible_tasks.test(i))
			comm.append("game.task.add_possible(" + tbl_name + ", " + std::to_string(i) + ")\n");
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<StructureComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<StructureComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.structure)\n"
		+ "game.grid.set_walk_through(" + tbl_name + ", " + (comp->walk_through ? "true" : "false") + ")\n"
		+ tbl_name + "_residences = { "
	};
	std::string set_residents{}; // This will ensure that the grid nodes will have their residents also set.

	for(tdt::uint i = 0; i < comp->residences.size(); ++i)
	{
		comm.append("entity_" + std::to_string(comp->residences[i]) +
					(i == comp->residences.size() - 1 ? "" : ", "));
		set_residents.append("game.grid.set_resident(entity_" + std::to_string(comp->residences[i])
							 + ", " + tbl_name + ")\n"
							 + "game.grid.set_free(entity_" + std::to_string(comp->residences[i]) + ", false)\n");

		// Portal nodes have residents, so this avoids check on free nodes.
		auto node = entities_.get_component<GridNodeComponent>(comp->residences[i]);
		if(node && node->neighbours[DIRECTION::PORTAL] != Component::NO_ENTITY)
		{
			set_residents.append("game.grid.set_portal_neighbour(entity_" + std::to_string(comp->residences[i])
								 + ", entity_" + std::to_string(node->neighbours[DIRECTION::PORTAL]) + ")\n");
		}
	}
	comm.append(" }\ngame.grid.add_residences(" + tbl_name + ", '" + tbl_name + "_residences')\n");
	comm.append(tbl_name + "_residences = nil");

	save_components_.emplace_back(std::move(comm));
	save_components_.emplace_back(std::move(set_residents));
}

template<>
inline void GameSerializer::save_component<HomingComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<EventHandlerComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<EventHandlerComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.event_handler)\n"
		+ "game.event_handling.set_handler(" + tbl_name + ", '" + comp->handler + "')\n"
	};

	for(tdt::uint i = 0; i < comp->possible_events.size(); ++i)
	{
		if(comp->possible_events.test(i))
			comm.append("game.event_handling.add_possible(" + tbl_name + ", " + std::to_string(i) + ")\n");
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<DestructorComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<DestructorComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.destructor)\n"
		+ "game.destructor.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<GoldComponent>(tdt::uint id, const std::string& tbl_name)
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
inline void GameSerializer::save_component<FactionComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<FactionComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.faction)\n" 
		+ "game.ai.set_faction(" + tbl_name + ", " + std::to_string((int)comp->faction) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<PriceComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<PriceComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.price)\n"
		+ "game.price.set(" + tbl_name + ", " + std::to_string(comp->price) + ")\n"
	};

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<AlignComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<AlignComponent>(id);
	std::string comm{
		"game.entity.add_component(" + tbl_name + ", game.enum.component.align)\n"
	};

	for(tdt::uint i = 0; i < AlignComponent::state_count; ++i)
	{
		comm.append(
			  "game.align.set_material(" + tbl_name + ", " + std::to_string(i) + ", '" + comp->states[i].material + "')\n"
			+ "game.align.set_mesh(" + tbl_name + ", " + std::to_string(i) + ", '" + comp->states[i].mesh + "')\n"
			+ "game.align.set_offset(" + tbl_name + ", " + std::to_string(i) + ", " + std::to_string(comp->states[i].position_offset.x) + ", "
			+ std::to_string(comp->states[i].position_offset.y) + ", " + std::to_string(comp->states[i].position_offset.z) + ")\n"
			+ "game.align.set_scale(" + tbl_name + ", " + std::to_string(i) + ", " + std::to_string(comp->states[i].scale.x) + ", "
			+ std::to_string(comp->states[i].scale.y) + ", " + std::to_string(comp->states[i].scale.z) + ")\n"
		);
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<MineComponent>(tdt::uint id, const std::string& tbl_name)
{
	save_components_.emplace_back("game.entity.add_component(" + tbl_name + ", game.enum.component.mine)\n");
}

template<>
inline void GameSerializer::save_component<ManaCrystalComponent>(tdt::uint id, const std::string& tbl_name)
{
	// TODO: Skip comm string where possible when saving previous components!
	auto comp = entities_.get_component<ManaCrystalComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.mana_crystal)\n"
		+ "game.mana_crystal.set_capacity(" + tbl_name + ", " + std::to_string(comp->cap_increase)
		+ ")\n game.mana_crystal.set_regen(" + tbl_name + ", " + std::to_string(comp->regen_increase) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<OnHitComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<OnHitComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.on_hit)\n"
		+ "game.on_hit.set_blueprint(" + tbl_name + ", '" + comp->blueprint
		+ "')\ngame.on_hit.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<ConstructorComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<ConstructorComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.constructor)\n"
		+ "game.constructor.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
	);
}

template<>
inline void GameSerializer::save_component<TriggerComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<TriggerComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.trigger)\n"
		+ "game.trigger.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		+ "game.trigger.set_linked_entity(" + tbl_name + ", entity_" + std::to_string(comp->linked_entity)
		+ ")\ngame.trigger.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.trigger.set_radius(" + tbl_name + ", " + std::to_string(comp->radius) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<UpgradeComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<UpgradeComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.upgrade)\n"
		+ "game.upgrade.set_blueprint(" + tbl_name + ", '" + comp->blueprint + "')\n"
		+ "game.upgrade.set_experience(" + tbl_name + ", " + std::to_string(comp->experience)
		+ ")\ngame.upgrade.set_exp_needed(" + tbl_name + ", " + std::to_string(comp->exp_needed)
		+ ")\ngame.upgrade.set_level(" + tbl_name + ", " + std::to_string(comp->level)
		+ ")\ngame.upgrade.set_level_cap(" + tbl_name + ", " + std::to_string(comp->level_cap) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<NotificationComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<NotificationComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.notification)\n"
		+ "game.notification.set_cooldown(" + tbl_name + ", " + std::to_string(comp->cooldown) + ")\n"
		+ "game.notification.advance_curr_time(" + tbl_name + ", " + std::to_string(comp->curr_time) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<ExplosionComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<ExplosionComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.explosion)\n"
		+ "game.explosion.set_delta(" + tbl_name + ", " + std::to_string(comp->delta) + ")\n"
		+ "game.explosion.set_max_radius(" + tbl_name + ", " + std::to_string(comp->max_radius) + ")\n"
		+ "game.explosion.increase_curr_radius(" + tbl_name + ", " + std::to_string(comp->curr_radius) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<LimitedLifeSpanComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<LimitedLifeSpanComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.lls)\n"
		+ "game.lls.set_max_time(" + tbl_name + ", " + std::to_string(comp->max_time) + ")\n"
		+ "game.lls.advance_curr_time(" + tbl_name + ", " + std::to_string(comp->curr_time) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<NameComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<NameComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.name)\n"
		+ "game.name.set(" + tbl_name + ", '" + comp->name + "')\n"
	);
}

template<>
inline void GameSerializer::save_component<ExperienceValueComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<ExperienceValueComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.exp_val)\n"
		+ "game.exp_val.set(" + tbl_name + ", " + std::to_string(comp->value) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<LightComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<LightComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.light)\n"
		+ "game.light.set_visible(" + tbl_name + ", " + (comp->light->isVisible() ? "true" : "false") + ")\n"
		+ "game.light.init(" + tbl_name + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<CommandComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<CommandComponent>(id);
	std::string comm{
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.command)\n"
	};

	for(tdt::uint i = 0; i < comp->possible_commands.size(); ++i)
	{
		comm.append("game.command.set(" + tbl_name + ", " + std::to_string(i) + ", "
					+ (comp->possible_commands.test(i) ? "true" : "false") + ")\n");
	}

	save_components_.emplace_back(std::move(comm));
}

template<>
inline void GameSerializer::save_component<CounterComponent>(tdt::uint id, const std::string& tbl_name)
{
	auto comp = entities_.get_component<CounterComponent>(id);
	save_components_.emplace_back(
		  "game.entity.add_component(" + tbl_name + ", game.enum.component.counter)\n"
		+ "game.counter.set(" + tbl_name + ", " + std::to_string(comp->curr_value) + ")\n"
		+ "game.counter.set_max(" + tbl_name + ", " + std::to_string(comp->max_value) + ")\n"
	);
}

template<>
inline void GameSerializer::save_component<PortalComponent>(tdt::uint id, const std::string& tbl_name)
{
	save_components_.emplace_back("game.entity.add_component(" + tbl_name + ", game.enum.component.portal)\n");
}
