#include "ResearchWindow.hpp"
#include "Player.hpp"
#include "lppscript/LppScript.hpp"
#include <CEGUI/CEGUI.h>

ResearchWindow::ResearchWindow()
	: script_{nullptr}, prices_{}, unlocked_{}
{ /* DUMMY BODY */ }

void ResearchWindow::unlock(tdt::uint i, tdt::uint j)
{
	if(i > rows_ || j > cols_ || is_unlocked_(i, j)
	   || !Player::instance().sub_gold(get_price_(i, j)))
		return;
	unlocked_[cols_ * (i - 1) + (j - 1)] = true;

	// This will notify the player that this research point
	// is already unlocked.
	std::string butt = "FRAME/" + std::to_string(i) + "_" + std::to_string(j);
	window_->getChild(butt)->setText("+" + window_->getChild(butt)->getText());

	if(j < cols_)
		show(i, j + 1);
	if(script_)
		script_->call<void, tdt::uint, tdt::uint>("game.gui.research.unlock", i, j);
}

void ResearchWindow::dummy_unlock(tdt::uint i, tdt::uint j)
{
	if(i > rows_ || j > cols_ || is_unlocked_(i, j))
		return;
	unlocked_[cols_ * (i - 1) + (j - 1)] = true;

	std::string butt = "FRAME/" + std::to_string(i) + "_" + std::to_string(j);
	window_->getChild(butt)->setText("+" + window_->getChild(butt)->getText());

	if(j < cols_)
		show(i, j + 1);
}

const std::array<bool, 42>& ResearchWindow::get_unlocked() const
{
	return unlocked_;
}

void ResearchWindow::show(tdt::uint i, tdt::uint j, bool val)
{
	window_->getChild("FRAME/" + std::to_string(i) + "_" + std::to_string(j))->setVisible(val);
}

void ResearchWindow::free_research()
{
	for(auto& p : prices_)
		p = 0;
}

void ResearchWindow::research_all()
{
	for(tdt::uint i = 1; i <= rows_; ++i)
	{
		for(tdt::uint j = 1; j <= cols_; ++j)
		{
			unlock(i, j);
		}
	}
}

void ResearchWindow::reset_research()
{
	for(auto& u : unlocked_)
		u = false;

	CEGUI::Window* butt{nullptr};
	std::string row{""}, col{""};
	for(tdt::uint i = 1; i <= rows_; ++i)
	{
		row = std::to_string(i) + "_";
		for(tdt::uint j = 1; j <= cols_; ++j)
		{
			col = std::to_string(j);
			butt = window_->getChild("FRAME/" + row + col);

			// Remove the researched '+' marker.
			if(butt->getText().size() > 0 && butt->getText()[0] == '+')
				butt->setText(butt->getText().substr(1));

			if(j == 1)
				butt->setVisible(true);
			else
				butt->setVisible(false);
		}
	}
}

void ResearchWindow::init_()
{
	set_visible(false);
	script_ = &lpp::Script::instance();

	window_->getChild("FRAME")->subscribeEvent(
		CEGUI::FrameWindow::EventCloseClicked,
		[this](const CEGUI::EventArgs&) -> bool {
			this->set_visible(false);
			return true;
		}
	);

	/**
	 * Makes sure all buttons can be used in the beggining.
	 */
	for(auto& u : unlocked_)
		u = false;

	/**
	 * Research button initialization.
	 */
	CEGUI::Window* butt{nullptr};
	std::string row{""}, col{""};
	for(tdt::uint i = 1; i <= rows_; ++i)
	{
		row = std::to_string(i) + "_"; // Saves repeated conversions.
		for(tdt::uint j = 1; j <= cols_; ++j)
		{
			col = std::to_string(j);
			butt = window_->getChild("FRAME/" + row + col);
			butt->subscribeEvent(
				CEGUI::PushButton::EventClicked,
				[this, i, j](const CEGUI::EventArgs&) -> bool {
					this->unlock(i, j);
					return true;
				}
			);
			butt->setText(
				script_->call<std::string, tdt::uint, tdt::uint>(
					"game.gui.research.get_name", i, j
				)
			);

			/** Note: AlfiskoSkin does not have tooltip support, maybe create own skin?
			butt->setTooltipText(
				script_->call<std::string, tdt::uint, tdt::uint>(
					"game.gui.research.get_tooltip", i, j
				)	
			); */

			prices_[cols_ * (i - 1) + (j - 1)] = script_->call<tdt::uint, tdt::uint, tdt::uint>(
				"game.gui.research.get_price", i, j
			);
		}
	}

}

tdt::uint ResearchWindow::get_price_(tdt::uint i, tdt::uint j)
{
	tdt::uint index{cols_ * (i - 1) + (j - 1)};
	if(index < prices_.size())
		return prices_[index];
	else
		return tdt::uint{};
}

bool ResearchWindow::is_unlocked_(tdt::uint i, tdt::uint j)
{
	tdt::uint index{cols_ * (i - 1) + (j - 1)};
	if(index < unlocked_.size())
		return unlocked_[index];
	else
		return false;
}
