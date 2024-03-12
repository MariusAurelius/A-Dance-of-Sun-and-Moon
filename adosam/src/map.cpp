#include "map.h"

Map::Map(const string& level_folder_path, const unsigned int& music_bpm, 
         const float& first_beat_offset)
         
{
    map_queue_ = new deque<string>;
    FileToMap(level_folder_path + "map.txt");
    map_music_ = new Conductor(music_bpm, first_beat_offset, level_folder_path);

}

Map::~Map() {

    delete map_music_;
    delete map_queue_;
    map_music_ = nullptr;
    map_queue_ = nullptr;

}

void Map::FileToMap(const string& map_path) {

    ifstream map_file(map_path);

    if (!map_file.is_open()) {
        cerr << "Error while opening the file : " 
             << map_path 
             << " - " 
             << strerror(errno) 
             << endl;
    } 

    else {
        
        string line;

        while (getline(map_file, line)) {

            map_queue_ -> push_back(line);

        }

        map_file.close();
    }

}

void Map::MapToFile(const string& map_path) const {

    ofstream map_file(map_path);

    if (!map_file.is_open()) {
        cerr << "Error while opening the file : " << map_path << endl;
    } 

    else {

        for (const string& line : *map_queue_) {
            map_file << line << endl;
        }

        map_file.close();
    }

}

void Map::Display() const {

    for (const string& element : *map_queue_) {
        cout << element << endl;
    }

}

string Map::GetNextTileTypeToDisplay() const {

    return map_queue_->front();

}

void Map::PopNewTile(){

    map_queue_->pop_front();

}

bool Map::IsEmpty() const{

    return map_queue_->empty();

}

void Map::UpdateMusic(){

    map_music_->Update();

}

void Map::PlayMusic(){

    map_music_->PlayMusic();

}

void Map::PlaySoundEffect(){

    map_music_->PlaySoundEffect();

}

float Map::GetMusicBpm() const{

    return map_music_->GetBpm();

}

float Map::GetMusicSecondsPerBeat() const{

    return map_music_->GetSecondsPerBeat();
    
}