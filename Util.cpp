#include "Util.hpp"
#include "EntitySystem.hpp"

util::IS_ENEMY::IS_ENEMY(EntitySystem& ents, std::size_t id)
	: enemy_faction_{}, entities_{ents}
{
	auto faction = AIHelper::get_faction(ents, id);
	if(faction == FACTION::FRIENDLY)
		enemy_faction_ = FACTION::ENEMY;
	else
		enemy_faction_ = FACTION::FRIENDLY;
}

bool util::IS_ENEMY::operator()(std::size_t id)
{
	return enemy_faction_ == AIHelper::get_faction(entities_, id);
}

util::IS_FRIENDLY::IS_FRIENDLY(EntitySystem& ents, std::size_t id)
	: faction_{AIHelper::get_faction(ents, id)}, entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_FRIENDLY::operator()(std::size_t id)
{
	return AIHelper::get_faction(entities_, id) == faction_;
}

util::IS_FRIENDLY_OR_NEUTRAL::IS_FRIENDLY_OR_NEUTRAL(EntitySystem& ents, std::size_t id)
	: faction_{AIHelper::get_faction(ents, id)}, entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_FRIENDLY_OR_NEUTRAL::operator()(std::size_t id)
{
	auto faction = AIHelper::get_faction(entities_, id);
	return faction == faction_ || faction == FACTION::NEUTRAL;
}
