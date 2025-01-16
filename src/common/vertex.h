#pragma once
#include "util.h"
#include <math.h>

void rotate_x(vec3_t* vertex, float theta);
void rotate_y(vec3_t* vertex, float theta);
void rotate_z(vec3_t* vertex, float theta);

vec2_t project(vec3_t vertex, size_t scale);