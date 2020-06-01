#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "../third_party/json.hpp"

struct cords_t
{
public:
    cords_t(int x, int y);
    cords_t(cords_t cords,int x_add, int y_add);
    cords_t();
    int x_, y_;
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

            printf("config: %d  %d %d %d",config->height_,config->width_,config->cell_size_,config->map_size_);
          
            return std::shared_ptr<config_t>(config);
        }
        else
        {
            return nullptr;
        }
    };

private:
    bool static verify_config_f(nlohmann::json config)
    {
        return true;
    };
};