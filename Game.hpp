#pragma once

#include <Ogre.h>
#include <OIS.h>

#include <memory>
#include <vector>

#include "EntitySystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"
#include "AISystem.hpp"
#include "lppscript/LppScript.hpp"

enum class GAME_STATE
{
	RUNNING, ENDED
};

class Game : public Ogre::FrameListener, public OIS::KeyListener,
			 public OIS::MouseListener, public Ogre::WindowEventListener
{
	public:
		Game();
		~Game();

		void run();
		void update(Ogre::Real);
	protected:
		// Inherited methods (callbacks).
		bool frameRenderingQueued(const Ogre::FrameEvent&) override;
		bool keyPressed(const OIS::KeyEvent&) override;
		bool keyReleased(const OIS::KeyEvent&) override;
		bool mouseMoved(const OIS::MouseEvent&) override;
		bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) override;
		bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) override;
		void windowResized(Ogre::RenderWindow* rw) override;
		void windowClosed(Ogre::RenderWindow* rw) override;
	private:
		// Init methods.
		void ogre_init();
		void ois_init();
		void level_init();
		void lua_init();

		GAME_STATE state_;

		std::unique_ptr<Ogre::Root> root_;
		Ogre::SceneManager* scene_mgr_;
		Ogre::RenderWindow* window_;
		Ogre::Camera* main_cam_;
		Ogre::Viewport* main_view_;
		Ogre::Light* main_light_;

		OIS::InputManager* input_;
		OIS::Keyboard* keyboard_;
		OIS::Mouse* mouse_;
		Ogre::Vector3 camera_dir_;

		std::unique_ptr<EntitySystem> entity_system_;
		std::unique_ptr<HealthSystem> health_system_;
		std::unique_ptr<MovementSystem> movement_system_;
		std::unique_ptr<AISystem> ai_system_;

		std::vector<System*> systems_;

		// Testing stuff.
		Ogre::SceneNode* test_node{nullptr};

		/**
		 * These methods are to be used from Lua, note that Lua can register only
		 * static functions, so a static pointer to the instance of this game is created in
		 * the game's constructor and used in these static functions.
		 */
		static Game* lua_this;
		static int lua_create_entity(lpp::Script::state);
		static int lua_destroy_entity(lpp::Script::state);

		// Movement system.
		static int lua_move_to(lpp::Script::state);
		static int lua_move(lpp::Script::state);
		static int lua_rotate(lpp::Script::state);
		static int lua_is_moving(lpp::Script::state);
		static int lua_is_solid(lpp::Script::state);
		static int lua_can_move_to(lpp::Script::state);
		static int lua_collide(lpp::Script::state);
		static int lua_get_distance(lpp::Script::state);
		static int lua_get_position(lpp::Script::state);
		static int lua_get_speed_modifier(lpp::Script::state);
		static int lua_set_speed_modifier(lpp::Script::state);

		// Health system.
		static int lua_get_health(lpp::Script::state);
		static int lua_add_health(lpp::Script::state);
		static int lua_sub_health(lpp::Script::state);
		static int lua_heal(lpp::Script::state);
		static int lua_buff(lpp::Script::state);
		static int lua_get_defense(lpp::Script::state);
		static int lua_add_defense(lpp::Script::state);
		static int lua_sub_defense(lpp::Script::state);

		// AI system.
		static int lua_is_friendly(lpp::Script::state);
		static int lua_is_neutral(lpp::Script::state);
		static int lua_is_inanimate(lpp::Script::state);
		static int lua_get_blueprint(lpp::Script::state);
		static int lua_get_state(lpp::Script::state);
		static int lua_get_faction(lpp::Script::state);
		static int lua_enemy_in_radius(lpp::Script::state);
		static int lua_closest_enemy(lpp::Script::state);
		static int lua_dir_to_closest_enemy(lpp::Script::state);
		static int lua_dir_to_closest_enemy_in_radius(lpp::Script::state);
		static int lua_dir_to_enemy(lpp::Script::state);
};