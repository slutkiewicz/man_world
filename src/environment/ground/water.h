#pragma once

#include "ground.h"

class water_t : public ground_t{
    public:
    water_t(std::shared_ptr<config_t> config, cords_t cordinates) 
        : ground_t(config, cordinates)
    {
         color_ = color_t(0, 0, 255, 255); 
    };
};