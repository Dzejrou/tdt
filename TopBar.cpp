#include "TopBar.hpp"
#include "Player.hpp"

TopBar::TopBar()
	: tdelta_{0.f}
{ /* DUMMY BODY */ }

void TopBar::update_time(Ogre::Real delta)
{
	tdelta_ += delta;
	if(tdelta_ > 1.f)
	{
		tdelta_ = 0.f;
		time_t now = time(0);
		struct tm* tstruct = localtime(&now);
		char buf[80];
		std::strftime(buf, sizeof(buf), "%HH - %MM - %SS", tstruct);
		window_->getChild("FRAME/TIME")->setText(buf);
	}
}

void TopBar::update_label(const std::string& label, const std::string& val)
{
	window_->getChild("FRAME/" + label)->setText(val);
}

void TopBar::init_()
{
	update_label("GOLD_VALUE", std::to_string(Player::instance().get_gold()));
	update_label("MANA_VALUE", std::to_string(Player::instance().get_mana()));
}
