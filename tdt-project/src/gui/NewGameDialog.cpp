#include <Game.hpp>
#include <systems/WaveSystem.hpp>
#include <lppscript/LppScript.hpp>
#include "NewGameDialog.hpp"
#include "Console.hpp"
#include "GUI.hpp"

NewGameDialog::NewGameDialog()
	: scenarios_{}
{ /* DUMMY BODY */ }

void NewGameDialog::register_scenario(const std::string& scenario, const std::string& wave_table)
{
	scenarios_.emplace(scenario, wave_table);

	auto item = new CEGUI::ListboxTextItem{scenario};
	item->setTextColours(Console::ORANGE_TEXT);
	item->setSelectionBrushImage("AlfiskoSkin/GenericBrush");
	item->setSelectionColours(Console::BLUE_TEXT);
	scenario_list_->addItem(item);
}

const std::string& NewGameDialog::get_selected_scenario_table()
{
	static const std::string NO_SCENARIO{lpp::Script::instance().get<std::string>("game.config.default_wave_table")};

	auto selected = scenario_list_->getFirstSelectedItem();
	if(selected)
	{
		auto res = scenarios_.find(selected->getText().c_str());
		if(res != scenarios_.end())
			return res->second;
	}
	return NO_SCENARIO;
}

void NewGameDialog::init_()
{
	scenario_list_ = (CEGUI::Listbox*)window_->getChild("SCENARIO_INPUT");

	window_->getChild("16x16")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("WIDTH_INPUT")->setText("16");
			window_->getChild("HEIGHT_INPUT")->setText("16");
			return true;
		}
	);

	window_->getChild("32x32")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("WIDTH_INPUT")->setText("32");
			window_->getChild("HEIGHT_INPUT")->setText("32");
			return true;
		}
	);

	window_->getChild("64x64")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			window_->getChild("WIDTH_INPUT")->setText("64");
			window_->getChild("HEIGHT_INPUT")->setText("64");
			return true;
		}
	);

	auto game = GUI::instance().game_;
	auto log = &GUI::instance().log_;
	auto window = GUI::instance().window_;
	window_->getChild("CREATE")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[this, game, log, window](const CEGUI::EventArgs&) -> bool {
			if(scenario_list_->getSelectedCount() != 1)
			{
				log->set_visible(true);
				log->print("\\[ERROR\\] You need to choose exactly one scenario.");
				return false;
			}

			try
			{
				// Converts text from edit boxes to uints, sadly no implicit conversion
				// from CEGUI::String to std::string exists :(.
				std::size_t w{
					(std::size_t)std::stoul(window_->getChild("WIDTH_INPUT")->getText().c_str())
				};
				std::size_t h{
					(std::size_t)std::stoul(window_->getChild("HEIGHT_INPUT")->getText().c_str())
				};

				if(w >= 10 && w <= 64 && h >= 10 && h <= 64)
				{
					game->wave_system_->set_wave_table(get_selected_scenario_table());
					game->new_game(w, h);
				}
				else
					throw std::out_of_range{"(" + std::to_string(w) + ", " + std::to_string(h) + ") != (10, 64)"};
			}
			catch(std::invalid_argument&)
			{
				log->set_visible(true);
				log->print("\\[ERROR\\] Invalid new game dimensions.");
				return false;
			}
			catch(std::out_of_range&)
			{
				log->set_visible(true);
				log->print("\\[ERROR\\] Game dimensions out of range.");
				return false;
			}

			window_->getChild("WIDTH_INPUT")->setText("");
			window_->getChild("HEIGHT_INPUT")->setText("");
			window_->setVisible(false);
		    window->getChild("MAIN_MENU")->setVisible(false);
			window->getChild("TOOLS")->setVisible(true);
			window->getChild("ENTITY_VIEW")->setVisible(true);
			window->getChild("GAME_LOG")->setVisible(true);
			window->getChild("NEXT_WAVE")->setVisible(true);
			game->set_state(GAME_STATE::RUNNING);
			return true;
		}
	);
}
