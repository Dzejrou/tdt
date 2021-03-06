#include <lppscript/LppScript.hpp>
#include "Console.hpp"

// Static initialization:
const CEGUI::Colour Console::RED_TEXT = CEGUI::Colour{1.f, 0.f, 0.f};
const CEGUI::Colour Console::GREEN_TEXT = CEGUI::Colour{0.f, 1.f, 0.f};
const CEGUI::Colour Console::ORANGE_TEXT = CEGUI::Colour{1.f, .5f, 0.1f};
const CEGUI::Colour Console::BLUE_TEXT = CEGUI::Colour{0.f, 0.f, 1.f};

Console::Console()
	: list_box_{nullptr}, curr_command_{},
	  time_since_last_fps_update_{}, console_history_{60}
{ /* DUMMY BODY */ }

void Console::init_()
{
	window_->setVisible(false);
	
	// Registers event handlers.
	window_->getChild("INPUT")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
											   CEGUI::Event::Subscriber(&Console::handle_text, this));
	window_->getChild("EXECUTE")->subscribeEvent(CEGUI::PushButton::EventClicked,
												 CEGUI::Event::Subscriber(&Console::execute, this));

	list_box_ = (CEGUI::Listbox*)window_->getChild("CONSOLE_LOG");
}

void Console::set_visible(bool visible)
{
	window_->setVisible(visible);
	if(visible)
		window_->getChild("INPUT")->activate();
}

bool Console::handle_text(const CEGUI::EventArgs& args)
{
	std::string command = window_->getChild("INPUT")->getText().c_str();
	curr_command_ += '\n' + command;
	print_text(command);
	window_->getChild("INPUT")->setText("");
	return true;
}

bool Console::execute(const CEGUI::EventArgs& args)
{
	bool success{true};
	std::string err_msg{};

	try
	{
		lpp::Script::instance().execute(curr_command_);
	}
	catch(const lpp::Exception& ex)
	{
		if(ex.has_lua_state())
			err_msg = ex.what_lua();
		else
			err_msg = ex.what();

		success = false;
	}
	catch(const std::exception& ex)
	{
		err_msg = "C++: ";
		err_msg += ex.what();
		success = false;
	}
	catch(...)
	{
		print_text("<FAIL> Caught an unspecified error.", RED_TEXT);
	}

	if(success)
		print_text("<SUCCESS>", GREEN_TEXT);
	else
		print_text("<FAILURE> " + err_msg, RED_TEXT);

	curr_command_ = "";
	return true;
}

void Console::print_text(const std::string& msg, CEGUI::Colour col)
{
	if(msg == "`") // Garbage value from toggling the console.
		return;

	CEGUI::ListboxTextItem* text;

	if(list_box_->getItemCount() >= console_history_)
	{ // Little trick, reuse the oldest command entry.
		text = (CEGUI::ListboxTextItem*)list_box_->getListboxItemFromIndex(0);
		text->setAutoDeleted(false);
		list_box_->removeItem(text);
		text->setAutoDeleted(true);
		text->setText(msg + "\n");
	}
	else
		text = new CEGUI::ListboxTextItem(msg + "\n");
	text->setTextColours(col);
	list_box_->addItem(text);
	scroll_down();
}

void Console::scroll_down(tdt::uint num_of_scrolls)
{
	for(tdt::uint i = 0; i < num_of_scrolls; ++i)
		list_box_->getVertScrollbar()->scrollForwardsByStep();
}

void Console::update_fps(tdt::real delta, tdt::real fps)
{
	time_since_last_fps_update_ += delta;
	if(time_since_last_fps_update_ > 1.f)
	{
		window_->setText("DEVELOPER CONSOLE (LUA 5.3) FPS: " + std::to_string(fps));
		time_since_last_fps_update_ = 0.f;
	}
}

void Console::set_history(tdt::uint val)
{
	console_history_ = val;
}

tdt::uint Console::get_history() const
{
	return console_history_;
}

void Console::clear()
{
	list_box_->resetList();
}
