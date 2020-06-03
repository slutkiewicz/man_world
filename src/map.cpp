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
    // map->map_of_high_ground = generate_high_ground_f();
    // map->map_of_items = generate_items_f();
    map->map_of_players = generate_players_f();

    return std::shared_ptr<map_t>(map);
};

void map_t::render_f(SDL_Renderer *renderer)
{
    render_ground_f(renderer);
    // render_high_ground_f(renderer);
    // render_items_f(renderer);
    render_players_f(renderer);
};

std::shared_ptr<std::map<cords_t, high_ground_t>> map_t::generate_high_ground_f()
{
    std::random_device rd;
    std::mt19937 eng(1);
    std::uniform_real_distribution<> distrReal(0, 1);

    std::cout << "start generate high ground" << std::endl;
    std::map<cords_t, high_ground_t> *hight_ground_map = new std::map<cords_t, high_ground_t>();
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

Uint8 get_pixel2(SDL_Surface *image, int x, int y)
{
    Uint8 index;
    index = *(Uint8 *)image->pixels + (y * image->pitch +
                                       x * sizeof(index));
    ;
    return index;
};
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0; /* shouldn't happen, but avoids warnings */
    }
}

std::shared_ptr<std::map<cords_t, ground_t>> map_t::generate_ground_f()
{
    std::cout << "start generate ground" << std::endl;
    SDL_Surface *image;
    SDL_PixelFormat *fmt;
    SDL_Color *color_;
    Uint32 index;

    image = utills::load_img_f(config_->ground_map_path);
    fmt = image->format;
    auto bp = fmt->BitsPerPixel;
    /* Check the bitdepth of the surface */
    if (bp != 8)
    {
        fprintf(stderr, "Not an 8-bit surface.\n");
        std::cout << unsigned(bp) << std::endl;
        return nullptr;
    }
    /* Lock the surface */
    SDL_LockSurface(image);

    // // /* Get the topleft pixel */
    // index = *(Uint8 *)image->pixels;
    // // index = get_pixel(image, 49, 49);

    // color_ = &fmt->palette->colors[index];
    // /* Unlock the surface */
    // printf("image size h:%d w:%d Pixel Color-> Red: %d, Green: %d, Blue: %d. Index: %d\n",
    //        image->h, image->w, color_->r, color_->g, color_->b, index);

    std::map<cords_t, ground_t> *ground_map = new std::map<cords_t, ground_t>;

    for (unsigned int y = 0; y < image->h; y++)
    {
        for (unsigned int x = 0; x < image->w; x++)
        {
            cords_t cords(x, y);
            index = get_pixel(image, x, y);
            Uint8 r;
            Uint8 g;
            Uint8 b;
            SDL_GetRGB(index, fmt, &r, &g, &b);
            color_ = &fmt->palette->colors[index];
            // printf("x-> %d y-> %d  Pixel Color-> Red: %d, Green: %d, Blue: %d. Index: %d\n",
            //        x, y, unsigned(r), unsigned(g), unsigned(b), index);
            if (unsigned(r) > 250 & unsigned(b) > 250 & unsigned(g) > 250)
            {
                // printf("white\n");
                ground_map->emplace(cords, marble_t(config_, cords));

                //set map to marble
            }
            else if (unsigned(r) < 5 & unsigned(b) < 5 & unsigned(g) < 5)
            {
                // printf("black\n");
                ground_map->emplace(cords, earth_t(config_, cords));
                //set map to earth
            }
            else if (unsigned(g) > 250)
            {
                // printf("green\n");
                ground_map->emplace(cords, grass_t(config_, cords));
                //set map to grass
            }
            else if (unsigned(r) > 250)
            {
                // printf("red\n");
                ground_map->emplace(cords, fire_t(config_, cords));
                //set map to fire
            }
            else if (unsigned(b) > 250)
            {
                // printf("blue\n");
                ground_map->emplace(cords, water_t(config_, cords));
                //set map to water
            }

            // if (image->)
            //     cords_t cords(x, y);
            ground_t ground(config_, cords);
            // //TODO
            // ground_map->emplace(cords, ground);
        }
    }
    SDL_UnlockSurface(image);
    utills::free_img_f(image);

    // std::map<cords_t, ground_t> *ground_map = &std::map<cords_t, ground_t>();

    // unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    // unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    // for (unsigned int x = 0; x < cells_width_n; x++)
    // {
    //     for (unsigned int y = 0; y < cells_height_n; y++)
    //     {
    //         cords_t cords(x, y);
    //         ground_t ground(config_, cords);
    //         //TODO
    //         ground_map->emplace(cords, ground);
    //     }
    // }
    std::cout << "finish generate ground" << std::endl;

    return std::shared_ptr<std::map<cords_t, ground_t>>(ground_map);
};

std::shared_ptr<std::map<cords_t, item_t>> map_t::generate_items_f()
{
    std::cout << "start generate items" << std::endl;
    std::map<cords_t, item_t> *item_map = new std::map<cords_t, item_t>;

    return std::shared_ptr<std::map<cords_t, item_t>>(item_map);
};
std::shared_ptr<std::map<cords_t, characters_t>> map_t::generate_players_f()
{
    std::cout << "start generate players" << std::endl;
    std::map<cords_t, characters_t> *characters_map = new std::map<cords_t, characters_t>;
    cords_t cords = cords_t(25, 25);
    characters_map->emplace(cords, player_t(config_, cords));
    return std::shared_ptr<std::map<cords_t, characters_t>>(characters_map);
};

std::shared_ptr<std::map<cords_t, characters_t>> map_t::generate_creatures_f()
{
    std::cout << "start generate creatures" << std::endl;
    std::map<cords_t, characters_t> *characters_map = new std::map<cords_t, characters_t>;

    return std::shared_ptr<std::map<cords_t, characters_t>>(characters_map);
};

void map_t::render_items_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, item_t>::iterator it = map_of_items->begin(); it != map_of_items->end(); ++it)
    {
        if (it != map_of_items->end())
        {
            it->second.draw_f(renderer);
        }
    }
};

void map_t::render_players_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, characters_t>::iterator it = map_of_players->begin(); it != map_of_players->end(); ++it)
    {
        if (it != map_of_players->end())
        {
            it->second.draw_f(renderer);
        }
    }
};

void map_t::render_creatures_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, characters_t>::iterator it = map_of_creatures->begin(); it != map_of_creatures->end(); ++it)
    {
        if (it != map_of_creatures->end())
        {
            it->second.draw_f(renderer);
        }
    }
};

void map_t::render_high_ground_f(SDL_Renderer *renderer)
{
    for (std::map<cords_t, high_ground_t>::iterator it = map_of_high_ground->begin(); it != map_of_high_ground->end(); ++it)
    {
        if (it != map_of_high_ground->end())
        {
            it->second.draw_f(renderer);
        }
    }
};

void map_t::render_ground_f(SDL_Renderer *renderer)
{
    //maybe return pointer
    // unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    // unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_width_n = 50;
    unsigned int cells_height_n = 50;

    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            map_of_ground->at(cords_t(x, y)).draw_f(renderer);
        }
    }
};

void map_t::calculate_characters_f(){

};

