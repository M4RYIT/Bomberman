#include <SDL.h>
#include "bomberman.h"
#include "level1.h"

int main(int argc, char **argv)
{
    level lv_1;
    level_init(&lv_1, 8, 8, 64, level1_cells);

    bomberman player;
    player.move_comp = (movable){100, 100, 64, 64, 48};

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          lv_1.cols * lv_1.cell_size, lv_1.rows * lv_1.cell_size, 0);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    drawable dw_cell;
    drawable_init(&dw_cell, renderer, "assets//level_tiles.bmp", 64, 64, 1, 4);

    drawable dw_player;
    drawable_init(&dw_player, renderer, "assets//player.bmp", 64, 128, 1, 3);
    dw_player.offset_y = -player.move_comp.height;

    float delta_x = 0;
    float delta_y = 0;
    uint8_t axis = 0;

    for(;;)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) goto quit;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    axis |= Left;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    axis |= Right;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    axis |= Up;
                }
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    axis |= Down;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_LEFT) axis &= INPUT_CANC(Left);

                if (event.key.keysym.sym == SDLK_RIGHT) axis &= INPUT_CANC(Right);

                if (event.key.keysym.sym == SDLK_UP) axis &= INPUT_CANC(Up);

                if (event.key.keysym.sym == SDLK_DOWN) axis &= INPUT_CANC(Down);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        for (uint32_t row=0; row<lv_1.rows; row++)
        {
            for (uint32_t col=0; col<lv_1.cols; col++)
            {
                int32_t cell = level_cell(&lv_1, col, row);
                cell &= 0xff;

                set_drawable_srcrect(&dw_cell, cell, 0);
                set_drawable_dstrect_coords(&dw_cell, col * lv_1.cell_size, row * lv_1.cell_size);

                SDL_RenderCopy(renderer, dw_cell.texture, &dw_cell.src_rect, &dw_cell.dst_rect);
            }
        }

        delta_x = (!(delta_y!=0))*(SHIFTED_INPUT(axis, Right) - SHIFTED_INPUT(axis, Left));
        delta_y = (!(delta_x!=0))*(SHIFTED_INPUT(axis, Down) - SHIFTED_INPUT(axis, Up));

        move_on_level(&lv_1, &player.move_comp, delta_x * player.move_comp.speed * (1.0/60), delta_y * player.move_comp.speed * (1.0/60));
       
        if (delta_x) 
        {
            set_drawable_srcrect(&dw_player, 1, 0);
        }
        else if (delta_y<0)
        {
            set_drawable_srcrect(&dw_player, 2, 0);
        } 
        else
        {
            set_drawable_srcrect(&dw_player, 0, 0);
        }
        set_drawable_dstrect_coords(&dw_player, player.move_comp.x, player.move_comp.y);      
        
        SDL_RenderCopyEx(renderer, dw_player.texture, &dw_player.src_rect, &dw_player.dst_rect, 
                         0, NULL, (delta_x<0) * SDL_FLIP_HORIZONTAL);

        SDL_RenderPresent(renderer);
    }    

quit:
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
