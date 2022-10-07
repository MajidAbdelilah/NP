#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "app.h"



typedef struct npPixel {
	unsigned char red, green, blue, alpha;
} npPixel;

typedef struct npImage {
	npPixel *pixels;
	unsigned int w;
	unsigned int h;
	SDL_Rect rect;
	SDL_Texture *texture;
}npImage;



npImage init_image(unsigned int w, unsigned int h, SDL_Rect rect, npPixel color, SDL_Renderer *renderer);
void draw_to_image(npImage image, npPixel color);
