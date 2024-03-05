#ifndef PROJECT_INC_IMAGE_H
#define PROJECT_INC_IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>
#include <string>

class Image{
public:

    Image(SDL_Renderer* source_renderer, const std::string& file_path, const float& x_pos, const float& y_pos, const int& width, const int& height);

    ~Image();

    void Load();

    void Unload();

    void Render();

    float GetXPos() const;

    float GetYPos() const;

    Uint16 GetWidth() const;

    Uint16 GetHeight() const;

    void SetXPos(const float& x_pos);

    void SetYPos(const float& y_pos);

private:

    SDL_Renderer* renderer_;
    SDL_Surface* surface_;
    SDL_Texture* texture_;
    SDL_Rect* rectangle_;

    std::string file_path_;

    float x_pos_;
    float y_pos_;

    Uint16 width_;
    Uint16 height_;
    
};

#endif