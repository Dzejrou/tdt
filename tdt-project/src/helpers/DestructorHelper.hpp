#pragma once

#include <string>
#include <Components.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the destructor component.
 */
namespace DestructorHelper
{
	/**
	 * \brief Sets the name of the table that contains the "dtor" function
	 *        which get's called when a given entity is destroyed.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param The new blueprint table's name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the table that contains the "dtor" function
	 *        which get's called when a given entity is destroyed.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Destroys a given entity and if possible calls it's destructor.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param If true, the destructor won't be called.
	 * \param ID of the killer (if any).
	 */
	void destroy(EntitySystem&, tdt::uint, bool = false, tdt::uint = Component::NO_ENTITY);
}