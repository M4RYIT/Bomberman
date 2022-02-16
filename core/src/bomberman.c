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