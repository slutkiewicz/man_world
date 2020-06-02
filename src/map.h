#pragma once

#include <vector>

#include "environment/ground/ground.hpp"
#include "environment/high_ground/high_ground.hpp"
#include "humanoids/humanoids.hpp"
#include "items/item.hpp"
#include "utills.h"

class cell_t; // FORWARD DECLARE CELL

class map_t
{
public:
    map_t(std::shared_ptr<config_t> config);
    map_t();

    // std::shared_ptr<map_t> generate_map_f();
    std::shared_ptr<map_t> generate_map_f();
    void render_map_f(SDL_Renderer *renderer);

    void calculate_humanoids_f();
    void print_config_f();

    std::shared_ptr<std::map<cords_t, ground_t>> map_of_ground;
    std::shared_ptr<std::map<cords_t, high_ground_t>> map_of_high_ground;
    std::shared_ptr<std::map<cords_t, item_t>> map_of_items;
    std::shared_ptr<std::map<cords_t, humanoids_t>> map_of_humanoids;

private:
    std::shared_ptr<std::map<cords_t, ground_t>> generate_ground_f();
    std::shared_ptr<std::map<cords_t, high_ground_t>>  generate_high_ground_f();
    std::shared_ptr<std::map<cords_t, item_t>>  generate_items_f();
    std::shared_ptr<std::map<cords_t, humanoids_t>>  generate_humanoids_f();

    void render_ground_f(SDL_Renderer *renderer);
    void render_high_ground_f(SDL_Renderer *renderer);
    void render_items_f(SDL_Renderer *renderer);
    void render_humanoids_f(SDL_Renderer *renderer);

    std::shared_ptr<config_t> config_;
};

inline bool operator<(const cords_t &l, const cords_t &r);