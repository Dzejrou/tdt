#include "SpellCastingWindow.hpp"
#include "GUI.hpp"
#include "Player.hpp"

SpellCastingWindow::SpellCastingWindow()
	: spells_{}, selection_number_{3}
{ /* DUMMY BODY */ }

void SpellCastingWindow::register_spell(const std::string& tname)
{
	for(const auto& s : spells_)
	{
		if(s == tname) // Prevents multiple entries of a spell.
			return;
	}
	spells_.push_back(tname);
	update_selection_();
}

void SpellCastingWindow::init_()
{
	update_selection_();
	script_ = lpp::Script::get_singleton_ptr();

	window_->getChild("FRAME/SPELL_1")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
		if(get_spell_(selection_number_ - 3) != "")
			cast_(get_spell_(selection_number_ - 3));
	}
	);

	window_->getChild("FRAME/SPELL_2")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
		if(get_spell_(selection_number_ - 2) != "")
			cast_(get_spell_(selection_number_ - 2));
	}
	);

	window_->getChild("FRAME/SPELL_3")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
		if(get_spell_(selection_number_ - 1) != "")
			cast_(get_spell_(selection_number_ - 1));
	}
	);

	window_->getChild("FRAME/SPELL_4")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
		if(get_spell_(selection_number_) != "")
			cast_(get_spell_(selection_number_));
	}
	);

	window_->getChild("FRAME/LEFT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&SpellCastingWindow::dec_selection_, this)
	);

	window_->getChild("FRAME/RIGHT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&SpellCastingWindow::inc_selection_, this)
	);
}

void SpellCastingWindow::cast_(const std::string& name)
{
	std::size_t price = script_->get<std::size_t>("game.spell.spells." + name + ".price");
	if(Player::instance().sub_mana(price))
		script_->call<void, std::size_t>("game.spell.spells." + name + ".cast", 0 /* DUMMY VARIABLE */);
}

void SpellCastingWindow::dec_selection_()
{
	if(selection_number_ > 3)
	{
		--selection_number_;
		update_selection_();
	}
}

void SpellCastingWindow::inc_selection_()
{
	if(spells_.size() > 4 && selection_number_ < spells_.size() - 1)
	{
		++selection_number_;
		update_selection_();
	}
}

const std::string& SpellCastingWindow::get_spell_(std::size_t index)
{
	static std::string NO_SPELL{""};

	if(index >= 0 && index < spells_.size())
		return spells_[index];
	else
		return NO_SPELL;
}

void SpellCastingWindow::update_selection_()
{
	window_->getChild("FRAME/SPELL_1")->setText(get_spell_(selection_number_ - 3));
	window_->getChild("FRAME/SPELL_2")->setText(get_spell_(selection_number_ - 2));
	window_->getChild("FRAME/SPELL_3")->setText(get_spell_(selection_number_ - 1));
	window_->getChild("FRAME/SPELL_4")->setText(get_spell_(selection_number_));
}
