#include <QApplication>
#include<iostream>
#include <string>
#include "device.h"
#include "objmodel.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Device device("渲染器",1280,720);
//    QLabel *label=new QLabel(&device);
//    Screen screen(1280,720);

//    for(int i = 0; i < 1280; i++){
//        for(int j = 0; j < 720; j++){
//            screen.setPixelColor(i,j,{0,0,0});
//        }
//    }
//    label->setPixmap(QPixmap::fromImage(screen));
//    label->setGeometry(0,0,screen.width(),screen.height());
    ObjModel model("cow");
    device.show();

    return a.exec();
}
