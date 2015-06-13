#include "camera.h"
bool should_draw(WicPair object_location, WicPair object_dimensions,
                 Camera camera, WicGame* game)
{
    return true;
    int largest = 0;
    if(object_dimensions.x > object_dimensions.y)
        largest = object_dimensions.x;
    else
        largest = object_dimensions.y;
    WicPair half_dimensions = wic_divide_pairs(game->dimensions_ro,
                                               (WicPair) {camera.zoom * 2,
                                                          camera.zoom * 2});
    if(object_location.x >= camera.location.x - half_dimensions.x - largest &&
       object_location.x <= camera.location.x + half_dimensions.x + largest &&
       object_location.y >= camera.location.y - half_dimensions.y - largest &&
       object_location.y <= camera.location.y + half_dimensions.y + largest)
        return true;
    return false;
}
WicPair to_screen_location(WicPair location, Camera camera, WicGame* game)
{
    WicPair scaled_dimensions = wic_divide_pairs(game->dimensions_ro,
                                                 (WicPair) {camera.zoom,
                                                            camera.zoom});
    WicPair half_dimensions = wic_divide_pairs(scaled_dimensions,
                                               (WicPair) {2,2});
    WicPair left_corner = wic_subtract_pairs(camera.location, half_dimensions);
    WicPair result = wic_subtract_pairs(location, left_corner);
    result = wic_divide_pairs(result, scaled_dimensions);
    result = wic_multiply_pairs(result, game->dimensions_ro);
    
    double cosine = cos(-camera.rotation + 3.14/2);
    double sine = sin(-camera.rotation + 3.14/2);
    result.x = result.x - game->dimensions_ro.x / 2;
    result.y = result.y - game->dimensions_ro.y / 2;
    double x = result.x * cosine - result.y * sine;
    double y = result.x * sine + result.y * cosine;
    result.x = x + game->dimensions_ro.x / 2;
    result.y = y + game->dimensions_ro.y / 2;
    
    return result;
}
double to_screen_rotation(double rotation, Camera camera)
{
    return rotation - camera.rotation + 3.14/2;

}
WicPair to_game_location(WicPair location, Camera camera, WicGame* game)
{
    WicPair scaled_dimensions = wic_divide_pairs(game->dimensions_ro,
                                                 (WicPair) {camera.zoom,
                                                            camera.zoom});
    WicPair half_dimensions = wic_divide_pairs(scaled_dimensions,
                                               (WicPair) {2,2});
    WicPair left_corner = wic_subtract_pairs(camera.location, half_dimensions);
    WicPair result = wic_divide_pairs(location, game->dimensions_ro);
    result = wic_multiply_pairs(result, scaled_dimensions);
    result = wic_add_pairs(result, left_corner);
    return result;
}
WicPair get_object_scale(Camera camera)
{
    return (WicPair) {camera.zoom, camera.zoom};
}