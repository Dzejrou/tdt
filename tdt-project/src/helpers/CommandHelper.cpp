#include <systems/EntitySystem.hpp>
#include <tools/SelectionBox.hpp>
#include <tools/Grid.hpp>
#include <gui/GUI.hpp>
#include <helpers/Helpers.hpp>
#include <systems/CombatSystem.hpp>
#include <Components.hpp>
#include <Cache.hpp>
#include "CommandHelper.hpp"

static tdt::cache::CommandCache cache{Component::NO_ENTITY, nullptr};

void CommandHelper::set_command(EntitySystem& ents, tdt::uint id, COMMAND_TYPE command, bool val)
{
	CommandComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CommandComponent);
	if(comp)
		comp->possible_commands.set((tdt::uint)command, val);
}

bool CommandHelper::test_command(EntitySystem& ents, tdt::uint id, COMMAND_TYPE command)
{
	CommandComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CommandComponent);
	if(comp)
		return comp->possible_commands.test((tdt::uint)command);
	else
		return false;
}

void CommandHelper::command_to_mine(EntitySystem& ents, SelectionBox& selection)
{
	if(selection.get_selected_entities().empty())
		return;
	std::size_t target = selection.get_selected_entities()[0];
	if(FactionHelper::get_faction(ents, target) == FACTION::FRIENDLY)
		return; // No friendly fire.

	// Find miner with the smallest task queue (if more are found, take the closest).
	std::size_t id = Component::NO_ENTITY;
	std::size_t queue_size = std::numeric_limits<std::size_t>::max();
	Ogre::Real distance = std::numeric_limits<Ogre::Real>::max();
	for(const auto& ent : ents.get_component_container<CommandComponent>())
	{
		if(!ent.second.possible_commands.test((std::size_t)COMMAND_TYPE::MINE))
			continue;

		auto comp = ents.get_component<TaskHandlerComponent>(ent.first);
		if(comp)
		{
			Ogre::Real new_distance = PhysicsHelper::get_distance(ents, ent.first, target);
			if(comp->task_queue.size() < queue_size || (comp->task_queue.size() == queue_size &&
			   new_distance < distance))
			{
				queue_size = comp->task_queue.size();
				id = ent.first;
				distance = new_distance;
			}
		}
	}
	if(id != Component::NO_ENTITY)
	{
		for(const auto& selected : selection.get_selected_entities())
		{
			if(ents.has_component<MineComponent>(selected))
			{
				auto task = TaskHelper::create_task(ents, selected, TASK_TYPE::GO_KILL);
				TaskHelper::add_task(ents, id, task);
			}
		}
	}
	else
		GUI::instance().get_log().print("\\[ERROR\\] You don't have any free miners.");
}

void CommandHelper::command_to_attack(EntitySystem& ents, SelectionBox& selection)
{
	if(selection.get_selected_entities().empty())
		return;
	std::size_t target = selection.get_selected_entities()[0];
	if(FactionHelper::get_faction(ents, target) == FACTION::FRIENDLY)
		return; // No friendly fire.

	// Find soldier with the smallest task queue (if more are found, take the closest).
	std::size_t id = Component::NO_ENTITY;
	std::size_t queue_size = std::numeric_limits<std::size_t>::max();
	Ogre::Real distance = std::numeric_limits<Ogre::Real>::max();
	for(const auto& ent : ents.get_component_container<CommandComponent>())
	{
		if(!ent.second.possible_commands.test((std::size_t)COMMAND_TYPE::ATTACK))
			continue;

		auto comp = ents.get_component<TaskHandlerComponent>(ent.first);
		if(comp)
		{
			Ogre::Real new_distance = PhysicsHelper::get_distance(ents, ent.first, target);
			if(comp->task_queue.size() < queue_size || (comp->task_queue.size() == queue_size &&
			   new_distance < distance))
			{
				queue_size = comp->task_queue.size();
				id = ent.first;
				distance = new_distance;
			}
		}
	}
	if(id != Component::NO_ENTITY)
	{
		auto task = TaskHelper::create_task(ents, target, TASK_TYPE::GO_KILL);
		TaskHelper::add_task(ents, id, task);
	}
	else
		GUI::instance().get_log().print("\\[ERROR\\] You don't have free any combat units.");
}

void CommandHelper::command_to_reposition(EntitySystem& ents, Ogre::Real x, Ogre::Real y)
{
	auto target = Grid::instance().get_node_from_position(x, y);

	// Find soldier with the smallest task queue (if more are found, take the closest).
	std::size_t id = Component::NO_ENTITY;
	std::size_t queue_size = std::numeric_limits<std::size_t>::max();
	Ogre::Real distance = std::numeric_limits<Ogre::Real>::max();
	for(const auto& ent : ents.get_component_container<CommandComponent>())
	{
		if(!ent.second.possible_commands.test((std::size_t)COMMAND_TYPE::REPOSITION))
			continue;
		if(!PathfindingHelper::get_path(ents, ent.first).empty())
			continue;

		auto comp = ents.get_component<TaskHandlerComponent>(ent.first);
		if(comp)
		{
			Ogre::Real new_distance = PhysicsHelper::get_distance(ents, ent.first, target);
			if((comp->task_queue.size() < queue_size || (comp->task_queue.size() == queue_size &&
			   new_distance < distance)) && new_distance > 100.f) // Don't come if already close.
			{
				queue_size = comp->task_queue.size();
				id = ent.first;
				distance = new_distance;
			}
		}
	}
	if(id != Component::NO_ENTITY)
	{
		auto task = TaskHelper::create_task(ents, target, TASK_TYPE::GO_TO);
		TaskHelper::add_task(ents, id, task);
	}
	else
		GUI::instance().get_log().print("\\[ERROR\\] You don't have any free units.");
}

void CommandHelper::command_to_return_gold(EntitySystem& ents, CombatSystem& combat)
{
	for(const auto& ent : ents.get_component_container<CommandComponent>())
	{
		if(!ent.second.possible_commands.test((std::size_t)COMMAND_TYPE::RETURN_GOLD))
			continue;

		if(GoldHelper::get_curr_gold(ents, ent.first) > 0)
		{
			auto target = combat.get_closest_gold_vault(ent.first, false, true);
			if(target != Component::NO_ENTITY)
			{
				auto task = TaskHelper::create_task(ents, target, TASK_TYPE::GO_DEPOSIT_GOLD);
				TaskHelper::add_task(ents, ent.first, task);
			}
			else
			{
				GUI::instance().get_log().print("\\[ERROR\\] You have no free gold vaults.");
				return;
			}
		}
	}
}

void CommandHelper::command_to_fall_back(EntitySystem& ents)
{
	for(const auto& ent : ents.get_component_container<CommandComponent>())
	{
		if(!ent.second.possible_commands.test((std::size_t)COMMAND_TYPE::FALL_BACK))
			continue;
		if(!PathfindingHelper::get_path(ents, ent.first).empty() ||
		   !TaskHandlerHelper::get_task_queue(ents, ent.first).empty())
			continue;

		auto producer = ProductHelper::get_producer(ents, ent.first);
		if(producer != Component::NO_ENTITY)
		{
			auto task = TaskHelper::create_task(ents, producer, TASK_TYPE::GO_TO);
			TaskHelper::add_task(ents, ent.first, task);
		}
	}
}
