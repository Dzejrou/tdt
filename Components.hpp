#pragma once

#include <Ogre.h>
#include <string>
#include <vector>
#include <queue>

// Temporary:
enum class EntityState {};
enum class Faction {};
enum class TaskType {};
class Attack {};
class Task {};


struct Component
{

};

struct PhysicsComponent : public Component
{
	Ogre::SceneNode& node;
	Ogre::Entity& entity;
	Ogre::Vector3 position;
};

struct HealthComponent : public Component
{
	std::size_t curr_hp;
	std::size_t max_hp;
	std::size_t regen;
};

struct AIComponent : public Component
{
	std::string script_name;
	EntityState state;
	Faction faction;
};

struct GraphicsComponent : public Component
{
	std::string mesh;
	std::string material;
};

struct MovementComponent : public Component
{
	Ogre::Vector3 movement_vector;
	Ogre::Vector3 speed_modifier;
	bool moving;
};

struct CombatComponent : public Component
{
	std::size_t range;
	std::size_t min_dmg;
	std::size_t max_dmg;
	std::vector<std::size_t> attacks;
};

struct TaskComponent : public Component
{
	std::queue<Task> queue;
	std::size_t curr_tast_progress;
	std::size_t curr_task_length;
	TaskType curr_task_type;
};