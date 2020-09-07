#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <iostream>
#include "Rect.h"

class TextView
{
    public:
        TextView(std::string text,int x,int y);
        void setPosition(struct vector2 m);
        void setText(std::string str);
        void setFontSize(int c);
        struct vector2 getPosition();
        struct vector2 getAttrs();
        int getFontSize();
        std::string getText();
        bool isClicked(int posX, int posY);
        bool isDoubleClicked(int posX, int posY);
        bool isFocused();
        Rect sayFocused;




    private:
        struct vector2 position;
        struct vector2 attrs;
        int clicks;
        std::string text;
        bool focused;


};

#endif