#pragma once

#include <Ogre.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <string>
#include <map>
#include <tuple>
#include <array>
#include <fstream>
#include "GUIWindow.hpp"
#include "Typedefs.hpp"
#include "Enums.hpp"

/**
 *
 */
class OptionsWindow : public GUIWindow
{
	typedef void (*ActionFuncPtr)();
	public:
		/**
		 *
		 */
		OptionsWindow();

		/**
		 *
		 */
		~OptionsWindow() = default;

		/**
		 *
		 */
		void add_start_parameters(Ogre::RenderWindow*, Ogre::Viewport*, CEGUI::OgreRenderer*);

		/**
		 *
		 */
		bool key_pressed(CEGUI::Key::Scan);

		/**
		 *
		 */
		void set_key_bind(KEY_BIND_ACTION::VAL, CEGUI::Key::Scan);

	protected:
		/**
		 *
		 */
		void init_();

	private:
		/**
		 *
		 */
		void apply_();

		/**
		 *
		 */
		void update_labels_();

		/**
		 *
		 */
		const std::string& get_key_bind_name_(KEY_BIND_ACTION::VAL);

		/**
		 *
		 */
		Ogre::RenderWindow* render_window_;

		/**
		 *
		 */
		Ogre::Viewport* view_;

		/**
		 *
		 */
		CEGUI::OgreRenderer* renderer_;

		/**
		 *
		 */
		tdt::uint width_, height_;

		/**
		 *
		 */
		bool fullscreen_;

		/**
		 *
		 */
		std::map<CEGUI::Key::Scan, std::string> key_names_;

		/**
		 *
		 */
		std::array<ActionFuncPtr, KEY_BIND_ACTION::COUNT> actions_;

		/**
		 *
		 */
		std::array<CEGUI::Key::Scan, KEY_BIND_ACTION::COUNT> key_binds_;

		/**
		 *
		 */
		std::map<std::string, std::tuple<tdt::uint, tdt::uint>> resolutions_;

		/**
		 *
		 */
		KEY_BIND_ACTION::VAL currently_binded_action_;
};

/**
 *
 */
namespace action
{
	/**
	 *
	 */
	void CAST_SPELL_1();

	/**
	 *
	 */
	void CAST_SPELL_2();

	/**
	 *
	 */
	void CAST_SPELL_3();

	/**
	 *
	 */
	void CAST_SPELL_4();

	/**
	 *
	 */
	void NEXT();

	/**
	 *
	 */
	void PREV();

	/**
	 *
	 */
	void SPELL_TAB();

	/**
	 *
	 */
	void BUILD_TAB();

	/**
	 *
	 */
	void MENU_TAB();

	/**
	 *
	 */
	void RESET_CAMERA();

	/**
	 *
	 */
	void QUICK_SAVE();

	/**
	 *
	 */
	void QUICK_LOAD();
}