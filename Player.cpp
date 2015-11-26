#include "Player.hpp"
#include "GUI.hpp"
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "Components.hpp"
#include "Util.hpp"
#include <limits>

void Player::init(EntitySystem* ents)
{
	entities_ = ents;
}

Player::Player()
	: gold_{1000}, mana_{100}, units_max_{0}, units_curr_{0},
	  uint_max_{std::numeric_limits<std::size_t>::max()}
{ /* DUMMY BODY */ }

void Player::add_gold(std::size_t val)
{
	if(gold_ < uint_max_ - val)
	{
		gold_ += val;
		GUI::instance().get_top_bar().update_label("GOLD_VALUE", std::to_string(gold_));
	}
}

bool Player::sub_gold(std::size_t val)
{
	if(gold_ >= val)
	{
		if(entities_)
		{ // Find first gold vault and remove gold from it, do not register the transaction though.
			util::IS_GOLD_VAULT cond{*entities_};
			for(auto& ent : entities_->get_component_container<GoldComponent>())
			{
				if(cond(ent.first))
				{ // TODO: Update if the vault was tracked ^^.
					GoldHelper::sub_gold(*entities_, ent.first, val, false);
					break; // Sub from first vault only.
				}
			}
		}
		gold_ -= val;
		GUI::instance().get_top_bar().update_label("GOLD_VALUE", std::to_string(gold_));
		return true;
	}
	else
		return false;
}

void Player::add_mana(std::size_t val)
{
	if(mana_ < uint_max_ - val)
	{
		mana_ += val;
		GUI::instance().get_top_bar().update_label("MANA_VALUE", std::to_string(mana_));
	}
}

bool Player::sub_mana(std::size_t val)
{
	if(mana_ >= val)
	{
		mana_ -= val;
		GUI::instance().get_top_bar().update_label("MANA_VALUE", std::to_string(mana_));
		return true;
	}
	else
		return false;
}

void Player::add_max_unit(std::size_t val)
{
	if(units_max_ < uint_max_ - val)
	{
		units_max_ += val;
		GUI::instance().get_top_bar().update_label("UNITS_VALUE", std::to_string(units_curr_)
												   + " / " + std::to_string(units_max_));
	}
}

bool Player::sub_max_unit(std::size_t val)
{
	if(units_max_ >= val)
	{
		units_max_ -= val;
		GUI::instance().get_top_bar().update_label("UNITS_VALUE", std::to_string(units_curr_)
												   + " / " + std::to_string(units_max_));
		return true;
	}
	else
		return false;
}

void Player::add_curr_unit(std::size_t val)
{
	if(units_curr_ < uint_max_ - val)
	{
		units_curr_ += val;
		GUI::instance().get_top_bar().update_label("UNITS_VALUE", std::to_string(units_curr_)
												   + " / " + std::to_string(units_max_));
	}
}

bool Player::sub_curr_unit(std::size_t val)
{
	if(units_curr_ >= val)
	{
		units_curr_ -= val;
		GUI::instance().get_top_bar().update_label("UNITS_VALUE", std::to_string(units_curr_)
												   + " / " + std::to_string(units_max_));
		return true;
	}
	else
		return false;
}

std::size_t Player::get_gold() const
{
	return gold_;
}

std::size_t Player::get_mana() const
{
	return mana_;
}
