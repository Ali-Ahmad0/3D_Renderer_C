#include "engine.h"
#include "../common/vertex.h"
#include <math.h>

engine_t engine_create() 
{
	// Create engine struct
	engine_t engine = {
		.window = NULL,
		.renderer = NULL,
		.render_queue = NULL,
		.maximum_size = 32,
		.object_count = 0
	};

	return engine;
}

// Initialize engine
void engine_init(engine_t* engine)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Initialize the window
		engine->window = SDL_CreateWindow("3D",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_FULLSCREEN
		);

		// Initialize the renderer
		engine->renderer = SDL_CreateRenderer(engine->window, -1, 0);
		SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	}
}

// Handle events
bool engine_event()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return false;
		break;
	}

	return true;
}

// Render objects
void engine_render(engine_t* engine)
{
	float time_factor = (float)SDL_GetTicks() / 1000.0f;

	float h = fmodf(time_factor * 0.1f, 1.0f) * 360.0f;
	float s = 0.9f;
	float v = 0.9f;

	uint32_t color = hsv_to_rgb(h, s, v);

	SDL_RenderClear(engine->renderer);
	SDL_SetRenderDrawColor(engine->renderer, 
		(color >> 16) & 0xFF, 
		(color >> 8 ) & 0xFF, 
		(color) & 0xFF, 255);

	// Draw all edges in the rendering queue
	for (uint8_t i = 0; i < engine->object_count; i++) 
	{
		size_t scale = engine->render_queue[i].scale;

		float speed_x = 0.015f * (float)sin(time_factor);
		float speed_y = 0.025f * (float)cos(time_factor);
		float speed_z = 0.005f * (float)sin(time_factor);

		// Rotate the vertices
		rotate_z(&engine->render_queue[i].start, speed_z);
		rotate_y(&engine->render_queue[i].start, speed_y);
		rotate_x(&engine->render_queue[i].start, speed_x);

		rotate_z(&engine->render_queue[i].end, speed_z);
		rotate_y(&engine->render_queue[i].end, speed_y);
		rotate_x(&engine->render_queue[i].end, speed_x);

		// Project vertices
		vec2_t start = project(engine->render_queue[i].start, scale);
		vec2_t end = project(engine->render_queue[i].end, scale);

		// Render the edges
		SDL_RenderDrawLineF(engine->renderer, start.x, start.y, end.x, end.y);
	}

	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(engine->renderer);
}


// Update engine
void engine_update(engine_t* engine)
{
	uint32_t frame_start_time;
	uint32_t frame_draw_time;

	// Main update loop
	while (true)
	{
		frame_start_time = SDL_GetTicks();

		// All the update logic
		if (!engine_event())
			break;
		engine_render(engine);

		frame_draw_time = SDL_GetTicks() - frame_start_time;

		// Delta time calculation
		// Maintain roughly 60fps
		if (frame_draw_time < TARGET_DELTA_TIME)
		{
			SDL_Delay(TARGET_DELTA_TIME - frame_draw_time);
		}
	}
}

// Exit engine
void engine_exit(engine_t* engine)
{
	SDL_DestroyWindow(engine->window);
	SDL_DestroyRenderer(engine->renderer);
	SDL_Quit();

	free(engine->render_queue);
	engine->render_queue = NULL;
}
