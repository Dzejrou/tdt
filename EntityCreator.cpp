#include "EntityCreator.hpp"

EntityCreator::EntityCreator(EntityPlacer& placer, EntitySystem& ents)
	: placer_{placer}, registered_entities_{ents.get_registered_entities()}
{
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("entity_creator.layout");
	window_->setVisible(false);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);

	// Register handlers.
	window_->getChild("PLACE")->subscribeEvent(CEGUI::PushButton::EventClicked,
											   CEGUI::Event::Subscriber(&EntityCreator::change_to_place, this));
	window_->getChild("CREATE")->subscribeEvent(CEGUI::PushButton::EventClicked,
											   CEGUI::Event::Subscriber(&EntityCreator::change_to_create, this));
	window_->getChild("PLACE_BUTT")->subscribeEvent(CEGUI::PushButton::EventClicked,
											   CEGUI::Event::Subscriber(&EntityCreator::place, this));
	window_->getChild("ACTUALIZE_LIST")->subscribeEvent(CEGUI::PushButton::EventClicked,
											   CEGUI::Event::Subscriber(&EntityCreator::actualize_list, this));
	list_box_ = (CEGUI::Listbox*)window_->getChild("ENTITY_LIST");
}

void EntityCreator::place(const CEGUI::EventArgs& args)
{
	auto selected = list_box_->getFirstSelectedItem();
	if(selected && !lpp::Script::get_singleton().is_nil(selected->getText().c_str()))
	{
		placer_.set_current_entity_table(selected->getText().c_str());
		placer_.set_visible(true);
	}
}

void EntityCreator::change_to_place(const CEGUI::EventArgs& args)
{
	// TODO: Place/Create modes.
}

void EntityCreator::change_to_create(const CEGUI::EventArgs& args)
{
	// TODO: Place/Create modes.
}

void EntityCreator::actualize_list(const CEGUI::EventArgs& args)
{
	list_box_->resetList();
	CEGUI::ListboxTextItem* item;
	CEGUI::Colour col{1.f, .5f, .1f};
	for(auto& ent : registered_entities_)
	{
		item = new CEGUI::ListboxTextItem(ent);
		item->setTextColours(Console::ORANGE_TEXT);
		item->setSelectionBrushImage("AlfiskoSkin/GenericBrush");
		item->setSelectionColours(Console::BLUE_TEXT);
		list_box_->addItem(item);
	}
}

void EntityCreator::set_visible(bool on_off)
{
	window_->setVisible(on_off);
}

bool EntityCreator::is_visible() const
{
	return window_->isVisible();
}
