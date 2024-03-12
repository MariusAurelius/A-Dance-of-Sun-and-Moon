#ifndef PROJECT_INC_TILES_H
#define PROJECT_INC_TILES_H

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

#include "image.h"

const int TILE_WIDTH = 100, TILE_HEIGHT = 80;

class Tile : public Image{
public:

    Tile(const std::string& file_path, const float& x_pos, const float& y_pos, const int& width, const int& height, const std::string& tile_type);

    ~Tile ();

    void DetermineNextTileCoordinates(const std::string& next_tile_type, float& next_tile_x_pos, float& next_tile_y_pos) const;

    bool IsNextTileVertical(Tile* next_tile) const;

    bool IsNextTileReverse(Tile* next_tile) const;

    void GetCenter(float& x_pos, float& y_pos) const;


private:

    enum Types_ { LEFT_HORIZONTAL, RIGHT_HORIZONTAL, LEFT_DOWN, LEFT_UP, 
                  RIGHT_DOWN, RIGHT_UP, DOWN_LEFT, UP_LEFT, DOWN_RIGHT, 
                  UP_RIGHT, DOWN_VERTICAL, UP_VERTICAL, LEFT_SWIRL
                };

    Types_ GetType(const std::string& type) const;

    Types_ tile_type_;

};

#endif