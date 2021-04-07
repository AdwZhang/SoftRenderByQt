#include <QApplication>
#include<iostream>
#include <string>
#include "device.h"
#include "objmodel.h"
#include "vector4.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Device device("渲染器",800,600);
//    QLabel *label=new QLabel(&device);
//    Screen screen(1280,720);

//    for(int i = 0; i < 1280; i++){
//        for(int j = 0; j < 720; j++){
//            screen.setPixelColor(i,j,{0,0,0});
//        }
//    }
//    label->setPixmap(QPixmap::fromImage(screen));
//    label->setGeometry(0,0,screen.width(),screen.height());
    //ObjModel model("models/sample.obj");
    Vector4 p1(60,50,0,0);
    Vector4 p2(120,710,0,0);
    cout<< p1.getLength() << endl;

//    device.drawLine(p1,p2,{50,50,50});
    device.drawBox(1.f);
    device.show();

    return a.exec();
}
