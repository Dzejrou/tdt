#include "TaskHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void TaskHelper::set_task_source(EntitySystem& ents, std::size_t id, std::size_t source)
{
	auto comp = ents.get_component<TaskComponent>(id);
	if(comp)
		comp->source = source;
}

std::size_t TaskHelper::get_task_source(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TaskComponent>(id);
	if(comp)
		return comp->source;
	else
		return Component::NO_ENTITY;
}

void TaskHelper::set_task_target(EntitySystem& ents, std::size_t id, std::size_t target)
{
	auto comp = ents.get_component<TaskComponent>(id);
	if(comp)
		comp->target = target;
}

std::size_t TaskHelper::get_task_target(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TaskComponent>(id);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void TaskHelper::set_task_type(EntitySystem& ents, std::size_t id, TASK_TYPE type)
{
	auto comp = ents.get_component<TaskComponent>(id);
	if(comp)
		comp->task_type = type;
}

TASK_TYPE TaskHelper::get_task_type(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TaskComponent>(id);
	if(comp)
		return comp->task_type;
	else
		return TASK_TYPE::NONE;
}

void TaskHelper::add_task(EntitySystem& ents, std::size_t ent_id, std::size_t task_id)
{
	auto comp1 = ents.get_component<TaskHandlerComponent>(ent_id);
	auto comp2 = ents.get_component<TaskComponent>(task_id);
	if(comp1 && comp2)
	{
		// Make sure the entity can handle this task.
		if(!comp1->possible_tasks.test((int)comp2->task_type))
			return;

		comp2->source = ent_id;
		comp1->task_queue.push_back(task_id);
	}
}

std::size_t TaskHelper::create_task(EntitySystem& ents, std::size_t target, TASK_TYPE type)
{
	std::size_t id = ents.create_entity();
	auto& comp = ents.add_component<TaskComponent>(id);
	comp.target = target;
	comp.task_type = type;

	return id;
}

void TaskHelper::cancel_task(EntitySystem& ents, std::size_t task_id)
{
	if(ents.has_component<TaskComponent>(task_id))
		DestructorHelper::destroy(ents, task_id);
}
