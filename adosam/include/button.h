#ifndef PROJECT_INC_BUTTON_H
#define PROJECT_INC_BUTTON_H

#include <SDL2/SDL.h>

#include "image.h"

using namespace std;


class Button : public Image{
public:

    Button(const string& file_path, 
           const float& x_pos, const float& y_pos, 
           const int& width, const int& height);
    
    ~Button();

    /**
    * @brief fonction renvoyant vrai si le bouton a été cliqué en vérifiant que 
    * ses coordonnées sont bien dans la fenetre.
    * 
    * @param event evenement SDL
    * @return true 
    * @return false 
    */
    bool CheckIfClicked(const SDL_Event& event);
    
};

#endif