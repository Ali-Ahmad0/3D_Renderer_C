#include "vertex.h"
#include <math.h>

// Move a vertex along the x axis
void translate_x(vec3_t* vertex, float dx) 
{
	vertex->x += dx;
}

// Move a vertex along the y axis
void translate_y(vec3_t* vertex, float dy) 
{
	vertex->y += dy;
}

// Move a vertex along the z axis
void translate_z(vec3_t* vertex, float dz) 
{
	vertex->z += dz;
}

// Move along all 3 directions
void translate(vec3_t* vertex, vec3_t dv) 
{
	translate_x(vertex, dv.x);
	translate_y(vertex, dv.y);
	translate_z(vertex, dv.z);
}

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

// Rotate a vertex along a custom axis
void rotate_a(vec3_t* vector, vec3_t axis, float theta) 
{
	float c = cos(theta);
	float s = sin(theta);

	vec3_t temp = {
		vector->x * (axis.x * axis.x * (1 - c) + c) +
		vector->y * (axis.x * axis.y * (1 - c) - axis.z * s) +
		vector->z * (axis.x * axis.z * (1 - c) + axis.y * s),

		vector->x * (axis.y * axis.x * (1 - c) + axis.z * s) +
		vector->y * (axis.y * axis.y * (1 - c) + c) +
		vector->z * (axis.y * axis.z * (1 - c) - axis.x * s),

		vector->x * (axis.z * axis.x * (1 - c) - axis.y * s) +
		vector->y * (axis.z * axis.y * (1 - c) + axis.x * s) +
		vector->z * (axis.z * axis.z * (1 - c) + c)
	};

	*vector = temp;
}

// Project 3D vertex onto a 2D screen
vec2_t project(vec3_t vertex, size_t scale)
{
	vec2_t projection = { WINDOW_SIZE_X / 2 + (FOV * vertex.x) / (FOV + vertex.z) * scale,
		WINDOW_SIZE_Y / 2 + (FOV * vertex.y) / (FOV + vertex.z) * scale };

	return projection;
}