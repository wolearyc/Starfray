#ifndef ENTITY_H
#define ENTITY_H
#include "wic_lib.h"
#include "resource_pack.h"
#include "player_info.h"
#include "ship.h"
#include "constants.h"
#include "bullet.h"
#include "resource_pack.h"
#include "camera.h"
typedef struct Entity
{
    WicPair location;
    double rotation;
    int health_or_damage;
    int shield_or_lifespan;
    enum EntityType type;
    bool red;
    int id;                     /* -1 if not assigned an id by a server */
} Entity;
void init_entity(Entity* target, WicPair location, double rotation,
                 enum EntityType type, PlayerInfo player);
void updt_bullet_entity(Entity* target, Bullet* bullet, WicGame* game);
void updt_ship_entity(Entity* target, Ship* ship, WicGame* game);
void draw_entity(Entity* target, ResourcePack* resource_pack, Camera camera,
                 WicGame* game);
void get_bullet_locations(Entity* ship_entity, WicPair* location_one,
                          WicPair* location_two);
#endif