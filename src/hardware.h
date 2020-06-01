#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include "utills.h"



#define errcheck(e)                                                            \
  {                                                                            \
    if (e)                                                                     \
      throw std::invalid_argument(SDL_GetError());                             \
  }


class hardware_objects_t
{

public:

  SDL_Renderer *renderer;
  SDL_Window *window;

  std::shared_ptr<hardware_objects_t> init_hardware_subsystems(int width, int height,
                                                             bool fscreen);
};




