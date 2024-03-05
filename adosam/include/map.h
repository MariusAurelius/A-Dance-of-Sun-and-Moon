#ifndef PROJECT_INC_MAP_H
#define PROJECT_INC_MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <memory> 

#include "conductor.h"

class Map {
public:

    Map(const std::string& level_folder_path, const unsigned int& music_bpm, const float& first_beat_offset);

    ~Map();

    void FileToMap(const std::string& map_path);

    void MapToFile(const std::string& map_path) const;

    void Display() const;

    std::string GetQueueFront() const;

    void PopQueueFront();

    bool IsQueueEmpty();

    float GetMusicBpm() const;

    float GetMusicSpb() const;

    void UpdateMapMusic();

    void PlayMapMusic();

    void PlayMapSoundEffect();

private:

    Conductor* map_music_;

    std::deque<std::string>* map_queue_;

};
 
#endif