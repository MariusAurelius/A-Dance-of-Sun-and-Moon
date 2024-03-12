#ifndef PROJECT_INC_TEXT_H
#define PROJECT_INC_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

class Text{

public:
    
    Text(SDL_Renderer* renderer, const SDL_Color& color, TTF_Font* font, 
         const float& x_pos, const float& y_pos, 
         const int& width, const int& height, 
         const string& initial_value);

    ~Text();

    void Update(SDL_Renderer* renderer, const string& value);

    void Render(SDL_Renderer* renderer);

private:


    SDL_Surface* text_surface_;
    SDL_Texture* text_texture_;
    SDL_Rect* text_rectangle_;

    SDL_Color color_;
    TTF_Font* font_;

    float x_pos_;
    float y_pos_;

    Uint16 width_;
    Uint16 height_;

};


#endif