#include "BuilderWindow.hpp"
#include "EntityPlacer.hpp"
#include "GUI.hpp"

BuilderWindow::BuilderWindow()
	: buildings_{}, selection_number_{3}, placer_{nullptr}
{ /* DUMMY BODY */ }

void BuilderWindow::register_building(const std::string& tname)
{
	for(const auto& b : buildings_)
	{
		if(b == tname) // Prevents multiple entries of a building.
			return;
	}
	buildings_.push_back(tname);
	update_selection_();
}

void BuilderWindow::set_placer(EntityPlacer* p)
{
	placer_ = p;
}

void BuilderWindow::init_()
{
	update_selection_();

	window_->getChild("BUILD_1")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
			if(get_building_(selection_number_ - 3) != "UNKNOWN" && placer_)
			{
				placer_->set_current_entity_table(buildings_[selection_number_ - 3], true);
				placer_->set_visible(true);
			}
		}
	);

	window_->getChild("BUILD_2")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
			if(get_building_(selection_number_ - 2) != "UNKNOWN" && placer_)
			{
				placer_->set_current_entity_table(buildings_[selection_number_ - 2], true);
				placer_->set_visible(true);
			}
		}
	);

	window_->getChild("BUILD_3")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
			if(get_building_(selection_number_ - 1) != "UNKNOWN" && placer_)
			{
				placer_->set_current_entity_table(buildings_[selection_number_ - 1], true);
				placer_->set_visible(true);
			}
		}
	);

	window_->getChild("BUILD_4")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		[&](const CEGUI::EventArgs&){
			if(get_building_(selection_number_) != "UNKNOWN" && placer_)
			{
				placer_->set_current_entity_table(buildings_[selection_number_], true);
				placer_->set_visible(true);
			}
		}
	);

	window_->getChild("LEFT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&BuilderWindow::dec_selection_, this)
	);

	window_->getChild("RIGHT")->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&BuilderWindow::inc_selection_, this)
	);
}

void BuilderWindow::dec_selection_()
{
	if(selection_number_ > 3)
	{
		--selection_number_;
		update_selection_();
	}
}

void BuilderWindow::inc_selection_()
{
	if(buildings_.size() > 4 && selection_number_ < buildings_.size() - 1)
	{
		++selection_number_;
		update_selection_();
	}
}

const std::string& BuilderWindow::get_building_(std::size_t index)
{
	static std::string NO_BUILDING{"UNKNOWN"};

	if(index >= 0 && index < buildings_.size())
		return buildings_[index];
	else
		return NO_BUILDING;
}

void BuilderWindow::update_selection_()
{
	window_->getChild("BUILD_1")->setText(get_building_(selection_number_ - 3));
	window_->getChild("BUILD_2")->setText(get_building_(selection_number_ - 2));
	window_->getChild("BUILD_3")->setText(get_building_(selection_number_ - 1));
	window_->getChild("BUILD_4")->setText(get_building_(selection_number_));
}
