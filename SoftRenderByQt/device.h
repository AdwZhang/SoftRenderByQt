#ifndef DEVICE_H
#define DEVICE_H
#include <QWidget>
#include "screen.h"
#include "vertex.h"
#include "vector.h"
#include <QString>
#include <QLabel>

class Device : public QWidget
{
public:
    Device(QString name, int width, int height);
    void drawPoint(const Vector& p, const Color& color, const Texcoord& tc, const Vector& normal);
    void drawLine(const Vector& p1, const Vector& p2);
    void drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

private:
    Screen screen;

};

#endif // DEVICE_H
