#include "TaskHandlerHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

std::deque<std::size_t>& TaskHandlerHelper::get_task_queue(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TaskHandlerComponent>(id);
	if(comp)
		return comp->task_queue;
	else
		return std::deque<std::size_t>{};
}

bool TaskHandlerHelper::task_possible(EntitySystem& ents, std::size_t ent_id, std::size_t task_id)
{
	auto comp1 = ents.get_component<TaskHandlerComponent>(ent_id);
	auto comp2 = ents.get_component<TaskComponent>(task_id);
	if(comp1 && comp2)
	{
		return comp1->possible_tasks.test((int)comp2->task_type);
	}
	else
		return false;
}

void TaskHandlerHelper::clear_task_queue(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TaskHandlerComponent>(id);
	if(comp)
	{
		auto& task_queue = comp->task_queue;
		for(auto& task : task_queue)
		{
			if(ents.has_component<TaskComponent>(task))
				ents.destroy_entity(task);
		}
		task_queue.clear();
	}
}

void TaskHandlerHelper::add_possible_task(EntitySystem& ents, std::size_t id, TASK_TYPE type)
{
	auto comp = ents.get_component<TaskHandlerComponent>(id);
	if(comp)
		comp->possible_tasks.set((int)type);
}

void TaskHandlerHelper::delete_possible_task(EntitySystem& ents, std::size_t id, TASK_TYPE type)
{
	auto comp = ents.get_component<TaskHandlerComponent>(id);
	if(comp)
		comp->possible_tasks.set((int)type, false);
}