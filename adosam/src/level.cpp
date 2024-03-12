#include "level.h"

Level::Level(const string& tile_image_path, 
             const string& img_extension, 
             const string& level_folder_path, 
             SDL_DisplayMode* displaymode, 
             const float& song_bpm, 
             const float& first_beat_offset) : 
        displaymode_(displaymode), 
        tile_image_path_(tile_image_path), image_extension_(img_extension)
        
{

    Load(level_folder_path, song_bpm, first_beat_offset);

    scroll_speed_ = FRAMERATE * map_->GetMusicSecondsPerBeat();
    life_ = 3;

}

Level::~Level(){

    delete map_;
    
    for (Tile* tile : *displayed_tiles_) {
        delete tile;
    }

    map_ = nullptr;
    displayed_tiles_ = nullptr;

}

void Level::Load(const string& level_folder_path, 
                 const float& song_bpm, 
                 const float& first_beat_offset)
{

    map_ = new Map(level_folder_path, song_bpm, first_beat_offset);

    displayed_tiles_ = new deque<Tile*>;

    string first_tile_type = map_->GetNextTileTypeToDisplay();

    string first_tile_image_path = tile_image_path_ 
                                 + first_tile_type 
                                 + image_extension_;

    Tile* first_tile = new Tile(first_tile_image_path, 
                                (displaymode_->w/2) - TILE_WIDTH, 
                                (displaymode_->h/2) - TILE_HEIGHT, 
                                TILE_WIDTH, 
                                TILE_HEIGHT, 
                                first_tile_type);

    AddTileToDisplay(first_tile);

    level_position_ = displayed_tiles_->begin();

    player_ = new Player(displaymode_, map_->GetMusicBpm());

}

void Level::LoadNewTiles(){

    float new_tile_x_pos = 0, new_tile_y_pos = 0;

    Tile* current_tile;
    Tile* new_tile;

    string new_tile_type;
    
    while(!map_->IsEmpty() /*&& 
          IsNextTileInDisplay(*GetCurrentTile(), map_->GetNextTileTypeToDisplay())*/){ 

        current_tile = GetCurrentTile();

        new_tile_type = map_->GetNextTileTypeToDisplay();

        current_tile->DetermineNextTileCoordinates(new_tile_type, 
                                                   new_tile_x_pos, 
                                                   new_tile_y_pos);

        string new_tile_image_path = tile_image_path_ 
                                   + new_tile_type 
                                   + image_extension_;

        new_tile = new Tile(new_tile_image_path, 
                            new_tile_x_pos, 
                            new_tile_y_pos, 
                            TILE_WIDTH, 
                            TILE_HEIGHT, 
                            new_tile_type);

        AddTileToDisplay(new_tile);

    }

}

void Level::UnloadOutOfScreenTiles(){

    Tile* oldest_displayed_tile = GetOldestDisplayedTile();

    while (!displayed_tiles_->empty() && IsTileOutOfScreen(*oldest_displayed_tile)){

        delete oldest_displayed_tile;
        PopOldestDisplayedTile();

    }

}

void Level::Render(SDL_Renderer* renderer) {
     
    for (Tile* tile : *displayed_tiles_) {
        tile->Render(renderer);
    }

    player_->Render(renderer);

}

void Level::Start(){

    map_->PlayMusic();
    score_ = 0;

}

void Level::Update(){

    player_->UpdatePosition(scroll_x_diff_, scroll_y_diff_);
    player_->UpdateRotation();

    UpdateTilesPosition();

    map_->UpdateMusic();

    LoadNewTiles();

    UnloadOutOfScreenTiles();

}

void Level::AddTileToDisplay(Tile* tile_to_add){

    map_->PopNewTile();
    displayed_tiles_->push_back(tile_to_add);

}

void Level::UpdateTilesPosition(){

    for (Tile* tile : *displayed_tiles_) {

        tile -> SetXPos(tile->GetXPos() + scroll_x_diff_);
        tile -> SetYPos(tile->GetYPos() + scroll_y_diff_);

    }

}

bool Level::IsNextTileInDisplay(const Tile& current_tile, 
                             const string& next_tyle_type) 
{

    float x_pos = 0, y_pos = 0;

    current_tile.DetermineNextTileCoordinates(next_tyle_type, x_pos, y_pos);

    if (x_pos >= 0 && 
        x_pos <= displaymode_->w && 
        y_pos >= 0 && 
        y_pos <= displaymode_->h) 
    {

        return true;

    }

    return false;

}

bool Level::IsTileOutOfScreen(const Tile& tile) const{

    if (tile.GetXPos() >= -2*TILE_WIDTH && 
        tile.GetXPos() <= displaymode_->w && 
        tile.GetYPos() >= -2*TILE_HEIGHT && 
        tile.GetYPos() <= displaymode_ ->h) 
    {

        return false;

    }

    return true;

}

Tile* Level::GetOldestDisplayedTile() const{

    return displayed_tiles_->front();

}

Tile* Level::GetCurrentTile() const{

    return displayed_tiles_->back();

}

void Level::PopOldestDisplayedTile(){

    displayed_tiles_->pop_front();

}

void Level::PlayerGoNextTile(){

    //PlaySoundEffect();

    Tile* current_tile = *level_position_;
    ++level_position_;
    Tile* next_tile = *level_position_;

    CheckPlayerAccuracy();

    bool is_next_tile_vertical = current_tile->IsNextTileVertical(next_tile);
    bool is_next_tile_reverse = current_tile->IsNextTileReverse(next_tile);

    player_->MovePlayerToNextTile(next_tile->GetXPos(), 
                                  next_tile->GetYPos(), 
                                  is_next_tile_vertical);

    player_->ChangeRotation();

    scroll_x_diff_ = (current_tile->GetXPos() - next_tile->GetXPos()) / scroll_speed_;
    scroll_y_diff_ = (current_tile->GetYPos() - next_tile->GetYPos()) / scroll_speed_;

    if(is_next_tile_reverse){
        player_->ReverseRotation();
    }

}

void Level::CheckPlayerAccuracy(){

    float next_tile_center_x, next_tile_center_y;
    float accuracy;

    (*level_position_)->GetCenter(next_tile_center_x, next_tile_center_y);

    if(player_->IsSunRotating()){

        accuracy = player_->GetSunDistanceFromPoint(next_tile_center_x, 
                                                    next_tile_center_y);

    }

    else{

        accuracy = player_->GetMoonDistanceFromPoint(next_tile_center_x, 
                                                     next_tile_center_y);

    }
    
    if(accuracy < 50){

        score_ += (int) 50 - accuracy;

    }

    else if(accuracy > 80){

        life_ = 0;

    }

    else{

        life_ -= 1;

    }

}

int Level::GetScore() const{

    return score_;

}

int Level::GetLife() const{

    return life_;

}

void Level::PlaySoundEffect() {

    map_->PlaySoundEffect();

}

float Level::GetMusicSecondsPerBeat() const{

    return map_->GetMusicSecondsPerBeat();

}