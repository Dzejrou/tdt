#include "Util.hpp"
#include "EntitySystem.hpp"
#include "Grid.hpp"

util::IS_ENEMY::IS_ENEMY(EntitySystem& ents, std::size_t id)
	: enemy_faction_{FACTION::NEUTRAL}, entities_{ents}
{
	auto faction = FactionHelper::get_faction(ents, id);
	if(faction == FACTION::FRIENDLY)
		enemy_faction_ = FACTION::ENEMY;
	else
		enemy_faction_ = FACTION::FRIENDLY;
}

bool util::IS_ENEMY::operator()(std::size_t id)
{
	return enemy_faction_ != FACTION::NEUTRAL &&
		   enemy_faction_ == FactionHelper::get_faction(entities_, id);
}

util::IS_FRIENDLY::IS_FRIENDLY(EntitySystem& ents, std::size_t id)
	: faction_{FactionHelper::get_faction(ents, id)}, entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_FRIENDLY::operator()(std::size_t id)
{
	return FactionHelper::get_faction(entities_, id) == faction_;
}

util::IS_FRIENDLY_OR_NEUTRAL::IS_FRIENDLY_OR_NEUTRAL(EntitySystem& ents, std::size_t id)
	: faction_{FactionHelper::get_faction(ents, id)}, entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_FRIENDLY_OR_NEUTRAL::operator()(std::size_t id)
{
	auto faction = FactionHelper::get_faction(entities_, id);
	return faction == faction_ || faction == FACTION::NEUTRAL;
}

void util::EntityDestroyer::destroy(EntitySystem& ents, std::size_t id)
{
	ents.destroy_entity(id);
}

util::HAS_GOLD::HAS_GOLD(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

bool util::HAS_GOLD::operator()(std::size_t id)
{
	return entities_.has_component<GoldComponent>(id);
}

int util::get_enum_direction(EntitySystem& ents, std::size_t id, std::size_t target)
{
	auto pos1 = PhysicsHelper::get_position(ents, id);
	auto pos2 = PhysicsHelper::get_position(ents, target);

	auto diff_x = pos1.x > pos2.x ? pos1.x - pos2.x : pos2.x - pos1.x;
	bool same_axis_x = diff_x < 20.f;
	
	auto diff_z = pos1.z > pos2.z ? pos1.z - pos2.z : pos2.z - pos1.z;
	bool same_axis_z = diff_z < 20.f;

	bool left = pos1.x > pos2.x;
	bool right = pos1.x <= pos2.x;
	bool up = pos1.z > pos2.z;
	bool down = pos1.z <= pos2.z;

	if(up)
		return DIRECTION::UP;
	else if(down)
		return DIRECTION::DOWN;
	else if(left)
		return DIRECTION::LEFT;
	else if(right)
		return DIRECTION::RIGHT;
	else
		return DIRECTION::NONE;
	/*
	if(same_axis_x && same_axis_z)
		return DIRECTION::NONE;
	else if(same_axis_x && up)
		return DIRECTION::UP;
	else if(same_axis_x && down)
		return DIRECTION::DOWN;
	else if(same_axis_z && left)
		return DIRECTION::LEFT;
	else if(same_axis_z && right)
		return DIRECTION::RIGHT;
	else if(up && left)
		return DIRECTION::UP_LEFT;
	else if(up && right)
		return DIRECTION::UP_RIGHT;
	else if(down && left)
		return DIRECTION::DOWN_LEFT;
	else if(down && right)
		return DIRECTION::DOWN_RIGHT;
	else
		return DIRECTION::NONE;
		*/
}

std::size_t util::get_random(std::size_t min, std::size_t max)
{
	return std::uniform_int_distribution<std::size_t>{0, std::numeric_limits<std::size_t>::max()}(
		   std::mt19937{std::random_device{}()}) % max + min;
}

std::size_t util::abs(int val)
{
	if(val < 0)
		return (std::size_t) -1 * val;
	else
		return val;
}
