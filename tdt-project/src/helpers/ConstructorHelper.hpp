#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with constructor component
 * management.
 */
namespace ConstructorHelper
{
	/**
	 * \brief Sets the name of the blueprint table that handles the construction
	 *        of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the blueprint table that handles the construction
	 *        of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Calls the blueprint table that handles the construction
	 *        of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	void call(EntitySystem&, tdt::uint);
}