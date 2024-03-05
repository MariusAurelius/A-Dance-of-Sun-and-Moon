#include "level.h"

Level::Level(SDL_Renderer* renderer, const std::string& img_tile_path, const std::string& img_extension, const std::string& level_folder_path, SDL_DisplayMode* displaymode, const float& song_bpm, const float& first_beat_offset)
 : renderer_(renderer), displaymode_(displaymode){

    img_tile_path_ = img_tile_path; 
    img_extension_ = img_extension;
    level_map_ = new Map(level_folder_path, song_bpm, first_beat_offset);
    level_queue_ = new std::deque<Tile*>;
    std::string file_path = img_tile_path_ + level_map_ -> GetQueueFront() + img_extension_;
    level_queue_ -> push_front(new Tile(renderer_, file_path, (displaymode_ -> w/2) - TILE_WIDTH, (displaymode_ -> h/2) - TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, level_map_ -> GetQueueFront()));
    level_map_ -> PopQueueFront();
    level_position_ = level_queue_ -> begin();
    player_ = new Player(renderer_, displaymode_, level_map_ -> GetMusicBpm());
    scroll_speed_ = 60 * level_map_ -> GetMusicSpb();
    lives_ = 3;
    score_ = 0;
}

Level::~Level(){
    delete level_map_;
    
    for (Tile* tile : *level_queue_) {
        delete tile;
    }

    level_map_ = nullptr;
    level_queue_ = nullptr;
}

void Level::Start(){
    level_map_ -> PlayMapMusic();
}

void Level::Update(){
    player_ -> UpdatePosition(x_diff_, y_diff_);
    player_ -> UpdateRotation();
    UpdateTilesPos();
    level_map_ -> UpdateMapMusic();
    
    while(!level_map_ -> IsQueueEmpty() /*&& CheckIfInDisplay(*level_queue_->back(), level_map_->GetQueueFront())*/){
        float x_pos, y_pos;
        level_queue_ -> back() -> DetermineNextTileCoordinates(level_map_ -> GetQueueFront(), x_pos, y_pos);
        std::string file_path = img_tile_path_ + level_map_->GetQueueFront() + img_extension_;
        level_queue_ -> push_back(new Tile(renderer_, file_path, x_pos, y_pos, TILE_WIDTH, TILE_HEIGHT, level_map_->GetQueueFront()));
        level_map_ -> PopQueueFront();
    }

    while(!level_queue_ -> empty() && CheckIfOutOfDisplay( *(level_queue_ -> front()) )){
        delete level_queue_ -> front();
        level_queue_ -> pop_front();
    }
}


bool Level::CheckIfOutOfDisplay(const Tile& tile) const{

    if (tile.GetXPos() >= -TILE_WIDTH && tile.GetXPos() <= displaymode_ -> w && tile.GetYPos() >= -TILE_HEIGHT && tile.GetYPos() <= displaymode_ -> h) {
        return false;
    }
    return true;
}

bool Level::CheckIfInDisplay(const Tile& current_tile, const std::string& next_tyle_type) const{
    float x_pos, y_pos;
    current_tile.DetermineNextTileCoordinates(next_tyle_type, x_pos, y_pos);
    if (x_pos >= 0 && x_pos <= displaymode_->w && y_pos >= 0 && y_pos <= displaymode_->h) {
        return true;
    }
    return false;
}

void Level::Render() {
    for (const auto& tile : *level_queue_) {
        tile -> Render();
    }

    player_ -> Render();
    SDL_RenderPresent(renderer_);
}

void Level::PlayerGoNextTile(){
    level_map_ -> PlayMapSoundEffect();
    Tile* current_tile = *level_position_;
    ++level_position_;
    CheckAccuracy();
    bool is_next_tile_vertical = current_tile -> IsNextTileVertical(*level_position_);
    bool is_next_tile_corner = current_tile -> IsNextTileCorner(*level_position_);
    player_ -> MovePlayerToNextTile( (*level_position_) -> GetXPos(), (*level_position_) -> GetYPos(), is_next_tile_vertical );
    player_ -> ChangeRotation();
    if(is_next_tile_corner){
        x_diff_ = (current_tile -> GetXPos() - (*level_position_) -> GetXPos()) / (scroll_speed_);
        y_diff_ = (current_tile -> GetYPos() - (*level_position_) -> GetYPos()) / (scroll_speed_ * 0.7);
    }
    else{
        x_diff_ = (current_tile -> GetXPos() - (*level_position_) -> GetXPos()) / scroll_speed_;
        y_diff_ = (current_tile -> GetYPos() - (*level_position_) -> GetYPos()) / scroll_speed_;
    }
}

void Level::UpdateTilesPos(){

    for (Tile* tile : *level_queue_) {
        tile -> SetXPos(tile -> GetXPos() + x_diff_);
        tile -> SetYPos(tile -> GetYPos() + y_diff_);
    }
}

void Level::CheckAccuracy(){
    float next_tile_center_x, next_tile_center_y;
    float accuracy;
    (*level_position_) -> GetCenter(next_tile_center_x, next_tile_center_y);

    if(player_ -> GetRotationState()){
        accuracy = player_ -> GetSunDistanceFromPoint(next_tile_center_x, next_tile_center_y);
    }

    else{
        accuracy = player_ -> GetMoonDistanceFromPoint(next_tile_center_x, next_tile_center_y);
    }
    if(accuracy < 35){
        score_ += (int) 35 - accuracy;
    }
    else{
        lives_ -= 1;
    }
}

int Level::GetScore() const{
    return score_;
}