#pragma once

#include <Ogre.h>

#include <chrono>
#include <memory>

enum class GAME_STATE
{
    RUNNING, ENDED
};

class Game
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
        GAME_STATE state_;

        std::unique_ptr<Ogre::Root> root_;
};