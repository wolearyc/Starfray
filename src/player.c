#include "ship.h"
void* init_local_ship(LocalShip* target, Ship* core, Player player)
{
    ShipStats stats;
    switch(player.ship_type)
    {
        case SMALL:
            stats = player.small_stats;
            break;
        case MEDIUM:
            stats = player.medium_stats;
            break;
        case LARGE:
            stats = player.large_stats;
            break;
    }
    
    target->core = core;
    target->stats = stats;
    target->velocity = (WicPair) {0,0};
    target->rotational_velocity = 0;
    target->time = 0;
    target->last_shot = 0;
    target->is_shooting = false;
}
void updt_local_ship(LocalShip* target, WicGame* game)
{
    ShipStats stats = target->stats; 
    /* rotation */
    double rotational_acceleration = 0.0;
    double rotational_velocity = target->rotational_velocity;
    if(wic_is_key_down(WIC_L))
    {
        rotational_acceleration = -stats.max_rotational_acceleration;
        rotational_velocity += rotational_acceleration * wic_get_delta(game);
    }
    else if(wic_is_key_down(WIC_J))
    {
        rotational_acceleration = stats.max_rotational_acceleration;
        rotational_velocity += rotational_acceleration * wic_get_delta(game);
    }
    else
    {
        if(rotational_velocity > 0.0001)
            rotational_acceleration = -stats.max_rotational_acceleration;
        else if(rotational_velocity < -0.0001)
            rotational_acceleration = stats.max_rotational_acceleration;
        double last_velocity = rotational_velocity;
        rotational_velocity += rotational_acceleration * wic_get_delta(game);;
        if((last_velocity > 0 && rotational_velocity < 0) ||
           (last_velocity < 0 && rotational_velocity > 0))
        {
            rotational_velocity = 0.0;
            rotational_acceleration = 0.0;
        }
    }
    if(fabs(rotational_velocity) > stats.max_rotational_velocity)
    {
        if(rotational_velocity > 0)
            rotational_velocity = stats.max_rotational_velocity;
        else
            rotational_velocity = -stats.max_rotational_velocity;
    }
    target->rotational_velocity = rotational_velocity;
    target->core->rotation += rotational_velocity * wic_get_delta(game);;

    /* location */
    WicPair acceleration = {0,0};
    WicPair velocity = target->velocity;
    bool moving = false;
    if(wic_is_key_down(WIC_W))
    {
        moving = true;
        acceleration.y += stats.max_acceleration;
    }
    if(wic_is_key_down(WIC_S))
    {
        moving = true;
        acceleration.y -= stats.max_acceleration;
    }
    if(wic_is_key_down(WIC_A))
    {
        moving = true;
        acceleration.x -= stats.max_acceleration;
    }
    if(wic_is_key_down(WIC_D))
    {
        moving = true;
        acceleration.x += stats.max_acceleration;
    }
    if(moving)
    {
        acceleration = wic_transform_pair(acceleration,
                                          target->core->rotation - 3.14/2,
                                          (WicPair) {1,1}, (WicPair) {0,0});
    }
    else
        acceleration = wic_multiply_pairs(velocity, (WicPair) {-1, -1});
    double norm = wic_get_norm_of_pair(acceleration);
    if(norm >= stats.max_acceleration)
    {
        double multipier = sqrt(stats.max_acceleration / norm);
        acceleration = wic_multiply_pairs(acceleration,
                                          (WicPair) {multipier, multipier});
    }
    acceleration = wic_multiply_pairs(acceleration,
                                      (WicPair) {wic_get_delta(game),
                                                 wic_get_delta(game)});
    velocity = wic_add_pairs(velocity, acceleration);
    norm = wic_get_norm_of_pair(velocity);
    if(norm >= stats.max_velocity)
    {
        double multiplier = sqrt(stats.max_velocity / norm);
        velocity = wic_multiply_pairs(velocity,
                                      (WicPair) {multiplier, multiplier});
    }
    if(!moving)
    {
        WicPair last_velocity = target->velocity;
        bool stop = (last_velocity.x > 0.0001 && velocity.x < -0.0001) ||
        (last_velocity.x < -0.0001 && velocity.x > 0.0001);
        if(stop)
            velocity.x = 0;
        stop = (last_velocity.y > 0.0001 && velocity.y < -0.0001) ||
        (last_velocity.y < -0.0001 && velocity.y > 0.0001);
        if(stop)
            velocity.y = 0;
    }
    target->velocity = velocity;
    velocity = wic_multiply_pairs(velocity,
                                  (WicPair) {wic_get_delta(game),
                                             wic_get_delta(game)});
    
    /* shooting */
    target->time += wic_get_delta(game);
    target->is_shooting = false;
    if(wic_is_key_down(WIC_SPACE) && target->time - target->last_shot
       >= stats.max_cannon_speed)
    {
        target->last_shot = target->time;
        target->is_shooting = true;
    }
}

void draw_ships(Ship** ships, Player* players, bool* used, unsigned num_players,
                ResourcePack* resource_pack, Camera camera, WicGame* game)
{
    for(int i = 1; i < num_players; i++)
    {
        if(used[i])
        {
            WicImage* image = get_ship_image(resource_pack, players[i]);
            if(should_draw(ships[i]->location,
                           wic_texture_get_dimensions(image->texture), camera,
                           game))
            {
                image->scale = get_object_scale(camera);
                image->location = to_screen_location(ships[i]->location, camera,
                                                     game);
                image->rotation = to_screen_rotation(ships[i]->rotation, camera);
                wic_draw_image(image, game);
            }
        }
    }
}