#include "engine.h"
#include "../common/vertex.h"
#include <math.h>
#include <stdio.h>

engine_t engine_create() 
{
	// Create engine struct
	engine_t engine = {
		.window = NULL, .renderer = NULL, .render_queue = NULL,
		.maximum_size = 32, .object_count = 0
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
		engine->window = SDL_CreateWindow("3D Renderer - C",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			WINDOW_SIZE_X, WINDOW_SIZE_Y, 0
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
void engine_render(engine_t* engine, camera_t* camera)
{
	float time_factor = (float)SDL_GetTicks() / 1000.0f;

	float h = fmodf(time_factor * 0.1f, 1.0f) * 360.0f;
	float s = 1.0f;
	float v = 1.0f;

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

		// // Rotate the vertices
		//rotate_z(&engine->render_queue[i].start, speed_z);
		//rotate_y(&engine->render_queue[i].start, speed_y);
		//rotate_x(&engine->render_queue[i].start, speed_x);

		//rotate_z(&engine->render_queue[i].end, speed_z);
		//rotate_y(&engine->render_queue[i].end, speed_y);
		//rotate_x(&engine->render_queue[i].end, speed_x);

		vec3_t start_view = {
			camera->view_matrix[0][0] * engine->render_queue[i].start.x +
			camera->view_matrix[0][1] * engine->render_queue[i].start.y +
			camera->view_matrix[0][2] * engine->render_queue[i].start.z +
			camera->view_matrix[0][3],

			camera->view_matrix[1][0] * engine->render_queue[i].start.x +
			camera->view_matrix[1][1] * engine->render_queue[i].start.y +
			camera->view_matrix[1][2] * engine->render_queue[i].start.z +
			camera->view_matrix[1][3],

			camera->view_matrix[2][0] * engine->render_queue[i].start.x +
			camera->view_matrix[2][1] * engine->render_queue[i].start.y +
			camera->view_matrix[2][2] * engine->render_queue[i].start.z +
			camera->view_matrix[2][3]
		};

		vec3_t end_view = {
			camera->view_matrix[0][0] * engine->render_queue[i].end.x +
			camera->view_matrix[0][1] * engine->render_queue[i].end.y +
			camera->view_matrix[0][2] * engine->render_queue[i].end.z +
			camera->view_matrix[0][3],

			camera->view_matrix[1][0] * engine->render_queue[i].end.x +
			camera->view_matrix[1][1] * engine->render_queue[i].end.y +
			camera->view_matrix[1][2] * engine->render_queue[i].end.z +
			camera->view_matrix[1][3],

			camera->view_matrix[2][0] * engine->render_queue[i].end.x +
			camera->view_matrix[2][1] * engine->render_queue[i].end.y +
			camera->view_matrix[2][2] * engine->render_queue[i].end.z +
			camera->view_matrix[2][3]
		};

		// Project vertices
		vec2_t start = project(start_view, scale);
		vec2_t end = project(end_view, scale);

		// Render the edges
		SDL_RenderDrawLineF(engine->renderer, start.x, start.y, end.x, end.y);
	}

	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(engine->renderer);
}


// Update engine
void engine_update(engine_t* engine, camera_t* camera)
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

		camera_update(camera);
		engine_render(engine, camera);

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
