#ifndef MATRIX_H
#define MATRIX_H
#include "vector4.h"

class Matrix
{
public:
    float m[4][4];

    // matrix identity
    void setIdentity();

    // matrix zero
    void setZero();

    // 平移变换
    void setTranslate(float x, float y, float z);

    // 缩放变换
    void setScale(float x, float y, float z);

    // 旋转矩阵
    void setRotate(float x, float y, float z, float theta);

    // 设置摄像机
    void setLookAt(const Vector4& eye, const Vector4& at, const Vector4& up);

    // perspective透视
    void setPerspective(float fovy, float aspect, float zn, float fn);

    // matrix c = a + b
    static Matrix add(const Matrix& a, const Matrix& b);

    // matrix c = a - b
    static Matrix sub(const Matrix& a, const Matrix& b);

    // matrix c = a * b
    static Matrix mul(const Matrix& a, const Matrix& b);

    // matrix m = a * f
    static Matrix scale(const Matrix& a, const float f);

    // matrix v = x * m
    static Vector4 apply(const Vector4& x, const Matrix& m);


};

#endif // MATRIX_H
