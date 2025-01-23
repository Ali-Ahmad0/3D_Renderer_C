#pragma once
#include "../common/util.h"

typedef struct 
{
	vec3_t position;
	vec3_t facing;

	float view_matrix[4][4];
} camera_t;

camera_t camera_create();
void camera_update(camera_t* camera);