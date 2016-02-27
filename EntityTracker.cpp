#include "EntityTracker.hpp"
#include "Components.hpp"
#include "Helpers.hpp"

EntityTracker::EntityTracker()
	: curr_tracked_entity_{Component::NO_ENTITY}, entities_{nullptr}
{ /* DUMMY BODY */ }

void EntityTracker::set_tracked_entity(std::size_t id, EntitySystem& ents)
{
	curr_tracked_entity_ = id;
	auto view = window_->getChild("FRAME");
	view->getChild("UPGRADE")->setVisible(false);
	if(id == Component::NO_ENTITY)
		clear();
	else
	{
		view->getChild("ID_VALUE")->setText(std::to_string(id));
		auto health = ents.get_component<HealthComponent>(id);
		if(health)
			update_tracking("HP_VALUE", std::to_string(health->curr_hp) + " / " + std::to_string(health->max_hp));
		
		// TODO: MANA
		// TODO: EXP
		// TODO: LVL

		auto gold = ents.get_component<GoldComponent>(id);
		if(gold)
			update_tracking("GOLD_VALUE", std::to_string(gold->curr_amount) + " / " + std::to_string(gold->max_amount));
	}
}

std::size_t EntityTracker::get_tracked_entity() const
{
	return curr_tracked_entity_;
}

void EntityTracker::update_tracking(const std::string& label, const std::string& value)
{
	window_->getChild("FRAME/" + label)->setText(value);
}

void EntityTracker::clear()
{
	auto view = window_->getChild("FRAME");
	view->getChild("ID_VALUE")->setText("NONE");
	view->getChild("HP_VALUE")->setText("0 / 0");
	view->getChild("MANA_VALUE")->setText("0 / 0");
	view->getChild("EXP_VALUE")->setText("0 / 0");
	view->getChild("LVL_VALUE")->setText("0");
	view->getChild("GOLD_VALUE")->setText("0 / 0");
}

void EntityTracker::init_upgrade_butt(EntitySystem* ents)
{
	if(!window_)
		return;

	window_->getChild("FRAME/UPGRADE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[ents, this](const CEGUI::EventArgs&) -> bool {
			UpgradeHelper::upgrade(*ents, curr_tracked_entity_);
			return true;
		}
	);
}

void EntityTracker::init_()
{
	clear();
}
