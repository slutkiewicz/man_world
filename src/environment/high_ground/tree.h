#pragma once

#include "high_ground.h"

class tree_t : public high_ground_t
{
public:
    tree_t(std::shared_ptr<config_t> config, cords_t cordinates)
        : high_ground_t(config, cordinates)
    {
        color_ = color_t(0, 0, 60, 255);
    };
};
