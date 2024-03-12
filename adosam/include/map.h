#ifndef PROJECT_INC_MAP_H
#define PROJECT_INC_MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <memory> 

#include "conductor.h"

using namespace std;

class Map {
public:

    Map(const string& level_folder_path, const unsigned int& music_bpm, 
        const float& first_beat_offset);

    ~Map();

    void FileToMap(const string& map_path);

    void MapToFile(const string& map_path) const;

    void Display() const;

    string GetNextTileTypeToDisplay() const;

    void PopNewTile();

    bool IsEmpty()const ;

    float GetMusicBpm() const;

    float GetMusicSecondsPerBeat() const;

    void UpdateMusic();

    void PlayMusic();

    void PlaySoundEffect();

private:

    Conductor* map_music_;

    deque<string>* map_queue_;

};
 
#endif