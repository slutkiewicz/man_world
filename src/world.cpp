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
    switch (character->direction_)
    {
    case MOVEMENT::LEFT:
    {
        for (unsigned int i = character->cordinates_.x_; i < character->cordinates_prev_.x_; i++)
        {
            if (map_->map_of_high_ground->find(cords_t(i, character->cordinates_.y_)) != map_->map_of_high_ground->end())
            {
                character->cordinates_.x_ = character->cordinates_prev_.x_;
                character->cordinates_dt_.x_ = character->cordinates_prev_.x_; //TODO all like that if coliision after
                return true;
            }
        }
        break;
    }
    case MOVEMENT::RIGHT:
        for (unsigned int i = character->cordinates_prev_.x_; i < character->cordinates_.x_ + 1; i++)
        {
            if (map_->map_of_high_ground->find(cords_t(i, character->cordinates_.y_)) != map_->map_of_high_ground->end())
            {
                character->cordinates_.x_ = character->cordinates_prev_.x_;
                character->cordinates_dt_.x_ = character->cordinates_prev_.x_;
                return true;
            }
        }
        break;
    case MOVEMENT::UP:
        for (unsigned int i = character->cordinates_.y_; i < character->cordinates_prev_.y_; i++)
        {
            if (map_->map_of_high_ground->find(cords_t(character->cordinates_.x_, i)) != map_->map_of_high_ground->end())
            {
                character->cordinates_.y_ = character->cordinates_prev_.y_;
                character->cordinates_dt_.y_ = character->cordinates_prev_.y_;
                return true;
            }
        }
        break;
    case MOVEMENT::DOWN:
        for (unsigned int i = character->cordinates_prev_.y_; i < character->cordinates_.y_ + 1; i++)
        {
            if (map_->map_of_high_ground->find(cords_t(character->cordinates_.x_, i)) != map_->map_of_high_ground->end())
            {
                character->cordinates_.y_ = character->cordinates_prev_.y_;
                character->cordinates_dt_.y_ = character->cordinates_prev_.y_;
                return true;
            }
        }
        break;
    default:
        break;
    }

    if (character->cordinates_.x_ > (config_->width_ - 1))
    {
        character->cordinates_.x_ = config_->width_ - 1;
        character->cordinates_dt_.x_ = config_->width_ - 1;
        return true;
    }
    else if (character->cordinates_.x_ < 0)
    {
        character->cordinates_.x_ = 1;
        character->cordinates_dt_.x_ = 1;
        return true;
    }
    else if (character->cordinates_.y_ > (config_->height_ - 1))
    {
        character->cordinates_.y_ = config_->height_ - 1;
        character->cordinates_dt_.y_ = config_->height_ - 1;
        return true;
    }
    else if (character->cordinates_.y_ < 0)
    {
        character->cordinates_.y_ = 1;
        character->cordinates_dt_.y_ = 1;
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
    for (std::map<cords_t, characters_t>::iterator it = map_->map_of_players->begin(); it != map_->map_of_players->end();)
    {

        characters_t *player = &it->second;
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

        switch (player->direction_)
        {
        case MOVEMENT::LEFT:
            player->cordinates_dt_.x_ = player->cordinates_dt_.x_ - (player->speed * dt * map_->map_of_ground->at(player->cordinates_).speed_);
            printf("x: %f\n", player->cordinates_dt_.x_);
            player->cordinates_prev_.x_ = player->cordinates_.x_;
            player->cordinates_.x_ = player->cordinates_dt_.x_;
            break;
        case MOVEMENT::RIGHT:
            player->cordinates_dt_.x_ = player->cordinates_dt_.x_ + (player->speed * dt * map_->map_of_ground->at(player->cordinates_).speed_);
            printf("x: %f\n", player->cordinates_dt_.x_);
            player->cordinates_prev_.x_ = player->cordinates_.x_;
            player->cordinates_.x_ = player->cordinates_dt_.x_;
            break;
        case MOVEMENT::UP:
            player->cordinates_dt_.y_ = player->cordinates_dt_.y_ - (player->speed * dt * map_->map_of_ground->at(player->cordinates_).speed_);
            printf("y: %f\n", player->cordinates_dt_.y_);
            player->cordinates_prev_.y_ = player->cordinates_.y_;
            player->cordinates_.y_ = player->cordinates_dt_.y_;
            break;
        case MOVEMENT::DOWN:
            player->cordinates_dt_.y_ = player->cordinates_dt_.y_ + (player->speed * dt * map_->map_of_ground->at(player->cordinates_).speed_); // multiply by ground speed_ability
            printf("y: %f\n", player->cordinates_dt_.y_);
            player->cordinates_prev_.y_ = player->cordinates_.y_;
            player->cordinates_.y_ = player->cordinates_dt_.y_;
            break;
        case MOVEMENT::NONE:
            break;
        default:
            break;
        }
        if (!if_collision(player))
        {

            auto ret = map_->map_of_players->emplace(player->cordinates_, *player);
            if (ret.second)
            {
                printf("teru\n");

                newCords.emplace(player->cordinates_, true);
                map_->map_of_players->erase(it++);
            }
            else
            {
                ++it;
            }
            map_->update_camera_f(player);
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
