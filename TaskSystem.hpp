#pragma once

#include <deque>
#include <map>
#include <string>

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
		 * Brief: Returns a reference to the task queue of a given entity.
		 * Param: ID of the entity.
		 */
		std::deque<std::size_t> get_task_queue(std::size_t);

		/**
		 * Brief: Checks whether an entity can accept and complete a given task.
		 * Param: ID of the entity.
		 * Param: ID of the task.
		 */
		bool task_possible(std::size_t, std::size_t) const;

		/**
		 * Brief: Cancels all tasks in a given entity's task queue.
		 * Param: ID of the entity.
		 */
		void clear_task_queue(std::size_t);

		/**
		 * Brief: Translates a task type enum value into a string that can be displayed
		 *        in the developer's console.
		 * Param: Task type to be translated.
		 */
		const std::string& get_task_name(TASK_TYPE) const;

		/**
		 * Brief: Sets the source of a given task (that is, the entity that is completing the task).
		 * Param: Task ID.
		 * Param: Source ID.
		 */
		void set_task_source(std::size_t, std::size_t);

		/**
		 * Brief: Sets the target entity of a given task.
		 * Param: Task ID.
		 * Param: Target ID.
		 */
		void set_task_target(std::size_t, std::size_t);

		/**
		 * Brief: Sets the task type of a given task.
		 * Param: Task ID.
		 * Param: The new task type.
		 */
		void set_task_type(std::size_t, TASK_TYPE);

		/**
		 * Brief: Marks a given entity as available to accept tasks of a given task type.
		 * Param: ID of the entity.
		 * Param: Type of the task to be added.
		 */
		void add_possible_task(std::size_t, TASK_TYPE);

		/**
		 * Brief: Marks a given entity as unavailable to accept tasks of a given task type.
		 * Param: ID of the entity.
		 * Param: Type of the task to be deleted.
		 */
		void delete_possible_task(std::size_t, TASK_TYPE);
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