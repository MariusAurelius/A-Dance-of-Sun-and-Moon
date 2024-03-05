#ifndef PROJECT_INC_BUTTON_H
#define PROJECT_INC_BUTTON_H

#include <SDL2/SDL.h>

#include "image.h"

/**
 * @class Button
 * 
 * @brief Classe représentant une image cliquable.
 * 
 * Cette classe hérite de la classe Image. Elle permet de manipuler un bouton.
 */
class Button : public Image{
public:
    /**
     * @brief Constructeur de la classe Button.
     * 
     * Initialise une image avec les champs qui sont en paramètre.
     * 
     * @param source_renderer 
     * @param file_path 
     * @param x_pos
     * @param y_pos
     * @param width
     * @param height
     */
    Button(SDL_Renderer* source_renderer, const std::string& file_path, 
           const float& x_pos, const float& y_pos, const int& width, const int& height);
    
    ~Button();

    bool CheckIfClicked(const SDL_Event& event);
    
};

#endif