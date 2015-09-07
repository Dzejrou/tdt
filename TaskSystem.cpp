#include "TaskSystem.hpp"

TaskSystem::TaskSystem(EntitySystem& ents, GridSystem& grid, CombatSystem& comb)
	: entities_{ents}, grid_{grid}, combat_{comb},
	  task_names_{{TASK_TYPE::NONE, "NONE"}, {TASK_TYPE::GO_TO, "GO_TO"},
	  {TASK_TYPE::GO_NEAR, "GO_NEAR"}, {TASK_TYPE::GO_KILL, "GO_KILL"},
	  {TASK_TYPE::KILL, "KILL"}, {TASK_TYPE::GET_IN_RANGE, "GET_IN_RANGE"}}
{ /* DUMMY BODY */ }

void TaskSystem::update(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<TaskHandlerComponent>())
	{
		if(ent.second.busy && current_task_completed_(ent.first, ent.second))
		{
			DestructorHelper::destroy(entities_, ent.second.curr_task);
			ent.second.curr_task = Component::NO_ENTITY;
			ent.second.busy = false;
		}
		else if(!ent.second.busy)
		{
			// Get next valid task if necessary.
			while(!ent.second.task_queue.empty() &&
				  (ent.second.curr_task == Component::NO_ENTITY ||
				  !entities_.has_component<TaskComponent>(ent.second.curr_task)))
			{
				next_task_(ent.second);
			}

			// Found atleast one valid task.
			if(ent.second.curr_task != Component::NO_ENTITY)
				ent.second.busy = handle_task_(ent.first, ent.second);
		}
	}
}

const std::string & TaskSystem::get_task_name(TASK_TYPE type) const
{
	auto name = task_names_.find(type);
	if(name != task_names_.end())
		return name->second;
	else
		return task_names_.at(TASK_TYPE::NONE);
}

void TaskSystem::next_task_(TaskHandlerComponent& comp)
{
	if(!comp.task_queue.empty())
	{
		comp.curr_task = comp.task_queue.front();
		comp.task_queue.pop_front();
	}
}

bool TaskSystem::handle_task_(std::size_t id, TaskHandlerComponent& handler)
{
	return lpp::Script::get_singleton().call<bool>(
		        handler.blueprint + ".handle_task", id, handler.curr_task
	);
}

bool TaskSystem::current_task_completed_(std::size_t id, TaskHandlerComponent& handler)
{
	return lpp::Script::get_singleton().call<bool>(
				handler.blueprint + ".task_complete", id, handler.curr_task	
	);
}
