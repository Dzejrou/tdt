#pragma once

#include <deque>
#include <map>
#include <string>
#include <cstdlib>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "GridSystem.hpp"
#include "CombatSystem.hpp"

/**
 * System managing all entities with the TaskComponent, their creation, assignment,
 * lifetime checks and canceling.
 */
class TaskSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 * Param: Reference to the game's grid system.
		 */
		TaskSystem(EntitySystem&, GridSystem&, CombatSystem&);

		/**
		 * Destructor.
		 */
		~TaskSystem() {}

		/**
		 * Brief: Manages the lifetime of tasks on each frame.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Assigns a new task to an entity (by adding it to the task queue).
		 * Param: ID of the entity.
		 * Param: ID of the task.
		 */
		void add_task(std::size_t, std::size_t);

		/**
		 * Brief: Destroys the TaskComponent of a given task, effectively stopping
		 *        it's completion.
		 * Param: ID of the task.
		 */
		void cancel_task(std::size_t);

		/**
		 * Brief: Creates a new task of a given tasks and returns it's ID.
		 * Param: ID of the task's target (goto location, kill target etc.).
		 * Param: Type of the task.
		 */
		std::size_t create_task(std::size_t, TASK_TYPE);

		/**
		 * Brief: Translates a task type enum value into a string that can be displayed
		 *        in the developer's console.
		 * Param: Task type to be translated.
		 */
		const std::string& get_task_name(TASK_TYPE) const;
	private:
		/**
		 * Brief: Set's the current task to the task in the front of the respective task queue
		 *        and removes it from the queue.
		 * Param: Reference to the TaskHandlerComponent containing the aforementioned task queue.
		 */
		void next_task_(TaskHandlerComponent&);

		/**
		 * Brief: Executes a single task.
		 * Param: ID of the entity that the task is assigned to.
		 * Param: Reference to the task component of the task to be handled.
		 * Param: Reference to the task handling component of the assigned entity.
		 */
		void handle_task_(std::size_t, TaskComponent&, TaskHandlerComponent&);

		/**
		 * Brief: Checks whether the current task of a given entity has been completed.
		 * Param: ID of the handling entity.
		 * Param: Reference to the entity's TaskHandlerComponent.
		 */
		bool current_task_completed_(std::size_t, TaskHandlerComponent&);

		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's grid system.
		 */
		GridSystem& grid_;

		/**
		 * Reference to the game's combat system used for line of sight checking.
		 */
		CombatSystem& combat_;

		/**
		 * Map used for task type translation.
		 */
		std::map<TASK_TYPE, std::string> task_names_;
};