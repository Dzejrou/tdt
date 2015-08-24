#pragma once

#include <cstdlib>
class EntitySystem;

namespace TaskHandlerHelper
{
	/**
	 * Brief: Returns a reference to the task queue of a given entity.
	 * Param: Reference to the entity system containing needed components.
	 * Param: ID of the entity.
	 */
	std::deque<std::size_t> get_task_queue(EntitySystem&, std::size_t);

	/**
	 * Brief: Checks whether an entity can accept and complete a given task.
	 * Param: Reference to the entity system containing needed components.
	 * Param: ID of the entity.
	 * Param: ID of the task.
	 */
	bool task_possible(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Cancels all tasks in a given entity's task queue.
	 * Param: Reference to the entity system containing needed components.
	 * Param: ID of the entity.
	 */
	void clear_task_queue(EntitySystem&, std::size_t);

	/**
	 * Brief: Marks a given entity as available to accept tasks of a given task type.
	 * Param: Reference to the entity system containing needed components.
	 * Param: ID of the entity.
	 * Param: Type of the task to be added.
	 */
	void add_possible_task(EntitySystem&, std::size_t, TASK_TYPE);

	/**
	 * Brief: Marks a given entity as unavailable to accept tasks of a given task type.
	 * Param: Reference to the entity system containing needed components.
	 * Param: ID of the entity.
	 * Param: Type of the task to be deleted.
	 */
	void delete_possible_task(EntitySystem&, std::size_t, TASK_TYPE);
}