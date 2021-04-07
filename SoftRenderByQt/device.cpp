#include "device.h"

Device::Device(QString name, int width, int height):transform(width,height)
{
    this->resize(width,height);
    this->width = width;
    this->height = height;
    this->zBuffer = vector<vector<float>>(width,vector<float>(height,0));
    dis = 10.f;
    // 初始化 transform
    this->setCamera(3.f, 3.f, dis);
    this->setWindowTitle(name);
    this->label = new QLabel(this);
    screen = Screen(width,height);
    clear();
    label->setPixmap(QPixmap::fromImage(screen));
    label->setGeometry(0,0,screen.width(),screen.height());

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(drawBox()));

    timer->start(10);

}

void Device::setCamera(float x, float y, float z)
{
    Vector4 eye = { x, y, z, 1.f }, at = { 0.f, 0.f, 0.f, 1.f }, up = { 0.f, 1.f, 0.f, 1.f };
    Matrix m;
    m.setLookAt(eye, at, up);
    transform.setView(m);
    transform.update();
}

// 画点
void Device::drawPoint(const Vector4& p, const Color& color, const Texcoord& tc, const Vector4& normal)
{
    int x = p.x;
    int y = p.y;

    if(x >= width || x < 0) return;
    if(y >= height || y < 0) return;
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
void Device::drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    Point c1 = transform.apply(v1.pos);
    Point c2 = transform.apply(v2.pos);
    Point c3 = transform.apply(v3.pos);

    if(transform.checkCvv(c1)) return;
    if(transform.checkCvv(c2)) return;
    if(transform.checkCvv(c3)) return;

    Point p1, p2, p3, min, max;

    p1 = transform.homogenize(c1);
    p2 = transform.homogenize(c2);
    p3 = transform.homogenize(c3);

    Color color = {50,50,50};
    drawLine(p1, p2, color);
    drawLine(p1, p3, color);
    drawLine(p2, p3, color);
}

void Device::drawBox(float theta)
{
    Matrix mm;
    mm.setRotate(0.f, 1.0f, 0.f, theta);

    Matrix tm;
    tm.setTranslate(5.0f, 0.f, 0.f);

    Matrix world;
    world = Matrix::mul(mm,tm);

    transform.setWorld(world);
    transform.update();

    Vertex vs[8] = {
        {{-1.f,  1.f, -1.f, 1.f}, {1.0f, 0.0f, 0.0f}, {0.f, 0.f}, {-1.f,  1.f, -1.f, 0.f},  1.f },
        {{-1.f,  1.f,  1.f, 1.f}, {0.0f, 1.0f, 0.0f}, {0.f, 1.f}, {-1.f,  1.f,  1.f, 0.f}, 1.f },
        {{ 1.f,  1.f,  1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}, { 1.f,  1.f,  1.f, 0.f}, 1.f },
        {{ 1.f,  1.f, -1.f, 1.f}, {1.0f, 1.0f, 0.0f}, {0.f, 1.f}, { 1.f,  1.f, -1.f, 0.f}, 1.f },

        {{-1.f, -1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}, {-1.f, -1.f, -1.f, 0.f}, 1.f },
        {{-1.f, -1.f,  1.f, 1.f}, {1.0f, 1.0f, 0.0f}, {0.f, 1.f}, {-1.f, -1.f,  1.f, 0.f}, 1.f },
        {{ 1.f, -1.f,  1.f, 1.f}, {1.0f, 0.0f, 0.0f}, {1.f, 1.f}, { 1.f, -1.f,  1.f, 0.f}, 1.f },
        {{ 1.f, -1.f, -1.f, 1.f}, {0.0f, 1.0f, 0.0f}, {1.f, 1.f}, { 1.f, -1.f, -1.f, 0.f}, 1.f },
    };

    drawPlane(vs[0], vs[1], vs[2], vs[3]);
    drawPlane(vs[7], vs[4], vs[0], vs[3]);
    drawPlane(vs[2], vs[6], vs[7], vs[3]);
    drawPlane(vs[5], vs[1], vs[0], vs[4]);
    drawPlane(vs[2], vs[1], vs[5], vs[6]);
    drawPlane(vs[6], vs[5], vs[4], vs[7]);
}

void Device::drawBox()
{
    clear();
    float theta = 1.0f;
    Matrix mm;
    mm.setRotate(0.f, 1.0f, 0.f, theta);

    Matrix tm;
    tm.setTranslate(5.0f, 0.f, 0.f);

    Matrix world;
    world = Matrix::mul(mm,tm);

    transform.setWorld(world);
    transform.update();

    Vertex vs[8] = {
        {{-1.f,  1.f, -1.f, 1.f}, {1.0f, 0.0f, 0.0f}, {0.f, 0.f}, {-1.f,  1.f, -1.f, 0.f},  1.f },
        {{-1.f,  1.f,  1.f, 1.f}, {0.0f, 1.0f, 0.0f}, {0.f, 1.f}, {-1.f,  1.f,  1.f, 0.f}, 1.f },
        {{ 1.f,  1.f,  1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}, { 1.f,  1.f,  1.f, 0.f}, 1.f },
        {{ 1.f,  1.f, -1.f, 1.f}, {1.0f, 1.0f, 0.0f}, {0.f, 1.f}, { 1.f,  1.f, -1.f, 0.f}, 1.f },

        {{-1.f, -1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}, {-1.f, -1.f, -1.f, 0.f}, 1.f },
        {{-1.f, -1.f,  1.f, 1.f}, {1.0f, 1.0f, 0.0f}, {0.f, 1.f}, {-1.f, -1.f,  1.f, 0.f}, 1.f },
        {{ 1.f, -1.f,  1.f, 1.f}, {1.0f, 0.0f, 0.0f}, {1.f, 1.f}, { 1.f, -1.f,  1.f, 0.f}, 1.f },
        {{ 1.f, -1.f, -1.f, 1.f}, {0.0f, 1.0f, 0.0f}, {1.f, 1.f}, { 1.f, -1.f, -1.f, 0.f}, 1.f },
    };

    drawPlane(vs[0], vs[1], vs[2], vs[3]);
    drawPlane(vs[7], vs[4], vs[0], vs[3]);
    drawPlane(vs[2], vs[6], vs[7], vs[3]);
    drawPlane(vs[5], vs[1], vs[0], vs[4]);
    drawPlane(vs[2], vs[1], vs[5], vs[6]);
    drawPlane(vs[6], vs[5], vs[4], vs[7]);
}


void Device::drawPlane(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4)
{
    // 必须重新制定一下纹理，不然就乱掉了
    Vertex t1 = v1, t2 = v2, t3 = v3, t4 = v4;
    t1.tex.u = 0.f; t2.tex.u = 1.f; t3.tex.u = 1.f; t4.tex.u = 0.f;
    t1.tex.v = 0.f; t2.tex.v = 0.f; t3.tex.v = 1.f; t4.tex.v = 1.f;

    drawTriangle(t1, t2, t3);
    drawTriangle(t3, t4, t1);
}

void Device::clear()
{
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            screen.setPixelColor(i,j,{0,0,0});
        }
    }
}

void Device::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        dis += 0.5;
        setCamera(3.f, 3.f, dis);
        //drawBox(1.f);
    }
    else if(event->key() == Qt::Key_Down)
    {
        dis -= 0.5;
        setCamera(3.f, 3.f, dis);
        //drawBox(1.f);
    }
}












