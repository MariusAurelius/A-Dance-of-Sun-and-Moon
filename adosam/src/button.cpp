#include "button.h"

Button::Button(SDL_Renderer* source_renderer, const std::string& file_path, const float& x_pos, const float& y_pos, const int& width, const int& height) 
    : Image(source_renderer, file_path, x_pos, y_pos, width, height){}

Button::~Button(){}

bool Button::CheckIfClicked(const SDL_Event& event){
    int mouse_x = event.button.x;
    int mouse_y = event.button.y;

    if (mouse_x >= GetXPos() && mouse_x <= GetWidth() &&
        mouse_y >= GetYPos() && mouse_y <= GetHeight()) {
        return true;
    }
    
    return false;
}