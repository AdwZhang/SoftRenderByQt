#ifndef VERTEX_H
#define VERTEX_H
#include "vector4.h"

struct Color { float r; float g; float b; };
struct Texcoord { float u; float v; };

struct Vertex
{
    Vector4 pos;
    Color color;
    Texcoord tex;
    Vector4 normal;
    float rhw; // 透视矫正
};

#endif // VERTEX_H
