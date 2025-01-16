#include <SDL.h>
#include <stdio.h>

#include "engine/engine.h"
#include "common/util.h"
#include "rendering/rendering.h"
#include "polyhedron/polyhedron.h"

int main(int argc, char* argv[])
{
	engine_t engine = engine_create();
	
	add_cube(&engine, 256);

	engine_init(&engine);
	engine_update(&engine);
	engine_exit(&engine);

	return 0;
}