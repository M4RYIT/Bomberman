#include <SDL.h>

static const Sint32 alignment = 4;
static const Sint32 channels = 3;

int bmp_to_static_texture(const char *file_name, SDL_Renderer *renderer, SDL_Texture **static_texture);

int bmp_to_streaming_texture(const char *file_name, SDL_Renderer *renderer, SDL_Texture **streaming_texture);

int open_file(const char* file_name, Sint8 **content);

Sint32 calc_padded_row(const Sint32 row_size);

void bmp_dim(const Sint8 *content, Sint32 *w, Sint32 *h);

Sint8 *start_point(Sint8 *content);