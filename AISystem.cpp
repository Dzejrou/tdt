#include "AISystem.hpp"

AISystem::AISystem(EntitySystem& ent)
	: entities_{ent}, update_timer_{0.f}, update_period_{.5f}
{ /* DUMMY BODY */ }

void AISystem::update(Ogre::Real delta)
{
	update_timer_ += delta;
	if(update_timer_ > update_period_)
		update_timer_ = 0;
	else
		return;

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

void AISystem::set_update_period(Ogre::Real val)
{
	return update_period_;
}

Ogre::Real AISystem::get_update_period() const
{
	return update_period_;
}

void AISystem::force_update()
{
	update_timer_ = update_period_;
}