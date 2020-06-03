#include "world.h"

world_t::world_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};

world_t::world_t(){};

void world_t::render_f(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    map_->render_f(renderer);
    // SDL_RenderSetViewport(renderer,&map_->render_viewport_);
    SDL_RenderPresent(renderer);
};

void world_t::update_f(double dt)
{

    update_players_f(dt);

    // calculate_characters();
};

bool world_t::if_collision(characters_t *character)
{
    //TODO check for every map
    if (character->cordinates_.x_ > config_->width_)
    {
        character->cordinates_.x_ = config_->width_ - 1;
        return true;
    }
    else if (character->cordinates_.x_ < 0)
    {
        character->cordinates_.x_ = 1;
        return true;
    }
    else if (character->cordinates_.y_ > config_->height_)
    {
        character->cordinates_.y_ = config_->height_ - 1;
        return true;
    }
    else if (character->cordinates_.y_ < 0)
    {
        character->cordinates_.y_ = 1;
        return true;
    }
    else
    {
        return false;
    }
}

void world_t::update_players_f(double dt)
{
    std::map<cords_t, bool> newCords;
    printf("before loop: %d\n");
    for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end();)
    {

        printf("after loop ");
        characters_t player = it->second;
        try
        {
            if (newCords.at(it->first))
            {
                ++it;
                continue;
            }
        }
        catch (const std::out_of_range &e)
        {
        }

        switch (player.direction_)
        {
        case MOVEMENT::LEFT:
            player.cordinates_dt_.x_ -= player.speed * dt;
            printf("x: %f", player.cordinates_dt_.x_);
            printf("x: %d", player.cordinates_.x_);
            player.cordinates_.x_ = player.cordinates_dt_.x_;
            printf("x: %d\n", player.cordinates_.x_);
            break;
        case MOVEMENT::RIGHT:
            player.cordinates_dt_.x_ += player.speed * dt;
            printf("x: %f", player.cordinates_dt_.x_);
            printf("x: %d", player.cordinates_.x_);
            player.cordinates_.x_ = player.cordinates_dt_.x_;
            printf("x: %d\n", player.cordinates_.x_);
            break;
        case MOVEMENT::UP:
            player.cordinates_dt_.y_ -= player.speed * dt;
            printf("y: %f", player.cordinates_dt_.y_);
            printf("y: %d", player.cordinates_.y_);
            player.cordinates_.y_ = player.cordinates_dt_.y_;
            printf("y: %d\n", player.cordinates_.y_);
            break;
        case MOVEMENT::DOWN:
            player.cordinates_dt_.y_ += player.speed * dt; // multiply by ground speed_ability
            printf("y: %f", player.cordinates_dt_.y_);
            printf("y: %d", player.cordinates_.y_);
            player.cordinates_.y_ = player.cordinates_dt_.y_;
            printf("y: %d\n", player.cordinates_.y_);
            break;
        case MOVEMENT::NONE:
            // player.cordinates_dt_.y_ = 0;
            // player.cordinates_dt_.x_ = 0;
            break;
        default:
            break;
        }
        printf("check if collision y: %d x: %d\n", player.cordinates_.y_, player.cordinates_.x_);
        if (!if_collision(&player))
        {
            printf("y: %d\n", player.cordinates_.y_);

            auto ret = map_->map_of_players->emplace(player.cordinates_, player);
            if (ret.second)
            {
                printf("teru\n");

                newCords.emplace(player.cordinates_, true);
                map_->map_of_players->erase(it++);
            }
            else
            {
                ++it;
            }

            printf("after emplace y: %d\n", player.cordinates_.y_);
        }
        else
        {
            ++it;
        }
    }
};

void world_t::handle_event_f()
{
    handle_players_f();
};

void world_t::handle_players_f()
{

    Uint8 const *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
    {
        for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end(); ++it)
        {
            if (it != map_->map_of_players->end())
            {
                it->second.direction_ = MOVEMENT::LEFT;
            }
        }
    }
    else if (keys[SDL_SCANCODE_RIGHT])
    {
        for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end(); ++it)
        {
            if (it != map_->map_of_players->end())
            {
                it->second.direction_ = MOVEMENT::RIGHT;
            }
        }
    }
    else if (keys[SDL_SCANCODE_UP])
    {
        for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end(); ++it)
        {
            if (it != map_->map_of_players->end())
            {
                it->second.direction_ = MOVEMENT::UP;
            }
        }
    }
    else if (keys[SDL_SCANCODE_DOWN])
    {
        for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end(); ++it)
        {
            if (it != map_->map_of_players->end())
            {
                it->second.direction_ = MOVEMENT::DOWN;
            }
        }
    }
    else
    {
        for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end(); ++it)
        {
            if (it != map_->map_of_players->end())
            {
                it->second.direction_ = MOVEMENT::NONE;
            }
        }
    }
};

void world_t::create_map_f()
{
    std::cout << "start create map" << std::endl;
    map_ = map_t(config_).generate_map_f();
    std::cout << "finish create map" << std::endl;
};
