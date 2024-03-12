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
#include "text.h"

using namespace std;


class GameRenderer{
public:

    GameRenderer();

    ~GameRenderer();

    void IfKeyDown();

    bool IfMouseButtonDown(const string& button_name, const SDL_Event& event);

    void InitMenu();

    void RenderMenu();

    void InitLevel();

    void UpdateLevel();

    void RenderLevel();

    void StartLevel();

    void Countdown();

private:

    SDL_Renderer* renderer_;
    SDL_DisplayMode* displaymode_;
    SDL_Window* window_;

    TTF_Font* font_;

    Text* score_;

    Text* life_;
    Image* life_image_;

    Level* level_;
    Image* level_background_;

    Image* menu_background_;
    Button* play_button_;

    Button* quit_button_;

    string img_tile_path_;
    string img_extension_;
    
};

#endif