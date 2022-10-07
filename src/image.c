#include "image.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>



npImage init_image(unsigned int w, unsigned int h, SDL_Rect rect, npPixel color, SDL_Renderer *renderer) {
  	
	npImage image = {0};
	image.w = w;
	image.h = h;
	image.rect = rect;
	image.pixels = malloc(sizeof(intptr_t) * image.h * image.w);
	memset(image.pixels, 0, sizeof(npPixel) * image.h * image.w);

	Uint32 rmask = 0x000000FF;
	Uint32 gmask = 0x0000FF00;
	Uint32 bmask = 0x00FF0000;
	Uint32 amask = 0xFF000000;
	
	
	SDL_Surface *tmp_surface = SDL_CreateRGBSurface(0, image.w, image.h, 32, rmask, gmask, bmask, amask);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	

	
	for(unsigned int i=0; i<image.h; i++){	
		for(unsigned int j=0; j<image.w; j++){
			image.pixels[i * image.w + j].alpha = color.alpha;
			image.pixels[i * image.w + j].red = color.red;
			image.pixels[i * image.w + j].green = color.green;
			image.pixels[i * image.w + j].blue = color.blue;
			
		}
    }
	
	
	SDL_UpdateTexture(texture, NULL, image.pixels, image.w * sizeof(npPixel));
	image.texture = texture;

	SDL_FreeSurface(tmp_surface);
	
	return image;

}


void draw_to_image(npImage image, npPixel color) {
	unsigned int pos_x = 0, pos_y = 0;
	float mul_w = 0.0f, mul_h = 0.0f;
	int mouse_x = 0, mouse_y = 0; Uint32 mouse_button = 0;
	bool is_in_bound = false;
	
	
	mouse_button = SDL_GetMouseState(&mouse_x, &mouse_y);
	
	
	//printf("mul_w: %f, mul_h: %f, is_in_bound = %s\n", mul_w, mul_h, is_in_bound ? "true" : "false");
	
    	if((mouse_button & SDL_BUTTON_LMASK) != 0){
			printf("loop 2: true\n");
			is_in_bound = (image.rect.x < mouse_x) && (image.rect.y < mouse_y) && ((image.rect.x + image.rect.w) > mouse_x) && ((image.rect.y + image.rect.h) > mouse_y);

			if(is_in_bound){
				//printf("loop 3: true\n");
				mul_w = ((float)image.w) / ((float)image.rect.w);
				mul_h = ((float)image.h) / ((float)image.rect.h);

				pos_x = (unsigned int)((float)mouse_x * mul_w);
				pos_y = (unsigned int)((float)mouse_y * mul_h);
				printf("pos_x = %u, pos_y = %u\n", pos_x, pos_y);
				image.pixels[pos_y * image.w + pos_x].red = 255;
				image.pixels[pos_y * image.w + pos_x].green = 255;
				image.pixels[pos_y * image.w + pos_x].blue = 255;

				SDL_UpdateTexture(image.texture, NULL, image.pixels, image.w * sizeof(npPixel));
				
				
				
			}

		}
	
	
	
}
