#include "player.h"

Player::Player(SDL_Renderer* renderer, SDL_DisplayMode* display_mode, const unsigned int& bpm){

    display_mode_ = display_mode;
    sun_ = std::make_unique<Image>(renderer, "../assets/sun2.png", (display_mode -> w / 2) - TILE_WIDTH + 20, (display_mode -> h / 2) - TILE_HEIGHT + 15, 50, 50);
    moon_ = std::make_unique<Image>(renderer, "../assets/moon2.png", (display_mode -> w / 2) - TILE_WIDTH - 80, (display_mode -> h / 2) - TILE_HEIGHT + 15, 50, 50);
    rotation_speed_ = (M_PI * bpm) / (60 * 60);
    is_sun_rotating_ = false;
}

Player::~Player(){
}

void Player::Render(){
    sun_->Render();
    moon_->Render();
}

void Player::UpdateRotation(){
    if(is_sun_rotating_){
        RotateSun();
    }

    else{
        RotateMoon();
    }
}

void Player::UpdatePosition(const float& x_diff, const float& y_diff){
    sun_ -> SetXPos(sun_ ->GetXPos() + x_diff);
    sun_ -> SetYPos(sun_->GetYPos() + y_diff);
    moon_ -> SetXPos(moon_->GetXPos() + x_diff); 
    moon_ -> SetYPos(moon_->GetYPos() + y_diff);
}

void Player::RotateMoon() {
    float initial_x = moon_->GetXPos();
    float initial_y = moon_->GetYPos();
    moon_ -> SetXPos(cos(rotation_speed_) * (initial_x - sun_ -> GetXPos()) - sin(rotation_speed_) * (initial_y - sun_ -> GetYPos()) + sun_ -> GetXPos());
    moon_ -> SetYPos(sin(rotation_speed_) * (initial_x - sun_ -> GetXPos()) + cos(rotation_speed_) * (initial_y - sun_ -> GetYPos()) + sun_ -> GetYPos());
}

void Player::RotateSun() {
    float initial_x = sun_ -> GetXPos();
    float initial_y = sun_ -> GetYPos();
    sun_ -> SetXPos(cos(rotation_speed_) * (initial_x - moon_ -> GetXPos()) - sin(rotation_speed_) * (initial_y - moon_ -> GetYPos()) + moon_ -> GetXPos());
    sun_ -> SetYPos(sin(rotation_speed_) * (initial_x - moon_ -> GetXPos()) + cos(rotation_speed_) * (initial_y - moon_ -> GetYPos()) + moon_ -> GetYPos());

}

void Player::ChangeRotation(){
    is_sun_rotating_ = !is_sun_rotating_;
}

bool Player::GetRotationState() const{
    return is_sun_rotating_;
}

void Player::MovePlayerToNextTile(const float& next_x_pos, const float& next_y_pos, const bool& next_is_vertical){
    if(is_sun_rotating_){

        if(next_is_vertical){
            sun_ -> SetXPos(next_x_pos);
            sun_ -> SetYPos(next_y_pos + 15);
        }

        else{
            sun_ -> SetXPos(next_x_pos + 25);
            sun_ -> SetYPos(next_y_pos + 15);
        }

    }

    else{

        if(next_is_vertical){
            moon_ -> SetXPos(next_x_pos);
            moon_ -> SetYPos(next_y_pos + 15);
        }

        else{
            moon_ -> SetXPos(next_x_pos + 25);
            moon_ -> SetYPos(next_y_pos + 15);
        }

    }
}

float Player::GetSunDistanceFromPoint(const float& x, const float& y){
    float sun_center_x = sun_ -> GetXPos() + sun_ -> GetWidth() / 2;
    float sun_center_y = sun_ -> GetYPos() + sun_ -> GetHeight() / 2;
    return sqrt( std::pow(x - sun_center_x, 2) + std::pow(y - sun_center_y, 2) );
}

float Player::GetMoonDistanceFromPoint(const float& x, const float& y){
    float moon_center_x = moon_ -> GetXPos() + moon_ -> GetWidth() / 2;
    float moon_center_y = moon_ -> GetYPos() + moon_ -> GetHeight() / 2;
    return sqrt( std::pow(x - moon_center_x, 2) + std::pow(y - moon_center_y, 2) );
}