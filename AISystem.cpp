#include "AISystem.hpp"

AISystem::AISystem(EntitySystem& ent)
	: entities_{ent}
{ /* DUMMY BODY */ }

void AISystem::update(Ogre::Real)
{
	std::string blueprint{};

	auto& ents = entities_.get_component_container<AIComponent>();
	for(auto& ent : ents)
	{
		if(is_valid(ent.first))
		{
			blueprint = entities_.get_component<AIComponent>(ent.first).blueprint;
			lpp::Script::get_singleton().call<void, std::size_t>(blueprint + ".update", ent.first);
		}
	}
	entities_.cleanup();
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

std::string AISystem::get_blueprint(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).blueprint;
	else
		return "ErrorBlueprint";
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

std::size_t AISystem::enemy_in_radius(std::size_t id, Ogre::Real radius) const
{
	if(is_valid(id) && entities_.has_component<PhysicsComponent>(id))
	{
		radius *= radius; // Using squared distance.
		Ogre::Real minimum_distance{std::numeric_limits<Ogre::Real>::max()};
		std::size_t minimum_id{id};
		std::size_t original_id{id};
		Ogre::Real current_distance{};

		auto& phys_comp = entities_.get_component<PhysicsComponent>(id);

		for(const auto& ent : entities_.get_component_container<PhysicsComponent>())
		{
			if(ent.first == original_id)
				continue;
			current_distance = phys_comp.position.squaredDistance(ent.second.position);
			if(current_distance < radius && current_distance < minimum_distance)
			{
				minimum_distance = current_distance;
				id = ent.first;
			}
		}
	}

	return id; // Return the calling ID if no close entity found.
}

std::size_t AISystem::closest_enemy(std::size_t id) const
{
	return enemy_in_radius(id, std::numeric_limits<Ogre::Real>::max());
}

Ogre::Vector3 AISystem::dir_to_closest_enemy(std::size_t id, Ogre::Real radius) const
{
	if(is_valid(id))
	{
		std::size_t id_enemy = enemy_in_radius(id, radius);
		if(id == id_enemy)
			return Ogre::Vector3{0, 0, 0};
		auto pos1 = entities_.get_component<PhysicsComponent>(id).position;
		auto pos2 = entities_.get_component<PhysicsComponent>(id_enemy).position;
		auto pos = pos2 - pos1;
		pos.normalise();
		return pos;
	}
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 AISystem::dir_to_enemy(std::size_t id1, std::size_t id2) const
{
	if(is_valid(id1) && is_valid(id2))
	{
		auto pos1 = entities_.get_component<PhysicsComponent>(id1).position;
		auto pos2 = entities_.get_component<PhysicsComponent>(id2).position;
		auto pos = pos2 - pos1;
		pos.normalise();
		return pos;
	}
	else
		return Ogre::Vector3{0, 0, 0};
}
