#include "bomberman.h"

void move_on_level(level *lv, movable *mv, const float delta_x, const float delta_y)
{
    float upper_x = lv->cols * lv->cell_size - mv->width;
    float upper_y = lv->rows * lv->cell_size - mv->height;
    float new_x = CLAMP(mv->x + delta_x, 0, upper_x);    
    float new_y = CLAMP(mv->y + delta_y, 0, upper_y);

    float offset_x = 0;
    float offset_y = 0;
    collision_check_rect(new_x, new_y, mv->width, mv->height, lv, WALL, &offset_x, &offset_y);

    float dx = fabsf(delta_x)>0?1:0;
    float dy = fabsf(delta_y)>0?1:0;  

    mv->x = new_x + ((SIGN(new_x-mv->x)) * dx * -offset_x);
    mv->y = new_y + ((SIGN(new_y-mv->y)) * dy * -offset_y);   
}