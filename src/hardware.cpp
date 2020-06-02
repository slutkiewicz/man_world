#include "hardware.h"
/**
 * @brief creates render, window and packs then into shared_ptr
 */
std::shared_ptr<hardware_objects_t> hardware_objects_t::init_hardware_subsystems(int width, int height,
                                                                                 bool fscreen)
{
        
        // inicjalizacja SDL tylko jesli jeszcze nie byl zainicjowany
        std::cout<<"init_hardware_subsystems"<<std::endl;
        errcheck(SDL_Init(SDL_INIT_EVERYTHING) != 0);
        IMG_Init(IMG_INIT_PNG);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        auto window = SDL_CreateWindow(
            "\\_man_world_/", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height,
            SDL_WINDOW_SHOWN | (fscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));

        errcheck(window == nullptr);

        auto renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

        errcheck(renderer == nullptr);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //

        hardware_objects_t *objects = new hardware_objects_t;
        objects->renderer = renderer;
        objects->window = window;
        std::cout<<"finish init_hardware_subsystems"<<std::endl;

        return std::shared_ptr<hardware_objects_t>(objects, [](auto o) {
                SDL_DestroyRenderer(o->renderer);
                SDL_DestroyWindow(o->window);
                IMG_Quit();
                SDL_Quit();
        });
}