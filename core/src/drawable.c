#include "bomberman.h"
#include "bmp_parser.h"

int drawable_init(drawable *dw, SDL_Renderer *rnd, char *file_name, uint32_t w, uint32_t h, uint32_t rows, uint32_t cols)
{
    if (!dw || !rnd || !w || !h || !cols || !rows) return -1;

    dw->rows = rows;
    dw->cols = cols;

    dw->src_rect.x = 0;
    dw->src_rect.y = 0;
    dw->src_rect.w = w;
    dw->src_rect.h = h;

    dw->dst_rect.x = 0;
    dw->dst_rect.y = 0;
    dw->dst_rect.w = w;
    dw->dst_rect.h = h;

    dw->offset_x = 0;
    dw->offset_y = 0;

    if (bmp_to_static_texture(file_name, rnd, &dw->texture)) return -1;

    return 0;
}

void set_drawable_srcrect(drawable *dw, uint32_t index_x, uint32_t index_y)
{
    dw->src_rect.x = (index_x%dw->cols)*dw->src_rect.w;
    dw->src_rect.y = (index_y%dw->rows)*dw->src_rect.h;
}

void set_drawable_dstrect_coords(drawable *dw, uint32_t x, uint32_t y)
{
    dw->dst_rect.x = x + dw->offset_x;
    dw->dst_rect.y = y + dw->offset_y;
}

int set_drawable_dstrect_size(drawable *dw, uint32_t w, uint32_t h)
{
    if (!w || !h) return -1;

    dw->offset_x *= (w/dw->dst_rect.w);
    dw->offset_y *= (h/dw->dst_rect.h);
    dw->dst_rect.w = w;
    dw->dst_rect.h = h;

    return 0;
}