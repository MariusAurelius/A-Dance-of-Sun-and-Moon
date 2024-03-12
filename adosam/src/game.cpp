#include "game.h"

Game::Game() : 
        is_running_(true), is_in_game_(false)

{

    game_renderer_ = new GameRenderer;

}

Game::~Game() {

    delete game_renderer_;
    game_renderer_ = nullptr;

}

void Game::Run() {

    while (is_running_) {

        while (SDL_PollEvent(&event_) != 0) {

            if(event_.type == SDL_QUIT){

                is_running_ = false;

            }

            if (event_.type == SDL_MOUSEBUTTONDOWN) {

                if(game_renderer_->IfMouseButtonDown("quit", event_)){

                    is_running_ = false;

                }

                if(game_renderer_->IfMouseButtonDown("play", event_)){

                    game_renderer_->StartLevel();
                    is_in_game_ = true;

                }

            }

            if(event_.type == SDL_KEYDOWN){

                if(is_in_game_){

                    game_renderer_->IfKeyDown();

                }

                if(event_.key.keysym.sym == SDLK_ESCAPE){

                    is_running_ = false;

                }

            }

        }

        if(is_in_game_){

            game_renderer_->UpdateLevel();
            game_renderer_->RenderLevel();

        }

        else{

            game_renderer_->RenderMenu();

        }

        SDL_Delay(1000 / FRAMERATE); //voir alternative pas obligatoire
        
    }
    
}



