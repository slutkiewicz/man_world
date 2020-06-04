#pragma once

#include "../render_object.h"
#include "../utills.h"

class characters_t : public render_object_t
{
public:
    characters_t(std::shared_ptr<config_t> config, cords_t cordinates) : render_object_t(config, cordinates)
    {
        cordinates_dt_ = cords_dt_t(cordinates_.x_,cordinates_.y_);
        direction_ = MOVEMENT::NONE;
    };
    //add destination for map click on screen click
    int speed;
    color_t color_;
    cords_dt_t cordinates_dt_;
    cords_t cordinates_prev_;

    MOVEMENT direction_;
    void draw_f(SDL_Renderer *renderer)
    {
        SDL_Rect rect = {((cordinates_.x_) * (config_->cell_size_)),
                         ((cordinates_.y_) * (config_->cell_size_)),
                         config_->cell_size_, config_->cell_size_};

        SDL_SetRenderDrawColor(renderer,
                               color_.r_,
                               color_.g_,
                               color_.b_,
                               color_.a_);

        SDL_RenderFillRect(renderer, &rect);

    };
};