#pragma once

#include <Ogre.h>
#include <string>
#include <vector>
#include <queue>
#include <bitset>

// Temporary:
enum class EntityState { NORMAL };
enum class Faction {};
enum class EventType {};
class Attack {};
class Event {};

struct Component
{
	// TODO: Is this necessary?
};

struct PhysicsComponent : public Component
{
	static constexpr int type = 0;

	PhysicsComponent(bool s)
		: node{nullptr}, entity{nullptr}, position{0, 0, 0}, solid{s}
	{ /* DUMMY BODY */ }

	Ogre::SceneNode* node;
	Ogre::Entity* entity;
	Ogre::Vector3 position;
	bool solid;
};

struct HealthComponent : public Component
{
	static constexpr int type = 1;

	HealthComponent(std::size_t max, std::size_t reg, std::size_t def)
		: curr_hp{max}, max_hp{max}, regen{reg}, defense{def}, alive{true}
	{ /* DUMMY BODY */ }

	std::size_t curr_hp;
	std::size_t max_hp;
	std::size_t regen;
	std::size_t defense;
	bool alive;
};

struct AIComponent : public Component
{
	static constexpr int type = 2;

	AIComponent(std::string s, int f)
		: script_name{s}, state{EntityState::NORMAL}, faction((Faction)f)
	{ /* DUMMY BODY */ }

	std::string script_name;
	EntityState state;
	Faction faction;
};

struct GraphicsComponent : public Component
{
	static constexpr int type = 3;

	GraphicsComponent(std::string me, std::string ma)
		: mesh{me}, material{ma}
	{ /* DUMMY BODY */ }

	std::string mesh;
	std::string material;
};

struct MovementComponent : public Component
{
	static constexpr int type = 4;

	MovementComponent()
		: movement_vector{0, 0, 0}, speed_modifier{0},
		  moving{false}
	{ /* DUMMY BODY */ }

	Ogre::Vector3 movement_vector;
	Ogre::Real speed_modifier;
	bool moving;
};

struct CombatComponent : public Component
{
	static constexpr int type = 5;

	CombatComponent(std::size_t r, std::size_t mi, std::size_t ma)
		: range{r}, min_dmg{mi}, max_dmg{ma}
	{ /* DUMMY BODY */ }

	std::size_t range;
	std::size_t min_dmg;
	std::size_t max_dmg;
};

struct EventComponent : public Component
{
	static constexpr int type = 6;

	EventComponent()
		: event_queue{}, curr_event_progress{},
		  curr_event_length{}, possible_events{}
	{ /* DUMMY BODY */ }

	std::queue<Event> event_queue;
	std::size_t curr_event_progress;
	std::size_t curr_event_length;
	std::bitset<32> possible_events;
};