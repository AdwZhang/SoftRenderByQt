#ifndef DEVICE_H
#define DEVICE_H
#include <QWidget>
#include "screen.h"
#include "vertex.h"
#include "vector4.h"
#include "transform.h"
#include "matrix.h"
#include <QString>
#include <QLabel>
#include <vector>
#include <QKeyEvent>
#include<QTimer>

using namespace std;

class Device : public QWidget
{
    Q_OBJECT

public:
    Device(QString name, int width, int height);

    void setCamera(float x, float y, float z);

    void drawPoint(const Vector4& p, const Color& color, const Texcoord& tc, const Vector4& normal);
    void drawLine(const Vector4& p1, const Vector4& p2,Color color);
    void drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

public slots:
    // 画立方体
    void drawBox(float theta);
    void drawBox();

    // 画四边形
    void drawPlane(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4);

    void clear();
private:
    Screen screen;
    QLabel *label;
    int width;
    int height;
    vector<vector<float>> zBuffer;
    Transform transform;
    float dis;
protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // DEVICE_H
