#pragma once

#include <deque>
#include <cstdlib>
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "Helpers.hpp"

namespace util
{
namespace pathfinding
{
	template<typename PATH_TYPE = util::DEFAULT_PATH_TYPE, typename HEURISTIC = util::DEFAULT_HEURISTIC>
	struct A_STAR
	{
		static std::deque<std::size_t> get_path(EntitySystem& ents, std::size_t id, std::size_t start, std::size_t end)
		{
			auto comp = ents.get_component<PathfindingComponent>(id);
			if(!comp)
				return std::deque<std::size_t>{};

			auto& script = lpp::Script::get_singleton();

			std::map<std::size_t, std::size_t> path_edges{};
			std::set<std::size_t> open{start};
			std::map<std::size_t, std::size_t> score;
			std::map<std::size_t, std::size_t> estimate;

			for(auto& node : ents.get_component_container<GridNodeComponent>())
			{ // Starting score and estimate is "infinity".
				score.emplace(node.first, std::numeric_limits<std::size_t>::max());
				estimate.emplace(node.first, std::numeric_limits<std::size_t>::max());
			}
			score[start] = 0;
			estimate[start] = HEURISTIC::get_cost(ents, start, end);

			std::size_t current{};
			bool found_path{false};
			while(!open.empty())
			{
				// Find the best candidate in the open set. Since open is not empty the
				// returned iterator will be dereferencable.
				current = *std::min_element(open.begin(), open.end(),
											[&estimate](const std::size_t& lhs, const std::size_t& rhs) -> bool
											{ return estimate[lhs] < estimate[rhs]; });
				if(current == end)
				{
					found_path = true;
					if(PATH_TYPE::return_path())
						break;
				}
				open.erase(current);
			
				for(const auto& neighbour : GridNodeHelper::get_neighbours(ents, current))
				{
					// TODO: If this continues when the neighbour is closed, shortest path won't be found!
					//       Shortest path vs. performance ?
					bool cannot_pass = !GridNodeHelper::is_free(ents, neighbour) && !PathfindingHelper::can_break(id, *comp, neighbour);
					if(!Grid::instance().in_board(neighbour) || cannot_pass)
						continue;
					auto s = script.call<std::size_t, std::size_t, std::size_t>(comp->blueprint + ".get_cost", id, current);
					auto new_score = score[current] + s;

					// Either unvisited or we found a better path to it.
					if(new_score < score[neighbour])
					{
						path_edges[neighbour] = current;
						score[neighbour] = new_score;
						estimate[neighbour] = new_score + HEURISTIC::get_cost(ents, neighbour, end);
					
						open.insert(neighbour);
					}
				
				}
			}

			if(found_path)
			{ // Reconstruct the path.
				std::deque<std::size_t> path;
				current = end;
				path.push_back(current);

				// Using assignment to an auxiliary iterator in the condition saves another lookup.
				auto it = path_edges.begin();
				while((it = path_edges.find(current)) != path_edges.end())
				{
					current = it->second;
					path.push_front(current);
				}
				return path;
			}
			else
				return std::deque<std::size_t>{};
		}
	};
}

namespace path_type
{
	struct BEST_PATH
	{
		static bool return_path()
		{
			return false;
		}
	};

	struct FIRST_PATH
	{
		static bool return_path()
		{
			return true;
		}

	};

	template<int UPPER>
	struct RANDOM_PATH
	{
		static bool return_path()
		{
			return util::get_random(0, UPPER) == 0;
		}
	};
}

namespace heuristic
{
	struct MANHATTAN_DISTANCE
	{
		static std::size_t get_cost(EntitySystem& ents, std::size_t id1, std::size_t id2)
		{
			return GridNodeHelper::get_manhattan_distance(ents, id1, id2);
		}
	};
}

/**
 * Default types for the different pathfinding functors.
 */
using DEFAULT_PATH_TYPE = path_type::BEST_PATH;
using DEFAULT_HEURISTIC = heuristic::MANHATTAN_DISTANCE;
using DEFAULT_PATHFINDING_ALGORITHM = pathfinding::A_STAR<DEFAULT_PATH_TYPE, DEFAULT_HEURISTIC>;
}