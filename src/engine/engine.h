#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "../common/util.h"

#define TARGET_DELTA_TIME 16

typedef struct 
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Edges to render
	edge_t* render_queue;

	uint16_t maximum_size;
	uint16_t object_count;
} engine_t;

engine_t engine_create();
void engine_init(engine_t* engine);
void engine_update(engine_t* engine);
void engine_exit(engine_t* engine);