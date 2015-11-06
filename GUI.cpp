#include "GUI.hpp"
#include "Game.hpp"

GUI::GUI(Game& game)
	: window_{nullptr}, curr_tool_{"TOOLS/MENU"}, game_{game}
{ /* DUMMY BODY */ }

void GUI::init()
{
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main_gui.layout");
	window_->setVisible(true);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);

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
				game_.set_state(GAME_STATE::ENDED);
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/LOAD")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&, this](const CEGUI::EventArgs& args){
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
				game_.game_serializer_->save_game(game_, "quick_save");
			}
		);

	window_->getChild("TOOLS/MENU/FRAME/QUICK_LOAD")->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			[&](const CEGUI::EventArgs& args){
				game_.game_serializer_->load_game(game_, "quick_save");
			}
		);

}

void GUI::set_visible(const std::string& wname, bool val)
{
	window_->getChild(wname)->setVisible(val);
}
