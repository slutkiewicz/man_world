#pragma once
#include <SDL2/SDL.h>

#include "map.h"
class world_t
{
public:
    world_t(std::shared_ptr<config_t> config);
    world_t();

    void render_f(SDL_Renderer *renderer);
    void create_map_f();
    void handle_event_f();
    void update_f(double dt);

private:
    std::shared_ptr<config_t> config_;
    std::shared_ptr<map_t> map_;
    void update_players_f(double dt);
    void calculate_characters_f(double dt);
    void handle_players_f();
    bool if_collision(characters_t *character);


};