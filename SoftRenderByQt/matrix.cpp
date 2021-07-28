#include "matrix.h"

// matrix identity
void Matrix::setIdentity()
{
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    m[0][1] = m[0][2] = m[0][3] = 0.0f;
    m[1][0] = m[1][2] = m[1][3] = 0.0f;
    m[2][0] = m[2][1] = m[2][3] = 0.0f;
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

// matrix zero
void Matrix::setZero()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m[i][j] = 0.0f;
        }
    }
}

// vector4 v = x * m
Vector4 Matrix::apply(const Vector4& x)
{
    Vector4 v;
    float X = x.x, Y = x.y, Z = x.z, W = x.w;
    v.x = X * m[0][0] + Y * m[1][0] + Z * m[2][0] + W * m[3][0];
    v.y = X * m[0][1] + Y * m[1][1] + Z * m[2][1] + W * m[3][1];
    v.z = X * m[0][2] + Y * m[1][2] + Z * m[2][2] + W * m[3][2];
    v.w = X * m[0][3] + Y * m[1][3] + Z * m[2][3] + W * m[3][3];
    return v;
}

// 平移变换
void Matrix::setTranslate(float x, float y, float z)
{
    this->setIdentity();
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

// 缩放变换
void Matrix::setScale(float x, float y, float z)
{
    this->setIdentity();
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
}

// 旋转矩阵
void Matrix::setRotate(float x, float y, float z, float theta)
{
    float qsin = (float)sin(theta * 0.5f);
    float qcos = (float)cos(theta * 0.5f);
    Vector4 vec = { x, y, z, 1.0f };
    float w = qcos;
    vec.normalize();
    x = vec.x * qsin;
    y = vec.y * qsin;
    z = vec.z * qsin;
    m[0][0] = 1 - 2 * y * y - 2 * z * z;
    m[1][0] = 2 * x * y - 2 * w * z;
    m[2][0] = 2 * x * z + 2 * w * y;
    m[0][1] = 2 * x * y + 2 * w * z;
    m[1][1] = 1 - 2 * x * x - 2 * z * z;
    m[2][1] = 2 * y * z - 2 * w * x;
    m[0][2] = 2 * x * z - 2 * w * y;
    m[1][2] = 2 * y * z + 2 * w * x;
    m[2][2] = 1 - 2 * x * x - 2 * y * y;
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

// 设置摄像机
void Matrix::setLookAt(const Vector4& eye, const Vector4& at, const Vector4& up)
{
    Vector4 xaxis, yaxis, zaxis;

    zaxis = Vector4::sub(at, eye); // 眼睛前方 z 轴方向矢量
    zaxis.normalize();
    xaxis = Vector4::crossProduct(up, zaxis); // up 和 z = x 轴
    xaxis.normalize();
    yaxis = Vector4::crossProduct(zaxis, xaxis);

    m[0][0] = xaxis.x;
    m[1][0] = xaxis.y;
    m[2][0] = xaxis.z;
    m[3][0] = -Vector4::dotProduct(xaxis, eye);

    m[0][1] = yaxis.x;
    m[1][1] = yaxis.y;
    m[2][1] = yaxis.z;
    m[3][1] = -Vector4::dotProduct(yaxis, eye);

    m[0][2] = zaxis.x;
    m[1][2] = zaxis.y;
    m[2][2] = zaxis.z;
    m[3][2] = -Vector4::dotProduct(zaxis, eye);

    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

// perspective透视 Fov:纵向的视角大小 aspect:裁剪面的宽高比 zNear:近裁剪面离摄像机的距离 zFar:远裁剪面离摄像机的距离
void Matrix::setPerspective(float fovy, float aspect, float zn, float zf)
{
    float fax = 1.0f / (float)tan(fovy * 0.5f);
    this->setZero();
    m[0][0] = (float)(fax / aspect);
    m[1][1] = (float)(fax);
    m[2][2] = zf / (zf - zn);
    m[3][2] = -zn * zf / (zf - zn);
    m[2][3] = 1;
}


// matrix c = a + b
Matrix Matrix::add(const Matrix& a, const Matrix& b)
{
    Matrix c;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            c.m[i][j] = a.m[i][j] + b.m[i][j];
        }
    }
    return c;
}

// matrix c = a - b
Matrix Matrix::sub(const Matrix& a, const Matrix& b)
{
    Matrix c;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            c.m[i][j] = a.m[i][j] - b.m[i][j];
        }
    }
    return c;
}

// matrix c = a * b
Matrix Matrix::mul(const Matrix& a, const Matrix& b)
{
    Matrix c;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            c.m[i][j] = a.m[i][0] * b.m[0][j] +
                    a.m[i][1] * b.m[1][j] +
                    a.m[i][2] * b.m[2][j] +
                    a.m[i][3] * b.m[3][j] ;
        }
    }
    return c;
}

// matrix c = a * f
Matrix Matrix::scale(const Matrix& a, const float f)
{
    Matrix c;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            c.m[i][j] = a.m[i][j] * f;
    }
    return c;
}
