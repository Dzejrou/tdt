#include <CEGUI/CEGUI.h>
#include <helpers/Helpers.hpp>
#include <systems/EntitySystem.hpp>
#include <Components.hpp>
#include "EntityTracker.hpp"

EntityTracker::EntityTracker()
	: curr_tracked_entity_{Component::NO_ENTITY}, entities_{nullptr}
{ /* DUMMY BODY */ }

void EntityTracker::set_tracked_entity(tdt::uint id, EntitySystem& ents)
{
	curr_tracked_entity_ = id;
	auto view = window_->getChild("FRAME");
	view->getChild("UPGRADE")->setVisible(false);
	view->getChild("ACTIVATE")->setVisible(false);
	view->getChild("DEACTIVATE")->setVisible(false);
	view->getChild("GOLD_TO_EXP")->setVisible(false);
	if(id == Component::NO_ENTITY)
		clear();
	else
	{
		view->getChild("ID_VALUE")->setText(std::to_string(id));
		auto health = ents.get_component<HealthComponent>(id);
		if(health)
			update_tracking("HP_VALUE", std::to_string(health->curr_hp) + " / " + std::to_string(health->max_hp));

		auto name = ents.get_component<NameComponent>(id);
		if(name)
			update_tracking("NAME_VALUE", name->name);
		
		auto mana = ents.get_component<ManaComponent>(id);
		if(mana)
			update_tracking("MANA_VALUE", std::to_string(mana->curr_mana) + " / " + std::to_string(mana->max_mana));

		auto upgrade = ents.get_component<UpgradeComponent>(id);
		if(upgrade)
		{
			update_tracking("EXP_VALUE", std::to_string(upgrade->experience) + " / " + std::to_string(upgrade->exp_needed));
			update_tracking("LVL_VALUE", std::to_string(upgrade->level) + " / " + std::to_string(upgrade->level_cap));
			if(upgrade->experience >= upgrade->exp_needed)
				view->getChild("UPGRADE")->setVisible(true);
			else
				view->getChild("GOLD_TO_EXP")->setVisible(true);
		}

		auto faction = ents.get_component<FactionComponent>(id);
		if(faction)
		{
			update_tracking("FACTION_VALUE", FactionHelper::get_faction_name(ents, id));
			if(faction->faction == FACTION::FRIENDLY)
				view->getChild("DELETE")->setVisible(true);
		}

		auto gold = ents.get_component<GoldComponent>(id);
		if(gold)
			update_tracking("GOLD_VALUE", std::to_string(gold->curr_amount) + " / " + std::to_string(gold->max_amount));

		auto activation = ents.get_component<ActivationComponent>(id);
		if(activation)
		{
			if(activation->activated)
				view->getChild("DEACTIVATE")->setVisible(true);
			else
				view->getChild("ACTIVATE")->setVisible(true);
		}
	}
}

tdt::uint EntityTracker::get_tracked_entity() const
{
	return curr_tracked_entity_;
}

void EntityTracker::update_tracking(const std::string& label, const std::string& value)
{
	if(curr_tracked_entity_ != Component::NO_ENTITY)
		window_->getChild("FRAME/" + label)->setText(value);
}

void EntityTracker::clear()
{
	auto view = window_->getChild("FRAME");
	view->getChild("ID_VALUE")->setText("NONE");
	view->getChild("NAME_VALUE")->setText("UNKNOWN");
	view->getChild("HP_VALUE")->setText("0 / 0");
	view->getChild("MANA_VALUE")->setText("0 / 0");
	view->getChild("EXP_VALUE")->setText("0 / 0");
	view->getChild("LVL_VALUE")->setText("0");
	view->getChild("FACTION_VALUE")->setText("NEUTRAL");
	view->getChild("GOLD_VALUE")->setText("0 / 0");
	view->getChild("DELETE")->setVisible(false);
	view->getChild("UPGRADE")->setVisible(false);
	view->getChild("ACTIVATE")->setVisible(false);
	view->getChild("DEACTIVATE")->setVisible(false);
	view->getChild("GOLD_TO_EXP")->setVisible(false);
	curr_tracked_entity_ = Component::NO_ENTITY;
}

void EntityTracker::init_upgrade_butt(EntitySystem* ents)
{
	if(!window_ || !ents)
		return;

	// Upgrades the entity to a new level.
	window_->getChild("FRAME/UPGRADE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[ents, this](const CEGUI::EventArgs&) -> bool {
			UpgradeHelper::upgrade(*ents, curr_tracked_entity_);
			window_->getChild("FRAME/UPGRADE")->setVisible(false);
			if(UpgradeHelper::get_level(*ents, curr_tracked_entity_)
			   < UpgradeHelper::get_level_cap(*ents, curr_tracked_entity_))
			{
				window_->getChild("FRAME/GOLD_TO_EXP")->setVisible(true);
			}
			return true;
		}
	);

	// Upgrades the entity to a new level.
	window_->getChild("FRAME/GOLD_TO_EXP")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[ents, this](const CEGUI::EventArgs&) -> bool {
			if(Player::instance().sub_gold(50))
				UpgradeHelper::add_experience(*ents, curr_tracked_entity_, 10);
			if(UpgradeHelper::can_level_up(*ents, curr_tracked_entity_))
			{
				window_->getChild("FRAME/UPGRADE")->setVisible(true);
				window_->getChild("FRAME/GOLD_TO_EXP")->setVisible(false);
			}
			return true;
		}
	);

	// Deletes the entity and refunds a quarter of it's cost.
	window_->getChild("FRAME/DELETE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[ents, this](const CEGUI::EventArgs&) -> bool {
			Player::instance().add_gold(PriceHelper::get_price(*ents, curr_tracked_entity_) / 4);
			DestructorHelper::destroy(*ents, curr_tracked_entity_, false);
			return true;
		}
	);

	// Activates an entity with an activation component.
	window_->getChild("FRAME/ACTIVATE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[ents, this](const CEGUI::EventArgs&) -> bool {
			ActivationHelper::activate(*ents, curr_tracked_entity_);
			window_->getChild("FRAME/DEACTIVATE")->setVisible(true);
			window_->getChild("FRAME/ACTIVATE")->setVisible(false);
			return true;
		}
	);

	// Deactivates an entity with an activation component.
	window_->getChild("FRAME/DEACTIVATE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[ents, this](const CEGUI::EventArgs&) -> bool {
			ActivationHelper::deactivate(*ents, curr_tracked_entity_);
			window_->getChild("FRAME/ACTIVATE")->setVisible(true);
			window_->getChild("FRAME/DEACTIVATE")->setVisible(false);
			return true;
		}
	);
}

void EntityTracker::show_upgrade_butt(bool val)
{
	window_->getChild("FRAME/UPGRADE")->setVisible(val);
}

void EntityTracker::init_()
{
	clear();
}
