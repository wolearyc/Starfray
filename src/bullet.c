#include "bullet.h"
void init_bullet(Bullet* target, enum EntityType type, int entity_id)
{
    double speed;
    double lifespan;
    switch(type)
    {
        case SMALL_BULLET:
            speed = 200;
            lifespan = 1.0;
            break;
        case MEDIUM_BULLET:
            speed = 200;
            lifespan = 4.0;
            break;
        case LARGE_BULLET:
            speed = 40;
            lifespan = 4.0;
            break;
        default: /* huge bullet */
            speed = 40;
            lifespan = 4.0;
            break;
    }
    
    target->speed = speed;
    target->lifespan = lifespan;
    target->age = 0;
    target->entity_id = entity_id;
}
bool should_destroy_bullet(Bullet* target)
{
    return target->lifespan <= target->age;
}
void updt_bullet(Bullet* target, WicGame* game)
{
    target->age += game->delta;
}