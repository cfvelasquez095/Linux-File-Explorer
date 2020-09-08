#include "../headers/Rect.h"


Rect::Rect(int x,int y,int width, int height)
{
    position.x = x;
    position.y = y;
    attr.x = width;
    attr.y = height;
}
Rect::Rect()
{
    position.x = 0;
    position.y = 0;
    attr.x = 10;
    attr.y = 10;
}

void Rect::setPosition(struct vector2 m)
{
    position.x = m.x;
    position.y = m.y;
}

void Rect::setRect(int x,int y,int width, int height)
{
    position.x = x;
    position.y = y;
    attr.x = width;
    attr.y = height;
}

void Rect::setAttributes(int w, int h)
{
    attr.x = w;
    attr.y = h;
}

void Rect::setColor(int c)
{
    color = c;
}

struct vector2 Rect::getPosition()
{
    struct vector2 m;
    m.x = position.x;
    m.y = position.y;
    return m;
}

struct vector2 Rect::getAttributes()
{
    struct vector2 m;
    m.x = attr.x;
    m.y = attr.y;
    return m;
}

int Rect::getColor()
{
    return color;
}