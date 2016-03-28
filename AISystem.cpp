#include "AISystem.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"
#include "Components.hpp"

AISystem::AISystem(EntitySystem& ent)
	: entities_{ent}, update_timer_{REAL_ZERO}, update_period_{.5f}
{ /* DUMMY BODY */ }

void AISystem::update(tdt::real delta)
{
	update_timer_ += delta;
	if(update_timer_ > update_period_)
		update_timer_ = REAL_ZERO;
	else
		return;

	for(auto& ent : entities_.get_component_container<AIComponent>())
	{
		auto task_comp = entities_.get_component<TaskHandlerComponent>(ent.first);
		if(task_comp && (task_comp->busy || !task_comp->task_queue.empty()
						 || task_comp->curr_task != Component::NO_ENTITY))
		{
			continue;
		}

		const std::string& blueprint  = ent.second.blueprint;
		lpp::Script::get_singleton().call<void, tdt::uint>(blueprint + ".update", ent.first);
	}
}

void AISystem::set_update_period(tdt::real val)
{
	update_period_ = val;
}

tdt::real AISystem::get_update_period() const
{
	return update_period_;
}

void AISystem::force_update()
{
	update_timer_ = update_period_;
}