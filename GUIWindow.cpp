#include "GUIWindow.hpp"

GUIWindow::GUIWindow()
	: window_{nullptr}
{ /* DUMMY BODY */ }

void GUIWindow::init(CEGUI::Window* w)
{
	window_ = w;
	init_();
}

void GUIWindow::set_visible(bool val)
{
	window_->setVisible(val);
}

bool GUIWindow::is_visible() const
{
	return window_->isVisible();
}
