#include "rendering.h"
#include <stdlib.h>

void rendering_add(engine_t* engine, edge_t edge)
{
	// Return if the engine is NULL
	if (!engine) return;

	// Initialize the engine render queue
	if (!engine->render_queue)
	{
		edge_t* queue = malloc(sizeof(edge_t) * engine->maximum_size);
		if (!queue) return;

		engine->render_queue = queue;
	}

	// Expand render queue capacity
	if (engine->object_count >= engine->maximum_size)
	{
		uint16_t new_maximum_size = engine->maximum_size * 2;
		edge_t* new_queue = realloc(engine->render_queue, sizeof(edge_t) * new_maximum_size);
		if (!new_queue) return;

		engine->render_queue = new_queue;
		engine->maximum_size = new_maximum_size;
	}

	// Add edge to rendering queue
	engine->render_queue[engine->object_count++] = edge;
}