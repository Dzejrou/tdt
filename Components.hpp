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
	static constexpr int count = 12;
};

/**
 * Components
 * Note: To be able to manually create components without blueprints, all components must have
 *       either default constructors or constructors with default values for all parameters, to be able
 *       to back components up, they need to provide a copy constructor.
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

struct InputComponent
{
	static constexpr int type = 7;

	InputComponent(const std::string& handler = "ERROR.input_handler")
		: input_handler{handler}
	{ /* DUMMY BODY */ }
	InputComponent(const InputComponent&) = default;

	std::string input_handler;
};

struct TimeComponent
{
	static constexpr int type = 8;
};

struct ManaComponent
{
	static constexpr int type = 9;
};

struct SpellComponent
{
	static constexpr int type = 10;
};

struct ProductionComponent
{
	static constexpr int type = 11;
};