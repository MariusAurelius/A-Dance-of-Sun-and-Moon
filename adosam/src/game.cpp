#include "game.h"

Game::Game() 
: is_running_(true){

    game_renderer_ = new GameRenderer;
}

Game::~Game() {
    delete game_renderer_;
    game_renderer_ = nullptr;
}

void Game::Run() {
    game_renderer_ -> Start();
    while (is_running_) {
        while (SDL_PollEvent(&event_) != 0) {
            if(event_.type == SDL_QUIT){
                is_running_ = false;
            }

            if (event_.type == SDL_MOUSEBUTTONDOWN) {
                if(game_renderer_ -> IfMouseButtonDown("quit", event_)){
                    is_running_ = false;
                }
            }

            if(event_.type == SDL_KEYDOWN){
                game_renderer_ -> IfKeyDown();
            }

        }
        
        SDL_RenderClear(game_renderer_ -> GetRenderer());
        game_renderer_ -> Update();
        game_renderer_ -> Render();
        SDL_Delay(1000 / FRAMERATE);
        
    }
}



