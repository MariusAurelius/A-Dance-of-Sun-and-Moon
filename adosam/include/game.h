#ifndef PROJECT_INC_GAME_H
#define PROJECT_INC_GAME_H

#include <memory>

#include <SDL2/SDL.h>

#include "game_renderer.h"

class Game {
public:
    
    Game();

    ~Game();

    void Run();

    uint GetFramerate();

private:

    SDL_Event event_;

    GameRenderer* game_renderer_;

    bool is_running_;

    bool is_in_game_;

};

#endif