#ifndef SCREEN_H
#define SCREEN_H

#include <QImage>
class Screen:public QImage
{
public:
    Screen(){
        printf("hello1\n");
    }

    Screen(int width,int height):QImage(width,height,QImage::Format_RGB32)
    {
        printf("hello2\n");
    }

private:

};

#endif // SCREEN_H
