#pragma once

#include <stdint.h>
#include <math.h>
#include <SDL.h>

#define UNWALKABLE 0x0100
#define TELEPORT 0x0200
#define EXIT 0x0400

#define GROUND 0
#define WALL 1

#define CLAMP(value, lower, upper) fminf(upper, fmaxf(value, lower))
#define SIGN(value) value>=0?1:-1
#define SHIFTED_INPUT(axis, value) ((axis&value)>>(int)log2f(value))
#define INPUT_CANC(value) (0xf-value)

typedef enum input
{
    Left = 0x1,
    Right = 0x2,
    Up = 0x4,
    Down = 0x8
}
input;

typedef struct level
{
    int32_t *cells;
    uint32_t cols;
    uint32_t rows;
    uint32_t cell_size;        
}
level;

typedef struct movable
{
    float x;
    float y;
    uint32_t width;
    uint32_t height;
    float speed;
}
movable;

typedef struct drawable
{
    SDL_Rect src_rect;
    SDL_Rect dst_rect;

    SDL_Texture *texture;
    
    uint32_t index_x;
    uint32_t index_y;
    
    uint32_t rows;
    uint32_t cols;
    
    int offset_x;
    int offset_y;
}
drawable;

typedef struct bomberman
{
    movable move_comp;
    uint32_t max_bombs;
    uint32_t bombs;
    uint32_t bomb_power;
}
bomberman;

int level_init(level *lv, const uint32_t cols, const uint32_t rows, const uint32_t cell_size, int32_t *cells);

int32_t level_cell(level *lv, const uint32_t col, const uint32_t row);

void move_on_level(level *lv, movable *mv, const float delta_x, const float delta_y);

int collision_check_point(const float x, const float y, level *lv, const int32_t mask, uint32_t *cell_x, uint32_t *cell_y);

int collision_check_rect(const float x, const float y, const uint32_t w, const uint32_t h, level *lv, const int32_t mask, float *offset_x, float *offset_y);

int drawable_init(drawable *dw, SDL_Renderer *rnd, char *file_name, uint32_t w, uint32_t h, uint32_t rows, uint32_t cols);

void set_drawable_srcrect(drawable *dw, uint32_t index_x, uint32_t index_y);

void set_drawable_dstrect_coords(drawable *dw, uint32_t x, uint32_t y);

int set_drawable_dstrect_size(drawable *dw, uint32_t w, uint32_t h);