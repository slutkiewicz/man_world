#pragma once

#include "ground.h"

class fire_t : public ground_t
{
public:
    fire_t(std::shared_ptr<config_t> config, cords_t cordinates)
        : ground_t(config, cordinates)
    {
        speed_ = 2.0;
        color_ = color_t(255, 0, 0, 255);
    };
};