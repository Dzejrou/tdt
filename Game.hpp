#pragma once

#include <Ogre.h>
#include <OIS.h>

#include <memory>
#include <vector>

#include "EntitySystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"
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

		std::vector<System*> systems_;

		// Testing stuff.
		Ogre::SceneNode* test_node{nullptr};
};