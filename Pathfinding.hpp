#pragma once

#include "EntitySystem.hpp"
#include "Helpers.hpp"
#include "PathfindingAlgorithms.hpp"

namespace util
{
	template<typename ALGORITHM = util::DEFAULT_PATHFINDING_ALGORITHM>
	bool pathfind(EntitySystem& ents, std::size_t id, std::size_t target, bool add_path = true)
	{
		auto path_comp = ents.get_component<PathfindingComponent>(id);
		if(!path_comp || !ents.has_component<PhysicsComponent>(id)
		   || !ents.has_component<PhysicsComponent>(target))
			return false;

		auto pos_start = PhysicsHelper::get_position(ents, id);
		//auto pos_end = PhysicsHelper::get_position(ents, target);
		std::size_t start{Grid::instance().get_node_from_position(pos_start.x, pos_start.z)},
					end{GridNodeHelper::get_node_in_dir(ents, target, util::get_enum_direction(ents, target, id))};

		auto path = ALGORITHM::get_path(ents, id, start, end);
		bool destruction{false};
		if(!path.empty())
		{ // Finds the first blocked node and orders the entity to destroy it's resident.
			for(auto node : path)
			{
				if(!GridNodeHelper::is_free(ents, node)) // can_break can be assumed as the node wouldn't be added without it.
				{
					auto resident = GridNodeHelper::get_resident(ents, node);
					if(resident != target)
					{
						auto comp = ents.get_component<TaskHandlerComponent>(id);
						if(comp)
						{
							auto task_get_in_range = TaskHelper::create_task(ents, resident, TASK_TYPE::GET_IN_RANGE);
							auto task_kill = TaskHelper::create_task(ents, resident, TASK_TYPE::KILL);
							TaskHelper::add_task(ents, id, comp->curr_task, true);
							TaskHelper::add_task(ents, id, task_kill, true);
							TaskHelper::add_task(ents, id, task_get_in_range, true);
							comp->curr_task = Component::NO_ENTITY;
							destruction = true;
							break;
						}
						else
							return false;
					}
				}
			}
		}

		if(!path.empty() && !destruction && add_path)
		{
			path_comp->path_queue.swap(path);
			path_comp->last_id = start;
			path_comp->target_id = end;

			// In case the entity moves backwards.
			GraphicsHelper::look_at(ents, id, path_comp->path_queue.front());
			return true;
		}

		if(!add_path)
			return !path.empty();
		else
			return false;
	}
}