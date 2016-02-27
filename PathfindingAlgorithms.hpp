#pragma once

#include <deque>
#include <cstdlib>
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "Helpers.hpp"
#include "Enums.hpp"

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
		static std::deque<std::size_t> get_path(EntitySystem& ents, std::size_t id, std::size_t start, std::size_t end, util::heuristic::HEURISTIC& heuristic,
												bool allow_destruction = true)
		{
			auto comp = ents.get_component<PathfindingComponent>(id);
			if(!comp)
				return std::deque<std::size_t>{};

			auto& script = lpp::Script::get_singleton();

			std::map<std::size_t, std::size_t> path_edges{};
			std::set<std::size_t> open{start};
			std::map<std::size_t, Ogre::Real> score;
			std::map<std::size_t, Ogre::Real> estimate;

			for(auto& node : ents.get_component_container<GridNodeComponent>())
			{ // Starting score and estimate is "infinity".
				score.emplace(node.first, std::numeric_limits<Ogre::Real>::max());
				estimate.emplace(node.first, std::numeric_limits<Ogre::Real>::max());
			}
			score[start] = 0;
			estimate[start] = heuristic.get_cost(start, end);

			std::size_t current{};
			bool found_path{false};
			while(!open.empty())
			{
				// Find the best candidate in the open set. Since open is not empty the
				// returned iterator will be dereferencable.
				current = *std::min_element(open.begin(), open.end(),
											[&estimate](const std::size_t& lhs, const std::size_t& rhs) -> bool
											{ return estimate[lhs] < estimate[rhs]; });
				if(current == end && !found_path)
				{
					found_path = true;
					if(PATH_TYPE::return_path())
						break;
				}
				open.erase(current);
			
				auto& neighbours = GridNodeHelper::get_neighbours(ents, current);
				for(std::size_t i = 0; i < neighbours.size(); ++i)
				{
					auto& neighbour = neighbours[i];

					bool cannot_pass = !GridNodeHelper::is_free(ents, neighbour) &&
						              (!allow_destruction || !PathfindingHelper::can_break(id, *comp, neighbour));
									   //&& !StructureHelper::is_walk_through(ents, GridNodeHelper::get_resident(ents, neighbour));
					if(!Grid::instance().in_board(neighbour) || cannot_pass)
						continue;
					auto s = PathfindingHelper::get_cost(id, *comp, current, (DIRECTION::VAL)i);
					auto new_score = score[current] + s;

					// Either unvisited or we found a better path to it.
					if(new_score < score[neighbour])
					{
						path_edges[neighbour] = current;
						score[neighbour] = new_score;
						estimate[neighbour] = new_score + heuristic.get_cost(neighbour, end);

						if(found_path && PATH_TYPE::return_path())
							break;
					
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

		virtual Ogre::Real get_cost(std::size_t id1, std::size_t id2) = 0;

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

		Ogre::Real get_cost(std::size_t id1, std::size_t id2) override
		{
			return (Ogre::Real)GridNodeHelper::get_manhattan_distance(entities_, id1, id2);
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

		Ogre::Real get_cost(std::size_t id1, std::size_t id2) override
		{
			return 0.f;
		}
	};

	/**
	 * Used by entities that want to run away from an enemy.
	 */
	struct RUN_AWAY_HEURISTIC : public HEURISTIC
	{
		RUN_AWAY_HEURISTIC(EntitySystem& ents, std::size_t from)
			: HEURISTIC{ents}, from_{from}
		{ /* DUMMY BODY */ }

		Ogre::Real get_cost(std::size_t id1, std::size_t id2) override
		{
			return (Ogre::Real)GridNodeHelper::get_manhattan_distance(entities_, id1, id2)
				- PhysicsHelper::get_distance(entities_, from_, id2);
		}

		private:
			std::size_t from_;
	};
}

/**
 * Default types for the different pathfinding functors.
 */
using DEFAULT_PATH_TYPE = path_type::FIRST_PATH;
using DEFAULT_HEURISTIC = heuristic::MANHATTAN_DISTANCE;
using DEFAULT_PATHFINDING_ALGORITHM = pathfinding::A_STAR<DEFAULT_PATH_TYPE>;
}