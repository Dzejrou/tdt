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
			auto comp = entities_.get_component<TaskComponent>(ent.second.curr_task);
			if(ent.second.curr_task != Component::NO_ENTITY && comp)
			{
				ent.second.busy = true;
				handle_task_(ent.first, *comp, ent.second);
			}
		}
	}
}

void TaskSystem::add_task(std::size_t ent_id, std::size_t task_id)
{
	auto comp1 = entities_.get_component<TaskHandlerComponent>(ent_id);
	auto comp2 = entities_.get_component<TaskComponent>(task_id);
	if(comp1 && comp2)
	{
		// Make sure the entity can handle this task.
		if(!comp1->possible_tasks.test((int)comp2->task_type))
			return;

		comp2->source = ent_id;
		comp1->task_queue.push_back(task_id);
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
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	if(comp)
		return comp->task_queue;
	else
		return std::deque<std::size_t>{};
}

void TaskSystem::clear_task_queue(std::size_t id)
{
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	if(comp)
	{
		auto& task_queue = comp->task_queue;
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

void TaskSystem::set_task_source(std::size_t id, std::size_t source)
{
	auto comp = entities_.get_component<TaskComponent>(id);
	if(comp)
		comp->source = source;
}

void TaskSystem::set_task_target(std::size_t id, std::size_t target)
{
	auto comp = entities_.get_component<TaskComponent>(id);
	if(comp)
		comp->target = target;
}

void TaskSystem::set_task_type(std::size_t id, TASK_TYPE type)
{
	auto comp = entities_.get_component<TaskComponent>(id);
	if(comp)
		comp->task_type = type;
}

void TaskSystem::add_possible_task(std::size_t id, TASK_TYPE type)
{
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	if(comp)
		comp->possible_tasks.set((int)type);
}

void TaskSystem::delete_possible_task(std::size_t id, TASK_TYPE type)
{
	auto comp = entities_.get_component<TaskHandlerComponent>(id);
	if(comp)
		comp->possible_tasks.set((int)type, false);
}

bool TaskSystem::task_possible(std::size_t ent_id, std::size_t task_id) const
{
	auto comp1 = entities_.get_component<TaskHandlerComponent>(ent_id);
	auto comp2 = entities_.get_component<TaskComponent>(task_id);
	if(comp1 && comp2)
	{
		return comp1->possible_tasks.test((int)comp2->task_type);
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

void TaskSystem::handle_task_(std::size_t id, TaskComponent& task, TaskHandlerComponent& handler)
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
		case TASK_TYPE::GET_IN_RANGE:
		{
			auto source_comp = entities_.get_component<PhysicsComponent>(task.source);
			auto target_comp = entities_.get_component<PhysicsComponent>(task.target);
			if(source_comp && target_comp)
			{
				grid_.perform_a_star(id, grid_.get_node_from_position(source_comp->position.x, source_comp->position.z),
										 grid_.get_node_from_position(target_comp->position.x, target_comp->position.z));
			}

			if(task.task_type == TASK_TYPE::GO_NEAR)
			{
				auto path_comp = entities_.get_component<PathfindingComponent>(task.source);
				if(path_comp && path_comp->path_queue.size() >= 2)
				{
					path_comp->path_queue.pop_back(); // Doesn't reach the final grid node.
					path_comp->target_id = path_comp->path_queue.back();
					task.target = path_comp->path_queue.back();
				}
			}
			break;
		}
		case TASK_TYPE::GO_KILL:
		{
			auto task_go_near = create_task(task.target, TASK_TYPE::GET_IN_RANGE);
			auto task_kill = create_task(task.target, TASK_TYPE::KILL);
			add_task(id, task_go_near);
			add_task(id, task_kill);

			entities_.destroy_entity(handler.curr_task);
			handler.curr_task = Component::NO_ENTITY;
			break;
		}
		case TASK_TYPE::KILL:
		{
			auto combat_comp = entities_.get_component<CombatComponent>(id);
			if(combat_comp)
				combat_comp->curr_target = task.target;
			else
			{
				entities_.destroy_entity(handler.curr_task);
				handler.curr_task = Component::NO_ENTITY;
			}
			break;
		}
	}
}

bool TaskSystem::current_task_completed_(std::size_t id, TaskHandlerComponent& handler)
{
	auto comp = entities_.get_component<TaskComponent>(handler.curr_task);
	if(comp)
	{
		if(!entities_.exists(comp->target) || !entities_.exists(comp->source))
			return true;
		switch(comp->task_type)
		{
			case TASK_TYPE::GO_TO:
			case TASK_TYPE::GO_NEAR:
			{
				auto source = entities_.get_component<PhysicsComponent>(comp->source);
				auto target = entities_.get_component<PhysicsComponent>(comp->target);
				auto path = entities_.get_component<PathfindingComponent>(comp->source);

				if(source && target)
					return source->position.x == target->position.x && source->position.z == target->position.z
						   || (path && path->path_queue.empty());
				else
					return true; // Runtime deletion, should not occur in release code.
			}
			case TASK_TYPE::GO_KILL:
				return handler.curr_task == Component::NO_ENTITY; // Removed when handled.
			case TASK_TYPE::KILL:
			{
				auto combat_comp = entities_.get_component<CombatComponent>(id);
				if(combat_comp)
					return combat_comp->curr_target == Component::NO_ENTITY;
				else
					return false;
			}
			case TASK_TYPE::GET_IN_RANGE:
			{
				auto combat_comp = entities_.get_component<CombatComponent>(id);
				if(combat_comp)
				{
					auto phys_comp = entities_.get_component<PhysicsComponent>(id);
					auto target_phys_comp = entities_.get_component<PhysicsComponent>(comp->target);
					if(phys_comp && target_phys_comp)
					{
						auto range = combat_comp->range * combat_comp->range; // Squared distance is faster (avoid square root).
						auto path_comp = entities_.get_component<PathfindingComponent>(id);
						if(path_comp && path_comp->path_queue.empty())
							return true;
						else if(phys_comp->position.squaredDistance(target_phys_comp->position) < range)
						{
							if(combat_.in_sight(id, comp->target))
							{
								if(path_comp) // Stop pursuing.
								{
									path_comp->target_id = Component::NO_ENTITY;
									path_comp->path_queue.clear();
								}
								return true;;
							}
						}
					}
				}
				return false;
			}
			default:
				return true; // Undefined task, kill it asap.
		}
	}
	else // Allows for task cancel.
		return true;
}
