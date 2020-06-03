#include "game.h"
namespace game
{

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
        double dt = 0; // przyrost czasu w sekundach
        long int frame_number = 0;
        long int df = 0; // przyrost ramek/milisekund
        Uint32 prev_tick = SDL_GetTicks();

        //TODO new way for calculating frames
        std::cout << "start start game" << std::endl;
        for (bool game_active = true; game_active;)
        {
            SDL_Event event;
            EVENT_ENUM evnt = EVENT_ENUM::NONE;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    evnt = EVENT_ENUM::QUIT;
                    break;
                default:
                    break;
                }
            }
            if (evnt != NONE)
            {
                game_active = false;
            }
            
            world_.handle_event_f();
            world_.update_f(dt);

            world_.render_f(hardware_->renderer);

            auto new_tick = SDL_GetTicks();
            dt = (new_tick - prev_tick) / 100.0;
            frame_number += (df = (new_tick - prev_tick));
            prev_tick = new_tick;
        }
        std::cout << "finish start game" << std::endl;
    };

    std::shared_ptr<hardware_objects_t> game_t::create_hardware_f()
    {
        return hardware_objects_t().init_hardware_subsystems(config_->width_, config_->height_, false);
    };
} // namespace game