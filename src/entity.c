#include "entity.h"
void init_entity(Entity* target, WicPair location, double rotation,
                 enum EntityType type, PlayerInfo player)
{
    int health_or_damage;
    int shield_or_lifespan;
    switch(type)
    {
        case SMALL_SHIP:
            health_or_damage = player.small_ship_info.max_health;
            shield_or_lifespan = player.small_ship_info.max_shield;
            break;
        case MEDIUM_SHIP:
            health_or_damage = player.medium_ship_info.max_health;
            shield_or_lifespan = player.medium_ship_info.max_shield;
            break;
        case LARGE_SHIP:
            health_or_damage = player.large_ship_info.max_health;
            shield_or_lifespan = player.large_ship_info.max_shield;
            break;
        case HUGE_SHIP:
            health_or_damage = player.huge_ship_info.max_health;
            shield_or_lifespan = player.huge_ship_info.max_shield;
            break;
            
        case SMALL_BULLET:
            health_or_damage = 4;
            shield_or_lifespan = 4;
            break;
        case MEDIUM_BULLET:
            health_or_damage = 4;
            shield_or_lifespan = 4;
            break;
        case LARGE_BULLET:
            health_or_damage = 4;
            shield_or_lifespan = 4;
            break;
        default:  /* huge bullet */
            health_or_damage = 4;
            shield_or_lifespan = 4;
            break;
    }
    
    target->location = location;
    target->rotation = rotation;
    target->health_or_damage = health_or_damage;
    target->shield_or_lifespan = shield_or_lifespan;
    target->type = type;
    target->red = player.red;
    target->id = -1;
}
void updt_bullet_entity(Entity* target, Bullet* bullet, WicGame* game)
{
    WicPair velocity = {bullet->speed * cos(target->rotation),
                        bullet->speed * sin(target->rotation) };
    velocity = wic_multiply_pairs(velocity, (WicPair) {game->delta,
                                                       game->delta});
    target->location = wic_add_pairs(target->location, velocity);
}
void updt_ship_entity(Entity* target, Ship* ship, WicGame* game)
{
    WicPair delta = {game->delta, game->delta};
    WicPair velocity = wic_multiply_pairs(ship->velocity, delta);
    target->location = wic_add_pairs(target->location, velocity);
    
    target->rotation = ship->rotation;
}
void draw_entity(Entity* target, ResourcePack* resource_pack, Camera camera,
                 WicGame* game)
{
    ImagePair image_pair;
    WicImage* image;
    switch(target->type)
    {
        case SMALL_SHIP:
            image_pair = resource_pack->small_ship;
            break;
        case MEDIUM_SHIP:
            image_pair = resource_pack->medium_ship;
            break;
        case LARGE_SHIP:
            image_pair = resource_pack->large_ship;
            break;
        case HUGE_SHIP:
            image_pair = resource_pack->huge_ship;
            break;
            
        case SMALL_BULLET:
            image_pair = resource_pack->small_bullet;
            break;
        case MEDIUM_BULLET:
            image_pair = resource_pack->medium_bullet;
            break;
        case LARGE_BULLET:
            image_pair = resource_pack->large_bullet;
            break;
        default: /* huge bullet */
            image_pair = resource_pack->huge_bullet;
            break;
    }
    if(target->red)
        image = image_pair.red;
    else
        image = image_pair.blue;
    
    if(should_draw(target->location, image->texture_ro->dimensions_ro,
                   camera, game))
    {
        image->scale = get_object_scale(camera);
        image->location = to_screen_location(target->location, camera, game);
        image->rotation = to_screen_rotation(target->rotation, camera);
        wic_draw_image(image, game);
    }
}
void get_bullet_locations(Entity* ship_entity, WicPair* location_one,
                          WicPair* location_two)
{
    WicPair scale = {1,1};
    WicPair center = {0,0};
    switch(ship_entity->type)
    {
        case SMALL_SHIP:
            *location_one = wic_transform_pair((WicPair) {3,4},
                                               ship_entity->rotation,
                                               scale, center);
            *location_two = wic_transform_pair((WicPair) {3,-4},
                                               ship_entity->rotation,
                                               scale, center);
            break;
        case MEDIUM_SHIP:
            break;
        case LARGE_SHIP:
            break;
        default: /* huge ship */
            break;
            
    }
    *location_one = wic_add_pairs(*location_one, ship_entity->location);
    *location_two = wic_add_pairs(*location_two, ship_entity->location);
}
