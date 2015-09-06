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
			auto comp = entities_.get_component<TaskComponent>(ent.second.curr_task);
			if(ent.second.curr_task != Component::NO_ENTITY && comp)
				ent.second.busy = handle_task_(ent.first, *comp, ent.second);
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

bool TaskSystem::handle_task_(std::size_t id, TaskComponent& task, TaskHandlerComponent& handler)
{
	/**
	 * Note: Not performing checks on components because the entity will have to have
	 *       those components to accept the task and these components should not be deleted
	 *       before this call.
	 */
	bool res{false};
	switch(task.task_type)
	{
		case TASK_TYPE::GO_TO:
		case TASK_TYPE::GO_NEAR:
		case TASK_TYPE::GET_IN_RANGE:
		{
			res = grid_.perform_a_star(id, task.target);

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
			res = true;
			break;
		}
		case TASK_TYPE::GO_KILL:
		{
			auto task_go_near = create_task(task.target, TASK_TYPE::GET_IN_RANGE);
			auto task_kill = create_task(task.target, TASK_TYPE::KILL);
			add_task(id, task_go_near);
			add_task(id, task_kill);

			DestructorHelper::destroy(entities_, handler.curr_task);
			handler.curr_task = Component::NO_ENTITY;
			res = true;
			break;
		}
		case TASK_TYPE::KILL:
		{
			auto combat_comp = entities_.get_component<CombatComponent>(id);
			if(combat_comp)
			{
				res = true;
				combat_comp->curr_target = task.target;
			}
			else
			{
				DestructorHelper::destroy(entities_, handler.curr_task);
				handler.curr_task = Component::NO_ENTITY;
			}
			break;
		}
		case TASK_TYPE::GO_PICK_UP_GOLD:
		{
			auto task_go_near = create_task(task.target, TASK_TYPE::GO_NEAR);
			auto task_pick_up = create_task(task.target, TASK_TYPE::PICK_UP_GOLD);
			add_task(id, task_go_near);
			add_task(id, task_pick_up);
		
			DestructorHelper::destroy(entities_, handler.curr_task);
			handler.curr_task = Component::NO_ENTITY;
			res = true;
			break;
		}
		case TASK_TYPE::PICK_UP_GOLD:
		{
			GoldHelper::transfer_all_gold(entities_, task.target, id);
			if(GoldHelper::get_curr_gold(entities_, task.target) > 0)
			{ // Calls other minions to pick it up.
				auto evt = entities_.create_entity("");
				auto& comp = entities_.add_component<EventComponent>(evt);
				comp.target = task.target;
				comp.event_type = EVENT_TYPE::GOLD_DROPPED;
				comp.radius = std::numeric_limits<Ogre::Real>::max(); // This time signal everyone.
			}
			handler.curr_task = Component::NO_ENTITY;
			break;
			// TODO: If gold capped, create new task to return the gold to the vault!
			// Note: Or handle this in the update method? Might be easier and more flexible.
		}
	}
	return res;
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
			case TASK_TYPE::GO_PICK_UP_GOLD:
				return TaskHandlerHelper::get_task_queue(entities_, id).empty();
			case TASK_TYPE::PICK_UP_GOLD:
				return handler.curr_task == Component::NO_ENTITY;
			default:
				return true; // Undefined task, kill it asap.
		}
	}
	else // Allows for task cancel.
		return true;
}
