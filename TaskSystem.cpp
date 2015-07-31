#include "TaskSystem.hpp"

TaskSystem::TaskSystem(EntitySystem& ents, GridSystem& grid)
	: entities_{ents}, grid_{grid}
{ /* DUMMY BODY */ }

void TaskSystem::update(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<TaskHandlerComponent>())
	{
		if(ent.second.busy && current_task_completed_(ent.second))
		{ // TODO: Delete the task when finnished.
			entities_.destroy_entity(ent.second.curr_task);
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
			if(ent.second.curr_task != Component::NO_ENTITY &&
			   entities_.has_component<TaskComponent>(ent.second.curr_task))
			{
				ent.second.busy = true;
				handle_task_(ent.first, entities_.get_component<TaskComponent>(ent.second.curr_task));
			}
		}
	}
}

void TaskSystem::add_task(std::size_t ent_id, std::size_t task_id)
{
	if(entities_.has_component<TaskHandlerComponent>(ent_id) &&
	   entities_.has_component<TaskComponent>(task_id))
	{
		auto& comp = entities_.get_component<TaskHandlerComponent>(ent_id);
		auto& task = entities_.get_component<TaskComponent>(task_id);
		task.source = ent_id;

		// Make sure the entity can handle this task.
		if(!comp.possible_tasks.test((int)task.task_type))
			return;

		comp.task_queue.push_back(task_id);
	}
}

void TaskSystem::cancel_task(std::size_t task_id)
{
	if(entities_.has_component<TaskComponent>(task_id))
		entities_.destroy_entity(task_id);
}

std::size_t TaskSystem::create_task(std::size_t target, TASK_TYPE type)
{
	std::size_t id = entities_.create_entity();
	auto& comp = entities_.add_component<TaskComponent>(id);
	comp.target = target;
	comp.task_type = type;

	return id;
}

void TaskSystem::next_task_(TaskHandlerComponent& comp)
{
	if(!comp.task_queue.empty())
	{
		comp.curr_task = comp.task_queue.front();
		comp.task_queue.pop_front();
	}
}

void TaskSystem::handle_task_(std::size_t id, TaskComponent& task)
{
	/**
	 * Note: Not performing checks on components because the entity will have to have
	 *       those components to accept the task and these components should not be deleted
	 *       before this call.
	 */
	switch(task.task_type)
	{
		case TASK_TYPE::GOTO:
		{
			Ogre::Vector3 source_pos = entities_.get_component<PhysicsComponent>(task.source).position;
			Ogre::Vector3 target_pos = entities_.get_component<PhysicsComponent>(task.target).position;
			grid_.perform_a_star(id, grid_.get_node_from_position(source_pos.x, source_pos.z),
								     grid_.get_node_from_position(target_pos.x, target_pos.z));
			break;
		}
	
	}
}

bool TaskSystem::current_task_completed_(TaskHandlerComponent& handler)
{
	if(entities_.has_component<TaskComponent>(handler.curr_task))
	{
		auto& task = entities_.get_component<TaskComponent>(handler.curr_task);
	
		switch(task.task_type)
		{
			case TASK_TYPE::GOTO:
				return entities_.get_component<PhysicsComponent>(task.source).position ==
					   entities_.get_component<PhysicsComponent>(task.target).position;
			default:
				return true; // Undefined task, kill it asap.
		}
	}
	else // Allows for task cancel.
		return true;
}
