#pragma once

#include "world.h"
#include "hardware.h"

enum event_enum { NONE=0, QUIT=1  };

class game_t
{
public:
    game_t(std::shared_ptr<config_t> config);
    game_t();
    void init_game_f();
    void start_game_f();
private:
    world_t create_world_f();
    std::shared_ptr<hardware_objects_t> create_hardware_f();

    world_t world_;
    std::shared_ptr<config_t> config_;
    std::shared_ptr<hardware_objects_t> hardware_;

};
