#include "GUI.hpp"
#include "Game.hpp"
#include "Helpers.hpp"

GUI::GUI()
	: window_{nullptr}, curr_tool_{"TOOLS/MENU"}, game_{nullptr},
	  curr_tracked_entity_{Component::NO_ENTITY}
{ /* DUMMY BODY */ }

void GUI::init(Game* game)
{
	game_ = game;
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main_gui.layout");
	window_->setVisible(true);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);
	log_ = (CEGUI::Listbox*)window_->getChild("GAME_LOG/FRAME/LOG");
	clear_entity_view();

	/**
	 * TOOL SELECTION
	 */
	window_->getChild("TOOLS/TOOL_SELECTION/SPELL_SELECTION")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
				this->set_visible(curr_tool_, false);
				this->set_visible("TOOLS/SPELLS", true);
				curr_tool_ = "TOOLS/SPELLS";
			}
		);

	window_->getChild("TOOLS/TOOL_SELECTION/MENU_SELECTION")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
				this->set_visible(curr_tool_, false);
				this->set_visible("TOOLS/MENU", true);
				curr_tool_ = "TOOLS/MENU";
			}
		);

	window_->getChild("TOOLS/TOOL_SELECTION/BUILD_SELECTION")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
				this->set_visible(curr_tool_, false);
				this->set_visible("TOOLS/BUILD", true);
				curr_tool_ = "TOOLS/BUILD";
			}
		);

	/**
	 * MENU
	 */
	window_->getChild("TOOLS/MENU/FRAME/QUIT")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&](const CEGUI::EventArgs& args){
				game_->set_state(GAME_STATE::ENDED);
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/LOAD")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&](const CEGUI::EventArgs& args){
				list_directory("saves/*.lua", *((CEGUI::Listbox*)window_->getChild("GAME_LOG/FRAME/LOG")), true);
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/SAVE")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/OPTIONS")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/NEW_GAME")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/QUICK_SAVE")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&](const CEGUI::EventArgs& args){
				game_->game_serializer_->save_game(*game_, "quick_save");
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/QUICK_LOAD")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&](const CEGUI::EventArgs& args){
				game_->game_serializer_->load_game(*game_, "quick_save");
			}
		);

}

void GUI::set_visible(bool val)
{
	window_->setVisible(val);
}

void GUI::is_visible() const
{
	window_->isVisible();
}

void GUI::set_visible(const std::string& wname, bool val)
{
	window_->getChild(wname)->setVisible(val);
}

void GUI::is_visible(const std::string& wname) const
{
	window_->getChild(wname)->isVisible();
}

void GUI::clear_log()
{
	log_->resetList();
}

void GUI::print_to_log(const std::string& msg)
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
	log_->getVertScrollbar()->scrollForwardsByStep();
}

void GUI::set_tracked_entity(std::size_t id, EntitySystem& ents)
{
	curr_tracked_entity_ = id;
	auto view = window_->getChild("ENTITY_VIEW/FRAME");
	if(id == Component::NO_ENTITY)
		clear_entity_view();
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

std::size_t GUI::get_tracked_entity() const
{
	return curr_tracked_entity_;
}

void GUI::update_tracking(const std::string& label, const std::string& value)
{
	window_->getChild("ENTITY_VIEW/FRAME/" + label)->setText(value);
}

void GUI::clear_entity_view()
{
	auto view = window_->getChild("ENTITY_VIEW/FRAME");
	view->getChild("ID_VALUE")->setText("NONE");
	view->getChild("HP_VALUE")->setText("0 / 0");
	view->getChild("MANA_VALUE")->setText("0 / 0");
	view->getChild("EXP_VALUE")->setText("0 / 0");
	view->getChild("LVL_VALUE")->setText("0");
	view->getChild("GOLD_VALUE")->setText("0 / 0");
}

GUI& GUI::instance()
{
	static GUI inst{};
	return inst;
}

void GUI::set_log_history(std::size_t val)
{
	log_history_ = val;
}

std::size_t GUI::get_log_history() const
{
	return log_history_;
}

void GUI::list_directory(const std::string& dir, CEGUI::Listbox& box, bool strip_ext)
{
	box.resetList();

#ifdef WIN32
	HANDLE handle;
	WIN32_FIND_DATA fdata;

	handle = FindFirstFile(dir.c_str(), &fdata);
	std::string tmp;
	if(handle == INVALID_HANDLE_VALUE)
	{
		// TODO: Handle missing directory.
	}
	else
	{
		do
		{
			tmp = fdata.cFileName;
			if(strip_ext && tmp.substr(tmp.size() - 4, tmp.size() - 1) == ".lua")
				tmp = tmp.substr(0, tmp.size() - 4);
			box.addItem(new CEGUI::ListboxTextItem{tmp});
		}
		while(FindNextFile(handle, &fdata));
		FindClose(handle);
	}
#else
	// TODO: Use dirent on POSIX compliant systems.
#endif
}
