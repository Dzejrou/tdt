#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "TaskHelper.hpp"

static tdt::cache::TaskCache cache{Component::NO_ENTITY, nullptr};

void TaskHelper::set_task_source(EntitySystem& ents, tdt::uint id, tdt::uint source)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		comp->source = source;
}

tdt::uint TaskHelper::get_task_source(EntitySystem& ents, tdt::uint id)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		return comp->source;
	else
		return Component::NO_ENTITY;
}

void TaskHelper::set_task_target(EntitySystem& ents, tdt::uint id, tdt::uint target)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		comp->target = target;
}

tdt::uint TaskHelper::get_task_target(EntitySystem& ents, tdt::uint id)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void TaskHelper::set_task_type(EntitySystem& ents, tdt::uint id, TASK_TYPE type)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		comp->task_type = type;
}

TASK_TYPE TaskHelper::get_task_type(EntitySystem& ents, tdt::uint id)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		return comp->task_type;
	else
		return TASK_TYPE::NONE;
}

void TaskHelper::add_task(EntitySystem& ents, tdt::uint ent_id, tdt::uint task_id, bool priority)
{
	auto comp1 = ents.get_component<TaskHandlerComponent>(ent_id);
	TaskComponent* comp2{nullptr};
	GET_COMPONENT(task_id, ents, comp2, TaskComponent);
	if(comp1 && comp2)
	{
		// Make sure the entity can handle this task.
		if(!comp1->possible_tasks.test((int)comp2->task_type))
			return;

		comp2->source = ent_id;

		if(priority)
		{
			if(comp1->curr_task != Component::NO_ENTITY)
			{
				comp1->task_queue.push_front(comp1->curr_task);
				comp1->curr_task = Component::NO_ENTITY;
			}
			comp1->task_queue.push_front(task_id);
			comp1->busy = false;
		}
		else
			comp1->task_queue.push_back(task_id);
	}
}

tdt::uint TaskHelper::create_task(EntitySystem& ents, tdt::uint target, TASK_TYPE type)
{
	tdt::uint id = ents.create_entity();
	ents.add_component<TaskComponent>(id);

	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
	{
		comp->target = target;
		comp->task_type = type;
	}

	return id;
}

void TaskHelper::cancel_task(EntitySystem& ents, tdt::uint id)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
	{
		auto handler = ents.get_component<TaskHandlerComponent>(comp->source);
		if(handler)
		{
			for(auto& task : handler->task_queue)
			{
				if(task == id)
					task = Component::NO_ENTITY;
			}
			if(handler->curr_task == id)
				handler->curr_task = Component::NO_ENTITY;
		}
		DestructorHelper::destroy(ents, id);
	}
}

void TaskHelper::set_complete(EntitySystem& ents, tdt::uint id)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		comp->complete = true;
}

bool TaskHelper::is_complete(EntitySystem& ents, tdt::uint id)
{
	TaskComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskComponent);
	if(comp)
		return comp->complete;
	else
		return false;
}
