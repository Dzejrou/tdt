#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <string>

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
		void handle_key(const CEGUI::EventArgs&);
		void handle_string(const std::string&);

		void print_text(const std::string&, CEGUI::Colour = CEGUI::Colour{0xFFFFFFFF});
	private:
		CEGUI::Window* window_;
		std::string prompt_, prompt_cont_;
		bool visible_;
};