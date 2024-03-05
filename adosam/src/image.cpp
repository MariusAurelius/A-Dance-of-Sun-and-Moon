#include "image.h"

Image::Image(SDL_Renderer* source_renderer, const std::string& file_path, const float& x_pos, const float& y_pos, const int& width, const int& height) 
: renderer_(source_renderer), surface_(nullptr), texture_(nullptr), rectangle_(nullptr){

    file_path_ = file_path;
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    width_ = width;
    height_ = height;
    Load();
}

Image::~Image(){
    Unload();
}


void Image::Load() {
    if (surface_ == nullptr){
        surface_ = IMG_Load(file_path_.c_str());
        
        if (surface_ == nullptr) {
            std::cerr << "Error loading image: " << IMG_GetError() << std::endl;
        }
    }

    if (texture_ == nullptr){
        texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
        
        if (texture_ == nullptr) {
            std::cerr << "Error Creating Texture: " << SDL_GetError() << std::endl;
        }
    }

    if (rectangle_ == nullptr){
        rectangle_ = new SDL_Rect;
        rectangle_ -> w = width_;
        rectangle_ -> h = height_;
    }

    rectangle_ -> x = x_pos_;
    rectangle_ -> y = y_pos_;
}


void Image::Unload(){
    if(surface_ != nullptr) {
        SDL_FreeSurface(surface_);
        surface_ = nullptr;
    }

    if(texture_ != nullptr){
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }

    if(rectangle_ != nullptr){
        delete rectangle_;
        rectangle_ = nullptr;
    }
}

void Image::Render(){
    Load();
    
    if(SDL_RenderCopy(renderer_, texture_, nullptr, rectangle_) != 0){
        std::cerr << "Error rendering Image class: " << SDL_GetError() << std::endl;
    }
}

float Image::GetXPos() const{
    return x_pos_;
}

float Image::GetYPos() const{
    return y_pos_;
}

void Image::SetXPos(const float& x_pos){
    x_pos_ = x_pos;
}

 void Image::SetYPos(const float& y_pos){
    y_pos_ = y_pos;
 }

Uint16 Image::GetWidth() const{
    return width_;
}

Uint16 Image::GetHeight() const{
    return height_;
}