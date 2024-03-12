#ifndef PROJECT_INC_LEVEL_H
#define PROJECT_INC_LEVEL_H

#include <SDL2/SDL_ttf.h>

#include "map.h"
#include "tile.h"
#include "player.h"
#include <deque>

using namespace std;

const int FRAMERATE = 60;

class Level{
public:

    Level(const string& img_tile_path, 
          const string& img_extension, const string& level_folder_path, 
          SDL_DisplayMode* displaymode, const float& song_bpm, 
          const float& first_beat_offset);

    ~Level();

    void Load(const string& level_folder_path, const float& song_bpm, 
              const float& first_beat_offset);

    void LoadNewTiles();

    void UnloadOutOfScreenTiles();

    void Render(SDL_Renderer* renderer);

    void Start();

    void Update();

    void AddTileToDisplay(Tile* tile_to_add);

    void UpdateTilesPosition();

    bool IsNextTileInDisplay(const Tile& current_tile, const string& next_tyle_type);

    bool IsTileOutOfScreen(const Tile& tile) const;

    Tile* GetOldestDisplayedTile() const;

    Tile* GetCurrentTile() const;

    void PopOldestDisplayedTile();

    void PlayerGoNextTile();

    void CheckPlayerAccuracy();

    int GetScore() const;

    int GetLife() const;

    void PlaySoundEffect();

    float GetMusicSecondsPerBeat() const;

private:

    SDL_DisplayMode* displaymode_;

    Map* map_;
    Player* player_;

    deque<Tile*>* displayed_tiles_;
    deque<Tile*>::iterator level_position_;

    string tile_image_path_;
    string image_extension_;

    float scroll_x_diff_;
    float scroll_y_diff_;
    float scroll_speed_;
    int score_;
    int life_;
    //bool finished_;
    
};


#endif