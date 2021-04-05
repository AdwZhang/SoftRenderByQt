#ifndef VERTEX_H
#define VERTEX_H
#include "vector.h"

struct Color { float r; float g; float b; };
struct Texcoord { float u; float v; };

struct Vertex
{
    Vector pos;
    Color color;
    Texcoord tex;
    Vector normal;
    float rhw; // 透视矫正
};

#endif // VERTEX_H
