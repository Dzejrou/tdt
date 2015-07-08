#pragma once

#include <Ogre.h>

#include <chrono>
#include <memory>

enum class GAME_STATE
{
    RUNNING, ENDED
};

class Game : public Ogre::WindowEventListener
{
    using clock = std::chrono::high_resolution_clock;
    using frame = std::chrono::duration<long long, std::ratio<1, 60>>;
    using point = std::chrono::time_point<clock>;

    public:
        Game();
        ~Game() {}

        void run();
        void process();
        void update();
        void render();
    private:
        void ogre_init();

        GAME_STATE state_;

        std::unique_ptr<Ogre::Root> root_;
        Ogre::SceneManager* scene_mgr_;
        Ogre::RenderWindow* window_;
        Ogre::Camera* main_cam_;
        Ogre::Viewport* main_view_;
        Ogre::Light* main_light_;
};