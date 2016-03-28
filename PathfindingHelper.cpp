#include "PathfindingHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

const std::string& PathfindingHelper::get_pathpfinding_blueprint(EntitySystem& ents, tdt::uint id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<PathfindingComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void PathfindingHelper::set_pathfinding_blueprint(EntitySystem& ents, tdt::uint id, const std::string& blueprint)
{
	auto comp = ents.get_component<PathfindingComponent>(id);
	if(comp)
		comp->blueprint = blueprint;
}

std::deque<tdt::uint>& PathfindingHelper::get_path(EntitySystem& ents, tdt::uint id)
{
	static std::deque<tdt::uint> NO_PATH{};

	auto comp = ents.get_component<PathfindingComponent>(id);
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
