#include <fstream>
#include <tools/GameSerializer.hpp>
#include <tools/Camera.hpp>
#include <Game.hpp>
#include "OptionsWindow.hpp"
#include "GUI.hpp"

OptionsWindow::OptionsWindow()
	: render_window_{}, view_{}, renderer_{}, fullscreen_{}, key_names_{},
	  actions_{}, key_binds_{}, resolutions_{}, currently_binded_action_{KEY_BIND_ACTION::NONE}
{ /* DUMMY BODY */ }

void OptionsWindow::add_start_parameters(Ogre::RenderWindow* window, Ogre::Viewport* view, CEGUI::OgreRenderer* renderer)
{
	if(render_window_ != nullptr)
		return;

	render_window_ = window;
	view_ = view;
	renderer_ = renderer;
	
	fullscreen_ = window->isFullScreen();
	update_labels_();
}

bool OptionsWindow::key_pressed(CEGUI::Key::Scan key)
{
	if(is_visible())
	{
		if(currently_binded_action_ >= 1 &&
		   currently_binded_action_ < KEY_BIND_ACTION::COUNT &&
		   key_names_.find(key) != key_names_.end())
		{
			key_binds_[currently_binded_action_] = key;
			currently_binded_action_ = KEY_BIND_ACTION::NONE;
			update_labels_();
			return true;
		}
		else if(key != CEGUI::Key::Scan::Escape)
			return false; // Allows to close the button.
		else
			return true; // Avoids background key activity.
	}
	else
	{
		for(tdt::uint i = 0; i < KEY_BIND_ACTION::COUNT; ++i)
		{
			if(key_binds_[i] == key)
			{
				actions_[i]();
				return true;
			}
		}
		return false;
	}
}

void OptionsWindow::set_key_bind(KEY_BIND_ACTION::VAL action, CEGUI::Key::Scan key)
{
	key_binds_[action] = key;
	update_labels_();
}

void OptionsWindow::init_()
{
	key_names_[CEGUI::Key::Scan::A] = "A";
	key_names_[CEGUI::Key::Scan::B] = "B";
	key_names_[CEGUI::Key::Scan::C] = "C";
	key_names_[CEGUI::Key::Scan::D] = "D";
	key_names_[CEGUI::Key::Scan::E] = "E";
	key_names_[CEGUI::Key::Scan::F] = "F";
	key_names_[CEGUI::Key::Scan::G] = "G";
	key_names_[CEGUI::Key::Scan::H] = "H";
	key_names_[CEGUI::Key::Scan::I] = "I";
	key_names_[CEGUI::Key::Scan::J] = "J";
	key_names_[CEGUI::Key::Scan::K] = "K";
	key_names_[CEGUI::Key::Scan::L] = "L";
	key_names_[CEGUI::Key::Scan::M] = "M";
	key_names_[CEGUI::Key::Scan::N] = "N";
	key_names_[CEGUI::Key::Scan::O] = "O";
	key_names_[CEGUI::Key::Scan::P] = "P";
	key_names_[CEGUI::Key::Scan::Q] = "Q";
	key_names_[CEGUI::Key::Scan::R] = "R";
	key_names_[CEGUI::Key::Scan::S] = "S";
	key_names_[CEGUI::Key::Scan::T] = "T";
	key_names_[CEGUI::Key::Scan::U] = "U";
	key_names_[CEGUI::Key::Scan::V] = "V";
	key_names_[CEGUI::Key::Scan::W] = "W";
	key_names_[CEGUI::Key::Scan::X] = "X";
	key_names_[CEGUI::Key::Scan::Y] = "Y";
	key_names_[CEGUI::Key::Scan::Z] = "Z";
	key_names_[CEGUI::Key::Scan::Zero] = "0";
	key_names_[CEGUI::Key::Scan::One] = "1";
	key_names_[CEGUI::Key::Scan::Two] = "2";
	key_names_[CEGUI::Key::Scan::Three] = "3";
	key_names_[CEGUI::Key::Scan::Four] = "4";
	key_names_[CEGUI::Key::Scan::Five] = "5";
	key_names_[CEGUI::Key::Scan::Six] = "6";
	key_names_[CEGUI::Key::Scan::Seven] = "7";
	key_names_[CEGUI::Key::Scan::Eight] = "8";
	key_names_[CEGUI::Key::Scan::Nine] = "9";
	key_names_[CEGUI::Key::Scan::F1] = "F1";
	key_names_[CEGUI::Key::Scan::F2] = "F2";
	key_names_[CEGUI::Key::Scan::F3] = "F3";
	key_names_[CEGUI::Key::Scan::F4] = "F4";
	key_names_[CEGUI::Key::Scan::F5] = "F5";
	key_names_[CEGUI::Key::Scan::F6] = "F6";
	key_names_[CEGUI::Key::Scan::F7] = "F7";
	key_names_[CEGUI::Key::Scan::F8] = "F8";
	key_names_[CEGUI::Key::Scan::F9] = "F9";
	key_names_[CEGUI::Key::Scan::F10] = "F10";
	key_names_[CEGUI::Key::Scan::F11] = "F11";
	key_names_[CEGUI::Key::Scan::F12] = "F12";

	actions_[KEY_BIND_ACTION::SPELL_BUILD_1] = action::CAST_SPELL_1;
	actions_[KEY_BIND_ACTION::SPELL_BUILD_2] = action::CAST_SPELL_2;
	actions_[KEY_BIND_ACTION::SPELL_BUILD_3] = action::CAST_SPELL_3;
	actions_[KEY_BIND_ACTION::SPELL_BUILD_4] = action::CAST_SPELL_4;
	actions_[KEY_BIND_ACTION::NEXT] = action::NEXT;
	actions_[KEY_BIND_ACTION::PREV] = action::PREV;
	actions_[KEY_BIND_ACTION::SPELL_TAB] = action::SPELL_TAB;
	actions_[KEY_BIND_ACTION::BUILD_TAB] = action::BUILD_TAB;
	actions_[KEY_BIND_ACTION::MENU_TAB] = action::MENU_TAB;
	actions_[KEY_BIND_ACTION::RESET_CAMERA] = action::RESET_CAMERA;
	actions_[KEY_BIND_ACTION::QUICK_LOAD] = action::QUICK_LOAD;
	actions_[KEY_BIND_ACTION::QUICK_SAVE] = action::QUICK_SAVE;

	key_binds_[KEY_BIND_ACTION::SPELL_BUILD_1] = CEGUI::Key::Scan::One;
	key_binds_[KEY_BIND_ACTION::SPELL_BUILD_2] = CEGUI::Key::Scan::Two;
	key_binds_[KEY_BIND_ACTION::SPELL_BUILD_3] = CEGUI::Key::Scan::Three;
	key_binds_[KEY_BIND_ACTION::SPELL_BUILD_4] = CEGUI::Key::Scan::Four;
	key_binds_[KEY_BIND_ACTION::NEXT] = CEGUI::Key::Scan::Six;
	key_binds_[KEY_BIND_ACTION::PREV] = CEGUI::Key::Scan::Five;
	key_binds_[KEY_BIND_ACTION::SPELL_TAB] = CEGUI::Key::Scan::Seven;
	key_binds_[KEY_BIND_ACTION::BUILD_TAB] = CEGUI::Key::Scan::Eight;
	key_binds_[KEY_BIND_ACTION::MENU_TAB] = CEGUI::Key::Scan::Nine;
	key_binds_[KEY_BIND_ACTION::RESET_CAMERA] = CEGUI::Key::Scan::F4;
	key_binds_[KEY_BIND_ACTION::QUICK_LOAD] = CEGUI::Key::Scan::F10;
	key_binds_[KEY_BIND_ACTION::QUICK_SAVE] = CEGUI::Key::Scan::F11;

	resolutions_["1920x1080"] = std::make_tuple(1920, 1080);
	resolutions_["1366x768"] = std::make_tuple(1366, 768);
	resolutions_["1280x720"] = std::make_tuple(1280, 720);
	resolutions_["1024x768"] = std::make_tuple(1024, 768);
	resolutions_["800x600"] = std::make_tuple(800, 600);

	auto res = (CEGUI::Listbox*)window_->getChild("FRAME/RESOLUTION_LISTBOX");
	for(const auto& r : resolutions_)
	{
		CEGUI::ListboxTextItem* text = new CEGUI::ListboxTextItem{r.first};
		text->setTextColours(CEGUI::Colour{0.f, 1.f, 0.f});
		res->addItem(text);
	}

	auto mode = (CEGUI::Listbox*)window_->getChild("FRAME/WINDOW_MODE_LISTBOX");
	CEGUI::ListboxTextItem* windowed = new CEGUI::ListboxTextItem{"WINDOWED"};
	windowed->setTextColours(CEGUI::Colour{0.f, 1.f, 0.f});
	CEGUI::ListboxTextItem* fullscreen = new CEGUI::ListboxTextItem{"FULLSCREEN"};
	fullscreen->setTextColours(CEGUI::Colour{0.f, 1.f, 0.f});
	mode->addItem(windowed);
	mode->addItem(fullscreen);

	res->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		[this](const CEGUI::EventArgs&) -> bool {
			auto selected = ((CEGUI::Listbox*)window_->getChild("FRAME/RESOLUTION_LISTBOX"))->getFirstSelectedItem();
			if(selected)
				window_->getChild("FRAME/RESOLUTION_SELECTION_LABEL")->setText(selected->getText());
			return true;
		}
	);

	mode->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		[this](const CEGUI::EventArgs&) -> bool {
			auto selected = ((CEGUI::Listbox*)window_->getChild("FRAME/WINDOW_MODE_LISTBOX"))->getFirstSelectedItem();
			if(selected)
				window_->getChild("FRAME/WINDOW_MODE_SELECTION_LABEL")->setText(selected->getText());
			return true;
		}
	);

	width_ = view_->getActualWidth();
	height_ = view_->getActualHeight();

	window_->getChild("FRAME/APPLY_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			apply_();
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_BUILD_1_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::SPELL_BUILD_1;
			window_->getChild("FRAME/SPELL_BUILD_1_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_BUILD_2_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::SPELL_BUILD_2;
			window_->getChild("FRAME/SPELL_BUILD_2_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_BUILD_3_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::SPELL_BUILD_3;
			window_->getChild("FRAME/SPELL_BUILD_3_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
		
	);

	window_->getChild("FRAME/SPELL_BUILD_4_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::SPELL_BUILD_4;
			window_->getChild("FRAME/SPELL_BUILD_4_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/NEXT_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::NEXT;
			window_->getChild("FRAME/NEXT_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/PREV_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::PREV;
			window_->getChild("FRAME/PREV_BUTTON")->setText("PRESS KEY (a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/SPELL_TAB_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::SPELL_TAB;
			window_->getChild("FRAME/SPELL_TAB_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/BUILD_TAB_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::BUILD_TAB;
			window_->getChild("FRAME/BUILD_TAB_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/MENU_TAB_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::MENU_TAB;
			window_->getChild("FRAME/MENU_TAB_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/RESET_CAMERA_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::RESET_CAMERA;
			window_->getChild("FRAME/RESET_CAMERA_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/QUICK_LOAD_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::QUICK_LOAD;
			window_->getChild("FRAME/QUICK_LOAD_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);

	window_->getChild("FRAME/QUICK_SAVE_BUTTON")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			currently_binded_action_ = KEY_BIND_ACTION::QUICK_SAVE;
			window_->getChild("FRAME/QUICK_SAVE_BUTTON")->setText("PRESS KEY(a-z0-9F1-F12)");
			return true;
		}
	);
	
	update_fonts_();
	update_labels_();
}

void OptionsWindow::apply_()
{
	if(!window_ || !render_window_)
		return;

	auto sel_mode = ((CEGUI::Listbox*)window_->getChild("FRAME/WINDOW_MODE_LISTBOX"))->getFirstSelectedItem();
	if(sel_mode)
		fullscreen_ = sel_mode->getText() == "FULLSCREEN";

	auto sel_res = ((CEGUI::Listbox*)window_->getChild("FRAME/RESOLUTION_LISTBOX"))->getFirstSelectedItem();
	if(sel_res)
	{
		for(const auto& r : resolutions_)
		{
			if(r.first == sel_res->getText())
			{
				width_ = std::get<0>(r.second);
				height_ = std::get<1>(r.second);
			}
		}
	}

	render_window_->setFullscreen(fullscreen_, width_, height_);
	renderer_->setDisplaySize(CEGUI::Sizef{(float)view_->getActualWidth(), (float)view_->getActualHeight()});
	currently_binded_action_ = KEY_BIND_ACTION::NONE;

	/**
	 * This will make sure that key bindings are persistent.
	 */
	std::ofstream output{"keybinds.lua"};
	for(int i = 1; i < KEY_BIND_ACTION::COUNT; ++i)
	{
		output << "game.set_key_bind(" << std::to_string(i) << ", "
			   << std::to_string(key_binds_[i]) << ")\n";
	}
	output.flush();
	output.close();

	update_fonts_();
}

void OptionsWindow::update_labels_()
{
	if(!window_ || !view_)
		return;

	window_->getChild("FRAME/RESOLUTION_LABEL")->setText(
		"RESOLUTION (" + std::to_string(width_) + " x " + std::to_string(height_) + ")"
	);

	window_->getChild("FRAME/WINDOW_MODE_LABEL")->setText(
		std::string{"WINDOW MODE ("} + (fullscreen_ ? "FULLSCREEN" : "WINDOWED") + ")"	
	);

	window_->getChild("FRAME/SPELL_BUILD_1_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::SPELL_BUILD_1));
	window_->getChild("FRAME/SPELL_BUILD_2_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::SPELL_BUILD_2));
	window_->getChild("FRAME/SPELL_BUILD_3_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::SPELL_BUILD_3));
	window_->getChild("FRAME/SPELL_BUILD_4_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::SPELL_BUILD_4));
	window_->getChild("FRAME/NEXT_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::NEXT));
	window_->getChild("FRAME/PREV_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::PREV));
	window_->getChild("FRAME/SPELL_TAB_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::SPELL_TAB));
	window_->getChild("FRAME/BUILD_TAB_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::BUILD_TAB));
	window_->getChild("FRAME/MENU_TAB_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::MENU_TAB));
	window_->getChild("FRAME/RESET_CAMERA_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::RESET_CAMERA));
	window_->getChild("FRAME/QUICK_LOAD_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::QUICK_LOAD));
	window_->getChild("FRAME/QUICK_SAVE_BUTTON")->setText(get_key_bind_name_(KEY_BIND_ACTION::QUICK_SAVE));
}

void OptionsWindow::update_fonts_()
{
	auto win = GUI::instance().get_window();
	std::string font{};
	if(width_ <= 1024)
		font = "Inconsolata-8";
	else if(width_ <= 1280)
		font = "Inconsolata-10";
	else
		font = "Inconsolata-14";
	
	update_font_of_window_(win, font);

	// Update existing listbox items.
	auto list = (CEGUI::Listbox*)window_->getChild("FRAME/RESOLUTION_LISTBOX");
	for(tdt::uint i = 0; i < list->getItemCount(); ++i)
		((CEGUI::ListboxTextItem*)list->getListboxItemFromIndex(i))->setFont(font);

	list = (CEGUI::Listbox*)window_->getChild("FRAME/WINDOW_MODE_LISTBOX");
	for(tdt::uint i = 0; i < list->getItemCount(); ++i)
		((CEGUI::ListboxTextItem*)list->getListboxItemFromIndex(i))->setFont(font);

	list = (CEGUI::Listbox*)win->getChild("DEVELOPER_CONSOLE/CONSOLE_LOG");
	for(tdt::uint i = 0; i < list->getItemCount(); ++i)
		((CEGUI::ListboxTextItem*)list->getListboxItemFromIndex(i))->setFont(font);

	list = (CEGUI::Listbox*)win->getChild("ENTITY_MANAGER/ENTITY_LIST");
	for(tdt::uint i = 0; i < list->getItemCount(); ++i)
		((CEGUI::ListboxTextItem*)list->getListboxItemFromIndex(i))->setFont(font);

	list = (CEGUI::Listbox*)win->getChild("GAME_LOG/FRAME/LOG");
	for(tdt::uint i = 0; i < list->getItemCount(); ++i)
		((CEGUI::ListboxTextItem*)list->getListboxItemFromIndex(i))->setFont(font);

	// Game log and console log will be resized and leave empty
	// space below its items, so printing/actualizing will fix it.
	GUI::instance().get_log().print("");
	GUI::instance().get_console().print_text("");
}

void OptionsWindow::update_font_of_window_(CEGUI::Window* win, const std::string& font)
{
	win->setFont(font);
	for(tdt::uint i = 0; i < win->getChildCount(); ++i)
	{
		auto sub_win = win->getChildAtIdx(i);
		update_font_of_window_(sub_win, font);
	}
}

const std::string& OptionsWindow::get_key_bind_name_(KEY_BIND_ACTION::VAL action)
{
	static const std::string NO_KEY{"NOT SET"};

	if(action >= 1 && action < KEY_BIND_ACTION::COUNT)
	{
		auto name = key_names_.find(key_binds_[action]);
		if(name != key_names_.end())
			return name->second;
	}
	return NO_KEY;
}

void action::CAST_SPELL_1()
{
	if(GUI::instance().get_curr_tool() == "TOOLS/SPELLS")
		GUI::instance().get_spell_casting().cast(1);
	else if(GUI::instance().get_curr_tool() == "TOOLS/BUILD")
		GUI::instance().get_builder().build(1);
}

void action::CAST_SPELL_2()
{
	if(GUI::instance().get_curr_tool() == "TOOLS/SPELLS")
		GUI::instance().get_spell_casting().cast(2);
	else if(GUI::instance().get_curr_tool() == "TOOLS/BUILD")
		GUI::instance().get_builder().build(2);
}

void action::CAST_SPELL_3()
{
	if(GUI::instance().get_curr_tool() == "TOOLS/SPELLS")
		GUI::instance().get_spell_casting().cast(3);
	else if(GUI::instance().get_curr_tool() == "TOOLS/BUILD")
		GUI::instance().get_builder().build(3);
}

void action::CAST_SPELL_4()
{
	if(GUI::instance().get_curr_tool() == "TOOLS/SPELLS")
		GUI::instance().get_spell_casting().cast(4);
	else if(GUI::instance().get_curr_tool() == "TOOLS/BUILD")
		GUI::instance().get_builder().build(4);
}

void action::NEXT()
{
	if(GUI::instance().get_curr_tool() == "TOOLS/SPELLS")
		GUI::instance().get_spell_casting().inc_selection();
	else if(GUI::instance().get_curr_tool() == "TOOLS/BUILD")
		GUI::instance().get_builder().inc_selection();
}

void action::PREV()
{
	if(GUI::instance().get_curr_tool() == "TOOLS/SPELLS")
		GUI::instance().get_spell_casting().dec_selection();
	else if(GUI::instance().get_curr_tool() == "TOOLS/BUILD")
		GUI::instance().get_builder().dec_selection();
}

void action::SPELL_TAB()
{
	GUI::instance().set_curr_tool_visible(false);
	GUI::instance().set_curr_tool("TOOLS/SPELLS");
	GUI::instance().set_curr_tool_visible(true);
}

void action::BUILD_TAB()
{
	GUI::instance().set_curr_tool_visible(false);
	GUI::instance().set_curr_tool("TOOLS/BUILD");
	GUI::instance().set_curr_tool_visible(true);
}

void action::MENU_TAB()
{
	GUI::instance().set_curr_tool_visible(false);
	GUI::instance().set_curr_tool("TOOLS/MENU");
	GUI::instance().set_curr_tool_visible(true);
}

void action::RESET_CAMERA()
{
	auto game = GUI::instance().game_;
	if(game && game->main_cam_)
		game->main_cam_->reset();
}

void action::QUICK_SAVE()
{
	auto game = GUI::instance().game_;
	if(game)
		game->game_serializer_->save_game(*game, "quick_save");
}

void action::QUICK_LOAD()
{
	auto game = GUI::instance().game_;
	if(game)
		game->game_serializer_->save_game(*game, "quick_load");
}
