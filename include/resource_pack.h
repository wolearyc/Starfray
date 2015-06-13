#ifndef RESOURCE_PACK_H
#define RESOURCE_PACK_H
#include "wic_lib.h"
#include "player.h"
typedef struct ImagePair
{
    WicImage* red;
    WicImage* blue;
} ImagePair;
typedef struct TexturePair
{
    WicTexture* red;
    WicTexture* blue;
} TexturePair;
typedef struct QuadPair
{
    WicQuad* red;
    WicQuad* blue;
} QuadPair;
typedef struct ResourcePack
{
    TexturePair small_ship_tex;
    ImagePair small_ship;
    
    TexturePair medium_ship_tex;
    ImagePair medium_ship;
    
    TexturePair large_ship_tex;
    ImagePair large_ship;
    
    TexturePair huge_ship_tex;
    ImagePair huge_ship;
    
    QuadPair small_bullet;
    QuadPair medium_bullet;
    QuadPair large_bullet;
    QuadPair huge_bullet;
    
} ResourcePack;
void init_resource_pack(ResourcePack* target);
WicImage* get_ship_image(ResourcePack* resource_pack, Player player);
void free_resource_pack(ResourcePack* target);
#endif
