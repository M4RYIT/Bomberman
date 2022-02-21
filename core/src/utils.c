#include "bomberman.h"

uint64_t last_t;
double delta_t;

void start_time()
{
    last_t = SDL_GetPerformanceCounter();
    delta_t = 0;
}

void update_time()
{
    uint64_t current_t = SDL_GetPerformanceCounter();
    delta_t = (double)(current_t-last_t)/(double)SDL_GetPerformanceFrequency();
    last_t = current_t;
}

double delta_time()
{       
    return delta_t;
}