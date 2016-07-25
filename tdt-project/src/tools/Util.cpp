#include <systems/EntitySystem.hpp>
#include "Util.hpp"
#include "Grid.hpp"

util::IS_ENEMY::IS_ENEMY(EntitySystem& ents, tdt::uint id)
	: enemy_faction_{FACTION::NEUTRAL}, entities_{ents}
{
	auto faction = FactionHelper::get_faction(ents, id);
	if(faction == FACTION::FRIENDLY)
		enemy_faction_ = FACTION::ENEMY;
	else
		enemy_faction_ = FACTION::FRIENDLY;
}

bool util::IS_ENEMY::operator()(tdt::uint id)
{
	return enemy_faction_ != FACTION::NEUTRAL &&
		   enemy_faction_ == FactionHelper::get_faction(entities_, id);
}

util::IS_FRIENDLY::IS_FRIENDLY(EntitySystem& ents, tdt::uint id)
	: faction_{FactionHelper::get_faction(ents, id)}, entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_FRIENDLY::operator()(tdt::uint id)
{
	return FactionHelper::get_faction(entities_, id) == faction_;
}

util::IS_FRIENDLY_OR_NEUTRAL::IS_FRIENDLY_OR_NEUTRAL(EntitySystem& ents, tdt::uint id)
	: faction_{FactionHelper::get_faction(ents, id)}, entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_FRIENDLY_OR_NEUTRAL::operator()(tdt::uint id)
{
	auto faction = FactionHelper::get_faction(entities_, id);
	return faction == faction_ || faction == FACTION::NEUTRAL;
}

void util::EntityDestroyer::destroy(EntitySystem& ents, tdt::uint id)
{
	ents.destroy_entity(id);
}

util::HAS_GOLD::HAS_GOLD(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

bool util::HAS_GOLD::operator()(tdt::uint id)
{
	return entities_.has_component<GoldComponent>(id);
}

int util::get_enum_direction(EntitySystem& ents, tdt::uint id, tdt::uint target)
{
	auto pos1 = PhysicsHelper::get_position(ents, id);
	auto pos2 = PhysicsHelper::get_position(ents, target);
	auto dist = Grid::instance().get_distance();

	auto diff_x = pos1.x > pos2.x ? pos1.x - pos2.x : pos2.x - pos1.x;
	bool same_axis_x = diff_x < dist;
	
	auto diff_z = pos1.z > pos2.z ? pos1.z - pos2.z : pos2.z - pos1.z;
	bool same_axis_z = diff_z < dist;

	bool left = pos1.x > pos2.x;
	bool right = pos1.x <= pos2.x;
	bool up = pos1.z > pos2.z;
	bool down = pos1.z <= pos2.z;

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
}

tdt::uint util::get_random(tdt::uint min, tdt::uint max)
{
	static std::uniform_int_distribution<tdt::uint> dist{0, std::numeric_limits<tdt::uint>::max()};
	static std::mt19937 mt{std::random_device{}()};

	auto res = dist(mt) % max;
	return (res >= min) ? res : res + min;
}

tdt::uint util::abs(int val)
{
	if(val < 0)
		return (tdt::uint) (-1 * val);
	else
		return val;
}

util::IS_GOLD_VAULT::IS_GOLD_VAULT(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

bool util::IS_GOLD_VAULT::operator()(tdt::uint id)
{
	return FactionHelper::get_faction(entities_, id) == FACTION::FRIENDLY
	       && entities_.has_component<StructureComponent>(id)
		   && entities_.has_component<GoldComponent>(id);

}
