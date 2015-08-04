#include "TaskSystem.hpp"

TaskSystem::TaskSystem(EntitySystem& ents, GridSystem& grid)
	: entities_{ents}, grid_{grid},
	  task_names_{{TASK_TYPE::NONE, "NONE"}, {TASK_TYPE::GO_TO, "GO_TO"}}
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

		// Make sure the entity can handle this task.
		if(!comp.possible_tasks.test((int)task.task_type))
			return;

		task.source = ent_id;
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

std::deque<std::size_t> TaskSystem::get_task_queue(std::size_t id)
{
	if(entities_.has_component<TaskHandlerComponent>(id))
		return entities_.get_component<TaskHandlerComponent>(id).task_queue;
	else
		return std::deque<std::size_t>{};
}

void TaskSystem::clear_task_queue(std::size_t id)
{
	if(entities_.has_component<TaskHandlerComponent>(id))
	{
		auto& task_queue = entities_.get_component<TaskHandlerComponent>(id).task_queue;
		for(auto& task : task_queue)
		{
			if(entities_.has_component<TaskComponent>(task))
				entities_.destroy_entity(task);
		}
		task_queue.clear();
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

bool TaskSystem::task_possible(std::size_t ent_id, std::size_t task_id) const
{
	if(entities_.has_component<TaskHandlerComponent>(ent_id) &&
	   entities_.has_component<TaskComponent>(task_id))
	{
		auto& handler = entities_.get_component<TaskHandlerComponent>(ent_id);
		auto& task = entities_.get_component<TaskComponent>(task_id);
		return handler.possible_tasks.test((int)task.task_type);
	}
	else
		return false;
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
		case TASK_TYPE::GO_TO:
		case TASK_TYPE::GO_NEAR:
		{
			auto source_pos = entities_.get_component<PhysicsComponent>(task.source).position;
			auto target_pos = entities_.get_component<PhysicsComponent>(task.target).position;
			grid_.perform_a_star(id, grid_.get_node_from_position(source_pos.x, source_pos.z),
								     grid_.get_node_from_position(target_pos.x, target_pos.z));

			if(task.task_type == TASK_TYPE::GO_NEAR)
			{
				auto& path_comp = entities_.get_component<PathfindingComponent>(task.source);
				path_comp.path_queue.pop_back(); // Doesn't reach the final grid node.
				path_comp.target_id = path_comp.path_queue.back();
				task.target = path_comp.path_queue.back();
			}

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
			case TASK_TYPE::GO_TO:
			case TASK_TYPE::GO_NEAR:
				return entities_.get_component<PhysicsComponent>(task.source).position ==
					   entities_.get_component<PhysicsComponent>(task.target).position;
			default:
				return true; // Undefined task, kill it asap.
		}
	}
	else // Allows for task cancel.
		return true;
}
