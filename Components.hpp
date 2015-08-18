#pragma once

#include <Ogre.h>
#include <string>
#include <array>
#include <deque>
#include <bitset>
#include <memory>
#include <numeric>

#include "Enums.hpp"

struct Component
{
	static constexpr int count = 19;
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
					  const std::string& ma = "Ogre", bool v = true,
					  bool manual = false, Ogre::Vector3 sc = Ogre::Vector3{0, 0, 0})
		: mesh{me}, material{ma}, visible{v}, node{nullptr}, entity{nullptr},
		  manual_scaling{manual}, scale{sc}
	{ /* DUMMY BODY */ }
	GraphicsComponent(const GraphicsComponent&) = default;
	GraphicsComponent(GraphicsComponent&&) = default;

	std::string mesh;
	std::string material;
	bool visible;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
	bool manual_scaling;
	Ogre::Vector3 scale;
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

	MovementComponent(Ogre::Real speed = 0.f, bool mov = false)
		: movement_vector{0, 0, 0}, speed_modifier{speed},
		  moving{mov}
	{ /* DUMMY BODY */ }
	MovementComponent(const MovementComponent&) = default;
	MovementComponent(MovementComponent&&) = default;

	Ogre::Vector3 movement_vector; // TODO: Is this needed?
	Ogre::Real speed_modifier;
	bool moving; // TODO: Is this needed?
};

/**
 * Holds info about an entity's attack types and damage.
 * TODO: Reseach the entire combat mechanism.
 */
struct CombatComponent
{
	static constexpr int type = 5;

	CombatComponent(std::size_t target = Component::NO_ENTITY, std::size_t mi = 0,
					std::size_t ma = 0, Ogre::Real cd = 0, Ogre::Real r = 0.f, int type = 0)
		: curr_target{target}, min_dmg{mi},	max_dmg{ma}, cooldown{cd}, cd_time{cd},
		  range{r}, atk_type((ATTACK_TYPE)type)
	{ /* DUMMY BODY */ }
	CombatComponent(const CombatComponent&) = default;
	CombatComponent(CombatComponent&&) = default;

	std::size_t curr_target;
	std::size_t min_dmg;
	std::size_t max_dmg;
	Ogre::Real cd_time;
	Ogre::Real cooldown;
	Ogre::Real range;
	ATTACK_TYPE atk_type;
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
		neighbours.fill(Component::NO_ENTITY);
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
 * DEPRECATED - REPLACE WHEN A NEW COMPONENT IS IMPLEMENTED.
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
 * Holds data related to the entity's current path.
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
 * Defines a task by giving it a type, source (the task handler) and a target
 * (subject of the task). Handling of these tasks is done via the TaskHandlerComponent below.
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
 * Task queue and register of possible tasks, every entity that is
 * able to actually do something on it's own should have it.
 */
struct TaskHandlerComponent
{
	static constexpr int type = 16;

	TaskHandlerComponent(std::size_t curr = Component::NO_ENTITY)
		: curr_task{curr}, possible_tasks{}, task_queue{},
		  busy{curr != Component::NO_ENTITY}
	{  /* DUMMY BODY */ }
	TaskHandlerComponent(const TaskHandlerComponent&) = default;

	std::size_t curr_task;
	std::bitset<(int)TASK_TYPE::COUNT> possible_tasks;
	std::deque<std::size_t> task_queue;
	bool busy;
};

/**
 * Defines a building (or a wall), by holding it's radius (of the area it takes
 * in the grid) and vector of nodes that it sits on.
 */
struct StructureComponent
{
	static constexpr int type = 17;

	StructureComponent(std::size_t r = 1)
		: radius{r}, residences{}
	{ /* DUMMY BODY */ }
	StructureComponent(const StructureComponent&) = default;
	StructureComponent(StructureComponent&&) = default;

	std::size_t radius;
	std::vector<std::size_t> residences;
};

/**
 * Used for projectiles that are supposed to follow a target and deal
 * damage when they hit it.
 */
struct HomingComponent
{
	static constexpr int type = 18;

	HomingComponent(std::size_t s = Component::NO_ENTITY,
					std::size_t t = Component::NO_ENTITY,
					std::size_t d = 0)
		: source{s}, target{t}, dmg{d}
	{ /* DUMMY BODY */ }
	HomingComponent(const HomingComponent&) = default;
	HomingComponent(HomingComponent&&) = default;

	std::size_t source;
	std::size_t target;
	std::size_t dmg;
};