#pragma once
#include <stdlib.h>
#include <stdint.h>

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080
#define FOV 60

// 2D Vector
typedef struct 
{
	float x;
	float y;
} vec2_t;

// 3D Vector
typedef struct 
{
	float x;
	float y;
	float z;
} vec3_t;

// An edge
typedef struct 
{
	vec3_t start;
	vec3_t end;

	size_t scale;
} edge_t;

uint32_t hsv_to_rgb(float h, float s, float v);