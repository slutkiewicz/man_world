#include "map.h"
#include <random>

map_t::map_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
map_t::map_t(){};

void map_t::print_config_f()
{
    printf("config: %d  %d %d %d", config_->map_height_, config_->map_width_, config_->cell_size_, config_->map_size_);
};

std::shared_ptr<map_t> map_t::generate_map_f()
{
    map_t *map = new map_t(config_);
    camera_ = camera_t();
    map->map_of_ground = generate_ground_f();
    map->map_of_high_ground = generate_high_ground_f();
    // map->map_of_items = generate_items_f();
    map->map_of_players = generate_players_f();

    if (config_->map_width_ < config_->screen_width_)
    {
        map->camera_.width_ = config_->map_width_;
    }
    else
    {
        map->camera_.width_ = config_->screen_width_;
    }

    if (config_->map_height_ < config_->screen_height_)
    {
        map->camera_.height_ = config_->map_height_;
    }
    else
    {
        map->camera_.height_ = config_->screen_height_;
    }
    map->camera_.cords_.x_ = map->camera_.width_ / 2;
    map->camera_.cords_.y_ = map->camera_.height_ / 2;
    printf("y %d | x %d | cameraHigh %d | cameraWidth %d\n", map->camera_.cords_.y_, map->camera_.cords_.x_, map->camera_.height_, map->camera_.width_);

    return std::shared_ptr<map_t>(map);
};

void map_t::update_camera_f(const characters_t *player)
{

        printf("in\n");
        printf("cameraCOrds x%d y%d\n",camera_.cords_.x_,camera_.cords_.y_);

    if ((( player->cordinates_.x_ < config_->map_width_/10 -(camera_.width_/2)/10)) && (player->cordinates_.x_ > (camera_.width_/2)/10))
    {
        camera_.cords_.x_ = player->cordinates_.x_*10;
    }
    if (((config_->map_height_ - player->cordinates_.y_) > (camera_.height_/2)/10) && (player->cordinates_.y_ > (camera_.height_/2)/10))
    {
        camera_.cords_.y_ = player->cordinates_.y_*10;
    }
        printf("cameraCOrds x%d y%d\n",camera_.cords_.x_,camera_.cords_.y_);
        printf("after\n");
};

void map_t::render_f(SDL_Renderer *renderer)
{
    render_ground_f(renderer);
    render_high_ground_f(renderer);
    // render_items_f(renderer);
    render_players_f(renderer);
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

std::shared_ptr<std::map<cords_t, high_ground_t>> map_t::generate_high_ground_f()
{

    std::cout << "start generate high ground" << std::endl;
    SDL_Surface *image;
    SDL_PixelFormat *fmt;
    SDL_Color *color_;
    Uint32 index;

    image = utills::load_img_f(config_->high_ground_map_path_);
    fmt = image->format;
    int w, h;
    if (image->h < config_->map_height_)
    {
        h = image->h;
    }
    else
    {
        h = config_->map_height_;
    }

    if (image->w < config_->map_width_)
    {
        w = image->w;
    }
    else
    {
        w = config_->map_width_;
    }
    printf("h%d w%d", config_->map_height_, config_->map_width_);
    printf("h%d w%d", h, w);

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

    std::map<cords_t, high_ground_t> *hight_ground_map = new std::map<cords_t, high_ground_t>();

    for (unsigned int y = 0; y < h; y++)
    {
        for (unsigned int x = 0; x < w; x++)
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
                hight_ground_map->emplace(cords, marble_block_t(config_, cords));
                //set map to marble
            }
            else if (unsigned(r) < 5 & unsigned(b) < 5 & unsigned(g) < 5)
            {
                // printf("black\n");
                // hight_ground_map->emplace(cords, earth_t(config_, cords));
                //set map to earth
            }
            else if (unsigned(g) > 250)
            {
                // printf("green\n");
                hight_ground_map->emplace(cords, tree_t(config_, cords));
                //set map to grass
            }

            ground_t ground(config_, cords);
        }
    }
    SDL_UnlockSurface(image);
    utills::free_img_f(image);

    std::cout << "finish generate high ground" << std::endl;
    return std::shared_ptr<std::map<cords_t, high_ground_t>>(hight_ground_map);
};

std::shared_ptr<std::map<cords_t, ground_t>> map_t::generate_ground_f()
{
    std::cout << "start generate ground" << std::endl;
    SDL_Surface *image;
    SDL_PixelFormat *fmt;
    SDL_Color *color_;
    Uint32 index;
    int w, h;
    image = utills::load_img_f(config_->ground_map_path_);
    fmt = image->format;
    h = config_->map_height_ = image->h;
    w = config_->map_width_ = image->w;
    printf("h%d w%d", config_->map_height_, config_->map_width_);
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

    std::map<cords_t, ground_t> *ground_map = new std::map<cords_t, ground_t>;

    for (unsigned int y = 0; y < h; y++)
    {
        for (unsigned int x = 0; x < w; x++)
        {
            cords_t cords(x, y);
            index = get_pixel(image, x, y);
            Uint8 r;
            Uint8 g;
            Uint8 b;
            SDL_GetRGB(index, fmt, &r, &g, &b);
            color_ = &fmt->palette->colors[index];
            if (unsigned(r) > 250 & unsigned(b) > 250 & unsigned(g) > 250)
            {
                ground_map->emplace(cords, marble_t(config_, cords));

                //set map to marble
            }
            else if (unsigned(r) < 5 & unsigned(b) < 5 & unsigned(g) < 5)
            {
                ground_map->emplace(cords, earth_t(config_, cords));
                //set map to earth
            }
            else if (unsigned(g) > 250)
            {
                ground_map->emplace(cords, grass_t(config_, cords));
                //set map to grass
            }
            else if (unsigned(r) > 250)
            {
                ground_map->emplace(cords, fire_t(config_, cords));
                //set map to fire
            }
            else if (unsigned(b) > 250)
            {
                ground_map->emplace(cords, water_t(config_, cords));
                //set map to water
            }
        }
    }
    SDL_UnlockSurface(image);
    utills::free_img_f(image);

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
    camera_.cords_ = cords;
    return std::shared_ptr<std::map<cords_t, characters_t>>(characters_map);
};

std::shared_ptr<std::map<cords_t, characters_t>> map_t::generate_creatures_f()
{

    std::random_device rd;
    std::mt19937 eng(1);
    std::uniform_real_distribution<> distrReal(0, 1);
    std::cout << "start generate creatures" << std::endl;
    std::map<cords_t, characters_t> *characters_map = new std::map<cords_t, characters_t>;

    return std::shared_ptr<std::map<cords_t, characters_t>>(characters_map);
};

//TODO pass map with template;
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
    // for (std::map<cords_t, high_ground_t>::iterator it = map_of_high_ground->begin(); it != map_of_high_ground->end(); ++it)
    // {
    //     if (it != map_of_high_ground->end())
    //     {
    //         it->second.draw_f(renderer);
    //     }
    // }
    for (int y = camera_.cords_.y_ - (camera_.height_ / 2); y < (camera_.cords_.y_ + (camera_.height_ / 2))/config_->cell_size_; y++)
    {
        for (int x = camera_.cords_.x_ - (camera_.width_ / 2); x < (camera_.cords_.x_ + (camera_.width_ / 2))/config_->cell_size_; x++)
        {
            // printf("x%d, y%d\n",x,y);
            auto it = map_of_high_ground->find(cords_t(x, y));
            if (it != map_of_high_ground->end())
            {
                it->second.draw_f(renderer);
            }
        }
    }
};

void map_t::render_ground_f(SDL_Renderer *renderer)
{
    int y_max = camera_.cords_.y_ + (camera_.height_ / 2)/config_->cell_size_;
    int y_min = camera_.cords_.y_ - (camera_.height_ / 2);
    int x_max = camera_.cords_.x_ + (camera_.width_ / 2)/config_->cell_size_;
    int x_min = camera_.cords_.x_ - (camera_.width_ / 2);

    printf("y_min%d x_min%d ymax%d xmax%d \n",y_min,x_min,y_max,x_max);

    for (int y = y_min; y < y_max; y++)
    {
        for (int x = x_min; x < x_max; x++)
        {
            // printf("x%d, y%d\n",x,y);
            map_of_ground->at(cords_t(x, y)).draw_f(renderer);
        }
    }
};

void map_t::calculate_characters_f(){

};
