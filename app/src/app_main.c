#include "bomberman.h"
#include "dict.h"
#include "level1.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    level lv_1;
    level_init(&lv_1, 8, 8, 64, level1_cells);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          lv_1.cols * lv_1.cell_size, lv_1.rows * lv_1.cell_size, 0);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    net network;
    if (!net_init(&network, "127.0.0.1")) goto quit;   
    
    dict *players = dict_new(sizeof(bomberman));
    bomberman *pl = bomberman_init(renderer, 100, 100);

    set_send_buffer(&network, &(update_struct){pl->move_comp.x, pl->move_comp.y}, sizeof(update_struct));
    if (!net_send(&network, sizeof(update_struct))) goto quit;   

    if (!net_recv(&network, sizeof(setup_struct))) goto quit;
    setup_struct *set_up = (setup_struct*)network.recv_buffer; 
    network.update_rate = set_up->update_rate;
    dict_append(players, set_up->auth, pl);    
    printf("%d\n", set_up->auth); 

    drawable dw_cell;
    drawable_init(&dw_cell, renderer, "assets//level_tiles.bmp", 64, 64, 1, 4);   

    if (!net_noblock_mode(&network, 1)) goto quit;

    dict *players_vel = dict_new(sizeof(update_struct));

    float delta_x = 0;
    float delta_y = 0;
    uint8_t axis = 0;

    start_time();

    for(;;)
    {
        update_time();

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

        move_on_level(&lv_1, &pl->move_comp, delta_x * pl->move_comp.speed * delta_time(), delta_y * pl->move_comp.speed * delta_time());
       
        if (delta_x) 
        {
            set_drawable_srcrect(&pl->draw_comp, 1, 0);
        }
        else if (delta_y<0)
        {
            set_drawable_srcrect(&pl->draw_comp, 2, 0);
        } 
        else
        {
            set_drawable_srcrect(&pl->draw_comp, 0, 0);
        }
        set_drawable_dstrect_coords(&pl->draw_comp, pl->move_comp.x, pl->move_comp.y);      
        
        SDL_RenderCopyEx(renderer, pl->draw_comp.texture, &pl->draw_comp.src_rect, &pl->draw_comp.dst_rect, 
                         0, NULL, (delta_x<0) * SDL_FLIP_HORIZONTAL);

        if (net_update(&network))
        {
            set_send_buffer(&network, &(update_struct){pl->move_comp.x, pl->move_comp.y}, sizeof(update_struct));
            if (!net_send(&network, sizeof(update_struct))) goto quit;   
        }

        if (net_recv(&network, sizeof(other_update_struct)))
        {
            other_update_struct *nus = (other_update_struct*)network.recv_buffer;

            if (nus->x<0 || nus->y<0)
            {
                dict_remove(players, nus->auth);
                dict_remove(players_vel, nus->auth);
            }
            else
            {
                if (!dict_contains_key(players, nus->auth))
                {
                    dict_append(players, nus->auth, bomberman_init(renderer, nus->x, nus->y));    
                    dict_append(players_vel, nus->auth, new_update_struct(0.f, 0.f));
                }

                bomberman *bm = dict_value_by_key(players, nus->auth);
                update_struct *ups = dict_value_by_key(players_vel, nus->auth);
                set_update_struct(ups, (nus->x - bm->move_comp.x) * (1.0f/network.update_rate), 
                                 (nus->y - bm->move_comp.y) * (1.0f/network.update_rate));
            }            
        }

        for (int i=0; i<players_vel->count; i++)
        {
            dict_node *dn = dict_at(players_vel, i);
            update_struct *vel = dn->value;

            bomberman *bm = dict_value_by_key(players, dn->key); 
            bm->move_comp.x += vel->x * delta_time();
            bm->move_comp.y += vel->y * delta_time();

            set_drawable_dstrect_coords(&bm->draw_comp, bm->move_comp.x, bm->move_comp.y);
            SDL_RenderCopy(renderer, bm->draw_comp.texture, &bm->draw_comp.src_rect, &bm->draw_comp.dst_rect);
        }

        SDL_RenderPresent(renderer);
    }    

quit:
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);

    set_send_buffer(&network, &(update_struct){-1, -1}, sizeof(update_struct));
    net_send(&network, sizeof(update_struct));
    
    net_free(&network);
    dict_free(players);
    dict_free(players_vel);
    SDL_Quit();
    return 0;
}
