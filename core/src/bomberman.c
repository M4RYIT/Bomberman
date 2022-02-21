#include "bomberman.h"

bomberman *bomberman_init(SDL_Renderer *rnd, float x, float y)
{
    bomberman *bm = malloc(sizeof(bomberman));
    if (!bm) return NULL;

    bm->move_comp = (movable){x, y, 64, 64, 48};
    drawable_init(&bm->draw_comp, rnd, "assets//player.bmp", 64, 128, 1, 3);
    bm->draw_comp.offset_y = -bm->move_comp.height;
    return bm;
}

update_struct *new_update_struct(float x, float y)
{
    update_struct *ups = malloc(sizeof(update_struct));
    if (!ups) return NULL;

    ups->x = x;
    ups->y = y;
    return ups;
}

void set_update_struct(update_struct *ups, float new_x, float new_y)
{
    ups->x = new_x;
    ups->y = new_y;
}