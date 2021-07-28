#include "transform.h"

Transform::Transform(int w, int h)
{
    this->width = w;
    this->height = h;
    world.setIdentity();
    view.setIdentity();

    float aspect = (float)width/height;
    projection.setPerspective(3.1415926 * 0.5f,aspect,1.f,500.f);

    update();
}

// 矩阵更新，计算 transform = world * view * projection
void Transform::update()
{
    transform = Matrix::mul(world,view);
    transform = Matrix::mul(transform,projection);
}

// 将矢量 x 进行 project
Point Transform::apply(const Point& a)
{
    Point b = transform.apply(a);
    return b;
}

void Transform::applyMV(Vector4& a, const Vector4& b)
{

}

// 归一化，得到屏幕坐标
Vector4 Transform::homogenize(const Vector4& a)
{
    Vector4 b;
    float rhw = 1 / a.w;
    // 屏幕坐标
    b.x = (1.f + a.x * rhw) * width * 0.5;
    b.y = (1.f - a.y * rhw) * height * 0.5;
    b.z = a.z * rhw;
    b.w = 1.0f;
    return b;
}

// 检查齐次坐标同 cvv 的边界用于视锥裁剪
int Transform::checkCvv(const Point& v)
{
    float w = v.w;
    int check = 0;
    if (v.z < 0.0f) check |= 1;
    if (v.z >  w) check |= 2;
    if (v.x < -w) check |= 4;
    if (v.x >  w) check |= 8;
    if (v.y < -w) check |= 16;
    if (v.y >  w) check |= 32;
    return check;
}

//int Transform::checkBackCulling(const Vector4& v)
//{

//}

// 设定世界坐标变换矩阵
void Transform::setWorld(const Matrix& m)
{
    world = m;
}

// 设定相机坐标变换矩阵
void Transform::setView(const Matrix& m)
{
    view = m;
}
















