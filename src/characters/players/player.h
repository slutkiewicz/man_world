#pragma once

#include "../characters.h"



class player_t : public characters_t
{
public:
    player_t(std::shared_ptr<config_t> config, cords_t cordinates) : characters_t(config, cordinates)
    {
        speed = 1;
        color_ = color_t(0,0,0,255);
    };
};