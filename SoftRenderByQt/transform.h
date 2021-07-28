#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "matrix.h"


class Transform
{
public:
    Transform();
    Transform(int w,int h);

    // 矩阵更新，计算 transform = world * view * projection
    void update();

    // 将矢量 x 进行 project
    Point apply(const Point& a);

    void applyMV(Vector4& b, const Vector4& a);

    // 归一化，得到屏幕坐标
    Vector4 homogenize(const Vector4& a);

    // 检查齐次坐标同 cvv 的边界用于视锥裁剪
    int checkCvv(const Point& v);

    //int checkBackCulling(const Vector4& v);

    // 设定世界坐标变换矩阵
    void setWorld(const Matrix& m);

    // 设定相机坐标变换矩阵
    void setView(const Matrix& m);

private:
    Matrix world;   // 世界坐标变换
    Matrix view;    // 相机坐标变换
    Matrix projection;  // 投影变换
    Matrix transform;   // transform = world * view * projection 变换矩阵
    int width;
    int height;
};

#endif // TRANSFORM_H
