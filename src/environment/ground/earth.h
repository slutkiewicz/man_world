#pragma once

#include "ground.h"

class earth_t : public ground_t{
    public:
    earth_t(std::shared_ptr<config_t> config, cords_t cordinates) 
        : ground_t(config, cordinates)
    {
         color_ = color_t(40, 20, 15, 255); 
    };
};