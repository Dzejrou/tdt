#include "Console.hpp"

Console::Console()
	: window_{nullptr}, list_box_{nullptr}, curr_command_{}
{ /* DUMMY BODY */ }

void Console::init()
{
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("console.layout");
	if(window_)
	{
		window_->setVisible(false);
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);
	}
	
	window_->getChild("INPUT")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
											   CEGUI::Event::Subscriber(&Console::handle_text, this));
	window_->getChild("EXECUTE")->subscribeEvent(CEGUI::PushButton::EventClicked,
												 CEGUI::Event::Subscriber(&Console::execute, this));

	list_box_ = (CEGUI::Listbox*)window_->getChild("CONSOLE_LOG");
}

void Console::set_visible(bool visible)
{
	window_->setVisible(visible);
}

bool Console::is_visible() const
{
	return window_->isVisible();
}

void Console::handle_text(const CEGUI::EventArgs &)
{
	std::string command = window_->getChild("INPUT")->getText().c_str();
	curr_command_ += '\n' + command;
	print_text(command);
	window_->getChild("INPUT")->setText("");

	list_box_->getVertScrollbar()->scrollForwardsByStep(); // Sync the list box.
}

void Console::execute(const CEGUI::EventArgs &)
{
	try
	{
		lpp::Script::get_singleton().execute(curr_command_);
	}
	catch(const lpp::Exception& ex)
	{
		if(ex.has_lua_state())
			print_text(ex.what_lua(), CEGUI::Colour{1.f, 0.1f, 0.1f});
		else
			print_text(ex.what(), CEGUI::Colour{1.f, 0.f, 0.f});
	}
	print_text(""); // Just visual delimiter.
	list_box_->getVertScrollbar()->scrollForwardsByStep(); // Sync the list box.
	curr_command_ = "";
}

void Console::print_text(const std::string& msg, CEGUI::Colour col)
{
	CEGUI::ListboxTextItem* text = new CEGUI::ListboxTextItem(msg + "\n");
	text->setTextColours(col);
	list_box_->addItem(text);
}