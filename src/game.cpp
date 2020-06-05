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
        const int MAX_PHYSICS_STEPS = 6;
        const double DESIRED_FPS = 60.0;
        const double DESIRED_FRAMERATE = 1000.0 / DESIRED_FPS;
        const double MAX_DELTA_TIME = 1.0;
        
        double tdt = 0; // przyrost czasu w sekundach
        long int frame_number = 0;
        long int df = 0; // przyrost ramek/milisekund

        Uint32 prev_tick = SDL_GetTicks();
        std::cout << "start start game" << std::endl;
        for (bool game_active = true; game_active;/*count++*/)
        {

            auto new_tick = SDL_GetTicks();
            tdt = (new_tick - prev_tick) / DESIRED_FRAMERATE;
            prev_tick = new_tick;

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
            int i = 0;
            while (tdt > 0.0 && i < MAX_PHYSICS_STEPS)
            {

                float dt = std::min(tdt, MAX_DELTA_TIME);
                world_.update_f(dt);
                i++;
                tdt -= dt;
            }
            world_.render_f(hardware_->renderer);
            
        }
        std::cout << "finish start game" << std::endl;
    };

    std::shared_ptr<hardware_objects_t> game_t::create_hardware_f()
    {
        return hardware_objects_t().init_hardware_subsystems(config_->screen_width_, config_->screen_height_, false);
    };
}