#ifndef PROJECT_INC_GAMERENDERER_H
#define PROJECT_INC_GAMERENDERER_H

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "image.h"
#include "tile.h"
#include "level.h"
#include "button.h"
#include "text.h"

using namespace std;


class GameRenderer{
public:

    /**
     * @brief Construit un nouveau GameRenderer. 
     * Initialise SDL. Crée la fenetre, le renderer, et le font (pour le texte), 
     * en gérant les potentielles erreurs pour chaque cas.
     * Appelle InitMenu pour initialiser le Menu Principal.
     * 
     */
    GameRenderer();

    ~GameRenderer();

    void IfKeyDown();

    /**
     * @brief Vérifie si bouton Quit ou Play a été cliqué.
     * 
     * @param button_name nom du bouton
     * @param event evenement SDL
     * @return true si bouton Quit ou Play a été cliqué, en vérifiant leur validité.
     * @return false sinon.
     */
    bool IfMouseButtonDown(const string& button_name, const SDL_Event& event);

    /**
     * @brief Initialise les images et boutons du Menu Principal.
     * 
     */
    void InitMenu();

    void RenderMenu();

    /**
     * @brief Initialise le niveau, et les images et le texte du niveau.
     * 
     */
    void InitLevel();

    /**
     * @brief Met à jour le niveau, le score du joueur, et le nombre de vies du joueur.
     * 
     */
    void UpdateLevel();

    void RenderLevel();

    /**
     * @brief Commence le compte à rebours, puis commence le niveau.
     * 
     */
    void StartLevel();

    /**
     * @brief Crée et affiche un texte qui prend successivement les valeurs "3 2 1" 
     * pour préparer le joueur au début du niveau.
     * Joue l'effet sonore du niveau à chaque affichage.
     * L'attente entre chaque affichage est le meme que le BPM de la musique.
     */
    void Countdown();

private:

    SDL_Renderer* renderer_;
    SDL_DisplayMode* displaymode_;
    SDL_Window* window_;

    TTF_Font* font_;

    Text* score_;

    Text* life_;
    Image* life_image_;

    Level* level_;
    Image* level_background_;

    Image* menu_background_;
    Button* play_button_;

    Button* quit_button_;

    string img_tile_path_;
    string img_extension_;
    
};

#endif