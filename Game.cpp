#include "Game.hpp"

Game::Game()
    : state_{GAME_STATE::RUNNING}, root_{new Ogre::Root()}
{ /* DUMMY BODY */ }

void Game::run()
{
    point last_time = clock::now();
    point curr_time{};
    frame frame_time{};

    while(state_ != GAME_STATE::ENDED)
    {
        curr_time = clock::now();
        auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(curr_time - last_time);

        while(delta_time >= frame_time)
        {
            // do the game stuff
        }

        last_time = curr_time;
    }
}