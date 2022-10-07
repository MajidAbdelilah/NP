#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
 
#include "app.h"
#include "image.h"

int main(int argnum, char **args) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("NewPixel",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        1280, 720,
                        SDL_WINDOW_RESIZABLE);

    
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	
	npImage image = init_image(30, 20, (SDL_Rect){0, 0, 1280, 720}, (npPixel){100, 20, 150, 255}, renderer);
 
	npMouse mouse = {0};
	
	bool app_is_running = true;
	while (app_is_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			app_is_running = (event.type != SDL_QUIT);
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			mouse.type = event.button.type;
			mouse.state = event.button.state;
			mouse.button = event.button.button;
			//printf("x: %u, y: %u;\n", mouse.x, mouse.y);
		};
		
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		
	    SDL_RenderCopy(renderer, image.texture, NULL, &image.rect);

		
		draw_to_image(image, (npPixel){255, 255, 255, 255});

		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	}
	

	return 0;
}
