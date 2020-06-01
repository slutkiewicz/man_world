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