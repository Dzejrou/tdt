#pragma once

#include <cstdlib>
#include <deque>
#include "Enums.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the task handler component.
 */
namespace TaskHandlerHelper
{
	/**
	 * Brief: Returns a reference to the task queue of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	std::deque<std::size_t>& get_task_queue(EntitySystem&, std::size_t);

	/**
	 * Brief: Checks whether an entity can accept and complete a given task.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: ID of the task.
	 */
	bool task_possible(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Checks whether an entity can accept and complete a task of agiven task type.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Task type to be tested.
	 */
	bool task_possible(EntitySystem&, std::size_t, TASK_TYPE);

	/**
	 * Brief: Cancels all tasks in a given entity's task queue.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	void clear_task_queue(EntitySystem&, std::size_t);

	/**
	 * Brief: Marks a given entity as available to accept tasks of a given task type.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Type of the task to be added.
	 */
	void add_possible_task(EntitySystem&, std::size_t, TASK_TYPE);

	/**
	 * Brief: Marks a given entity as unavailable to accept tasks of a given task type.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Type of the task to be deleted.
	 */
	void delete_possible_task(EntitySystem&, std::size_t, TASK_TYPE);

	/**
	 * Brief: Sets the handling blueprint of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The name of the new blueprint.
	 */
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the handling blueprint of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, std::size_t);
}