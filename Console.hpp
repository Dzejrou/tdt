#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

/**
 *
 */
class Console
{
	public:
		Console();
		~Console() {}

		void set_visible(bool);
		bool is_visible() const;
	private:
		CEGUI::Window* window_;
		std::string input_, input_cont_;
		bool visible_;
};