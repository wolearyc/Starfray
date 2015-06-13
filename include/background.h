#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "wic_lib.h"
#include <math.h>
#include "camera.h"
#include <stdlib.h>
#include <time.h>
typedef struct Background
{
    WicPair locations[50];
    WicQuad quad;
} Background;
void init_background(Background* target);
void draw_background(Background* target, Camera camera, WicGame* game);
void free_background(Background* target);
#endif