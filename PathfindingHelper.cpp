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