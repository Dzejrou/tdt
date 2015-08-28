#include "CombatSystem.hpp"

CombatSystem::CombatSystem(EntitySystem& ents, Ogre::SceneManager& scene, GridSystem& grid)
	: entities_{ents}, ray_query_{*scene.createRayQuery(Ogre::Ray{})},
	  grid_{grid}
{
	ray_query_.setSortByDistance(true);
	ray_query_.setQueryMask((int)ENTITY_TYPE::WALL || (int)ENTITY_TYPE::BUILDING);
}

void CombatSystem::update(Ogre::Real delta)
{
	// Autoattacks.
	for(auto& ent : entities_.get_component_container<CombatComponent>())
	{
		if(ent.second.curr_target != Component::NO_ENTITY)
		{
			if(!in_sight(ent.first, ent.second.curr_target))
			{
				ent.second.curr_target = Component::NO_ENTITY;
				continue;
			}

			if(ent.second.cd_time < ent.second.cooldown)
			{
				ent.second.cd_time += delta;
				continue;
			}
			else
				ent.second.cd_time = 0;

			auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
			auto target_phys_comp = entities_.get_component<PhysicsComponent>(ent.second.curr_target);

			auto range = ent.second.range * ent.second.range;
			if(phys_comp && target_phys_comp &&
			   phys_comp->position.squaredDistance(target_phys_comp->position) < range)
			{
				auto dmg = CombatHelper::get_dmg(entities_, ent.second.min_dmg, ent.second.max_dmg);
				GraphicsHelper::look_at(entities_, ent.first, ent.second.curr_target);
				switch(ent.second.atk_type)
				{
					case ATTACK_TYPE::MELEE:
						HealthHelper::sub_health(entities_, ent.second.curr_target, dmg);
						if(HealthHelper::get_health(entities_, ent.second.curr_target) <= 0)
						{
							ent.second.curr_target = Component::NO_ENTITY;
							ent.second.cd_time = ent.second.cooldown; // Allows to attack again instantly.
						}
						// TODO: Animation...
						break;
					case ATTACK_TYPE::RANGED:
						create_homing_projectile(ent.first, ent.second);
						break;
				}
			}
			else // Target killed or ran away.
				ent.second.curr_target = Component::NO_ENTITY;
		}
	}

	// TODO: Spells.


	// Homing projectiles.
	for(auto& ent : entities_.get_component_container<HomingComponent>())
	{
		if(ent.second.target == Component::NO_ENTITY)
			continue; // Manually spawned.
		else if(!entities_.exists(ent.second.target)) // Target killed.
			entities_.destroy_entity(ent.first);

		auto mov_comp = entities_.get_component<MovementComponent>(ent.first);
		auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
		auto graph_comp = entities_.get_component<GraphicsComponent>(ent.first);
		auto enemy_graph_comp = entities_.get_component<GraphicsComponent>(ent.second.target);

		if(mov_comp && phys_comp && graph_comp && enemy_graph_comp &&
		   graph_comp->node && graph_comp->entity && enemy_graph_comp->entity)
		{ // Moves the homing projectile in the target's direction and checks if hit occured.
			auto& pos = phys_comp->position;
			auto enemy_pos = enemy_graph_comp->node->getPosition();
			auto dir = enemy_pos - pos;
			dir.normalise();

			pos += dir;
			graph_comp->node->setPosition(pos);

			if(graph_comp->entity->getWorldBoundingBox(true).intersects(enemy_graph_comp->entity->getWorldBoundingBox(true)))
			{ // That's a hit.
				HealthHelper::sub_health(entities_, ent.second.target, ent.second.dmg);
				entities_.destroy_entity(ent.first);
			}
		}
	}
}

bool CombatSystem::in_sight(std::size_t ent_id, std::size_t target) const
{
	auto phys_comp = entities_.get_component<PhysicsComponent>(ent_id);
	auto target_graph_comp = entities_.get_component<GraphicsComponent>(target);

	if(phys_comp && target_graph_comp && target_graph_comp->node && target_graph_comp->entity)
	{
		auto target_position = target_graph_comp->node->getPosition();
		auto direction = target_position - phys_comp->position;
		direction.normalise();
		Ogre::Ray line_of_sight{phys_comp->position, direction};
		ray_query_.setRay(line_of_sight);
		auto res = ray_query_.execute();

		if(res.size() > 0)
		{
			auto dist_to_first_struct = res.front().distance * res.front().distance;
			return phys_comp->position.squaredDistance(target_position) < dist_to_first_struct;
		}
		else
			return true; // No structs found at all.
	}
	else
		return false;
}

std::size_t CombatSystem::get_closest_entity(std::size_t id, bool only_sight, bool friendly) const
{
	auto ai_comp = entities_.get_component<AIComponent>(id);
	auto phys_comp = entities_.get_component<PhysicsComponent>(id);

	std::size_t closest_id = Component::NO_ENTITY;
	Ogre::Real min_distance = std::numeric_limits<Ogre::Real>::max();
	if(ai_comp && phys_comp)
	{
		FACTION enemy_faction{};
		if(!friendly)
		{
			if(ai_comp->faction == FACTION::FRIENDLY)
				enemy_faction = FACTION::ENEMY;
			else if(ai_comp->faction == FACTION::ENEMY)
				enemy_faction = FACTION::FRIENDLY;
			else
				return closest_id; // Called by a neutral (those won't initiate combat).
		}
		else // For example might be used for healing etc.
			enemy_faction = ai_comp->faction;

		for(auto& ent : entities_.get_component_container<AIComponent>())
		{
			if(ent.first == id || ent.second.faction != enemy_faction)
				continue;

			auto enemy_phys_comp = entities_.get_component<PhysicsComponent>(id);
			auto dist = phys_comp->position.squaredDistance(enemy_phys_comp->position);
			if(enemy_phys_comp && dist < min_distance && (!only_sight || in_sight(id, ent.first)))
			{
				min_distance = dist;
				closest_id = ent.first;
			}
		}
	}
	return closest_id;
}

void CombatSystem::create_homing_projectile(std::size_t caster, CombatComponent& combat)
{
	std::size_t id = entities_.create_entity("basic_projectile");
	auto comp = entities_.get_component<HomingComponent>(id);
	if(comp)
	{
		comp->dmg = CombatHelper::get_dmg(entities_, combat.min_dmg, combat.max_dmg);
		comp->source = caster;
		comp->target = combat.curr_target;
	}

	auto caster_phys_comp = entities_.get_component<PhysicsComponent>(caster);
	auto phys_comp = entities_.get_component<PhysicsComponent>(id);
	if(caster_phys_comp && phys_comp)
	{
		phys_comp->position = caster_phys_comp->position;

		auto graph_comp = entities_.get_component<GraphicsComponent>(id);
		if(graph_comp && graph_comp->node)
			graph_comp->node->setPosition(phys_comp->position);
	}
}
