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
	static constexpr int count = 20;
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

	MovementComponent(Ogre::Real speed = 0.f)
		: speed_modifier{speed}
	{ /* DUMMY BODY */ }
	MovementComponent(const MovementComponent&) = default;
	MovementComponent(MovementComponent&&) = default;

	Ogre::Real speed_modifier;
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
 * Represents events that happen in the game, like gold seams dropping gold,
 * curing an entity of poisoning or triggers from traps etc.
 */
struct EventComponent
{ 
	static constexpr int type = 6;

	EventComponent(EVENT_TYPE ev = EVENT_TYPE::NONE, std::size_t t = Component::NO_ENTITY,
				   Ogre::Real r = 0.f, bool a = true)
		: event_type{ev}, target{t}, radius{r}, active{a}
	{ /* DUMMY BODY */ }
	EventComponent(const EventComponent&) = default;
	EventComponent(EventComponent&&) = default;

	EVENT_TYPE event_type;
	std::size_t target;
	Ogre::Real radius;
	bool active;
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
 * Represents a timer that after a certain amount of time can start
 * end an event (it's target).
 */
struct TimeComponent
{
	static constexpr int type = 8;

	TimeComponent(TIME_EVENT ev = TIME_EVENT::NONE, Ogre::Real limit = 0.f,
				  std::size_t t = Component::NO_ENTITY)
		: curr_time{0.f}, time_limit{limit}, target{t}, event_type{ev}
	{ /* DUMMY BODY */ }
	TimeComponent(const TimeComponent&) = default;
	TimeComponent(TimeComponent&&) = default;

	Ogre::Real curr_time;
	Ogre::Real time_limit;
	std::size_t target;
	TIME_EVENT event_type;
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

	ProductionComponent(const std::string& b = "ERROR", std::size_t l = 1, Ogre::Real cd = 0.f)
		: product_blueprint{b}, curr_produced{0}, max_produced{l}, cooldown{cd}, curr_cd{0}
	{ /* DUMMY BODY */ }
	ProductionComponent(const ProductionComponent&) = default;
	ProductionComponent(ProductionComponent&&) = default;

	std::string product_blueprint;
	std::size_t curr_produced;
	std::size_t max_produced;
	Ogre::Real cooldown;
	Ogre::Real curr_cd;
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
 * References the producer of the entity that has this component.
 * (Producer == building/tile that spawned it.)
 */
struct ProductComponent
{
	static constexpr int type = 13;

	ProductComponent(std::size_t prod_id = Component::NO_ENTITY)
		: producer{prod_id}
	{ /* DUMMY BODY */ }
	ProductComponent(const ProductComponent&) = default;
	ProductComponent(ProductComponent&&) = default;

	std::size_t producer;
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

	StructureComponent(std::size_t r = 1, bool wt = false)
		: radius{r}, walk_through{wt}, residences{}
	{ /* DUMMY BODY */ }
	StructureComponent(const StructureComponent&) = default;
	StructureComponent(StructureComponent&&) = default;

	std::size_t radius;
	bool walk_through;
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

/**
 * Allows to cherry pink when it comes to event handling and handle
 * only certain events. (Also, only entities with this component
 * will react to events.)
 */
struct EventHandlerComponent
{
	static constexpr int type = 19;

	EventHandlerComponent(const std::string& h = "ERROR")
		: handler{h}, possible_events{}
	{ /* DUMMY BODY */ }
	EventHandlerComponent(const EventHandlerComponent&) = default;
	EventHandlerComponent(EventHandlerComponent&&) = default;

	std::string handler;
	std::bitset<(int)EVENT_TYPE::COUNT> possible_events;
/**
 * Contains name of the table that contains the function
 * (called "dtor") which is called when an entity is destroyed.
 */
struct DestructorComponent
{
	static constexpr int type = 20;

	DestructorComponent(std::string b = "ERROR")
		: blueprint{b}
	{ /* DUMMY BODY */ }
	DestructorComponent(const DestructorComponent&) = default;
	DestructorComponent(DestructorComponent&&) = default;

	std::string blueprint;
};

};