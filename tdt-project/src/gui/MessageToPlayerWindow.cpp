#include <CEGUI/CEGUI.h>
#include <lppscript/LppScript.hpp>
#include "MessageToPlayerWindow.hpp"

MessageToPlayerWindow::MessageToPlayerWindow()
	: script_{lpp::Script::instance()},
	  ok_func_{}, yes_func_{}, no_func_{}
{ /* DUMMY BODY */ }

void MessageToPlayerWindow::show(const std::string& msg, const std::string& ok,
								 const std::string& yes, const std::string& no)
{
	window_->getChild("MESSAGE")->setText(msg);
	window_->setVisible(true);

	if(ok != "NONE")
	{
		ok_func_ = ok;
		window_->getChild("OK")->setVisible(true);
	}
	else
		window_->getChild("OK")->setVisible(false);

	if(yes != "NONE")
	{
		yes_func_ = yes;
		window_->getChild("YES")->setVisible(true);
	}
	else
		window_->getChild("YES")->setVisible(false);

	if(no != "NONE")
	{
		no_func_ = no;
		window_->getChild("NO")->setVisible(true);
	}
	else
		window_->getChild("NO")->setVisible(false);
}

void MessageToPlayerWindow::set_butt_label(const std::string& butt, const std::string& val)
{
	window_->getChild(butt)->setText(val);
}

void MessageToPlayerWindow::reset_butt_labels()
{
	window_->getChild("OK")->setText("OK");
	window_->getChild("YES")->setText("YES");
	window_->getChild("NO")->setText("NO");
}

void MessageToPlayerWindow::init_()
{
	window_->getChild("OK")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			script_.call<void>(ok_func_);
			window_->setVisible(false);
			reset_butt_labels();
			return true;
		}
	);

	window_->getChild("YES")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			script_.call<void>(yes_func_);
			window_->setVisible(false);
			reset_butt_labels();
			return true;
		}
	);

	window_->getChild("NO")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			script_.call<void>(no_func_);
			window_->setVisible(false);
			reset_butt_labels();
			return true;
		}
	);
}
