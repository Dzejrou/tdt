#include "CombatSystem.hpp"
#include "PathfindingAlgorithms.hpp"
#include "Pathfinding.hpp"
#include "Effects.hpp"
#include "HealthHelper.hpp"
#include "CombatHelper.hpp"
#include "GridSystem.hpp"
#include "RayCaster.hpp"
#include "GraphicsHelper.hpp"

CombatSystem::CombatSystem(EntitySystem& ents, Ogre::SceneManager& scene, GridSystem& grid)
	: entities_{ents}, ray_query_{*scene.createRayQuery(Ogre::Ray{})},
	  grid_{grid}, ray_caster_{scene}, run_away_queue_{}
{
	ray_query_.setSortByDistance(true);
	ray_query_.setQueryMask((int)ENTITY_TYPE::WALL || (int)ENTITY_TYPE::BUILDING);
}

void CombatSystem::update(Ogre::Real delta)
{
	// Running away.
	if(!run_away_queue_.empty())
	{
		run_away_from_(
			std::get<0>(run_away_queue_.front()),
			std::get<1>(run_away_queue_.front()),
			std::get<2>(run_away_queue_.front())
		);
		run_away_queue_.pop();
	}

	// Autoattacks.
	for(auto& ent : entities_.get_component_container<CombatComponent>())
	{
		if(ent.second.cd_time < ent.second.cooldown)
		{
			ent.second.cd_time += delta;
			continue;
		}
		else
			ent.second.cd_time = 0;

		if(ent.second.curr_target != Component::NO_ENTITY &&
		   entities_.exists(ent.second.curr_target))
		{
			auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
			auto target_phys_comp = entities_.get_component<PhysicsComponent>(ent.second.curr_target);

			auto range = ent.second.range * ent.second.range;
			auto task_comp = entities_.get_component<TaskHandlerComponent>(ent.first);
			if(phys_comp && target_phys_comp)
			{
				auto dist = phys_comp->position.squaredDistance(target_phys_comp->position);
				auto path_comp = entities_.get_component<PathfindingComponent>(ent.first);

				/**
				 * Check if the target is in range and in sight and if so, attack, otherwise
				 * pursue the target if necessary.
				 */
				bool is_in_sight{in_sight(ent.first, ent.second.curr_target)};
				bool kill_task_assigned{task_comp ? (TaskHelper::get_task_type(entities_, task_comp->curr_task) == TASK_TYPE::KILL) : false};
				bool on_path{path_comp && !path_comp->path_queue.empty()};
				bool is_in_range{dist <= range};
				if((!is_in_range || !is_in_sight) && !on_path && kill_task_assigned)
				{
					if(ent.second.pursue)
					{ // Order it to go after the target again.
						TaskHelper::add_task(entities_, ent.first, ent.second.curr_target, true);
						task_comp->task_queue.push_front(task_comp->curr_task);
						auto new_task = TaskHelper::create_task(entities_, ent.second.curr_target, TASK_TYPE::GET_IN_RANGE);
						task_comp->task_queue.push_front(new_task);
						task_comp->curr_task = Component::NO_ENTITY;
					}
					else
					{ // Just give up.
						TaskHelper::cancel_task(entities_, task_comp->curr_task);
					}

					ent.second.curr_target = Component::NO_ENTITY;
				}
				else if(is_in_range && is_in_sight)
				{
					if(on_path) // Enemy came to us, just start attacking!
						path_comp->path_queue.clear();

					auto dmg = CombatHelper::get_dmg(ent.second.min_dmg, ent.second.max_dmg);
					GraphicsHelper::look_at(entities_, ent.first, ent.second.curr_target);
					switch(ent.second.atk_type)
					{
						case ATTACK_TYPE::MELEE:
							HealthHelper::sub_health(entities_, ent.second.curr_target, dmg);
							OnHitHelper::call(entities_, ent.second.curr_target, ent.first);
							if(HealthHelper::get_health(entities_, ent.second.curr_target) <= 0)
							{
								DestructorHelper::destroy(entities_, ent.second.curr_target, false, ent.first);
								ent.second.curr_target = Component::NO_ENTITY;
								ent.second.cd_time = ent.second.cooldown; // Allows to attack again instantly.
								if(task_comp && TaskHelper::get_task_type(entities_, task_comp->curr_task) == TASK_TYPE::KILL)
									TaskHelper::cancel_task(entities_, task_comp->curr_task);
							}
							break;
						case ATTACK_TYPE::RANGED:
							create_homing_projectile(ent.first, ent.second);
							break;
					}
				}
				else if(!kill_task_assigned)
					ent.second.curr_target = Component::NO_ENTITY;
			}
			else // Target killed or ran away.
				ent.second.curr_target = Component::NO_ENTITY;
		}
	}

	// Homing projectiles.
	for(auto& ent : entities_.get_component_container<HomingComponent>())
	{
		if(ent.second.target == Component::NO_ENTITY)
			continue; // Manually spawned.
		else if(!entities_.exists(ent.second.target)) // Target killed.
			DestructorHelper::destroy(entities_, ent.first);

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

			pos += dir * mov_comp->speed_modifier;
			graph_comp->node->setPosition(pos);

			if(graph_comp->entity->getWorldBoundingBox(true).intersects(enemy_graph_comp->entity->getWorldBoundingBox(true)))
			{ // That's a hit.
				HealthHelper::sub_health(entities_, ent.second.target, ent.second.dmg);
				OnHitHelper::call(entities_, ent.second.target, ent.second.source);
				if(HealthHelper::get_health(entities_, ent.second.target) <= 0)
				{
					DestructorHelper::destroy(entities_, ent.second.target, false, ent.second.source);

					auto task_comp = entities_.get_component<TaskHandlerComponent>(ent.second.source);
					if(task_comp && TaskHelper::get_task_type(entities_, task_comp->curr_task) == TASK_TYPE::KILL)
						TaskHelper::cancel_task(entities_, task_comp->curr_task);
				}
				DestructorHelper::destroy(entities_, ent.first, false, ent.second.target);
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
		auto res = ray_caster_.cast(phys_comp->position, direction, "entity_" + std::to_string(target));

		if(res.first)
		{
			res.second *= res.second;
			return phys_comp->position.squaredDistance(target_position) <= res.second;
		}
		else
			return true;
	}
	else
		return false;
}

bool CombatSystem::in_sight_wrt_BB(std::size_t ent_id, std::size_t target) const
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
			return phys_comp->position.squaredDistance(target_position) < dist_to_first_struct
				   || res.front().movable->getParentSceneNode()->getName() == "entity_" + std::to_string(target);
		}
		else
			return true; // No structs found at all.
	}
	else
		return false;
}

std::size_t CombatSystem::get_closest_entity(std::size_t id, bool only_sight, bool friendly) const
{
	if(friendly)
		return get_closest_entity<CombatComponent>(id, util::IS_FRIENDLY(entities_, id), only_sight);
	else
		return get_closest_entity<CombatComponent>(id, util::IS_ENEMY(entities_, id), only_sight);
}

std::size_t CombatSystem::get_closest_structure(std::size_t id, bool only_sight, bool friendly) const
{
	if(friendly)
		return get_closest_entity<StructureComponent>(id, util::IS_FRIENDLY(entities_, id), only_sight);
	else
		return get_closest_entity<StructureComponent>(id, util::IS_ENEMY(entities_, id), only_sight);
}

std::size_t CombatSystem::get_closest_entity_thats_not(std::size_t id, std::size_t ignored, bool only_sight, bool friendly) const
{
	if(friendly)
	{
		util::IS_FRIENDLY condition{entities_, id};
		return get_closest_entity<AIComponent>(id, [&condition, ignored](std::size_t i) -> bool { return i != ignored && condition(i); }, only_sight);
	}
	else
	{
		util::IS_ENEMY condition{entities_, id};
		return get_closest_entity<AIComponent>(id, [&condition, ignored](std::size_t i) -> bool { return i != ignored && condition(i); }, only_sight);
	}
}

std::size_t CombatSystem::get_closest_gold_deposit(std::size_t id, bool only_sight) const
{
	util::HAS_GOLD cond{entities_};
	return get_closest_entity<MineComponent>(
		id, [&](std::size_t ent) -> bool { return cond(ent) && FactionHelper::get_faction(entities_, ent) == FACTION::NEUTRAL; },
		only_sight
	);
}

std::size_t CombatSystem::get_closest_gold_vault(std::size_t id, bool only_sight, bool only_free) const
{
	if(only_free)
	{
		util::IS_GOLD_VAULT cond{entities_};
		return get_closest_entity<StructureComponent>(
			id, [&](std::size_t ent) -> bool { return cond(ent) && !GoldHelper::gold_full(entities_, ent); },
			only_sight
		);
	}
	else
		return get_closest_entity<StructureComponent>(id, util::IS_GOLD_VAULT(entities_), only_sight);
}

void CombatSystem::apply_heal_to_entities_in_range(std::size_t id, Ogre::Real range)
{
	util::IS_FRIENDLY condition{entities_, id};
	util::effect::HEAL_EFFECT effect{entities_};
	apply_effect_to_entities_in_range<HealthComponent>(id, condition, effect, range);
}

void CombatSystem::apply_damage_to_entities_in_range(std::size_t id, Ogre::Real range, std::size_t min, std::size_t max)
{
	util::IS_ENEMY condition{entities_, id};
	util::effect::DAMAGE_EFFECT effect{entities_, min, max};
	apply_effect_to_entities_in_range<HealthComponent>(id, condition, effect, range);
}

void CombatSystem::apply_slow_to_entities_in_range(std::size_t id, Ogre::Real range, Ogre::Real time)
{
	util::IS_ENEMY condition{entities_, id};
	util::effect::LOWER_SPEED_EFFECT effect{entities_, time};
	apply_effect_to_entities_in_range<MovementComponent>(id, condition, effect, range);
}

void CombatSystem::apply_freeze_to_entities_in_range(std::size_t id, Ogre::Real range, Ogre::Real time)
{
	util::IS_ENEMY condition{entities_, id};
	util::effect::FREEZE_EFFECT effect{entities_, time};
	apply_effect_to_entities_in_range<MovementComponent>(id, condition, effect, range);
}

void CombatSystem::apply_slow_to(std::size_t id, Ogre::Real time)
{
	util::effect::LOWER_SPEED_EFFECT effect{entities_, time};
	effect(id);
}

void CombatSystem::apply_freeze_to(std::size_t id, Ogre::Real time)
{
	util::effect::FREEZE_EFFECT effect{entities_, time};
	effect(id);
}

void CombatSystem::run_away_from_(std::size_t id, std::size_t from_id, std::size_t min_node_count)
{
	auto phys = entities_.get_component<PhysicsComponent>(id);
	auto path = entities_.get_component<PathfindingComponent>(id);
	if(phys && path)
	{
		std::size_t attempts{0};
		std::size_t start_node{Grid::instance().get_node_from_position(phys->position.x, phys->position.z)};
		std::size_t target{Component::NO_ENTITY}, target_node_count{0};

		std::deque<std::size_t> path{};
		Ogre::Real min_distance{}; // Closest node from the path to the enemy.
		util::heuristic::RUN_AWAY_HEURISTIC heuristic{entities_, from_id};

		while(attempts < max_run_away_attempts_)
		{ // Check different random nodes to find the furthest one.
			std::size_t new_target{Grid::instance().get_random_free_node()};
			path = util::DEFAULT_PATHFINDING_ALGORITHM::get_path(entities_, id, start_node, new_target, heuristic, false);

			Ogre::Real new_min_distance{std::numeric_limits<Ogre::Real>::max()};
			for(const auto& node : path)
			{
				Ogre::Real dist = PhysicsHelper::get_distance(entities_, node, from_id);
				new_min_distance = (dist < new_min_distance) ? dist : new_min_distance;
			}

			if(new_min_distance > min_distance && path.size() > target_node_count
			   && path.size() > min_node_count)
			{
				target = new_target;
				min_distance = new_min_distance;
			}
			++attempts;
		}

		if(!path.empty()) // Perform the actual pathfinding for the best target found.
			util::pathfind<util::DEFAULT_PATHFINDING_ALGORITHM>(entities_, id, target, heuristic, true, false);
	}
}

void CombatSystem::set_max_run_away_attempts(std::size_t val)
{
	max_run_away_attempts_ = val;
}

void CombatSystem::run_away_from(std::size_t id, std::size_t from_id, std::size_t min_node_count)
{
	run_away_queue_.push(std::make_tuple(id, from_id, min_node_count));
}

std::size_t CombatSystem::get_max_run_away_attempts()
{
	return max_run_away_attempts_;
}

bool CombatSystem::enemy_in_range(std::size_t id)
{
	FACTION friendly_faction = FactionHelper::get_faction(entities_, id);
	FACTION enemy_faction{};

	switch(friendly_faction)
	{
		case FACTION::FRIENDLY:
			enemy_faction = FACTION::ENEMY;
			break;
		case FACTION::ENEMY:
			enemy_faction = FACTION::FRIENDLY;
			break;
		case FACTION::NEUTRAL:
			return false;
	}

	auto range = CombatHelper::get_range(entities_, id);
	range *= range;
	auto position = PhysicsHelper::get_2d_position(entities_, id);
	for(const auto& ent : entities_.get_component_container<FactionComponent>())
	{
		if(ent.second.faction == enemy_faction &&
		   position.squaredDistance(PhysicsHelper::get_2d_position(entities_, ent.first)) <= range)
		{
			return true;
		}
	}
	return false;
}

void CombatSystem::create_homing_projectile(std::size_t caster, CombatComponent& combat)
{
	std::size_t id = entities_.create_entity(combat.projectile_blueprint);
	auto comp = entities_.get_component<HomingComponent>(id);
	if(comp)
	{
		comp->dmg = CombatHelper::get_dmg(combat.min_dmg, combat.max_dmg);
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
