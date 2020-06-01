#pragma once

#include "../humanoids.hpp"



class player_t : public humanoids_t
{
public:
    void draw_f(SDL_Renderer *renderer);
    player_t(std::shared_ptr<config_t> config, cords_t cordinates) : humanoids_t(config, cordinates){};
};