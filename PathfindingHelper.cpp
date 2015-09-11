#include "PathfindingHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

const std::string& PathfindingHelper::get_pathpfinding_blueprint(EntitySystem& ents, std::size_t id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<PathfindingComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void PathfindingHelper::set_pathfinding_blueprint(EntitySystem& ents, std::size_t id, const std::string& blueprint)
{
	auto comp = ents.get_component<PathfindingComponent>(id);
	if(comp)
		comp->blueprint = blueprint;
}

std::deque<std::size_t>& PathfindingHelper::get_path(EntitySystem& ents, std::size_t id)
{
	static std::deque<std::size_t> NO_PATH{};

	auto comp = ents.get_component<PathfindingComponent>(id);
	if(comp)
		return comp->path_queue;
	else
		return NO_PATH;
}

bool PathfindingHelper::can_break(std::size_t id, PathfindingComponent& comp, std::size_t structure)
{
	return lpp::Script::get_singleton().call<bool, std::size_t, std::size_t>(comp.blueprint + ".can_break", id, structure);
}
