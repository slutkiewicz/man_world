#pragma once

#include "../humanoids.hpp"




class creature_t : public humanoids_t
{
public:
    void draw_f(SDL_Renderer *renderer);
    creature_t(std::shared_ptr<config_t> config, cords_t cordinates) : humanoids_t(config, cordinates){};
};