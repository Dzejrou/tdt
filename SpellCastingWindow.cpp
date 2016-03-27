#include "SpellCastingWindow.hpp"
#include "GUI.hpp"
#include "Player.hpp"

SpellCastingWindow::SpellCastingWindow()
	: spells_{}, selection_number_{3}, curr_active_spell_{-1}
{ /* DUMMY BODY */ }

void SpellCastingWindow::register_spell(const std::string& name)
{
	for(const auto& s : spells_)
	{
		if(s == name) // Prevents multiple entries of a spell.
			return;
	}
	spells_.push_back(name);
	update_selection_();
}

void SpellCastingWindow::set_caster(Spellcaster* caster)
{
	caster_ = caster;
}

void SpellCastingWindow::deactivate_current_spell()
{
	window_->getChild("FRAME/ACTIVE")->setVisible(false);
	curr_active_spell_ = -1;
}

const std::vector<std::string>& SpellCastingWindow::get_spells() const
{
	return spells_;
}

void SpellCastingWindow::clear_spells()
{
	spells_.clear();
	selection_number_ = 3;
	curr_active_spell_ = -1;
	update_selection_();

	if(caster_)
		caster_->stop_casting();
}

void SpellCastingWindow::cast(int spell_num)
{
	if(spell_num < 1 || spell_num > 4)
		return;
	if(caster_ && get_spell_(selection_number_ - (4 - spell_num)) != "")
	{
		caster_->set_spell(get_spell_(selection_number_ - (4 - spell_num)));
		curr_active_spell_ = spell_num - 1;
		update_selection_();
	}
}

void SpellCastingWindow::init_()
{
	update_selection_();
	script_ = lpp::Script::get_singleton_ptr();

	window_->getChild("FRAME/SPELL_1")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			cast(1);
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_2")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			cast(2);
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_3")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			cast(3);
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_4")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			cast(4);
			return true;
		}
	);

	window_->getChild("FRAME/LEFT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			dec_selection();
			return true;
		}
	);

	window_->getChild("FRAME/RIGHT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			inc_selection();
			return true;
		}
	);
}

bool SpellCastingWindow::dec_selection()
{
	if(selection_number_ > 3)
	{
		--selection_number_;

		if(curr_active_spell_ != -1)
			++curr_active_spell_;
		update_selection_();
	}

	return true;
}

bool SpellCastingWindow::inc_selection()
{
	if(spells_.size() > 4 && selection_number_ < spells_.size() - 1)
	{
		++selection_number_;

		if(curr_active_spell_ != -1)
			--curr_active_spell_;
		update_selection_();
	}
	return true;
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

	auto* active = window_->getChild("FRAME/ACTIVE");
	if(curr_active_spell_ >= 0 && curr_active_spell_ <= 3)
		active->setVisible(true);
	switch(curr_active_spell_)
	{
		case 0:
			active->setPosition(CEGUI::UVector2{CEGUI::UDim{0.f, 0.f}, CEGUI::UDim{0.4f, 0.f}});
			break;
		case 1:
			active->setPosition(CEGUI::UVector2{CEGUI::UDim{0.25f, 0.f}, CEGUI::UDim{0.4f, 0.f}});
			break;
		case 2:
			active->setPosition(CEGUI::UVector2{CEGUI::UDim{0.5f, 0.f}, CEGUI::UDim{0.4f, 0.f}});
			break;
		case 3:
			active->setPosition(CEGUI::UVector2{CEGUI::UDim{0.75f, 0.f}, CEGUI::UDim{0.4f, 0.f}});
			break;
		default:
			active->setVisible(false);
			break;
	}
}

void SpellCastingWindow::set_spell_active(int val)
{
	curr_active_spell_ = val;
}
