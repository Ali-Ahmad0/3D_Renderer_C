#include "camera.h"
#include "../common/vertex.h"
#include <SDL.h>
#include <math.h>

camera_t camera_create()
{
    camera_t camera;
    camera.position = (vec3_t){ 0.0f, 0.0f, 0.0f };
    camera.facing = (vec3_t){ 0.0f, 0.0f, 1.0f };
    
    for (size_t i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            camera.view_matrix[i][j] = 0;

    return camera;
}

void camera_update(camera_t* camera)
{
    const uint8_t* key_state = SDL_GetKeyboardState(NULL);

    // Constant global up direction
    const vec3_t global_up = { 0.0f, -1.0f, 0.0f };

    // Calculate right vector (cross product of facing and global up)
    vec3_t right = {
        camera->facing.y * global_up.z - camera->facing.z * global_up.y,
        camera->facing.z * global_up.x - camera->facing.x * global_up.z,
        camera->facing.x * global_up.y - camera->facing.y * global_up.x
    };

    // Normalize right vector
    float magnitude_r = sqrtf(right.x * right.x + right.y * right.y + right.z * right.z);
    right.x /= magnitude_r;
    right.y /= magnitude_r;
    right.z /= magnitude_r;

    // Calculate up vector (cross product of right and facing)
    vec3_t up = {
        right.y * camera->facing.z - right.z * camera->facing.y,
        right.z * camera->facing.x - right.x * camera->facing.z,
        right.x * camera->facing.y - right.y * camera->facing.x
    };

    // Normalize up vector
    float magnitude_u = sqrtf(up.x * up.x + up.y * up.y + up.z * up.z);
    up.x /= magnitude_u;
    up.y /= magnitude_u;
    up.z /= magnitude_u;

    // Normalize facing direction
    float magnitude_f = sqrtf(camera->facing.x * camera->facing.x 
        + camera->facing.y * camera->facing.y 
        + camera->facing.z * camera->facing.z);
    camera->facing.x /= magnitude_f;
    camera->facing.y /= magnitude_f;
    camera->facing.z /= magnitude_f;

    // Compute the view matrix
    camera->view_matrix[0][0] = right.x;
    camera->view_matrix[0][1] = right.y;
    camera->view_matrix[0][2] = right.z;
    camera->view_matrix[0][3] = -(right.x * camera->position.x + right.y * camera->position.y + right.z * camera->position.z);

    camera->view_matrix[1][0] = up.x;
    camera->view_matrix[1][1] = up.y;
    camera->view_matrix[1][2] = up.z;
    camera->view_matrix[1][3] = -(up.x * camera->position.x + up.y * camera->position.y + up.z * camera->position.z);

    camera->view_matrix[2][0] = -camera->facing.x;
    camera->view_matrix[2][1] = -camera->facing.y;
    camera->view_matrix[2][2] = -camera->facing.z;
    camera->view_matrix[2][3] = camera->facing.x * camera->position.x 
        + camera->facing.y * camera->position.y 
        + camera->facing.z * camera->position.z;

    camera->view_matrix[3][0] = 0.0f;
    camera->view_matrix[3][1] = 0.0f;
    camera->view_matrix[3][2] = 0.0f;
    camera->view_matrix[3][3] = 1.0f;

    // Handle camera movement
    if (key_state[SDL_SCANCODE_W])
    {
        camera->position.x -= camera->facing.x / 2.5f;
        camera->position.y -= camera->facing.y / 2.5f;
        camera->position.z -= camera->facing.z / 2.5f;
    }
    if (key_state[SDL_SCANCODE_S])
    {
        camera->position.x += camera->facing.x / 2.5f;
        camera->position.y += camera->facing.y / 2.5f;
        camera->position.z += camera->facing.z / 2.5f;
    }
    if (key_state[SDL_SCANCODE_A])
    {
        camera->position.x -= right.x / 10.0f;
        camera->position.y -= right.y / 10.0f;
        camera->position.z -= right.z / 10.0f;
    }
    if (key_state[SDL_SCANCODE_D])
    {
        camera->position.x += right.x / 10.0f;
        camera->position.y += right.y / 10.0f;
        camera->position.z += right.z / 10.0f;
    }

    if (key_state[SDL_SCANCODE_LSHIFT]) 
    {
        camera->position.y -= global_up.y / 5.0f;
    }

    if (key_state[SDL_SCANCODE_LCTRL]) 
    {
        camera->position.y += global_up.y / 5.0f;
    }

    // Handle camera rotation
    if (key_state[SDL_SCANCODE_UP])
    {
        rotate_a(&camera->facing, right, 0.01f);
    }
    if (key_state[SDL_SCANCODE_DOWN])
    {
        rotate_a(&camera->facing, right, -0.01f);
    }
    if (key_state[SDL_SCANCODE_LEFT])
    {
        rotate_a(&camera->facing, up, 0.01f);
    }
    if (key_state[SDL_SCANCODE_RIGHT])
    {
        rotate_a(&camera->facing, up, -0.01f);
    }
}

