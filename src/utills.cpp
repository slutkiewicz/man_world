#include "utills.h"

color_t::color_t(int r, int g, int b, int a)
{
    r_ = r;
    g_ = g;
    b_ = b;
    a_ = a;
};
color_t::color_t(){

};
cords_t::cords_t(int x, int y)
{
    x_ = x;
    y_ = y;
};
cords_t::cords_t(cords_t cords, int x_add, int y_add)
{
    x_ = cords.x_ + x_add;
    y_ = cords.y_ + y_add;
};
cords_t::cords_t(){

};

camera_t::camera_t(cords_t cords, int width, int height)
{
    cords_ = cords;
    width_ = width_;
    height_ = height_;
};

camera_t::camera_t(cords_t cords)
{
    cords_ = cords;
    width_ = 0;
    height_ = 0;
};
camera_t::camera_t(){

};

cords_dt_t::cords_dt_t(float x, float y)
{
    x_ = x;
    y_ = y;
};
cords_dt_t::cords_dt_t(cords_dt_t cords, float x_add, float y_add)
{
    x_ = cords.x_ + x_add;
    y_ = cords.y_ + y_add;
};
cords_dt_t::cords_dt_t(){

};