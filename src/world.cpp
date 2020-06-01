#include "world.h"

world_t::world_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};

world_t::world_t(){};

void world_t::render_map_f(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    map_->render_map_f(renderer);
    SDL_RenderPresent(renderer);
};
void world_t::calculate_events_f()
{
    map_->calculate_humanoids_f(); // pass events 
};
void world_t::create_map_f()
{
    std::cout << "start create map" << std::endl;
    map_ = map_t(config_).generate_map_f();
    std::cout << "finish create map" << std::endl;
};
