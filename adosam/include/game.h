#ifndef PROJECT_INC_GAME_H
#define PROJECT_INC_GAME_H

#include <memory>

#include <SDL2/SDL.h>

#include "game_renderer.h"

class Game {
public:
    
    /**
     * @brief Construit un nouveau Game. Initialise les booléens nécessaires 
     * pour la boucle du jeu.
     * 
     */
    Game();

    ~Game();

    /**
     * @brief Procédure contenant la boucle principale. Gère les inputs clavier 
     * et sourie.
     * Tant que le joueur est dans un niveau, on met a jour le niveau 
     * et l'affichage.
     * 
     */
    void Run();

    uint GetFramerate();

private:

    SDL_Event event_;

    GameRenderer* game_renderer_;

    bool is_running_;

    bool is_in_game_;

};

#endif