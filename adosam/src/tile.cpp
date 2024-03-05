#include "tile.h"


Tile::Tile(SDL_Renderer* source_renderer, const std::string& file_path, const float& x_pos, const float& y_pos, const int& width, const int& height, const std::string& tile_type) 
: Image(source_renderer, file_path,  x_pos,  y_pos,  width, height){

    tile_type_ = GetType(tile_type);
}

Tile::~Tile(){
}

void Tile::GetCenter(float& x_pos, float& y_pos) const{
    if(tile_type_ == UP_VERTICAL || tile_type_ == DOWN_VERTICAL){
        x_pos = GetXPos() + GetWidth() / 4;
        y_pos = GetYPos() + GetHeight() / 2;
    }
    else{
        x_pos = GetXPos() + GetWidth() / 2;
        y_pos = GetYPos() + GetHeight() / 2;
    }
}

Tile::Types_ Tile::GetType(const std::string& type) const{
    if (type == "left-horizontal") {
        return LEFT_HORIZONTAL;
    }

    if (type == "right-horizontal") {
        return RIGHT_HORIZONTAL;
    }

    if (type == "down-vertical") {
        return DOWN_VERTICAL;
    }

    if (type == "left-down") {
        return LEFT_DOWN;
    }

    if (type == "left-up") {
        return LEFT_UP;
    }

    if (type == "right-down") {
        return RIGHT_DOWN;
    }

    if (type == "right-up") {
        return RIGHT_UP;
    }

    if (type == "up-right") {
        return UP_RIGHT;
    }

    if (type == "up-left") {
        return UP_LEFT;
    }

    if (type == "down-right") {
        return DOWN_RIGHT;
    }

    if (type == "down-left") {
        return DOWN_LEFT;
    }
    
    return UP_VERTICAL;
}

bool Tile::IsNextTileVertical(Tile* next_tile) const{
    if(next_tile -> tile_type_ == UP_VERTICAL || next_tile -> tile_type_ == DOWN_VERTICAL){
        return true;
    }
    return false;
}

bool Tile::IsNextTileCorner(Tile* next_tile) const{
    if(next_tile -> tile_type_ == UP_VERTICAL || next_tile -> tile_type_ == DOWN_VERTICAL
    || next_tile -> tile_type_ == LEFT_HORIZONTAL || next_tile -> tile_type_ == RIGHT_HORIZONTAL){
        return false;
    }
    return true;
}

void Tile::DetermineNextTileCoordinates(const std::string& next_tile_type, float& next_tile_x_pos, float& next_tile_y_pos) const{
    Tile::Types_ next_type = GetType(next_tile_type);

    switch(tile_type_){
        case LEFT_HORIZONTAL:
            switch(next_type){
                case LEFT_HORIZONTAL:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case LEFT_DOWN:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case LEFT_UP:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case RIGHT_HORIZONTAL:
            switch(next_type){
                case RIGHT_HORIZONTAL:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case RIGHT_DOWN:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case RIGHT_UP:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case DOWN_VERTICAL:
            switch(next_type){
                case DOWN_VERTICAL:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case DOWN_LEFT:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case DOWN_RIGHT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case UP_VERTICAL:
            switch(next_type){
                case UP_VERTICAL:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                case UP_LEFT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case UP_RIGHT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case LEFT_DOWN:
            switch(next_type){
                case UP_VERTICAL:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                case UP_RIGHT:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                case UP_LEFT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case LEFT_UP:
            switch(next_type){
                case DOWN_VERTICAL:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case DOWN_LEFT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case DOWN_RIGHT:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;
        
        case DOWN_LEFT:
            switch(next_type){
                case RIGHT_HORIZONTAL:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case RIGHT_DOWN:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case RIGHT_UP:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT/2;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case DOWN_RIGHT:
            switch(next_type){
                case LEFT_HORIZONTAL:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case LEFT_DOWN:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case LEFT_UP:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case UP_LEFT:
            switch(next_type){
                case RIGHT_HORIZONTAL:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case RIGHT_DOWN:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT/2;
                    break;
                case RIGHT_UP:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case UP_RIGHT:
            switch(next_type){
                case LEFT_HORIZONTAL:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case LEFT_DOWN:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                case LEFT_UP:
                    next_tile_x_pos = GetXPos() + TILE_WIDTH;
                    next_tile_y_pos = GetYPos();
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case RIGHT_DOWN:
            switch(next_type){
                case UP_VERTICAL:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                case UP_LEFT:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                case UP_RIGHT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() + TILE_HEIGHT;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;

        case RIGHT_UP:
            switch(next_type){
                case DOWN_VERTICAL:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case DOWN_LEFT:
                    next_tile_x_pos = GetXPos() - TILE_WIDTH/2;
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                case DOWN_RIGHT:
                    next_tile_x_pos = GetXPos();
                    next_tile_y_pos = GetYPos() - TILE_HEIGHT;
                    break;
                default:
                    std::cerr << "Unknown next Tile Type: "<< next_tile_type << std::endl;
                    break;
            }
            break;
        default:
            std::cerr << "Unknown Tile Type: " << tile_type_ << std::endl;
            break;    
    }
}
