#pragma once

#include <Ogre.h>
#include <string>
#include <array>
#include <deque>
#include <bitset>
#include <memory>
#include <numeric>

#include "Enums.hpp"

// Temporary:
enum class AttackType { NONE, MELEE };

struct Component
{
	static constexpr int count = 17;
	static constexpr std::size_t NO_ENTITY = std::numeric_limits<std::size_t>::max();
};

/**
 * Components
 * Note: To be able to manually create components without blueprints, all components must have
 *       either default constructors or constructors with default values for all parameters, to be able
 *       to back components up, they need to provide a copy constructor.
 */

/**
 * Holds info related to physical interaction of an entity with the rest
 * of the game world.
 */
struct PhysicsComponent
{
	static constexpr int type = 0;

	PhysicsComponent(bool s = false, Ogre::Vector3 pos = Ogre::Vector3{0, 0, 0}, Ogre::Real hh = 0.f)
		: solid{s}, position{pos}, half_height{hh}
	{ /* DUMMY BODY */ }
	PhysicsComponent(const PhysicsComponent&) = default;
	PhysicsComponent(PhysicsComponent&&) = default;

	bool solid;
	Ogre::Vector3 position;
	Ogre::Real half_height;
};

/**
 * Holds info about an entity's health and regeneration.
 */
struct HealthComponent
{
	static constexpr int type = 1;

	HealthComponent(std::size_t max = 0, std::size_t reg = 0,
					std::size_t def = 0, bool a = true)
		: curr_hp{max}, max_hp{max}, regen{reg}, defense{def}, alive{a}
	{ /* DUMMY BODY */ }
	HealthComponent(const HealthComponent&) = default;
	HealthComponent(HealthComponent&&) = default;

	std::size_t curr_hp;
	std::size_t max_hp;
	std::size_t regen;
	std::size_t defense;
	bool alive;
};

/**
 * Holds info about the base Lua table to be called for initializing, updating and finnishing
 * an entity as well as couple categorizing enums.
 */
struct AIComponent
{
	static constexpr int type = 2;

	AIComponent(const std::string& s = "ERROR",
				FACTION f = FACTION::NEUTRAL,
				ENTITY_STATE st = ENTITY_STATE::NORMAL)
		: blueprint{s}, state{st}, faction(f)
	{ /* DUMMY BODY */ }
	AIComponent(const AIComponent&) = default;
	AIComponent(AIComponent&&) = default;

	std::string blueprint;
	ENTITY_STATE state;
	FACTION faction;
};

/**
 * Holds info related to the Ogre3D rendering library.
 */
struct GraphicsComponent
{
	static constexpr int type = 3;

	GraphicsComponent(const std::string& me = "ogrehead.mesh",
					  const std::string& ma = "Ogre", bool v = true)
		: mesh{me}, material{ma}, visible{v}, node{nullptr}, entity{nullptr}
	{ /* DUMMY BODY */ }
	GraphicsComponent(const GraphicsComponent&) = delete;
	GraphicsComponent(GraphicsComponent&&) = delete;

	std::string mesh;
	std::string material;
	bool visible;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
	// TODO: Animation + set_animation etc. in a system. Possibly a new component?
};

/**
 * Holds info related to movement, if an entity has this component it should also
 * have a Physics component (containing the entity's position), otherwise the
 * MovementSystem might not work correctly.
 */
struct MovementComponent
{
	static constexpr int type = 4;

	MovementComponent(Ogre::Vector3 mov_vec = Ogre::Vector3{0, 0, 0},
					  Ogre::Real speed = 0.f, bool mov = false)
		: movement_vector{mov_vec}, speed_modifier{speed},
		  moving{mov}
	{ /* DUMMY BODY */ }
	MovementComponent(const MovementComponent&) = default;
	MovementComponent(MovementComponent&&) = default;

	Ogre::Vector3 movement_vector;
	Ogre::Real speed_modifier;
	bool moving;
};

/**
 * Holds info about an entity's attack types and damage.
 * TODO: Reseach the entire combat mechanism.
 */
struct CombatComponent
{
	static constexpr int type = 5;

	CombatComponent(std::size_t r = 0, std::size_t mi = 0, std::size_t ma = 0,
					int a1 = 0, int a2 = 0, float a2_chance = 0.f)
		: range{r}, min_dmg{mi}, max_dmg{ma}, atk_1((AttackType)a1),
		  atk_2((AttackType)a2), atk2_chance{a2_chance}
	{ /* DUMMY BODY */ }
	CombatComponent(const CombatComponent&) = default;
	CombatComponent(CombatComponent&&) = default;

	std::size_t range;
	std::size_t min_dmg;
	std::size_t max_dmg;
	AttackType atk_1;
	AttackType atk_2;
	float atk2_chance;
};

/**
 * TODO:
 */
struct EventComponent
{ // TODO: 
	static constexpr int type = 6;

	EventComponent()
		: curr_event_position{0, 0, 0}, curr_event_radius{0}, curr_event_progress{},
		  curr_event_length{}, possible_events{}
	{ /* DUMMY BODY */ }
	EventComponent(const EventComponent&) = default;

	Ogre::Vector3 curr_event_position;
	Ogre::Real curr_event_radius;
	std::size_t curr_event_progress;
	std::size_t curr_event_length;
	std::bitset<32> possible_events;
};

/**
 * Holds info related to direct player input applied to an entity.
 */
struct InputComponent
{
	static constexpr int type = 7;

	InputComponent(const std::string& handler = "ERROR.input_handler")
		: input_handler{handler}
	{ /* DUMMY BODY */ }
	InputComponent(const InputComponent&) = default;
	InputComponent(InputComponent&&) = default;

	std::string input_handler;
};

/**
 * TODO:
 */
struct TimeComponent
{
	static constexpr int type = 8;
};

/**
 * TODO:
 */
struct ManaComponent
{
	static constexpr int type = 9;
};

/**
 * TODO:
 */
struct SpellComponent
{
	static constexpr int type = 10;
};

/**
 * TODO:
 */
struct ProductionComponent
{
	static constexpr int type = 11;
};

/**
 * Holds GridNode's neighbour nodes.
 * Note: The neighbours are set to the maximum value of std::size_t to
 *       fix a state when one or more neighbours weren't set (won't have that many
 *       nodes so the A* algorithm will ignore them).
 */
struct GridNodeComponent
{
	static constexpr int type = 12;
	static constexpr std::size_t neighbour_count = 8;

	GridNodeComponent(std::array<std::size_t, neighbour_count> neigh = std::array<std::size_t, neighbour_count>{},
					  bool f = true, std::size_t pos_x = 0, std::size_t pos_y = 0, std::size_t res = Component::NO_ENTITY)
		: neighbours(neigh), free{f}, x{pos_x}, y{pos_y}, resident{res}
	{
		for(std::size_t i = 0; i < neighbours.size(); ++i)
			neighbours[i] = Component::NO_ENTITY;
	}
	GridNodeComponent(const GridNodeComponent&) = default;
	GridNodeComponent(GridNodeComponent&&) = default;

	/**
	 * Note: For more versatility of the game engine, using
	 * a std::vector instead would allow for non grid-like
	 * pathfinding graphs.
	 */
	std::array<std::size_t, neighbour_count> neighbours;
	bool free;
	std::size_t x, y; // Position in the grid.
	std::size_t resident;
};

/**
 * Holds data related to a grid line - ID of it's starting GridNode,
 * ID of it's ending GridNode and the distance between the two nodes.
 */
struct GridLineComponent
{
	static constexpr int type = 13;

	GridLineComponent(std::size_t start = 0, std::size_t end = 0)
		: start_id{start}, end_id{end}
	{ /* DUMMY BODY */ }
	GridLineComponent(const GridLineComponent&) = default;
	GridLineComponent(GridLineComponent&&) = default;

	std::size_t start_id, end_id;
};

/**
 *
 */
struct PathfindingComponent
{
	static constexpr int type = 14;

	PathfindingComponent(const std::string& cost = "ERROR", std::size_t tar = 0,
						 std::size_t last = 0)
		: target_id{tar}, last_id{last}, path_queue{}, blueprint{cost}
	{ /* DUMMY BODY */ }
	PathfindingComponent(const PathfindingComponent&) = default;
	PathfindingComponent(PathfindingComponent&&) = default;
	
	std::size_t target_id, last_id;
	std::deque<std::size_t> path_queue;
	std::string blueprint; // Name of the table the get_cost(id1, id2) function is in.
};

/**
 *
 */
struct TaskComponent
{
	static constexpr int type = 15;

	TaskComponent(std::size_t target_id = Component::NO_ENTITY,
				  std::size_t source_id = Component::NO_ENTITY,
				  TASK_TYPE t_type = TASK_TYPE::NONE)
		: task_type{t_type}, source{source_id}, target{target_id}
	{ /* DUMMY BODY */ }
	TaskComponent(const TaskComponent&) = default;
	TaskComponent(TaskComponent&&) = default;

	TASK_TYPE task_type;
	std::size_t source, target;
};

/**
 *
 */
struct TaskHandlerComponent
{
	static constexpr int type = 16;

	TaskHandlerComponent(std::size_t curr = Component::NO_ENTITY)
		: curr_task{curr}, possible_tasks{}, task_queue{},
		  busy{curr == Component::NO_ENTITY}
	{  /* DUMMY BODY */ }
	TaskHandlerComponent(const TaskHandlerComponent&) = default;

	std::size_t curr_task;
	std::bitset<(int)TASK_TYPE::COUNT> possible_tasks;
	std::deque<std::size_t> task_queue;
	bool busy;
};