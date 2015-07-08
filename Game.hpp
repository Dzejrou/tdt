#pragma once

#include <Ogre.h>

#include <memory>
#include <vector>

#include "Entity.hpp"

class Game : public Ogre::FrameListener
{
    public:
        Game();
        ~Game() { /* DUMMY BODY */ }

        void run();
        void process();
        void update(Ogre::Real);

        bool frameRenderingQueued(const Ogre::FrameEvent&) override;

    private:
        void ogre_init();

        Ogre::SceneNode* test_node;

        std::unique_ptr<Ogre::Root> root_;
        Ogre::SceneManager* scene_mgr_;
        Ogre::RenderWindow* window_;
        Ogre::Camera* main_cam_;
        Ogre::Viewport* main_view_;
        Ogre::Light* main_light_;

        std::vector<Entity> entities_;
};