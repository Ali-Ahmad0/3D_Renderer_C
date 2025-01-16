#include "vertex.h"

// Rotate a vertex along the x axis
// By an angle of theta
void rotate_x(vec3_t* vertex, float theta)
{
	float new_y = (float)cos(theta) * vertex->y - (float)sin(theta) * vertex->z;
	float new_z = (float)sin(theta) * vertex->y + (float)cos(theta) * vertex->z;

	vertex->y = new_y;
	vertex->z = new_z;
}

// Rotate a vertex along the y axis
// By an angle of theta
void rotate_y(vec3_t* vertex, float theta)
{
	float new_x = (float)cos(theta) * vertex->x - (float)sin(theta) * vertex->z;
	float new_z = (float)sin(theta) * vertex->x + (float)cos(theta) * vertex->z;

	vertex->x = new_x;
	vertex->z = new_z;
}

// Rotate a vertex along the z axis
// By an angle of theta
void rotate_z(vec3_t* vertex, float theta)
{
	float new_x = (float)cos(theta) * vertex->x - (float)sin(theta) * vertex->y;
	float new_y = (float)sin(theta) * vertex->x + (float)cos(theta) * vertex->y;

	vertex->x = new_x;
	vertex->y = new_y;
}

// Project 3D vertex onto a 2D screen
vec2_t project(vec3_t vertex, size_t scale)
{
	vec2_t projection = { WINDOW_SIZE_X / 2 + (FOV * vertex.x) / (FOV + vertex.z) * scale,
		WINDOW_SIZE_Y / 2 + (FOV * vertex.y) / (FOV + vertex.z) * scale };

	return projection;
}