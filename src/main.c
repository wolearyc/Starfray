#include "wic_lib.h"
#include "bullet.h"
#include "ship.h"
#include "background.h"
#include "player_info.h"
#include "entity_manager.h"
#include "packets.h"
typedef struct ClientData
{
    bool joined;
    unsigned char client_id;
    EntityManager manager;
    char username[20];
} ClientData;
int game()
{
    WicGame* game = wic_init_game("Starfray", (WicPair) {700,700}, 60, false,
                                  false, 3);
    wic_draw_splash(WIC_SPLASH_BACKGROUND_COLOR, WIC_SPLASH_TEXT_COLOR, game);
    
    PlayerInfo player_info = get_new_player_info();
    
    /* TODO: client initialization */
    ShipType ship_types[] = {0, SMALL};
    
    ResourcePack resource_pack;
    init_resource_pack(&resource_pack);
    
    Camera camera = {(WicPair) {0,0}, 6, 0.0};
    
    LocalShip local_ship;
    Ship* player_ship = init_local_ship(&local_ship, 1, player_info.small_stats,
                                        (WicPair) {0,0}, 0.);
    
    while(wic_updt_game(game))
    {
        WicPair scroll = wic_get_scroll_offset();
        if(scroll.y > 0)
            camera.zoom += 0.1;
        else if(scroll.y < 0)
            camera.zoom -= 0.1;
        
        updt_local_ship(&local_ship, game);
        
        camera.location = player_ship->location;
        camera.rotation = player_ship->rotation;
        
        draw_ship(local_ship, camera, game);
        
    }
    
    wic_free_game(game); game = 0;
    free_resource_pack(&resource_pack);
    return 0;
}

int main(int argc, char** argv)
{
    return game();
} 

