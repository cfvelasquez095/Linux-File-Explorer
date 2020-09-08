#include "../headers/TextView.h"

TextView::TextView(std::string txt,int x,int y)
{
    text = txt;
    position.x = x;
    position.y = y;
    attrs.x = txt.length()*12;
    attrs.y = 24;
    clicks = 0;
    focused = false;
    sayFocused = Rect(x-30,y,30,1);
}

std::string TextView::getText()
{
    return text;
}

struct vector2 TextView::getPosition()
{
    return position;
}

struct vector2 TextView::getAttrs()
{
    return attrs;
}

void TextView::setText(std::string str)
{
    text = str;
}

bool TextView::isClicked(int posX, int posY)
{
    if(posX > position.x && posX < (position.x + attrs.x))
    {
        if(posY < position.y && posY > (position.y - attrs.y))
        {
            clicks = clicks >= 2?0:clicks+1;
            if(clicks == 1)
                focused = true;
            else 
                focused = false;
            return true;
        }
    }
    clicks = 0;
    focused = false;
    return false;
}

bool TextView::isFocused()
{
    return focused;
}

bool TextView::isDoubleClicked(int posX, int posY)
{
    if(isClicked(posX,posY) && clicks == 2)
    {
        return true;
    }
    return false;
}