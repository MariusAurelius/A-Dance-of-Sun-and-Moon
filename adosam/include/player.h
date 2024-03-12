#ifndef PROJECT_INC_PLAYER_H
#define PROJECT_INC_PLAYER_H

#include <SDL2/SDL.h>

#include "image.h"
#include "tile.h"

#include <deque>

using namespace std;

class Player {
public:

    Player(SDL_DisplayMode* display_mode, 
           const unsigned int& bpm);

    ~Player();

    void Render(SDL_Renderer* renderer);

    void UpdateRotation();

    void UpdatePosition(const float& x_diff, const float& y_diff);

    void RotateSun();

    void RotateMoon();

    void ChangeRotation();

    void ReverseRotation();

    void NextPosition();

    bool IsSunRotating() const;

    void MovePlayerToNextTile(const float& next_x_pos, const float& next_y_pos, const bool& is_next_tile_vertical);

    float GetSunDistanceFromPoint(const float& x, const float& y) const;

    float GetMoonDistanceFromPoint(const float& x, const float& y) const;

    void Scroll();

private:

    SDL_DisplayMode* display_mode_;

    unique_ptr<Image> sun_;
    unique_ptr<Image> moon_;

    float rotation_speed_;
    bool is_sun_rotating_;

};

#endif