#include <SDL.h>
#include <stdio.h>

#include "engine/engine.h"
#include "common/util.h"
#include "camera/camera.h"
#include "rendering/rendering.h"
#include "polyhedron/polyhedron.h"

int main(int argc, char* argv[])
{
	engine_t engine = engine_create();
	camera_t camera = camera_create();
	
	add_cube(&engine, 100);

	engine_init(&engine);
	engine_update(&engine, &camera);
	engine_exit(&engine);

	return 0;
}