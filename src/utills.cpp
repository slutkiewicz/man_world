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
cords_t::cords_t(cords_t cords,int x_add, int y_add)
{
    x_ = cords.x_+x_add;
    y_ = cords.y_+y_add;
};
cords_t::cords_t(){

};

camera_t::camera_t(int x, int y)
{
    cords.x_ = x;
    cords.y_ = y;
};
camera_t::camera_t(cords_t cords,int x_add, int y_add)
{
    cords.x_ = cords.x_+x_add;
    cords.y_ = cords.y_+y_add;
};
camera_t::camera_t(cords_t cords)
{
    cords = cords;

};
camera_t::camera_t(){

};

cords_dt_t::cords_dt_t(float x, float y)
{
    x_ = x;
    y_ = y;
};
cords_dt_t::cords_dt_t(cords_dt_t cords,float x_add, float y_add)
{
    x_ = cords.x_+x_add;
    y_ = cords.y_+y_add;
};
cords_dt_t::cords_dt_t(){

};