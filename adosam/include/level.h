#ifndef PROJECT_INC_LEVEL_H
#define PROJECT_INC_LEVEL_H

#include <SDL2/SDL_ttf.h>

#include "map.h"
#include "tile.h"
#include "player.h"
#include <deque>

class Level{
public:

    Level(SDL_Renderer* renderer, const std::string& img_tile_path, const std::string& img_extension, const std::string& level_folder_path, SDL_DisplayMode* displaymode, const float& song_bpm, const float& first_beat_offset);

    ~Level();

    void Render();

    bool CheckIfInDisplay(const Tile& current_tile, const std::string& next_tyle_type) const;

    bool CheckIfOutOfDisplay(const Tile& tile) const;

    void Update();

    void Start();

    void PlayerGoNextTile();

    void UpdateTilesPos();

    void CheckAccuracy();

    int GetScore() const;

private:

    SDL_Renderer* renderer_;
    SDL_DisplayMode* displaymode_;

    Map* level_map_;
    Player* player_;

    std::deque<Tile*>* level_queue_;
    std::deque<Tile*>::iterator level_position_;

    std::string img_tile_path_;
    std::string img_extension_;

    float x_diff_;
    float y_diff_;
    float scroll_speed_;
    int score_;
    int lives_;
    //bool finished_;
    
};


#endif