#include "AISystem.hpp"

AISystem::AISystem(EntitySystem& ent)
	: entities_{ent}
{ /* DUMMY BODY */ }

void AISystem::update(Ogre::Real)
{
	for(auto& ent : entities_.get_component_container<AIComponent>())
	{
		auto task_comp = entities_.get_component<TaskHandlerComponent>(ent.first);
		if(task_comp && (task_comp->busy || !task_comp->task_queue.empty()
						 || task_comp->curr_task != Component::NO_ENTITY))
			continue; // TODO: Callbacks on_hit etc.

		const std::string& blueprint  = ent.second.blueprint;
		lpp::Script::get_singleton().call<void, std::size_t>(blueprint + ".update", ent.first);
	}
}

bool AISystem::is_valid(std::size_t id) const
{
	return entities_.has_component<AIComponent>(id);
}

bool AISystem::is_friendly(std::size_t id1, std::size_t id2) const
{
	auto comp1 = entities_.get_component<AIComponent>(id1);
	auto comp2 = entities_.get_component<AIComponent>(id2);
	if(comp1 && comp2)
	{

		if(comp1->faction == FACTION::NEUTRAL || comp2->faction == FACTION::NEUTRAL)
			return true;
		else
			return comp1->faction == comp2->faction;
	}
	else
		return true; // Entities withou AIComponent are buildings, walls etc.
}

bool AISystem::is_neutral(std::size_t id) const
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		return comp->faction == FACTION::NEUTRAL;
	else
		return true;
}

bool AISystem::is_inanimate(std::size_t id) const
{
	return !is_valid(id);
}

std::string AISystem::get_blueprint(std::size_t id) const
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return "ERROR"; // Special blueprint defined in ogre_utils.lua
}

void AISystem::set_blueprint(std::size_t id, const std::string& blueprint)
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		comp->blueprint = blueprint;
}

ENTITY_STATE AISystem::get_state(std::size_t id) const
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		return comp->state;
	else
		return ENTITY_STATE::NONE;
}

void AISystem::set_state(std::size_t id, ENTITY_STATE state)
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		comp->state = state;
}

FACTION AISystem::get_faction(std::size_t id) const
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		return comp->faction;
	else
		return FACTION::NEUTRAL;
}

void AISystem::set_faction(std::size_t id, FACTION faction)
{
	auto comp = entities_.get_component<AIComponent>(id);
	if(comp)
		comp->faction = faction;
}
