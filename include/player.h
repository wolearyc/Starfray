#ifndef SHIP_H
#define SHIP_H
#include "wic_lib.h"
#include "constants.h"
#include "resource_pack.h"
#include "player.h"
#include "camera.h"
#include <math.h>
typedef enum ShipType
{
    S_SHIP; M_SHIP; L_SHIP;
} ShipType;

typedef struct Player
{
    WicNodeIndex index;
    
    WicPair location;
    double rotation;
    bool engine;
} Ship;
typedef struct PlayerStats
{
    double max_rotational_velocity;
    double max_rotational_acceleration;
    double max_velocity;
    double max_acceleration;
    double max_cannon_speed;
} PlayerStats;
typedef struct LocalPlayer
{
    Player* core;
    PlayerStats stats;
    WicPair velocity;
    double rotational_velocity;
    double time;
    double last_shot;
    bool is_shooting;
} LocalShip;

void* init_local_ship(LocalShip* target, Ship* core, Player player);

void updt_local_ship(LocalShip* target, WicGame* game);

void draw_ships(Ship** ships, Player* players, bool* used, unsigned num_players,
                ResourcePack* resource_pack, Camera camera, WicGame* game);
#endif



