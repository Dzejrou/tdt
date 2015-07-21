#include "Console.hpp"

Console::Console()
	: window_{nullptr}, prompt_{"> "}, prompt_cont_{">> "}, visible_{false}
{ /* DUMMY BODY */ }

void Console::init()
{
	window_ = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("console.layout", "Layouts");
	if(window_)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window_);
	}
}

void Console::set_visible(bool)
{
}

bool Console::is_visible() const
{
	return false;
}

void Console::handle_text(const CEGUI::EventArgs &)
{
}

void Console::handle_key(const CEGUI::EventArgs &)
{
}

void Console::handle_string(const std::string &)
{
}

void Console::print_text(const std::string &, CEGUI::Colour)
{
}
