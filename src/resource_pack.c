#include "resource_pack.h"
void init_resource_pack(ResourcePack* target)
{
    /* small ships */
    target->small_ship_tex.red = wic_init_texture_from_file("../resources/ship/small_red.png", WIC_NEAREST, WIC_STOP);
    target->small_ship_tex.blue = wic_init_texture_from_file("../resources/ship/small_blue.png", WIC_NEAREST, WIC_STOP);
    target->small_ship.red = malloc(sizeof(WicImage));
    wic_init_image(target->small_ship.red, (WicPair)  {0,0}, target->small_ship_tex.red);
    target->small_ship.red->center = wic_image_get_geometric_center(target->small_ship.red);
    target->small_ship.red->draw_centered = true;
    target->small_ship.blue = malloc(sizeof(WicImage));
    wic_init_image(target->small_ship.blue, (WicPair)  {0,0}, target->small_ship_tex.blue);
    target->small_ship.blue->center=wic_image_get_geometric_center(target->small_ship.blue);
    target->small_ship.blue->draw_centered = true;
    
    /* medium ships */
    target->medium_ship_tex.red = wic_init_texture_from_file("../resources/ship/medium_red.png", WIC_NEAREST, WIC_STOP);
    target->medium_ship_tex.blue = wic_init_texture_from_file("../resources/ship/medium_blue.png", WIC_NEAREST, WIC_STOP);
    target->medium_ship.red = malloc(sizeof(WicImage));
    wic_init_image(target->medium_ship.red, (WicPair)  {0,0}, target->medium_ship_tex.red);
    target->medium_ship.red->center = wic_image_get_geometric_center(target->medium_ship.red);
    target->medium_ship.red->draw_centered = true;
    target->medium_ship.blue = malloc(sizeof(WicImage));
    wic_init_image(target->medium_ship.blue, (WicPair)  {0,0}, target->medium_ship_tex.blue);
    target->medium_ship.blue->center=wic_image_get_geometric_center(target->medium_ship.blue);
    target->medium_ship.blue->draw_centered = true;
    
    /* large ships */
    target->large_ship_tex.red = wic_init_texture_from_file("../resources/ship/large_red.png", WIC_NEAREST, WIC_STOP);
    target->large_ship_tex.blue = wic_init_texture_from_file("../resources/ship/large_blue.png", WIC_NEAREST, WIC_STOP);
    target->large_ship.red = malloc(sizeof(WicImage));
    wic_init_image(target->large_ship.red, (WicPair)  {0,0}, target->large_ship_tex.red);
    target->large_ship.red->center = wic_image_get_geometric_center(target->large_ship.red);
    target->large_ship.red->draw_centered = true;
    target->large_ship.blue = malloc(sizeof(WicImage));
    wic_init_image(target->large_ship.blue, (WicPair)  {0,0}, target->large_ship_tex.blue);
    target->large_ship.blue->center = wic_image_get_geometric_center(target->large_ship.blue);
    target->large_ship.blue->draw_centered = true;
    
    /* small bullet */
    target->small_bullet.red = malloc(sizeof(WicQuad));
    wic_init_quad(target->small_bullet.red, (WicPair) {0,0}, (WicPair) {3,1}, WIC_RED);
    target->small_bullet.red->center = wic_quad_get_geometric_center(target->small_bullet.red);
    target->small_bullet.red->draw_centered = true;
    target->small_bullet.blue = malloc(sizeof(WicQuad));
    wic_init_quad(target->small_bullet.blue, (WicPair)  {0,0}, (WicPair) {3,1}, WIC_BLUE);
    target->small_bullet.blue->center = wic_quad_get_geometric_center(target->small_bullet.blue);
    target->small_bullet.blue->draw_centered = true;
    
    /* medium bullet */
    target->medium_bullet.red = malloc(sizeof(WicQuad));
    wic_init_quad(target->medium_bullet.red, (WicPair)  {0,0}, (WicPair) {6,2}, WIC_RED);
    target->medium_bullet.red->center = wic_quad_get_geometric_center(target->medium_bullet.red);
    target->medium_bullet.red->draw_centered = true;
    target->medium_bullet.blue = malloc(sizeof(WicQuad));
    wic_init_quad(target->medium_bullet.blue, (WicPair)  {0,0}, (WicPair) {6,2}, WIC_BLUE);
    target->medium_bullet.blue->center = wic_quad_get_geometric_center(target->medium_bullet.blue);
    target->medium_bullet.blue->draw_centered = true;
    
    /* large bullet */
    target->large_bullet.red = malloc(sizeof(WicQuad));
    wic_init_quad(target->large_bullet.red, (WicPair)  {0,0}, (WicPair) {6,2}, WIC_RED);
    target->large_bullet.red->center = wic_quad_get_geometric_center(target->large_bullet.red);
    target->large_bullet.red->draw_centered = true;
    target->large_bullet.blue = malloc(sizeof(WicQuad));
    wic_init_quad(target->large_bullet.blue, (WicPair)  {0,0}, (WicPair) {6,2}, WIC_BLUE);
    target->large_bullet.blue->center = wic_quad_get_geometric_center(target->large_bullet.blue);
    target->large_bullet.blue->draw_centered = true;
    
}
WicImage* get_ship_image(ResourcePack* resource_pack, Player player)
{
    if(player.red)
    {
        switch(player.ship_type)
        {
            case SMALL:
                return resource_pack->small_ship.red;
            case MEDIUM:
                return resource_pack->medium_ship.red;
            case LARGE:
                return resource_pack->large_ship.red;
        }
    }
    else
    {
        switch(player.ship_type)
        {
            case SMALL:
                return resource_pack->small_ship.blue;
            case MEDIUM:
                return resource_pack->medium_ship.blue;
            case LARGE:
                return resource_pack->large_ship.blue;
        }
    }
}
void free_resource_pack(ResourcePack* target)
{
    /* small ships */
    wic_free_texture(target->small_ship_tex.red);
    free(target->small_ship_tex.red); target->small_ship_tex.red = 0;
    wic_free_texture(target->small_ship_tex.blue);
    free(target->small_ship_tex.blue); target->small_ship_tex.blue = 0;
    free(target->small_ship.red); target->small_ship.red = 0;
    free(target->small_ship.blue); target->small_ship.blue = 0;
    
    /* medium ships */
    wic_free_texture(target->medium_ship_tex.red);
    free(target->medium_ship_tex.red); target->medium_ship_tex.red = 0;
    wic_free_texture(target->medium_ship_tex.blue);
    free(target->medium_ship_tex.blue); target->medium_ship_tex.blue = 0;
    free(target->medium_ship.red); target->medium_ship.red = 0;
    free(target->medium_ship.blue); target->medium_ship.blue = 0;
    
    /* large ships */
    wic_free_texture(target->large_ship_tex.red);
    free(target->large_ship_tex.red); target->large_ship_tex.red = 0;
    wic_free_texture(target->large_ship_tex.blue);
    free(target->large_ship_tex.blue); target->large_ship_tex.blue = 0;
    free(target->large_ship.red); target->large_ship.red = 0;
    free(target->large_ship.blue); target->large_ship.blue = 0;
    
    /* small bullets */
    free(target->small_bullet.red); target->small_bullet.red = 0;
    free(target->small_bullet.blue); target->small_bullet.blue = 0;
    
    /* medium bullets */
    free(target->medium_bullet.red); target->medium_bullet.red = 0;
    free(target->medium_bullet.blue); target->medium_bullet.blue = 0;
    
    /* large bullets */
    free(target->large_bullet.red); target->large_bullet.red = 0;
    free(target->large_bullet.blue); target->large_bullet.blue = 0;
}
