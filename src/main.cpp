#include "game.h"

/*
*TODO:
* a lot //search for TODO
*/
int main(int argc, char **argv)
{
    std::shared_ptr<config_t> config;
    //Read config
    if (argc > 1)
    {
        config = utills::load_config_f(argv[1]);
    }
    else
    {
        std::cout<<"no config specified shutting down"<<std::endl;
        return -1; // try to load default config 
    }
    if(config == nullptr)
    {
        std::cout<<"config is not valid shutting down"<<std::endl;
        return -1;
    }

    game::game_t game(config);
    game.init_game_f();
    game.start_game_f();
    return 0;
}