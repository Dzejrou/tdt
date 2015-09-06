#pragma once

#include <cstdlib>
#include "Enums.hpp"
class EntitySystem;

namespace TaskHelper
{
	/**
	 * Brief: Sets the source of a given task (that is, the entity that is completing the task).
	 * Param: Reference to the entity system containing components.
	 * Param: Task ID.
	 * Param: Source ID.
	 */
	void set_task_source(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the source of a given task (that is, the entity that is completing the task).
	 * Param: Reference to the entity system containing components.
	 * Param: Task ID.
	 */
	std::size_t get_task_source(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the target entity of a given task.
	 * Param: Reference to the entity system containing components.
	 * Param: Task ID.
	 * Param: Target ID.
	 */
	void set_task_target(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the target entity of a given task.
	 * Param: Reference to the entity system containing components.
	 * Param: Task ID.
	 */
	std::size_t get_task_target(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the task type of a given task.
	 * Param: Reference to the entity system containing components.
	 * Param: Task ID.
	 * Param: The new task type.
	 */
	void set_task_type(EntitySystem&, std::size_t, TASK_TYPE);

	/**
	 * Returns the task type of a given task.
	 * Param: Reference to the entity system containing components.
	 * Param: Task ID.
	 */
	TASK_TYPE get_task_type(EntitySystem&, std::size_t);

	/**
	 * Brief: Assigns a new task to an entity (by adding it to the task queue).
	 * Param: ID of the entity.
	 * Param: ID of the task.
	 */
	void add_task(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Creates a new task of a given tasks and returns it's ID.
	 * Param: ID of the task's target (goto location, kill target etc.).
	 * Param: Type of the task.
	 */
	std::size_t create_task(EntitySystem&, std::size_t, TASK_TYPE);

	/**
	 * Brief: Destroys the TaskComponent of a given task, effectively stopping
	 *        it's completion.
	 * Param: ID of the task.
	 */
	void cancel_task(EntitySystem&, std::size_t);
}