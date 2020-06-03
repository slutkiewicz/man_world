#pragma once

#include "ground.h"

class marble_t : public ground_t
{
public:
    marble_t(std::shared_ptr<config_t> config, cords_t cordinates) 
        : ground_t(config, cordinates) 
    {
         color_ = color_t(255, 255, 255, 255); 
    };
};