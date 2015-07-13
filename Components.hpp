#pragma once

#include <Ogre.h>
#include <string>
#include <vector>
#include <queue>
#include <bitset>

// Temporary:
enum class EntityState {};
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

	Ogre::SceneNode& node;
	Ogre::Entity& entity;
	Ogre::Vector3 position;
};

struct HealthComponent : public Component
{
	static constexpr int type = 1;

	std::size_t curr_hp;
	std::size_t max_hp;
	std::size_t regen;
};

struct AIComponent : public Component
{
	static constexpr int type = 2;

	std::string script_name;
	EntityState state;
	Faction faction;
};

struct GraphicsComponent : public Component
{
	static constexpr int type = 3;

	std::string mesh;
	std::string material;
};

struct MovementComponent : public Component
{
	static constexpr int type = 4;

	Ogre::Vector3 movement_vector;
	Ogre::Vector3 speed_modifier;
	bool moving;
};

struct CombatComponent : public Component
{
	static constexpr int type = 5;

	std::size_t range;
	std::size_t min_dmg;
	std::size_t max_dmg;
	std::vector<std::size_t> attacks;
};

struct EventComponent : public Component
{
	static constexpr int type = 6;

	std::queue<Event> event_queue;
	std::size_t curr_event_progress;
	std::size_t curr_event_length;
	EventType curr_event_type;
	std::bitset<32> possible_events;
};