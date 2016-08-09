#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "TaskHandlerHelper.hpp"

static tdt::cache::TaskHandlerCache cache{Component::NO_ENTITY, nullptr};

std::deque<tdt::uint>& TaskHandlerHelper::get_task_queue(EntitySystem& ents, tdt::uint id)
{
	static std::deque<tdt::uint> NO_QUEUE{};

	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp)
		return comp->task_queue;
	else
		return NO_QUEUE;
}

bool TaskHandlerHelper::task_possible(EntitySystem& ents, tdt::uint id, tdt::uint task_id)
{
	TaskHandlerComponent* comp1{nullptr};
	GET_COMPONENT(id, ents, comp1, TaskHandlerComponent);
	auto comp2 = ents.get_component<TaskComponent>(task_id);
	if(comp1 && comp2)
		return comp1->possible_tasks.test((tdt::uint)comp2->task_type);
	else
		return false;
}

bool TaskHandlerHelper::task_possible(EntitySystem& ents, tdt::uint id, TASK_TYPE val)
{
	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp && (tdt::uint)val > 0 && (tdt::uint)val < (tdt::uint)TASK_TYPE::COUNT)
		return comp->possible_tasks.test((tdt::uint)val);
	else
		return false;
}

void TaskHandlerHelper::clear_task_queue(EntitySystem& ents, tdt::uint id)
{
	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp)
	{
		auto& task_queue = comp->task_queue;
		for(auto& task : task_queue)
		{
			if(ents.has_component<TaskComponent>(task))
				DestructorHelper::destroy(ents, task);
		}
		task_queue.clear();
	}
}

void TaskHandlerHelper::add_possible_task(EntitySystem& ents, tdt::uint id, TASK_TYPE type)
{
	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp)
		comp->possible_tasks.set((tdt::uint)type);
}

void TaskHandlerHelper::delete_possible_task(EntitySystem& ents, tdt::uint id, TASK_TYPE type)
{
	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp)
		comp->possible_tasks.set((tdt::uint)type, false);
}

void TaskHandlerHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string& TaskHandlerHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	TaskHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TaskHandlerComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}
