#include "background.h"
void init_background(Background* target)
{
    srand((unsigned int) time(0));
    for(int i = 0; i < 50; i++)
        target->locations[i] = (WicPair) {rand() % 250, rand() % 250};
    wic_init_quad(&target->quad, (WicPair) {0,0}, (WicPair) {1,1},
                  WIC_WHITE);
}
void draw_background(Background* target, Camera camera, WicGame* game)
{
    camera.location.x = fmod(camera.location.x, 250.0);
    camera.location.y = fmod(camera.location.y, 250.0);
    camera.zoom = 0.5;
    for(int x = 0; x < 3; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            for(int i = 0; i < 50; i++)
            {
                target->quad.rotation = to_screen_rotation(0.0, camera);
                WicPair location = target->locations[i];
                location.x += -375 + x * 250;
                location.y += -375 +  y * 250;
                target->quad.location = to_screen_location(location, camera,
                                                           game);
                target->quad.scale = get_object_scale(camera);
                wic_draw_quad(&target->quad, game);
            }
        }
    }
}
void free_background(Background* target)
{
    wic_free_quad(&target->quad);
}