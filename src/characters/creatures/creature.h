#pragma once

#include "../characters.h"




class creature_t : public characters_t
{
public:
    void draw_f(SDL_Renderer *renderer){};
    creature_t(std::shared_ptr<config_t> config, cords_t cordinates) : characters_t(config, cordinates){};
};