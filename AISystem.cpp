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

bool AISystem::is_friendly(std::size_t id1, std::size_t id2) const
{
	if(is_valid(id1) && is_valid(id2))
		return entities_.get_component<AIComponent>(id1).faction ==
		       entities_.get_component<AIComponent>(id2).faction;
	else
		return true; // Entities withou AIComponent are buildings, walls etc.
}

bool AISystem::is_neutral(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).faction == Faction::NEUTRAL;
	else
		return true;
}

bool AISystem::is_inanimate(std::size_t id) const
{
	return !is_valid(id);
}

const std::string & AISystem::get_blueprint(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).blueprint;
	else
		return std::string{"ErrorBlueprint"};
}

EntityState AISystem::get_state(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).state;
	else
		return EntityState::NONE;
}

Faction AISystem::get_faction(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).faction;
	else
		return Faction::NEUTRAL;
}
