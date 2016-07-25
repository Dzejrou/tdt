#pragma once

#include <vector>
#include <string>
#include "GUIWindow.hpp"
namespace lpp
{
	class Script;
}
class Spellcaster;

/**
 * Class representing the spell selection window, allows the player to cast
 * registered (unlocked) spells.
 */
class SpellCastingWindow : public GUIWindow
{
	public:
		/**
		 * Constructor.
		 */
		SpellCastingWindow();

		/**
		 * Destructor.
		 */
		~SpellCastingWindow() = default;

		/**
		 * \brief Appends a table name to the vector of all spell tables.
		 * \param Name of the table to register.
		 */
		void register_spell(const std::string&);

		/**
		 * \brief Sets the caster instance used to cast the spells.
		 * \param The new spell caster.
		 */
		void set_caster(Spellcaster*);

		/**
		 * \brief Hides the "active" label.
		 */
		void deactivate_current_spell();

		/**
		 * \brief Returns a vector containing the names of all
		 *        unlocked spells. (Used for serialization.)
		 */
		const std::vector<std::string>& get_spells() const;

		/**
		 * \brief Removes all unlocked spell.
		 */
		void clear_spells();

		/**
		 * \brief Decrements selection_number_ by one and updates
		 *        the window.
		 */
		bool dec_selection();

		/**
		 * \brief Increments selection_number_ by one and updates
		 *        the window.
		 */
		bool inc_selection();

		/**
		 * \brief Marks a given spell as active.
		 * \param Position of the spell in the current view (0-3).
		 */
		void set_spell_active(int);

		/**
		 * \brief Casts a spell at a given
		 *        position in the roster.
		 * \param The position of the spell (1-4).
		 */
		void cast(int);
		
	protected:
		/**
		 * \brief Initializes the window and subscribes events.
		 */
		void init_() override;

	private:

		/**
		 * \brief Range checked buildings_ index access, returns the name
		 *        of the building at a given index or "UNKNOWN" if the
		 *        index is out of bounds.
		 * \param Index of the building in the buildings_ vector.
		 */
		const std::string& get_spell_(std::size_t);

		/**
		 * \brief Updates building names on the buttons.
		 */
		void update_selection_();

		/**
		 * Names of all registered buildings.
		 */
		std::vector<std::string> spells_;

		/**
		 * Number of the current rightmost selection.
		 * The window shows buildings with indices <selection_number_ - 3, selection_number_>.
		 */
		std::size_t selection_number_;

		/**
		 * Pointer to the scripting engine used for easier
		 * access.
		 */
		lpp::Script* script_;

		/**
		 * Does the actual spell casting once a spell is selected
		 * in this window.
		 */
		Spellcaster* caster_;

		/**
		 * Keeps track of the spell that is being currently casted.
		 */
		int curr_active_spell_;
};