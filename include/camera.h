#ifndef CAMERA_H
#define CAMERA_H
#include "wic_lib.h"
#include <stdbool.h>
typedef struct Camera
{
    WicPair location;
    double zoom;
    double rotation;
} Camera;
bool should_draw(WicPair object_location, WicPair object_dimensions,
                 Camera camera, WicGame* game);
WicPair to_screen_location(WicPair location, Camera camera, WicGame* game);
double to_screen_rotation(double rotation, Camera camera);
WicPair to_game_location(WicPair location, Camera camera, WicGame* game);
WicPair get_object_scale(Camera camera);
#endif