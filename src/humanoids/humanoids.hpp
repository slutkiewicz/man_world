#pragma once

#include "../render_object.h"
#include "../utills.h"



class humanoids_t : public render_object_t
{
public:
    void draw_f(SDL_Renderer *renderer);
    humanoids_t(std::shared_ptr<config_t> config, cords_t cordinates) : render_object_t(config, cordinates){};
    int speed; 
};