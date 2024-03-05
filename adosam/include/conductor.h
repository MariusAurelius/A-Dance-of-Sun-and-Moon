#ifndef PROJECT_INC_CONDUCTOR_H
#define PROJECT_INC_CONDUCTOR_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class Conductor{
public:

    Conductor(const float& music_bpm, const float& first_beat_offset, const std::string& music_path);

    ~Conductor();

    void Load();

    void Unload();

    void PlayMusic();

    void PlaySoundEffect();

    void Pause();

    void Update();

    float GetBpm() const;

    float GetSecondsPerBeat() const;

private:

    Mix_Chunk* music_;
    Mix_Chunk* sound_effect_;

    std::string level_folder_path_;

    Uint32 music_length_; 
    Uint32 start_time_;

    float music_bpm_;
    float seconds_per_beat_;
    double music_position_;
    float music_position_in_beats_;
    float first_beat_offset_;

};

#endif