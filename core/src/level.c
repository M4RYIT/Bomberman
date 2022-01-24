#include "bomberman.h"

int level_init(level *lv, const uint32_t cols, const uint32_t rows, const uint32_t cell_size, int32_t *cells)
{
    if (!lv || !cols || !rows || !cell_size) return -1;

    lv->cols = cols;
    lv->rows = rows;
    lv->cell_size = cell_size;
    lv->cells = cells;

    return 0;
}

int32_t level_cell(level *lv, const uint32_t col, const uint32_t row)
{
    if (!lv->cells) return -1;
    if (col >= lv->cols || row >= lv->rows) return -1;

    return lv->cells[col + row * lv->cols];
}

int collision_check_point(const float x, const float y, level *lv, const int32_t mask, uint32_t *cell_x, uint32_t *cell_y)
{
    *cell_x = x / lv->cell_size;
    *cell_y = y / lv->cell_size;
    return level_cell(lv, *cell_x, *cell_y) & mask;
}

int collision_check_rect(const float x, const float y, const uint32_t w, const uint32_t h, level *lv, const int32_t mask, float *offset_x, float *offset_y)
{
    uint32_t cell_x = 0;
    uint32_t cell_y = 0;
    if (collision_check_point(x+w-1, y, lv, mask, &cell_x, &cell_y) || 
        collision_check_point(x+w-1, y+h-1, lv, mask, &cell_x, &cell_y) ||
        collision_check_point(x, y, lv, mask, &cell_x, &cell_y) ||
        collision_check_point(x, y+h-1, lv, mask, &cell_x, &cell_y))
    {        
        *offset_x = ((w+lv->cell_size) - (fabsf(x-cell_x*lv->cell_size) + fabsf(x+w-(cell_x*lv->cell_size+lv->cell_size))))/2;
        *offset_y = ((h+lv->cell_size) - (fabsf(y-cell_y*lv->cell_size) + fabsf(y+h-(cell_y*lv->cell_size+lv->cell_size))))/2;
        return 1;
    }

    return 0;
}