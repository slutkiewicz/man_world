#include "game.h"

game_t::game_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
game_t::game_t(){

};

void game_t::init_game_f()
{
    std::cout << "start init game" << std::endl;
    hardware_ = create_hardware_f();
    printf("config: %d  %d %d %d", config_->height_, config_->width_, config_->cell_size_, config_->map_size_);

    world_ = world_t(config_);
    world_.create_map_f();
    std::cout << "finish init game" << std::endl;
};
void game_t::start_game_f()
{

    //TODO new way for calculating frames
    std::cout << "start start game" << std::endl;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 15;
    const int frameDelay = 1000 / FPS;
    long int time = 1;
    for (bool game_active = true; game_active; time++)
    {
        frameStart = SDL_GetTicks();
        SDL_Event event;
        event_enum evnt = NONE;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                evnt = QUIT;
                break;
            }
        }
        if (evnt != NONE)
        {
            game_active = false;
        }

        world_.render_map_f(hardware_->renderer);
        if (time % 10 == 0)
        {
            world_.calculate_events_f();
        }

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    std::cout << "finish start game" << std::endl;
};

std::shared_ptr<hardware_objects_t> game_t::create_hardware_f()
{
    return hardware_objects_t().init_hardware_subsystems(config_->width_, config_->height_, false);
};