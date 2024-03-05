#ifndef PROJECT_INC_GAMERENDERER_H
#define PROJECT_INC_GAMERENDERER_H

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "image.h"
#include "tile.h"
#include "level.h"
#include "button.h"


class GameRenderer{
public:

    GameRenderer();

    ~GameRenderer();

    void IfKeyDown();

    bool IfMouseButtonDown(std::string button_name, SDL_Event event);

    void Update();

    void Render();

    void Start();

    SDL_Renderer* GetRenderer();

private:

    SDL_Renderer* renderer_;
    SDL_DisplayMode* displaymode_;
    SDL_Window* window_;

    SDL_Texture* score_texture_;
    SDL_Rect* score_rect_;
    SDL_Surface* score_surface_;
    TTF_Font* font_;

    Level* level_;
    Image* menu_background_;
    Image* background_;
    Button* quit_;

    std::string img_tile_path_;
    std::string img_extension_;
    
};

#endif