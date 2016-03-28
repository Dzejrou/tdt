#include "Spellcaster.hpp"
#include "Components.hpp"
#include "GUI.hpp"
#include "EntityPlacer.hpp"
#include "SelectionBox.hpp"
#include "lppscript/LppScript.hpp"

Spellcaster::Spellcaster(EntityPlacer& placer, SelectionBox& selector)
	: placer_{placer}, selector_{selector}, script_{lpp::Script::instance()},
	  curr_spell_{SPELL_TYPE::NONE, ""}, last_spell_{SPELL_TYPE::NONE, ""},
	  last_spell_id_{Component::NO_ENTITY}
{ /* DUMMY BODY */ }

void Spellcaster::set_spell_type(SPELL_TYPE val)
{
	if(!placer_.is_visible())
		curr_spell_.type_ = val;
}

SPELL_TYPE Spellcaster::get_spell_type() const
{
	return curr_spell_.type_;
}

void Spellcaster::set_spell(const std::string& val)
{
	script_.call<void>("game.spell.spells." + val + ".init");
	curr_spell_.spell_ = val;
}

const std::string& Spellcaster::get_spell() const
{
	return curr_spell_.spell_;
}

void Spellcaster::cast(Ogre::Vector2 mouse_position)
{
	auto& selected = selector_.get_selected_entities();
	if(curr_spell_.type_ == SPELL_TYPE::NONE ||
	  (curr_spell_.type_ == SPELL_TYPE::TARGETED && selected.size() != 1))
	{
		stop_casting();
		return;
	}
	else if(!script_.call<bool>("game.spell.spells." + curr_spell_.spell_ + ".pay_mana"))
	{
		GUI::instance().get_log().print("\\[ERROR\\] Not enough mana to cast that.");
		stop_casting();
		return;
	}

	switch(curr_spell_.type_)
	{
		case SPELL_TYPE::TARGETED:
			script_.call<void, tdt::uint>("game.spell.spells." + curr_spell_.spell_
										  + ".cast", selected[0]);
			break;
		case SPELL_TYPE::POSITIONAL:
			script_.call<void, tdt::real, tdt::real>("game.spell.spells." + curr_spell_.spell_
													 + ".cast", mouse_position.x, mouse_position.y);
			break;
		case SPELL_TYPE::PLACING:
		{
			auto id = placer_.place();
			script_.call<void, tdt::uint>("game.spell.spells." + curr_spell_.spell_ + ".cast", id);
			break;
		}
		case SPELL_TYPE::GLOBAL:
			script_.call<void>("game.spell.spells." + curr_spell_.spell_ + ".cast");
			break;
		default:
			break;
	}

	last_spell_ = curr_spell_;
}

SPELL_TYPE Spellcaster::get_last_spell_type() const
{
	return last_spell_.type_;
}

const std::string& Spellcaster::get_last_spell() const
{
	return last_spell_.spell_;
}

void Spellcaster::set_last_spell_id(tdt::uint val)
{
	last_spell_id_ = val;
}

tdt::uint Spellcaster::get_last_spell_id() const
{
	return last_spell_id_;
}

bool Spellcaster::is_casting() const
{
	return curr_spell_.type_ != SPELL_TYPE::NONE;
}

void Spellcaster::stop_casting()
{
	curr_spell_.type_ = SPELL_TYPE::NONE;
	placer_.set_visible(false);
	GUI::instance().get_spell_casting().deactivate_current_spell();
}
