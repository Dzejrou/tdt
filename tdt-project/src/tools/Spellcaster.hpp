#pragma once

#include <OGRE/Ogre.h>
#include <string>
#include <Typedefs.hpp>
#include <Enums.hpp>
namespace lpp
{
	class Script;
}
class SelectionBox;
class EntityPlacer;

/**
 * A utility class that manages the player's spell casting and
 * is usually called from input handlers and the spell casting window.
 */
class Spellcaster
{
	public:
		/**
		 * Constructor.
		 * \param The placer that is used for placing spells.
		 * \param Selector that is used for targeted spells.
		 */
		Spellcaster(EntityPlacer&, SelectionBox&);

		/**
		 * Destructor.
		 */
		~Spellcaster() = default;

		/**
		 * \brief Sets the type of the currently casted spell.
		 * \param The new spell type.
		 */
		void set_spell_type(SPELL_TYPE);

		/**
		 * \brief Returns the type of the currently casted spell.
		 */
		SPELL_TYPE get_spell_type() const;

		/**
		 * \brief Sets the name of the currently casted spell.
		 * \param The new name.
		 */
		void set_spell(const std::string&);

		/**
		 * \brief Returns the name of the currently casted spell.
		 */
		const std::string& get_spell() const;

		/**
		 * \brief Applies the effect of the currently casted spell.
		 * \param Optional mouse position parameter for positional spells.
		 */
		void cast(Ogre::Vector2 = Ogre::Vector2{});

		/**
		 * \brief Returns the type of the previously casted spell.
		 *        (Used if spells have sequential effect - like portals.)
		 */
		SPELL_TYPE get_last_spell_type() const;

		/**
		 * \brief Returns the name of the previously casted spell.
		 *        (Used if spells have sequential effect - like portals.)
		 */
		const std::string& get_last_spell() const;

		/**
		 * \brief Sets the ID of the entity created by the last spell.
		 *        (Used if spells have sequential effect - like portals.)
		 * \param The ID of the entity created.
		 */
		void set_last_spell_id(tdt::uint);

		/**
		 * \brief Returns the ID of the entity created by the last spell.
		 *        (Used if spells have sequential effect - like portals.)
		 */
		tdt::uint get_last_spell_id() const;

		/**
		 * \brief Returns true if this spellcaster is currently casting,
		 *        false otherwise.
		 */
		bool is_casting() const;

		/**
		 * \brief Immediately stops any cast being performed.
		 */
		void stop_casting();

	private:
		/**
		 * A structure representing a spell by containing
		 * it's type and name.
		 */
		struct SPELL
		{
			SPELL_TYPE type_;
			std::string spell_;
		};

		/**
		 * Used to place entities created by placing spell.
		 */
		EntityPlacer& placer_;

		/**
		 * Used to get selected targets for targeted spells.
		 */
		SelectionBox& selector_;

		/**
		 * Reference to the scripting engine used for easier calls
		 * to the spell functions.
		 */
		lpp::Script& script_;

		/**
		 * The spell that is currently being casted.
		 */
		SPELL curr_spell_;

		/**
		 * The spell that has been casted previously.
		 */
		SPELL last_spell_;

		/**
		 * ID of the entity created by a placing spell (if any).
		 */
		tdt::uint last_spell_id_;
};