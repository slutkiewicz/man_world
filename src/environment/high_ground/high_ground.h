#pragma once

#include "../../render_object.h"
#include "../../utills.h"

class high_ground_t : render_object_t
{
public:
    void draw_f(SDL_Renderer *renderer)
    {
        SDL_Rect rect = {((cordinates_.x_) * (config_->cell_size_)),
                         ((cordinates_.y_) * (config_->cell_size_)),
                         config_->cell_size_, config_->cell_size_};
        SDL_SetRenderDrawColor(renderer,
                               255,
                               255,
                               255,
                               255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_Rect rect2 = {((cordinates_.x_) * (config_->cell_size_)),
                    ((cordinates_.y_) * (config_->cell_size_)),
                    config_->cell_size_, config_->cell_size_};
        SDL_SetRenderDrawColor(renderer,
                               color_.r_,
                               color_.g_,
                               color_.b_,
                               color_.a_);
        SDL_RenderFillRect(renderer, &rect2);
    };
    high_ground_t(std::shared_ptr<config_t> config, cords_t cordinates) : render_object_t(config, cordinates){};
    color_t color_;
};