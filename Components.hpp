#pragma once

#include <Ogre.h>
#include <string>
#include <vector>
#include <queue>
#include <bitset>

// Temporary:
enum class EntityState { NONE, NORMAL };
enum class Faction { FRIENDLY, ENEMY, NEUTRAL };
enum class EventType {};
enum class AttackType { NONE, MELEE };
class Attack {};
class Event {};

struct Component
{
	static constexpr int count = 14;
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

	PhysicsComponent(bool s = false)
		: position{0, 0, 0}, solid{s}
	{ /* DUMMY BODY */ }
	PhysicsComponent(const PhysicsComponent&) = default;

	Ogre::Vector3 position;
	bool solid;
};

/**
 * Holds info about an entity's health and regeneration.
 */
struct HealthComponent
{
	static constexpr int type = 1;

	HealthComponent(std::size_t max = 0, std::size_t reg = 0, std::size_t def = 0)
		: curr_hp{max}, max_hp{max}, regen{reg}, defense{def}, alive{true}
	{ /* DUMMY BODY */ }
	HealthComponent(const HealthComponent&) = default;

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

	AIComponent(const std::string& s = "ERROR", int f = 2)
		: blueprint{s}, state{EntityState::NORMAL}, faction((Faction)f)
	{ /* DUMMY BODY */ }
	AIComponent(const AIComponent&) = default;

	std::string blueprint;
	EntityState state;
	Faction faction;
};

/**
 * Holds info related to the Ogre3D rendering library.
 */
struct GraphicsComponent
{
	static constexpr int type = 3;

	GraphicsComponent(const std::string& me = "ogrehead.mesh", const std::string& ma = "Ogre")
		: mesh{me}, material{ma}, visible{true}, node{nullptr}, entity{nullptr}
	{ /* DUMMY BODY */ }
	GraphicsComponent(const GraphicsComponent&) = default;

	std::string mesh;
	std::string material;
	bool visible;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
	// TODO: Animation + set_animation etc. in a system.
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
		: movement_vector{0, 0, 0}, speed_modifier{speed},
		  moving{false}
	{ /* DUMMY BODY */ }
	MovementComponent(const MovementComponent&) = default;

	Ogre::Vector3 movement_vector;
	Ogre::Real speed_modifier;
	bool moving;
};

/**
 * Holds info about an entity's attack types and damage.
 */
struct CombatComponent
{
	static constexpr int type = 5;

	CombatComponent(std::size_t r = 0, std::size_t mi = 0, std::size_t ma = 0, int a1 = 0, int a2 = 0, float a2_chance = 0.f)
		: range{r}, min_dmg{mi}, max_dmg{ma}, atk_1((AttackType)a1), atk_2((AttackType)a2), atk2_chance{a2_chance}
	{ /* DUMMY BODY */ }
	CombatComponent(const CombatComponent&) = default;

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
 */
struct GridNodeComponent
{
	GridNodeComponent()
		: neighbours{}, free{true}
	{ /* DUMMY BODY */ }

	std::vector<std::size_t> neighbours;
	bool free;
};

/**
 * Holds data related to a grid line - ID of it's starting GridNode,
 * ID of it's ending GridNode and the distance between the two nodes.
 */
struct GridLineComponent
{
	GridLineComponent(std::size_t start = 0, std::size_t end = 0)
		: start_id{start}, end_id{end}, distance{0}
	{ /* DUMMY BODY */ }

	std::size_t start_id, end_id;
	Ogre::Real distance;
};