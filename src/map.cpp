#include "map.h"
#include <random>

map_t::map_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
map_t::map_t(){};

void map_t::print_config_f()
{
    printf("config: %d  %d %d %d", config_->height_, config_->width_, config_->cell_size_, config_->map_size_);
};

std::shared_ptr<map_t> map_t::generate_map_f()
{
    map_t *map = new map_t(config_);
    map->map_of_ground = generate_ground_f();
    map->map_of_high_ground = generate_high_ground_f();
    map->map_of_items = generate_items_f();
    map->map_of_humanoids = generate_humanoids_f();

    return std::shared_ptr<map_t>(map);
};

void map_t::render_map_f(SDL_Renderer *renderer)
{
    render_ground_f(renderer);
    render_high_ground_f(renderer);
    render_items_f(renderer);
    render_humanoids_f(renderer);
};

std::shared_ptr<std::map<cords_t, high_ground_t>> map_t::generate_high_ground_f()
{
    std::random_device rd;
    std::mt19937 eng(1);
    std::uniform_real_distribution<> distrReal(0, 1);

    std::cout << "start generate high ground" << std::endl;
    std::map<cords_t, high_ground_t> *hight_ground_map =  &std::map<cords_t, high_ground_t>();
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cords_t cords(x, y);
            high_ground_t high_ground(config_, cords);
            //TODO
            hight_ground_map->emplace(cords, high_ground);
        }
    }

    return std::shared_ptr<std::map<cords_t, high_ground_t>>(hight_ground_map);
};

std::shared_ptr<std::map<cords_t, ground_t>> map_t::generate_ground_f()
{
    std::cout << "start generate ground" << std::endl;
    std::map<cords_t, ground_t> *ground_map = &std::map<cords_t, ground_t>();

    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cords_t cords(x, y);
            ground_t ground(config_, cords);
            //TODO
            ground_map->emplace(cords, ground);
        }
    }
    return std::shared_ptr<std::map<cords_t, ground_t>>(ground_map);
};

std::shared_ptr<std::map<cords_t, item_t>> map_t::generate_items_f()
{
    std::cout << "start generate items" << std::endl;
    std::map<cords_t, item_t> *item_map = &std::map<cords_t, item_t>();


    return std::shared_ptr<std::map<cords_t, item_t>>(item_map);
};
std::shared_ptr<std::map<cords_t, humanoids_t>> map_t::generate_humanoids_f()
{
    std::cout << "start generate humanoids" << std::endl;
    std::map<cords_t, humanoids_t> *humanoids_map = &std::map<cords_t, humanoids_t>();


    return std::shared_ptr<std::map<cords_t, humanoids_t>>(humanoids_map);
};

void map_t::render_items_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, item_t>::iterator it = map_of_items->begin(); it != map_of_items->end(); ++it)
    {
        it->second.draw_f(renderer);
    }
};

void map_t::render_humanoids_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, humanoids_t>::iterator it = map_of_humanoids->begin(); it != map_of_humanoids->end(); ++it)
    {
        it->second.draw_f(renderer);
    }
};

void map_t::render_high_ground_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, high_ground_t>::iterator it = map_of_high_ground->begin(); it != map_of_high_ground->end(); ++it)
    {
        it->second.draw_f(renderer);
    }
};

void map_t::render_ground_f(SDL_Renderer *renderer)
{
    //maybe return pointer
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);

    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            // env_map_->at(cords_t(x, y)).draw_f(renderer);
        }
    }
};

void map_t::calculate_humanoids_f(){

};

inline bool operator<(const cords_t &l, const cords_t &r)
{
    return (l.x_ < r.x_ || (l.x_ == r.x_ && l.y_ < r.y_));
}