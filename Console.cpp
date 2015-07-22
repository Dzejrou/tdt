#include "Console.hpp"

Console::Console()
	: window_{nullptr}, curr_command_{}
{ /* DUMMY BODY */ }

void Console::init()
{
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("console.layout");
	if(window_)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);
	}
	
	window_->getChild("INPUT")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
											   CEGUI::Event::Subscriber(&Console::handle_text, this));
	window_->getChild("EXECUTE")->subscribeEvent(CEGUI::PushButton::EventClicked,
												 CEGUI::Event::Subscriber(&Console::execute, this));
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
}

void Console::execute(const CEGUI::EventArgs &)
{
	try
	{
		lpp::Script::get_singleton().execute(curr_command_);
	}
	catch(const lpp::Exception& ex)
	{
		print_text(ex.what(), CEGUI::Colour{1, 0, 0});
	}
	curr_command_ = "";
}

void Console::handle_string(const std::string &)
{
}

void Console::print_text(const std::string& msg, CEGUI::Colour col)
{
	CEGUI::Listbox* lbox = (CEGUI::Listbox*)window_->getChild("CONSOLE_LOG");
	CEGUI::ListboxTextItem* text = new CEGUI::ListboxTextItem(msg + "\n");
	text->setTextColours(col);
	lbox->addItem(text);
}