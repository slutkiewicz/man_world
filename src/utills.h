#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "../third_party/json.hpp"
#include <SDL2/SDL_image.h>


//TODO on map loading set in config width height
enum MOVEMENT 
{
    RIGHT,LEFT,UP,DOWN,NONE
};

struct cords_t
{
public:
    cords_t(int x, int y);
    cords_t(cords_t cords, int x_add, int y_add);
    cords_t();
    int x_, y_;
};
struct cords_dt_t
{
public:
    cords_dt_t(double x, double y);
    cords_dt_t(cords_dt_t cords, double x_add, double y_add);
    cords_dt_t();
    double x_, y_;
};

struct color_t
{
public:
    color_t(int r, int g, int b, int a);
    color_t();
    int r_, g_, b_, a_;
};

class config_t
{
public:
    int height_, width_, cell_size_, map_size_;
    std::string ground_map_path;
};
class utills
{
public:
    std::shared_ptr<config_t> static load_config_f(std::string path)
    {
        nlohmann::json config_json;
        std::ifstream is(path); // open file
        config_json = nlohmann::json::parse(is);
        if (verify_config_f(config_json))
        {
            config_t *config = new config_t;
            config->height_ = config_json["height"];
            config->width_ = config_json["width"];
            config->cell_size_ = config_json["cell_size"];
            config->map_size_ = config_json["map_size"];
            config->ground_map_path = config_json["ground_map_path"];

            printf("config: %d  %d %d %d %s", config->height_, config->width_, config->cell_size_, config->map_size_,config->ground_map_path.c_str());

            return std::shared_ptr<config_t>(config);
        }
        else
        {
            return nullptr;
        }
    };

    SDL_Surface static * load_img_f(std::string path)
    {
        SDL_Surface *image;
        image = IMG_Load(path.c_str());
        if (!image)
        {
            printf("IMG_Load: %s\n", IMG_GetError());
            return nullptr;
        }
        else
        {
            return image;
        }
        //SDL_FreeSurface(image);
    };

    void static free_img_f(SDL_Surface *image)
    {
        SDL_FreeSurface(image);
    };

private:
    bool static verify_config_f(nlohmann::json config)
    {
        return true;
        //TODO check if image size same
    };
};