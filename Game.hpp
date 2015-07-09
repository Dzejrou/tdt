#pragma once

#include <Ogre.h>
#include <OIS.h>

#include <memory>
#include <vector>

#include "Entity.hpp"

enum class GAME_STATE
{
    RUNNING, ENDED
};

class Game : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
    public:
        Game();
        ~Game() { /* DUMMY BODY */ }

        void run();
        void update(Ogre::Real);

        // Inherited methods (callbacks):
        bool frameRenderingQueued(const Ogre::FrameEvent&) override;
        bool keyPressed(const OIS::KeyEvent&) override;
        bool keyReleased(const OIS::KeyEvent&) override;
        bool mouseMoved(const OIS::MouseEvent&) override;
        bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) override;
        bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) override;

    private:
        void ogre_init();
        void ois_init();
        void level_init();

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

        std::vector<Entity> entities_;

        // Testing stuff.
        int test_dir{0};
        Ogre::SceneNode* test_node{nullptr};
};