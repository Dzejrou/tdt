#include "ResearchWindow.hpp"
#include "Player.hpp"

ResearchWindow::ResearchWindow()
	: script_{nullptr}, prices_{}, unlocked_{}
{ /* DUMMY BODY */ }

void ResearchWindow::unlock(std::size_t i, std::size_t j)
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
		script_->call<void, std::size_t, std::size_t>("game.gui.research.unlock", i, j);
}

void ResearchWindow::dummy_unlock(std::size_t i, std::size_t j)
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

void ResearchWindow::show(std::size_t i, std::size_t j, bool val)
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
	for(std::size_t i = 1; i <= rows_; ++i)
	{
		for(std::size_t j = 1; j <= cols_; ++j)
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
	for(std::size_t i = 1; i <= rows_; ++i)
	{
		row = std::to_string(i) + "_";
		for(std::size_t j = 1; j <= cols_; ++j)
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
	script_ = lpp::Script::get_singleton_ptr();

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
	for(std::size_t i = 1; i <= rows_; ++i)
	{
		row = std::to_string(i) + "_"; // Saves repeated conversions.
		for(std::size_t j = 1; j <= cols_; ++j)
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
				script_->call<std::string, std::size_t, std::size_t>(
					"game.gui.research.get_name", i, j
				)
			);

			/** Note: AlfiskoSkin does not have tooltip support, maybe create own skin?
			butt->setTooltipText(
				script_->call<std::string, std::size_t, std::size_t>(
					"game.gui.research.get_tooltip", i, j
				)	
			); */

			prices_[cols_ * (i - 1) + (j - 1)] = script_->call<std::size_t, std::size_t, std::size_t>(
				"game.gui.research.get_price", i, j
			);
		}
	}

}

std::size_t ResearchWindow::get_price_(std::size_t i, std::size_t j)
{
	std::size_t index{cols_ * (i - 1) + (j - 1)};
	if(index < prices_.size())
		return prices_[index];
	else
		return std::size_t{};
}

bool ResearchWindow::is_unlocked_(std::size_t i, std::size_t j)
{
	std::size_t index{cols_ * (i - 1) + (j - 1)};
	if(index < unlocked_.size())
		return unlocked_[index];
	else
		return false;
}
