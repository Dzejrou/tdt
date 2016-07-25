#include <CEGUI/CEGUI.h>
#include "GameLog.hpp"

GameLog::GameLog()
	: log_history_{60}, log_{}
{ /* DUMMY BODY */ }

void GameLog::clear()
{
	log_->resetList();
}

void GameLog::print(const std::string& msg)
{
	CEGUI::ListboxTextItem* text;
	if(log_->getItemCount() >= log_history_)
	{
		text = (CEGUI::ListboxTextItem*)log_->getListboxItemFromIndex(0);
		text->setAutoDeleted(false);
		log_->removeItem(text);
		text->setAutoDeleted(true);
		text->setText(msg);
	}
	else
		text = new CEGUI::ListboxTextItem(msg);
	text->setTextColours(CEGUI::Colour{0.f, 1.f, 0.f});
	log_->addItem(text);
	log_->getVertScrollbar()->setScrollPosition(log_->getVertScrollbar()->getDocumentSize());
}

void GameLog::set_history(tdt::uint val)
{
	log_history_ = val;
}

tdt::uint GameLog::get_history() const
{
	return log_history_;
}

void GameLog::init_()
{
	log_ = (CEGUI::Listbox*)window_->getChild("FRAME/LOG");
}
