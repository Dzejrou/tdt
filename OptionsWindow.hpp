#pragma once

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <string>
#include <map>
#include <tuple>
#include <array>
#include "GUIWindow.hpp"
#include "Typedefs.hpp"
#include "Enums.hpp"

/**
 * Options menu window that lets the player to change the resolution, window mode and
 * keybinging.
 */
class OptionsWindow : public GUIWindow
{
	typedef void (*ActionFuncPtr)();
	public:
		/**
		 * Constructor.
		 */
		OptionsWindow();

		/**
		 * Destructor.
		 */
		~OptionsWindow() = default;

		/**
		 * Brief: Saves pointers to the window, view and renderer and sets starting
		 *        values for the resolution, window mode etc.
		 * Param: Window that the game is rendered to.
		 * Param: Viewport of the window.
		 * Param: Renderer used by CEGUI.
		 */
		void add_start_parameters(Ogre::RenderWindow*, Ogre::Viewport*, CEGUI::OgreRenderer*);

		/**
		 * Brief: Registers a key press for keybinding. Returns true if the click was consumed,
		 *        false otherwise.
		 * Param: Key pressed.
		 */
		bool key_pressed(CEGUI::Key::Scan);

		/**
		 * Brief: Binds a given action to a given key.
		 * Param: Action to be bound.
		 * Param: Key to be bound.
		 */
		void set_key_bind(KEY_BIND_ACTION::VAL, CEGUI::Key::Scan);

	protected:
		/**
		 * Brief: Initializes the CEGUI window.
		 */
		void init_() override;

	private:
		/**
		 * Brief: Applies the graphical changes and saves key bindings
		 *        into a script that allows persistent key binds.
		 */
		void apply_();

		/**
		 * Brief: Updates the button texts and labels to reflect
		 *        the new settings.
		 */
		void update_labels_();

		/**
		 *
		 */
		void update_fonts_();

		/**
		 *
		 */
		void update_font_of_window_(CEGUI::Window*, const std::string&);

		/**
		 * Brief: Returns the name of the key a given action
		 *        is bound to.
		 * Param: The action.
		 */
		const std::string& get_key_bind_name_(KEY_BIND_ACTION::VAL);

		/**
		 * Window the game is rendered to.
		 */
		Ogre::RenderWindow* render_window_;

		/**
		 * Main viewport of the render window.
		 */
		Ogre::Viewport* view_;

		/**
		 * Renderer used by CEGUI (used to sync resolution between game and UI).
		 */
		CEGUI::OgreRenderer* renderer_;

		/**
		 * Dimensions of the display resolution.
		 */
		tdt::uint width_, height_;

		/**
		 * True for fullscreen, false for windowed mode.
		 */
		bool fullscreen_;

		/**
		 * This map connects key codes with their names (used for key bind buttons).
		 */
		std::map<CEGUI::Key::Scan, std::string> key_names_;

		/**
		 * Action functions assigned to actions.
		 */
		std::array<ActionFuncPtr, KEY_BIND_ACTION::COUNT> actions_;

		/**
		 * Keys bound to actions.
		 */
		std::array<CEGUI::Key::Scan, KEY_BIND_ACTION::COUNT> key_binds_;

		/**
		 * Resolution strings and their assigned dimensions.
		 */
		std::map<std::string, std::tuple<tdt::uint, tdt::uint>> resolutions_;

		/**
		 * Saves the currently binded action so that the next key press
		 * can be used.
		 */
		KEY_BIND_ACTION::VAL currently_binded_action_;
};

/**
 * Functions representing actions that can be
 * key bound.
 */
namespace action
{
	/**
	 * Brief: Casts the first spell in the spell tool window.
	 */
	void CAST_SPELL_1();

	/**
	 * Brief: Casts the second spell in the spell tool window.
	 */
	void CAST_SPELL_2();

	/**
	 * Brief: Casts the third spell in the spell tool window.
	 */
	void CAST_SPELL_3();

	/**
	 * Brief: Casts the fourth spell in the spell tool window.
	 */
	void CAST_SPELL_4();

	/**
	 * Brief: Moves the spell selection to the right.
	 */
	void NEXT();

	/**
	 * Brief: Moves the spell selection to the left.
	 */
	void PREV();

	/**
	 * Brief: Switches the current tool to the spell tab.
	 */
	void SPELL_TAB();

	/**
	 * Brief: Switches the current tool to the build tab.
	 */
	void BUILD_TAB();

	/**
	 * Brief: Switches the current tool to the menu tab.
	 */
	void MENU_TAB();

	/**
	 * Brief: Resets the position and orientation of the camera.
	 */
	void RESET_CAMERA();

	/**
	 * Brief: Saves the current game to the quick_save.lua file.
	 */
	void QUICK_SAVE();

	/**
	 * Brief: Restores the game save in the quick_save.lua file.
	 */
	void QUICK_LOAD();
}