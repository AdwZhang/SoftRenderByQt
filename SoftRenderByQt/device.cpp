#include "device.h"

Device::Device(QString name, int width, int height)
{
    this->resize(width,height);
    this->width = width;
    this->height = height;
    this->zBuffer = vector<vector<float>>(width,vector<float>(height,0));

    this->setWindowTitle(name);
    this->label = new QLabel(this);
    screen = Screen(width,height);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            screen.setPixelColor(i,j,{0,0,0});
        }
    }
    label->setPixmap(QPixmap::fromImage(screen));
    label->setGeometry(0,0,screen.width(),screen.height());
}

// 画点
void Device::drawPoint(const Vector4& p, const Color& color, const Texcoord& tc, const Vector4& normal)
{
    int x = p.x;
    int y = p.y;

    if(x > width || x < 0) return;
    if(y > height || y < 0) return;
    //if (zbuffer[y * width + x] < p.z) return;

    screen.setPixelColor(x,y,{color.r,color.g,color.b});
    label->setPixmap(QPixmap::fromImage(screen));
}


// 画线
void Device::drawLine(const Vector4& p1, const Vector4& p2, Color color)
{
    Texcoord tex = { 0.f, 0.f };
    Vector4 normal = { 0.f, 0.f, 0.f , 0.f };

    float x1,y1,x2,y2;
    x1 = p1.x;
    y1 = p1.y;

    x2 = p2.x;
    y2 = p2.y;

    if (x1 == x2 && y1 == y2) {
        drawPoint(p1, color, tex, normal);
    }
    else if (x1 == x2) {
        drawPoint(p1, color, tex, normal);

        int inc = (y1 < y2) ? 1 : -1;
        while (1) {
            y1 += inc;
            if (inc == 1 && y1 >= y2) break;
            if (inc == -1 && y1 <= y2) break;
            Vector4 p = { x1, y1, 0.f, 1.f };
            drawPoint(p, color, tex, normal);
        }

        drawPoint(p2, color, tex, normal);
    }
    else if (y1 == y2) {
        drawPoint(p1, color, tex, normal);

        int inc = (x1 < x2) ? 1 : -1;
        while (1) {
            x1 += inc;
            if (inc == 1 && x1 >= x2) break;
            if (inc == -1 && x1 <= x2) break;
            Vector4 p = { x1, y1, 0.f, 1.f };
            drawPoint(p, color, tex, normal);
        }

        drawPoint(p2, color, tex, normal);
    }
    else {
        drawPoint(p1, color, tex, normal);

        float t = (float)abs(x2 - x1) / abs(y2 - y1);
        int xinc = (p1.x < p2.x) ? 1 : -1;
        int yinc = (p1.y < p2.y) ? 1 : -1;
        while (1) {
            y1 += yinc;
            if (yinc == 1 && y1 >= y2) break;
            if (yinc == -1 && y1 <= y2) break;
            x1 += t * xinc;
            drawPoint({ x1,y1,0.f,1.f }, color, tex, normal);
        }

        drawPoint(p2, color, tex, normal);
    }
}

// 画三角形
void Device::drawTriangle(const Vertex& p1, const Vertex& p2, const Vertex& p3)
{

}
