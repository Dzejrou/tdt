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
