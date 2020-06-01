#pragma once
#include <SDL2/SDL.h>

#include "utills.h"

class render_object_t
{
public:
    render_object_t(std::shared_ptr<config_t> config, cords_t cordinates);

    virtual void draw_f(SDL_Renderer *renderer){};
    cords_t cordinates_;
    // size_t size_;
    std::shared_ptr<config_t> config_;
    //SOME IMG OR COLOR ???????????
};