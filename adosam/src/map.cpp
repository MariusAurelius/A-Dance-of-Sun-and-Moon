#include "map.h"

Map::Map(const std::string& level_folder_path, const unsigned int& music_bpm, const float& first_beat_offset) 
: map_queue_(new std::deque<std::string>) {

    FileToMap(level_folder_path + "map.txt");
    map_music_ = new Conductor(music_bpm, first_beat_offset, level_folder_path);
}

Map::~Map() {
    delete map_music_;
    delete map_queue_;
    map_music_ = nullptr;
    map_queue_ = nullptr;
}

void Map::FileToMap(const std::string& map_path) {
    std::ifstream map_file(map_path);

    if (!map_file.is_open()) {
        std::cerr << "Error while opening the file : " << map_path << " - " << strerror(errno) << std::endl;
    } 

    else {
        std::string line;

        while (std::getline(map_file, line)) {
            map_queue_ -> push_back(line);
        }

        map_file.close();
    }
}

void Map::MapToFile(const std::string& map_path) const {
    std::ofstream map_file(map_path);

    if (!map_file.is_open()) {
        std::cerr << "Error while opening the file : " << map_path << std::endl;
    } 

    else {

        for (const std::string& line : *map_queue_) {
            map_file << line << std::endl;
        }

        map_file.close();
    }
}

void Map::Display() const {

    for (const std::string& element : *map_queue_) {
        std::cout << element << std::endl;
    }
}

std::string Map::GetQueueFront() const {
    return map_queue_ -> front();
}

void Map::PopQueueFront(){
    map_queue_ -> pop_front();
}

bool Map::IsQueueEmpty(){
    return map_queue_ -> empty();
}

void Map::UpdateMapMusic(){
    map_music_ -> Update();
}

void Map::PlayMapMusic(){
    map_music_ -> PlayMusic();
}

void Map::PlayMapSoundEffect(){
    map_music_ ->  PlaySoundEffect();
}

float Map::GetMusicBpm() const{
    return map_music_ -> GetBpm();
}

float Map::GetMusicSpb() const{
    return map_music_ -> GetSecondsPerBeat();
}