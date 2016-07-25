#pragma once

#include <OGRE/Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <string>
#include <map>
#include <tuple>
#include <array>
#include <Typedefs.hpp>
#include <Enums.hpp>
#include "GUIWindow.hpp"

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
		 * \brief Saves pointers to the window, view and renderer and sets starting
		 *        values for the resolution, window mode etc.
		 * \param Window that the game is rendered to.
		 * \param Viewport of the window.
		 * \param Renderer used by CEGUI.
		 */
		void add_start_parameters(Ogre::RenderWindow*, Ogre::Viewport*, CEGUI::OgreRenderer*);

		/**
		 * \brief Registers a key press for keybinding. Returns true if the click was consumed,
		 *        false otherwise.
		 * \param Key pressed.
		 */
		bool key_pressed(CEGUI::Key::Scan);

		/**
		 * \brief Binds a given action to a given key.
		 * \param Action to be bound.
		 * \param Key to be bound.
		 */
		void set_key_bind(KEY_BIND_ACTION::VAL, CEGUI::Key::Scan);

	protected:
		/**
		 * \brief Initializes the CEGUI window.
		 */
		void init_() override;

	private:
		/**
		 * \brief Applies the graphical changes and saves key bindings
		 *        into a script that allows persistent key binds.
		 */
		void apply_();

		/**
		 * \brief Updates the button texts and labels to reflect
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
		 * \brief Returns the name of the key a given action
		 *        is bound to.
		 * \param The action.
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
	 * \brief Casts the first spell in the spell tool window.
	 */
	void CAST_SPELL_1();

	/**
	 * \brief Casts the second spell in the spell tool window.
	 */
	void CAST_SPELL_2();

	/**
	 * \brief Casts the third spell in the spell tool window.
	 */
	void CAST_SPELL_3();

	/**
	 * \brief Casts the fourth spell in the spell tool window.
	 */
	void CAST_SPELL_4();

	/**
	 * \brief Moves the spell selection to the right.
	 */
	void NEXT();

	/**
	 * \brief Moves the spell selection to the left.
	 */
	void PREV();

	/**
	 * \brief Switches the current tool to the spell tab.
	 */
	void SPELL_TAB();

	/**
	 * \brief Switches the current tool to the build tab.
	 */
	void BUILD_TAB();

	/**
	 * \brief Switches the current tool to the menu tab.
	 */
	void MENU_TAB();

	/**
	 * \brief Resets the position and orientation of the camera.
	 */
	void RESET_CAMERA();

	/**
	 * \brief Saves the current game to the quick_save.lua file.
	 */
	void QUICK_SAVE();

	/**
	 * \brief Restores the game save in the quick_save.lua file.
	 */
	void QUICK_LOAD();
}