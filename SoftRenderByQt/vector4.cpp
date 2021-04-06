#include "vector4.h"

Vector4::Vector4():x(0),y(0),z(0),w(0)
{
}

Vector4::Vector4(float x1, float y1, float z1, float w1):x(x1),y(y1),z(z1),w(w1)
{
}

//  获取矢量模
float Vector4::getLength()
{
    return sqrt(x*x + y*y + z*z + w*w);
}

//  矢量归一化
void Vector4::normalize()
{
    float len = this->getLength();
    // 防止对零矢量进行归一化
    if(len != 0)
    {
        float temp = 1/len;     //减少除法运算,性能优化
        x *= temp;
        y *= temp;
        z *= temp;
        w *= temp;
    }
}

// 矢量加法
Vector4 Vector4::add(const Vector4& v1, const Vector4& v2)
{
    Vector4 ans;
    ans.x = v1.x + v2.x;
    ans.y = v1.y + v2.y;
    ans.z = v1.z + v2.z;
    ans.w = 1.0f;
    return ans;
}

// 矢量减法
Vector4 Vector4::sub(const Vector4& v1, const Vector4& v2)
{
    Vector4 ans;
    ans.x = v1.x - v2.x;
    ans.y = v1.y - v2.y;
    ans.z = v1.z - v2.z;
    ans.w = 1.0f;
    return ans;
}

// 点乘
float Vector4::dotProduct(const Vector4& v1, const Vector4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// 叉乘
Vector4 Vector4::crossProduct(const Vector4& v1, const Vector4& v2)
{
    Vector4 ans;
    ans.x = v1.y * v2.z - v1.z * v2.y;
    ans.y = v1.z * v2.x - v1.x * v2.z;
    ans.z = v1.x * v2.y - v1.y * v2.x;
    ans.w = 1.0f;
    return ans;
}

