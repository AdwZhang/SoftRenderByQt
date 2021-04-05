#include "device.h"

Device::Device(QString name, int width, int height)
{
    this->resize(width,height);
    this->setWindowTitle(name);
    QLabel *label=new QLabel(this);
    screen = Screen(width,height);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            screen.setPixelColor(i,j,{0,0,0});
        }
    }
    label->setPixmap(QPixmap::fromImage(screen));
    label->setGeometry(0,0,screen.width(),screen.height());
}
