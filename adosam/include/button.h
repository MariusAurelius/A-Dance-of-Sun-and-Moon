#ifndef PROJECT_INC_BUTTON_H
#define PROJECT_INC_BUTTON_H

#include <SDL2/SDL.h>

#include "image.h"


class Button : public Image{
public:

    Button(SDL_Renderer* source_renderer, const std::string& file_path, const float& x_pos, const float& y_pos, const int& width, const int& height);
    
    ~Button();

    bool CheckIfClicked(const SDL_Event& event);
    
};

#endif