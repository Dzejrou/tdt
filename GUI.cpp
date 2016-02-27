#include "GUI.hpp"
#include "Game.hpp"
#include "Helpers.hpp"
#include "EntitySystem.hpp"

GUI::GUI()
	: window_{nullptr}, curr_tool_{"TOOLS/MENU"}, game_{nullptr},
	  console_{}, tracker_{}, builder_{}, top_bar_{},
	  research_{}, spell_casting_{}, menu_{}
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
	tracker_.init_upgrade_butt(game->entity_system_.get());
	log_.init(window_->getChild("GAME_LOG"));
	builder_.init(window_->getChild("TOOLS/BUILD"));
	builder_.set_placer(game_->placer_.get());
	top_bar_.init(window_->getChild("TOP_BAR"));
	spell_casting_.init(window_->getChild("TOOLS/SPELLS"));

	/**
	 * MAIN MENU
	 */
	auto* menu = window_->getChild("MAIN_MENU");
	menu->setVisible(true);
	window_->getChild("TOOLS")->setVisible(false);
	window_->getChild("ENTITY_VIEW")->setVisible(false);
	window_->getChild("GAME_LOG")->setVisible(false);
	
	menu->getChild("LOAD_GAME")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			show_load_save_dialog("LOAD");
			window_->getChild("SAVE_LOAD")->activate();
			return true;
		}
	);

	auto* new_game = menu->getChild("NEW_GAME_DIALOG");
	menu->getChild("NEW_GAME")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[new_game](const CEGUI::EventArgs&) -> bool {
			new_game->setVisible(true);
			return true;
		}
	);

	menu->getChild("OPTIONS")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[](const CEGUI::EventArgs&) -> bool {
			// TODO:
			return true;
		}
	);

	menu->getChild("QUIT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			game_->set_state(GAME_STATE::ENDED);
			return true;
		}
	);

	new_game->getChild("16x16")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[new_game](const CEGUI::EventArgs&) -> bool {
			new_game->getChild("WIDTH_INPUT")->setText("16");
			new_game->getChild("HEIGHT_INPUT")->setText("16");
			return true;
		}
	);

	new_game->getChild("32x32")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[new_game](const CEGUI::EventArgs&) -> bool {
			new_game->getChild("WIDTH_INPUT")->setText("32");
			new_game->getChild("HEIGHT_INPUT")->setText("32");
			return true;
		}
	);

	new_game->getChild("64x64")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[new_game](const CEGUI::EventArgs&) -> bool {
			new_game->getChild("WIDTH_INPUT")->setText("64");
			new_game->getChild("HEIGHT_INPUT")->setText("64");
			return true;
		}
	);

	new_game->getChild("CREATE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this, new_game, menu](const CEGUI::EventArgs&) -> bool {
			try
			{
				// Converts text from edit boxes to uints, sadly no implicit conversion
				// from CEGUI::String to std::string exists :(.
				std::size_t w{
					(std::size_t)std::stoul(new_game->getChild("WIDTH_INPUT")->getText().c_str())
				};
				std::size_t h{
					(std::size_t)std::stoul(new_game->getChild("HEIGHT_INPUT")->getText().c_str())
				};

				if(w >= 10 && w <= 256 && h >= 10 && h <= 256)
					game_->new_game(w, h);
				else
					throw std::out_of_range{"(10, 1024)"};
			}
			catch(std::invalid_argument&)
			{
				log_.print("[ERROR] Invalid new game dimensions.");
			}
			catch(std::out_of_range&)
			{
				log_.print("[ERROR] Game dimensions out of range.");
			}

			new_game->getChild("WIDTH_INPUT")->setText("");
			new_game->getChild("HEIGHT_INPUT")->setText("");
			new_game->setVisible(false);
			menu->setVisible(false);
			window_->getChild("TOOLS")->setVisible(true);
			window_->getChild("ENTITY_VIEW")->setVisible(true);
			window_->getChild("GAME_LOG")->setVisible(true);
			game_->set_state(GAME_STATE::RUNNING);
			return true;
		}
	);

	/**
	 * TOOL SELECTION
	 */
	window_->getChild("TOOLS/TOOL_SELECTION/FRAME/SPELL_SELECTION")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			set_visible(curr_tool_, false);
			set_visible("TOOLS/SPELLS", true);
			curr_tool_ = "TOOLS/SPELLS";
			return true;
		}
	);

	window_->getChild("TOOLS/TOOL_SELECTION/FRAME/MENU_SELECTION")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			set_visible(curr_tool_, false);
			set_visible("TOOLS/MENU", true);
			curr_tool_ = "TOOLS/MENU";
			return true;
		}
	);

	window_->getChild("TOOLS/TOOL_SELECTION/FRAME/BUILD_SELECTION")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			set_visible(curr_tool_, false);
			set_visible("TOOLS/BUILD", true);
			curr_tool_ = "TOOLS/BUILD";
			return true;
		}
	);

	/**
	 * MENU
	 */
	window_->getChild("TOOLS/MENU/FRAME/QUIT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			game_->set_state(GAME_STATE::ENDED);
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/LOAD")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			show_load_save_dialog("LOAD");
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/SAVE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			show_load_save_dialog("SAVE");
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/OPTIONS")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			// TODO:
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/RESEARCH")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("RESEARCH")->setVisible(
				!window_->getChild("RESEARCH")->isVisible()
			);
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/MAIN_MENU")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("MAIN_MENU")->setVisible(true);
			window_->getChild("TOOLS")->setVisible(false);
			window_->getChild("ENTITY_VIEW")->setVisible(false);
			window_->getChild("GAME_LOG")->setVisible(false);
			game_->set_state(GAME_STATE::MENU);
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/QUICK_SAVE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			game_->game_serializer_->save_game(*game_, "quick_save");
			return true;
		}
	);

	window_->getChild("TOOLS/MENU/FRAME/QUICK_LOAD")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			game_->game_serializer_->load_game(*game_, "quick_save");
			return true;
		}
	);


	window_->getChild("SAVE_LOAD/FRAME/BUTT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			if(window_->getChild("SAVE_LOAD/FRAME/BUTT")->getText() == "LOAD")
			{
				game_->game_serializer_->load_game(
					*game_, window_->getChild("SAVE_LOAD/FRAME/INPUT")->getText().c_str()
				);

				// In case this was called from main menu.
				window_->getChild("MAIN_MENU")->setVisible(false);
				window_->getChild("TOOLS")->setVisible(true);
				window_->getChild("ENTITY_VIEW")->setVisible(true);
				window_->getChild("GAME_LOG")->setVisible(true);
				game_->set_state(GAME_STATE::RUNNING);
			}
			else
			{
				game_->game_serializer_->save_game(
					*game_, window_->getChild("SAVE_LOAD/FRAME/INPUT")->getText().c_str()
				);
			}
			window_->getChild("SAVE_LOAD")->setVisible(false);
			return true;
		}
	);


	// When an save file is selected, it's name is copied to the editbox.
	window_->getChild("SAVE_LOAD/FRAME/ITEMS")->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("SAVE_LOAD/FRAME/INPUT")->setText(
				((CEGUI::Listbox*)window_->getChild("SAVE_LOAD/FRAME/ITEMS"))->getFirstSelectedItem()->getText()
			);
			return true;
		}
	);

	window_->getChild("SAVE_LOAD/FRAME")->subscribeEvent(
		CEGUI::FrameWindow::EventCloseClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("SAVE_LOAD")->setVisible(false);
			return true;
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

ResearchWindow& GUI::get_research()
{
	return research_;
}

SpellCastingWindow& GUI::get_spell_casting()
{
	return spell_casting_;
}

bool GUI::escape_pressed()
{
	bool res{false};

	// Note: Console and EntityCreator have their own hotkeys.
	std::string sub_windows[] {
		"MAIN_MENU/NEW_GAME_DIALOG",
		"RESEARCH", "SAVE_LOAD"
	};

	for(const auto& sub_window : sub_windows)
	{
		if(window_->getChild(sub_window)->isVisible())
		{
			window_->getChild(sub_window)->setVisible(false);
			res = true;
		}
	}

	return res;
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
			else if(strip_ext && tmp.substr(tmp.size() - 5, tmp.size() - 1) == ".lua~")
				continue;
			box.addItem(new CEGUI::ListboxTextItem{tmp});
		}
		while(FindNextFile(handle, &fdata));
		FindClose(handle);
	}
#else
	// TODO: Use dirent on POSIX compliant systems.
#endif
}
