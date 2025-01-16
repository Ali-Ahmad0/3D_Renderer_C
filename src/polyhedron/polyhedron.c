#include "polyhedron.h"
#include "../rendering/rendering.h"

void add_tetrahedron(engine_t* engine, size_t scale)
{
    // Vertices
    vec3_t vertices[4] = {
        {  1.0f,  1.0f,  1.0f },
        { -1.0f, -1.0f,  1.0f },
        { -1.0f,  1.0f, -1.0f },
        {  1.0f, -1.0f, -1.0f }
    };

    // Edges
    edge_t edges[6] = {
        { vertices[0], vertices[1] },
        { vertices[1], vertices[2] },
        { vertices[2], vertices[0] },
        { vertices[0], vertices[3] },
        { vertices[1], vertices[3] },
        { vertices[2], vertices[3] }
    };

    for (int i = 0; i < 6; i++)
    {
        edges[i].scale = scale;
        rendering_add(engine, edges[i]);
    }
}

#include "polyhedron.h"
#include "../rendering/rendering.h"

void add_pyramid(engine_t* engine, size_t scale)
{
    // Vertices
    vec3_t vertices[5] = {
        { -1.0f, 1.0f, -1.0f },
        {  1.0f, 1.0f, -1.0f },
        {  1.0f, 1.0f,  1.0f },
        { -1.0f, 1.0f,  1.0f },
        {  0.0f, -1.0f, 0.0f }
    };

    // Edges
    edge_t edges[9] = {
        { vertices[0], vertices[1] },
        { vertices[1], vertices[2] },
        { vertices[2], vertices[3] },
        { vertices[3], vertices[0] },
        { vertices[0], vertices[2] },
        { vertices[0], vertices[4] },
        { vertices[1], vertices[4] },
        { vertices[2], vertices[4] },
        { vertices[3], vertices[4] }
    };

    for (int i = 0; i < 9; i++)
    {
        edges[i].scale = scale;
        rendering_add(engine, edges[i]);
    }
}


void add_cube(engine_t* engine, size_t scale) 
{
	// Vertices
    vec3_t vertices[8] = {
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, -1.0f,  1.0f },
    { -1.0f,  1.0f, -1.0f },
    { -1.0f,  1.0f,  1.0f },
    {  1.0f, -1.0f, -1.0f },
    {  1.0f, -1.0f,  1.0f },
    {  1.0f,  1.0f, -1.0f },
    {  1.0f,  1.0f,  1.0f }
    };

    // Edges
    edge_t edges[12] = {
        { vertices[0], vertices[1] },
        { vertices[1], vertices[3] },
        { vertices[3], vertices[2] },
        { vertices[2], vertices[0] },

        { vertices[4], vertices[5] },
        { vertices[5], vertices[7] },
        { vertices[7], vertices[6] },
        { vertices[6], vertices[4] },

        { vertices[0], vertices[4] },
        { vertices[1], vertices[5] },
        { vertices[3], vertices[7] },
        { vertices[2], vertices[6] }
    };

    for (int i = 0; i < 12; i++) 
    {
        edges[i].scale = scale;
        rendering_add(engine, edges[i]);
    }
        
}

void add_octahedron(engine_t* engine, size_t scale)
{
    // Vertices
    vec3_t vertices[6] = {
        {  0.0f,  0.0f,  1.0f },
        {  0.0f,  0.0f, -1.0f },
        { -1.0f,  0.0f,  0.0f },
        {  1.0f,  0.0f,  0.0f },
        {  0.0f, -1.0f,  0.0f },
        {  0.0f,  1.0f,  0.0f }
    };

    // Edges
    edge_t edges[12] = {
        { vertices[0], vertices[2] },
        { vertices[0], vertices[3] },
        { vertices[0], vertices[4] },
        { vertices[0], vertices[5] },
        { vertices[1], vertices[2] },
        { vertices[1], vertices[3] },
        { vertices[1], vertices[4] },
        { vertices[1], vertices[5] },
        { vertices[2], vertices[4] },
        { vertices[2], vertices[5] },
        { vertices[3], vertices[4] },
        { vertices[3], vertices[5] }
    };

    for (int i = 0; i < 12; i++)
    {
        edges[i].scale = scale;
        rendering_add(engine, edges[i]);
    }
}
