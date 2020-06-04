#pragma once

#include <vector>

#include "environment/ground/ground.h"
#include "environment/ground/marble.h"
#include "environment/ground/earth.h"
#include "environment/ground/water.h"
#include "environment/ground/fire.h"
#include "environment/ground/grass.h"

#include "environment/high_ground/high_ground.h"
#include "environment/high_ground/marble_block.h"
#include "environment/high_ground/tree.h"
#include "characters/characters.h"
#include "characters/players/player.h"
#include "items/item.h"
#include "utills.h"

class cell_t; // FORWARD DECLARE CELL

class map_t
{
public:
    map_t(std::shared_ptr<config_t> config);
    map_t();
    // std::shared_ptr<map_t> generate_map_f();
    std::shared_ptr<map_t> generate_map_f();
    void render_f(SDL_Renderer *renderer);
    camera_t camera_;
    void calculate_characters_f();
    void print_config_f();

    SDL_Rect render_viewport_;
    std::shared_ptr<std::map<cords_t, ground_t>> map_of_ground;
    std::shared_ptr<std::map<cords_t, high_ground_t>> map_of_high_ground;
    std::shared_ptr<std::map<cords_t, item_t>> map_of_items;
    std::shared_ptr<std::map<cords_t, characters_t>> map_of_creatures;
    std::shared_ptr<std::map<cords_t, characters_t>> map_of_players;
    void update_camera_f(const characters_t *player);

private:
    std::shared_ptr<std::map<cords_t, ground_t>> generate_ground_f();
    std::shared_ptr<std::map<cords_t, high_ground_t>>  generate_high_ground_f();
    std::shared_ptr<std::map<cords_t, item_t>>  generate_items_f();
    std::shared_ptr<std::map<cords_t, characters_t>>  generate_creatures_f();
    std::shared_ptr<std::map<cords_t, characters_t>>  generate_players_f();

    void render_ground_f(SDL_Renderer *renderer);
    void render_high_ground_f(SDL_Renderer *renderer);
    void render_items_f(SDL_Renderer *renderer);
    void render_creatures_f(SDL_Renderer *renderer);
    void render_players_f(SDL_Renderer *renderer);

    bool check_camera_f();

    std::shared_ptr<config_t> config_;
};

inline bool operator<(const cords_t &l, const cords_t &r)
{
    return (l.x_ < r.x_ || (l.x_ == r.x_ && l.y_ < r.y_));
}