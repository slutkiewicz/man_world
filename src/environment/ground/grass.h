#pragma once

#include "ground.h"

class grass_t : public ground_t{
    public:
    grass_t(std::shared_ptr<config_t> config, cords_t cordinates) 
        : ground_t(config, cordinates)
    {
         color_ = color_t(0, 255, 0, 255); 
    };
};