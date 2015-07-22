#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <string>

#include "lppscript/LppScript.hpp"

/**
 *
 */
class Console
{
	public:
		Console();
		~Console() {}

		void init();
		void set_visible(bool);
		bool is_visible() const;

		void handle_text(const CEGUI::EventArgs&);
		void execute(const CEGUI::EventArgs&);

		void print_text(const std::string&, CEGUI::Colour = CEGUI::Colour{0xFFFFFFFF});
	private:
		CEGUI::Window* window_;
		std::string curr_command_;
};