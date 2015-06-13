#ifndef BULLET_H
#define BULLET_H
#include "wic_lib.h"
#include "constants.h"
typedef struct CoreBullet
typedef struct Bullet
{
    double speed;
    double lifespan;
    double age;
    int entity_id;
} Bullet;
void init_bullet(Bullet* target, enum EntityType type, int entity_id);
bool should_destroy_bullet(Bullet* target);
void updt_bullet(Bullet* target, WicGame* game);
#endif