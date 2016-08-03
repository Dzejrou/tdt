#pragma once

#include <systems/EntitySystem.hpp>
#include <helpers/Helpers.hpp>
#include <Typedefs.hpp>
#include "PathfindingAlgorithms.hpp"

/**
 * Util namespace contains general tools and utilities used by the game's
 * engine. This part of the namespace contains functions used for pathfinding.
 */
namespace util
{
	/**
	 * \brief Finds a path using a given algorithm (specified as a template parameter)
	 *        and heuristic and adds the path to the pathfinding entity if needed.
	 * \param Entity system containing the entity and the pathfinding grid.
	 * \param ID of the pathfinding entity.
	 * \param Target of the pathfinding.
	 * \param Heuristic used by the pathfinding algorithm.
	 * \param If true, the path will be added to the pathdinding entity's pathfinding
	 *        component.
	 * \param If true, the entity will be allowed to destroy blocks on it's way.
	 */
	template<typename ALGORITHM = util::DEFAULT_PATHFINDING_ALGORITHM>
	bool pathfind(EntitySystem& ents, tdt::uint id, tdt::uint target,
				  util::heuristic::HEURISTIC& heuristic, bool add_path = true, bool allow_destruction = true)
	{
		auto path_comp = ents.get_component<PathfindingComponent>(id);
		if(!path_comp || !ents.has_component<PhysicsComponent>(id)
		   || !ents.has_component<PhysicsComponent>(target))
			return false;

		auto pos_start = PhysicsHelper::get_position(ents, id);
		auto pos_end = PhysicsHelper::get_position(ents, target);
		tdt::uint start{Grid::instance().get_node_from_position(pos_start.x, pos_start.z)},
			        end{Grid::instance().get_node_from_position(pos_end.x, pos_end.z)};

		auto path = ALGORITHM::get_path(ents, id, start, end, heuristic, allow_destruction);
		bool destruction{false};
		if(allow_destruction && add_path && !path.empty())
		{ // Finds the first blocked node and orders the entity to destroy it's resident.
			for(auto node : path)
			{
				if(!GridNodeHelper::is_free(ents, node)) // can_break can be assumed as the node wouldn't be added without it.
				{
					auto resident = GridNodeHelper::get_resident(ents, node);
					if(StructureHelper::is_walk_through(ents, resident))
						continue;
					if(resident != target)
					{
						auto comp = ents.get_component<TaskHandlerComponent>(id);
						if(comp)
						{ // TODO: Just cut the path and add kill task?
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

			if(path_comp->path_queue.size() >= 3)
				path_comp->path_queue.pop_front(); // This will stop the entity from returning when halfway to the second node.

			// In case the entity moves backwards.
			GraphicsHelper::look_at(ents, id, path_comp->path_queue.front());
			AnimationHelper::play(ents, id, ANIMATION_TYPE::WALK, true);
			return true;
		}

		if(!add_path)
			return !path.empty();
		else
			return false;
	}
}