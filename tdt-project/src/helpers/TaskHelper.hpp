#pragma once

#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of the task
 * component.
 */
namespace TaskHelper
{
	/**
	 * \brief Sets the source of a given task (that is, the entity that is completing the task).
	 * \param Reference to the entity system containing components.
	 * \param Task ID.
	 * \param Source ID.
	 */
	void set_task_source(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the source of a given task (that is, the entity that is completing the task).
	 * \param Reference to the entity system containing components.
	 * \param Task ID.
	 */
	tdt::uint get_task_source(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the target entity of a given task.
	 * \param Reference to the entity system containing components.
	 * \param Task ID.
	 * \param Target ID.
	 */
	void set_task_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the target entity of a given task.
	 * \param Reference to the entity system containing components.
	 * \param Task ID.
	 */
	tdt::uint get_task_target(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the task type of a given task.
	 * \param Reference to the entity system containing components.
	 * \param Task ID.
	 * \param The new task type.
	 */
	void set_task_type(EntitySystem&, tdt::uint, TASK_TYPE);

	/**
	 * Returns the task type of a given task.
	 * \param Reference to the entity system containing components.
	 * \param Task ID.
	 */
	TASK_TYPE get_task_type(EntitySystem&, tdt::uint);

	/**
	 * \brief Assigns a new task to an entity (by adding it to the task queue).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param ID of the task.
	 * \param If true, the task will be added to the fron of the task queue.
	 */
	void add_task(EntitySystem&, tdt::uint, tdt::uint, bool = false);

	/**
	 * \brief Creates a new task of a given tasks and returns it's ID.
	 * \param Reference to the entity system containing components.
	 * \param ID of the task's target (goto location, kill target etc.).
	 * \param Type of the task.
	 */
	tdt::uint create_task(EntitySystem&, tdt::uint, TASK_TYPE);

	/**
	 * \brief Destroys the TaskComponent of a given task, effectively stopping
	 *        it's completion.
	 * \param Reference to the entity system containing components.
	 * \param ID of the task.
	 */
	void cancel_task(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets a given task to a complete state.
	 * \param Reference to the entity system containing components.
	 * \param ID of the task.
	 */
	void set_complete(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if a given task is complete, false otherwise.
	 * \param Reference to the entity system containing components.
	 * \param ID of the task.
	 */
	bool is_complete(EntitySystem&, tdt::uint);
}