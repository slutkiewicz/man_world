#pragma once

#include "high_ground.h"

class marble_block_t : public high_ground_t
{
public:
    marble_block_t(std::shared_ptr<config_t> config, cords_t cordinates)
        : high_ground_t(config, cordinates)
    {
        color_ = color_t(60, 60, 60, 255);
    };
};
