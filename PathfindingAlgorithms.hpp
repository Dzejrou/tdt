#pragma once

#include <deque>
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "Helpers.hpp"
#include "Enums.hpp"
#include "Grid.hpp"
#include "Typedefs.hpp"

/**
 * The utim namespace contains various tools and utilities used by the game's engine.
 * This part contains the pathfinding algorithms, heuristics and path types.
 * Also contains the typedefs for DETAULT_PATH_TYPE, DEFAULT_PATHFINDING_ALGORITHM and
 * DEFAULT_HEURISTIC.
 */
namespace util
{

/**
 * Forward declarations.
 */
namespace heuristic { struct HEURISTIC; }

/**
 * Contains the pathfinding algorithms used by the util::pathfind function.
 */
namespace pathfinding
{
	/**
	 * Brief: Simple A* pathfinding implementations with path type specified as a template
	 *        parameter.
	 * Param: Entity system containing the pathfinding entity and the grid.
	 * Param: ID of the pathfinding entity.
	 * Param: ID of the starting node.
	 * Param: ID of the ending node.
	 * Param: Heuristic to be used.
	 * Param: If true, the entity will be allowed to destroy blocks along it's way.
	 */
	template<typename PATH_TYPE = util::DEFAULT_PATH_TYPE>
	struct A_STAR
	{
		static std::deque<tdt::uint> get_path(EntitySystem& ents, tdt::uint id, tdt::uint start, tdt::uint end, util::heuristic::HEURISTIC& heuristic,
												bool allow_destruction = true)
		{
			auto comp = ents.get_component<PathfindingComponent>(id);
			if(!comp)
				return std::deque<tdt::uint>{};

			auto& script = lpp::Script::instance();

			std::map<tdt::uint, tdt::uint> path_edges{};
			std::set<tdt::uint> open{start};
			std::map<tdt::uint, tdt::real> score;
			std::map<tdt::uint, tdt::real> estimate;

			for(auto& node : ents.get_component_container<GridNodeComponent>())
			{ // Starting score and estimate is "infinity".
				score.emplace(node.first, std::numeric_limits<tdt::real>::max());
				estimate.emplace(node.first, std::numeric_limits<tdt::real>::max());
			}
			score[start] = 0;
			estimate[start] = heuristic.get_cost(start, end);

			tdt::uint current{};
			bool found_path{false};
			while(!open.empty())
			{
				// Find the best candidate in the open set. Since open is not empty the
				// returned iterator will be dereferencable.
				current = *std::min_element(open.begin(), open.end(),
											[&estimate](const tdt::uint& lhs, const tdt::uint& rhs) -> bool
											{ return estimate[lhs] < estimate[rhs]; });
				if(current == end && !found_path)
				{
					found_path = true;
					if(PATH_TYPE::return_path())
						break;
				}
				open.erase(current);
			
				auto& neighbours = GridNodeHelper::get_neighbours(ents, current);
				for(tdt::uint i = 0; i < neighbours.size(); ++i)
				{
					auto& neighbour = neighbours[i];

					/**
					 * This will allow the concept of portals to be integrated into the
					 * pathfinding process (because paths will ignore distance between portals).
					 */
					tdt::real s{};
					tdt::real h{};
					bool portal{false};
					if(i == DIRECTION::PORTAL)
					{
						auto resident = GridNodeHelper::get_resident(ents, neighbour);
						if(resident != Component::NO_ENTITY && TriggerHelper::can_be_triggered_by(ents, resident, id))
						{
							s = 0.f;

							auto other_end = TriggerHelper::get_linked_entity(ents, resident);
							auto pos = PhysicsHelper::get_2d_position(ents, other_end);
							auto other_node = Grid::instance().get_node_from_position(pos.x, pos.y);
							h = heuristic.get_cost(other_node, end);
							portal = true;
						}
						else
							continue;
					}

					if(!portal)
					{
						bool cannot_pass = !GridNodeHelper::is_free(ents, neighbour) &&
										  (!allow_destruction || !PathfindingHelper::can_break(id, *comp, neighbour))
										   && !StructureHelper::is_walk_through(ents, GridNodeHelper::get_resident(ents, neighbour));
						if(!Grid::instance().in_board(neighbour) || cannot_pass)
							continue;

						s = PathfindingHelper::get_cost(id, *comp, current, (DIRECTION::VAL)i);
						h = heuristic.get_cost(neighbour, end);
					}
					auto new_score = score[current] + s;

					// Either unvisited or we found a better path to it.
					if(new_score < score[neighbour])
					{
						path_edges[neighbour] = current;
						score[neighbour] = new_score;
						estimate[neighbour] = new_score + h;

						if(found_path && PATH_TYPE::return_path())
							break;
					
						open.insert(neighbour);
					}
				}
			}

			if(found_path)
			{ // Reconstruct the path.
				std::deque<tdt::uint> path;
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
				return std::deque<tdt::uint>{};
		}
	};
}

/**
 * Contains different path types, which are used to check if a path should be returned
 * once found or when an augmenting edge is found to the path.
 */
namespace path_type
{
	/**
	 * Finds the best path by refusing any paths found.
	 */
	struct BEST_PATH
	{
		static bool return_path()
		{
			return false;
		}
	};

	/**
	 * Finds the first path by accepting the first path found.
	 */
	struct FIRST_PATH
	{
		static bool return_path()
		{
			return true;
		}

	};

	/**
	 * Finds a random path by returning true only when a random
	 * number in the range (0, UPPER) is equal to 0. (UPPER is specialized
	 * as a template parameter.)
	 */
	template<int UPPER>
	struct RANDOM_PATH
	{
		static bool return_path()
		{
			return util::get_random(0, UPPER) == 0;
		}
	};
}

/**
 * Contains the heuristics used by the pathfinding algorithms.
 */
namespace heuristic
{
	/**
	 * Abstract parent of all heuristics. Inheritance hierarchy used instead
	 * of static functions (like in the case of PATH_TYPEs) to allow for a
	 * heuristic to have a state.
	 */
	struct HEURISTIC
	{
		HEURISTIC(EntitySystem& ents)
			: entities_{ents}
		{ /* DUMMY BODY */ }

		virtual tdt::real get_cost(tdt::uint id1, tdt::uint id2) = 0;

		protected:
			EntitySystem& entities_;
	};

	/**
	 * Returns the manhattan distance between two nodes.
	 * (Well, actually, it's an octal distance :)
	 */
	struct MANHATTAN_DISTANCE : public HEURISTIC
	{
		MANHATTAN_DISTANCE(EntitySystem& ents)
			: HEURISTIC{ents}
		{ /* DUMMY BODY */ }

		tdt::real get_cost(tdt::uint id1, tdt::uint id2) override
		{
			return (tdt::real)GridNodeHelper::get_manhattan_distance(entities_, id1, id2);
		}
	};

	/**
	 * Represents no heuristic by returning 0 all the time.
	 */
	struct NO_HEURISTIC : public HEURISTIC
	{
		NO_HEURISTIC(EntitySystem& ents)
			: HEURISTIC{ents}
		{ /* DUMMY BODY */ }

		tdt::real get_cost(tdt::uint id1, tdt::uint id2) override
		{
			return 0.f;
		}
	};

	/**
	 * Used by entities that want to run away from an enemy.
	 */
	struct RUN_AWAY_HEURISTIC : public HEURISTIC
	{
		RUN_AWAY_HEURISTIC(EntitySystem& ents, tdt::uint from)
			: HEURISTIC{ents}, from_{from}
		{ /* DUMMY BODY */ }

		tdt::real get_cost(tdt::uint id1, tdt::uint id2) override
		{
			return (tdt::real)GridNodeHelper::get_manhattan_distance(entities_, id1, id2)
				- PhysicsHelper::get_distance(entities_, from_, id2);
		}

		private:
			tdt::uint from_;
	};
}

/**
 * Default types for the different pathfinding functors.
 */
using DEFAULT_PATH_TYPE = path_type::BEST_PATH;
using DEFAULT_HEURISTIC = heuristic::MANHATTAN_DISTANCE;
using DEFAULT_PATHFINDING_ALGORITHM = pathfinding::A_STAR<DEFAULT_PATH_TYPE>;
}