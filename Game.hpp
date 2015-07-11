#pragma once

#include <Ogre.h>
#include <OIS.h>

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "EntityFactory.hpp"
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

        std::vector<std::unique_ptr<Entity>> entities_;
        std::unique_ptr<EntityFactory> factory_;

        // Testing stuff.
        Ogre::Vector3 camera_dir_;
        Ogre::SceneNode* test_node{nullptr};
};