#ifndef VECTOR_H
#define VECTOR_H
#include "math.h"

class Vector4{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4();

    Vector4(float x1, float y1, float z1, float w1);

    // 获取矢量的模
    float getLength();

    // 归一化
    void normalize();

    // 矢量加法
    static Vector4 add(const Vector4& v1, const Vector4& v2);

    // 矢量减法
    static Vector4 sub(const Vector4& v1, const Vector4& v2);

    // 点乘
    static float dotProduct(const Vector4& v1, const Vector4& v2);

    // 叉乘
    static Vector4 crossProduct(const Vector4& v1, const Vector4& v2);

    // 插值
    static Vector4 interp(const Vector4& v1, const Vector4& v2, float t);

};

typedef Vector4 Point;
#endif // VECTOR_H
