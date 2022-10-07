#pragma once
#include <SDL2/SDL_stdinc.h>
#include <stdbool.h>

typedef struct npMouse {
	unsigned int x, y;
	Uint32 type;
	Uint8 state;
	Uint8 button;
}npMouse;

