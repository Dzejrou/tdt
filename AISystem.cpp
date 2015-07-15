#include "AISystem.hpp"

AISystem::AISystem(EntitySystem& ent)
	: entities_{ent}
{ /* DUMMY BODY */ }

void AISystem::update(Ogre::Real)
{
	std::string blueprint{};
	for(const auto& entity : entities_.get_component_list())
	{
		if(is_valid(entity.first))
		{
			blueprint = entities_.get_component<AIComponent>(entity.first).blueprint;
			lpp::Script::get_singleton().call<void, std::size_t>(blueprint + ".update", entity.first);
		}
	}
}

bool AISystem::is_valid(std::size_t id) const
{
	return entities_.has_component<AIComponent>(id);
}
