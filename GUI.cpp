#include "GUI.hpp"
#include "Game.hpp"
#include "Helpers.hpp"
#include "EntitySystem.hpp"

GUI::GUI()
	: window_{nullptr}, curr_tool_{"TOOLS/MENU"}, game_{nullptr},
	  console_{}, tracker_{}, builder_{}, top_bar_{}
{ /* DUMMY BODY */ }

void GUI::init(Game* game)
{
	game_ = game;
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main_gui.layout");
	window_->setVisible(true);
	window_->getChild("SAVE_LOAD")->setVisible(false);
	window_->getChild("MESSAGE")->setVisible(false);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);
	console_.init(window_->getChild("DEVELOPER_CONSOLE"));
	tracker_.init(window_->getChild("ENTITY_VIEW"));
	log_.init(window_->getChild("GAME_LOG"));
	builder_.init(window_->getChild("TOOLS/BUILD"));
	builder_.set_placer(game_->placer_.get());
	top_bar_.init(window_->getChild("TOP_BAR"));

	/**
	 * TOOL SELECTION
	 */
	window_->getChild("TOOLS/TOOL_SELECTION/FRAME/SPELL_SELECTION")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&, this](const CEGUI::EventArgs& args){
			this->set_visible(curr_tool_, false);
			this->set_visible("TOOLS/SPELLS", true);
			curr_tool_ = "TOOLS/SPELLS";
		}
	);

	window_->getChild("TOOLS/TOOL_SELECTION/FRAME/MENU_SELECTION")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&, this](const CEGUI::EventArgs& args){
			this->set_visible(curr_tool_, false);
			this->set_visible("TOOLS/MENU", true);
			curr_tool_ = "TOOLS/MENU";
		}
	);

	window_->getChild("TOOLS/TOOL_SELECTION/FRAME/BUILD_SELECTION")->subscribeEvent(
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
			show_load_save_dialog("LOAD");
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/SAVE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&, this](const CEGUI::EventArgs& args){
			show_load_save_dialog("SAVE");
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/OPTIONS")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&, this](const CEGUI::EventArgs& args){
			// TODO:
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/RESEARCH")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&, this](const CEGUI::EventArgs& args){
			window_->getChild("RESEARCH")->setVisible(
				!window_->getChild("RESEARCH")->isVisible()
			);
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


	window_->getChild("SAVE_LOAD/FRAME/BUTT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs& args){
			if(window_->getChild("SAVE_LOAD/FRAME/BUTT")->getText() == "LOAD")
			{
				game_->game_serializer_->load_game(
					*game, window_->getChild("SAVE_LOAD/FRAME/INPUT")->getText().c_str()
				);
			}
			else
			{
				game_->game_serializer_->save_game(
					*game, window_->getChild("SAVE_LOAD/FRAME/INPUT")->getText().c_str()
				);
			}
		}
	);


	// When an save file is selected, it's name is copied to the editbox.
	window_->getChild("SAVE_LOAD/FRAME/ITEMS")->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		[&](const CEGUI::EventArgs& args){
			window_->getChild("SAVE_LOAD/FRAME/INPUT")->setText(
				((CEGUI::Listbox*)window_->getChild("SAVE_LOAD/FRAME/ITEMS"))->getFirstSelectedItem()->getText()
			);
		}
	);

	window_->getChild("SAVE_LOAD")->subscribeEvent(
		CEGUI::Window::EventKeyDown,
		[&](const CEGUI::EventArgs& args){
			if(((CEGUI::KeyEventArgs&)args).scancode == CEGUI::Key::Scan::Escape)
				window_->getChild("SAVE_LOAD")->setVisible(false);
		}
	);

	window_->getChild("SAVE_LOAD/FRAME")->subscribeEvent(
		CEGUI::FrameWindow::EventCloseClicked,
		[&](const CEGUI::EventArgs& args){
			window_->getChild("SAVE_LOAD")->setVisible(false);
		}
	);
}

void GUI::set_visible(bool val)
{
	window_->setVisible(val);
}

bool GUI::is_visible() const
{
	return window_->isVisible();
}

void GUI::set_visible(const std::string& wname, bool val)
{
	window_->getChild(wname)->setVisible(val);
}

bool GUI::is_visible(const std::string& wname) const
{
	return window_->getChild(wname)->isVisible();
}

GUI& GUI::instance()
{
	static GUI inst{};
	return inst;
}

void GUI::show_load_save_dialog(const std::string& type)
{
	auto dialog = window_->getChild("SAVE_LOAD");
	if(dialog->isVisible() && dialog->getChild("FRAME/BUTT")->getText() == type)
	{
		dialog->setVisible(false);
		return;
	}

	dialog->setVisible(true);
	dialog->getChild("FRAME")->setText(type);
	dialog->getChild("FRAME/BUTT")->setText(type);
	dialog->getChild("FRAME/INPUT")->setText("");
	list_directory("saves/*.lua",
				   *((CEGUI::Listbox*)dialog->getChild("FRAME/ITEMS")),
				   true);
}

CEGUI::Window* GUI::get_window(const std::string& name)
{
	return window_->getChild(name);
}

Console& GUI::get_console()
{
	return console_;
}

EntityTracker& GUI::get_tracker()
{
	return tracker_;
}

GameLog& GUI::get_log()
{
	return log_;
}

BuilderWindow& GUI::get_builder()
{
	return builder_;
}

TopBar& GUI::get_top_bar()
{
	return top_bar_;
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
