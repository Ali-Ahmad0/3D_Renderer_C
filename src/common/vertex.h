#pragma once
#include "util.h"
#include <math.h>

void translate_x(vec3_t* vertex, float dx);
void translate_y(vec3_t* vertex, float dy);
void translate_z(vec3_t* vertex, float dz);
void translate(vec3_t* vertex, vec3_t dv);

void rotate_x(vec3_t* vertex, float theta);
void rotate_y(vec3_t* vertex, float theta);
void rotate_z(vec3_t* vertex, float theta);
void rotate_a(vec3_t* vertex, vec3_t axis, float theta);

vec2_t project(vec3_t vertex, size_t scale);