#pragma once

#include <deque>
#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the task handler component.
 */
namespace TaskHandlerHelper
{
	/**
	 * \brief Returns a reference to the task queue of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	std::deque<tdt::uint>& get_task_queue(EntitySystem&, tdt::uint);

	/**
	 * \brief Checks whether an entity can accept and complete a given task.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param ID of the task.
	 */
	bool task_possible(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Checks whether an entity can accept and complete a task of agiven task type.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param Task type to be tested.
	 */
	bool task_possible(EntitySystem&, tdt::uint, TASK_TYPE);

	/**
	 * \brief Cancels all tasks in a given entity's task queue.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	void clear_task_queue(EntitySystem&, tdt::uint);

	/**
	 * \brief Marks a given entity as available to accept tasks of a given task type.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param Type of the task to be added.
	 */
	void add_possible_task(EntitySystem&, tdt::uint, TASK_TYPE);

	/**
	 * \brief Marks a given entity as unavailable to accept tasks of a given task type.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param Type of the task to be deleted.
	 */
	void delete_possible_task(EntitySystem&, tdt::uint, TASK_TYPE);

	/**
	 * \brief Sets the handling blueprint of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The name of the new blueprint.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the handling blueprint of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);
}