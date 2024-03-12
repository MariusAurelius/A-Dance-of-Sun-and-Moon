#ifndef PROJECT_INC_CONDUCTOR_H
#define PROJECT_INC_CONDUCTOR_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;


class Conductor{
public:

    Conductor(const float& music_bpm, const float& first_beat_offset, 
              const string& music_path);

    ~Conductor();

    /**
    * @brief procédure qui initialise les chaines de son pour la musique et 
    * les effets sonores.
    * 
    */
    void Load();

    /**
    * @brief procédure qui arrete de jouer tous les sons et libère les ressources 
    * appropriées.
    * 
    */
    void Unload();

    void PlayMusic();

    void PlaySoundEffect();

    void Pause();

    /**
     * @brief Met à jour 
     * 
     */
    void Update();

    float GetBpm() const;

    float GetSecondsPerBeat() const;

private:

    Mix_Chunk* music_;
    Mix_Chunk* sound_effect_;

    string level_folder_path_;

    Uint32 music_length_; 
    Uint32 start_time_;

    float bpm_;
    float seconds_per_beat_;
    double music_position_;
    float music_position_in_beats_;
    float first_beat_offset_;

};

#endif