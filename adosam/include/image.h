#ifndef PROJECT_INC_IMAGE_H
#define PROJECT_INC_IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Image{
public:

    Image(const string& file_path, const float& x_pos, const float& y_pos, 
          const int& width, const int& height);

    ~Image();

    void Load(SDL_Renderer* renderer);

    void Unload();

    void Render(SDL_Renderer* renderer);

    void InitiateRectangle();

    void UpdateRectangleCoordinates();

    float GetXPos() const;

    float GetYPos() const;

    Uint16 GetWidth() const;

    Uint16 GetHeight() const;

    void SetXPos(const float& x_pos);

    void SetYPos(const float& y_pos);

private:

    SDL_Surface* surface_;
    SDL_Texture* texture_;
    SDL_Rect* rectangle_;

    string file_path_;

    float x_pos_;
    float y_pos_;

    Uint16 width_;
    Uint16 height_;
    
};

#endif