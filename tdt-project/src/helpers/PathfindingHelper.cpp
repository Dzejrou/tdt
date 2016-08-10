#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "PathfindingHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::PathfindingCache cache{Component::NO_ENTITY, nullptr};
#endif

const std::string& PathfindingHelper::get_pathpfinding_blueprint(EntitySystem& ents, tdt::uint id)
{
	PathfindingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, PathfindingComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void PathfindingHelper::set_pathfinding_blueprint(EntitySystem& ents, tdt::uint id, const std::string& blueprint)
{
	PathfindingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, PathfindingComponent);
	if(comp)
		comp->blueprint = blueprint;
}

std::deque<tdt::uint>& PathfindingHelper::get_path(EntitySystem& ents, tdt::uint id)
{
	static std::deque<tdt::uint> NO_PATH{};

	PathfindingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, PathfindingComponent);
	if(comp)
		return comp->path_queue;
	else
		return NO_PATH;
}

bool PathfindingHelper::can_break(tdt::uint id1, const PathfindingComponent& comp, tdt::uint id2)
{
	return lpp::Script::instance().call<bool, tdt::uint, tdt::uint>(comp.blueprint + ".can_break", id1, id2);
}

tdt::real PathfindingHelper::get_cost(tdt::uint id1, const PathfindingComponent& comp, tdt::uint id2, DIRECTION::VAL dir)
{
	auto cost = lpp::Script::instance().call<tdt::real, tdt::uint, tdt::uint>(comp.blueprint + ".get_cost", id1, id2);
	if(cost <= 0.f)
		cost = 1.f;
	if(dir == DIRECTION::UP_LEFT || dir == DIRECTION::UP_RIGHT || dir == DIRECTION::DOWN_LEFT || dir == DIRECTION::DOWN_RIGHT)
		cost *= 1.41421356237f; // Diagonal multiplier (hardcoded to avoid sqrt computation).
	return cost;
}
