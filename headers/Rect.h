#ifndef RECT_H
#define RECT_H
#include <iostream>

struct vector2
{
    int x;//cuando sea atributos, este sera el width
    int y;//cuando sea atributos, este sera el height
};

class Rect
{
    public:
        Rect(int x,int y,int width, int height);
        Rect();
        void setPosition(struct vector2 m);
        void setRect(int x,int y,int width, int height);
        void setAttributes(int w, int h);
        void setColor(int c);
        struct vector2 getPosition();
        struct vector2 getAttributes();
        int getColor();



    private:
        struct vector2 position;
        struct vector2 attr;
        int color;


};

#endif