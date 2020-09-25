#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>
#include <string>
#include "Rect.h"
#include <stdio.h>
#include <string.h>

class TextEdit
{
    public:
        TextEdit(int x, int y, int width);
        std::string getText();
        bool isClicked(int posX, int posY);
        void setText(std::string txt);
        void handleBackspace();
        void handleEvent(XEvent e,Display* dpy);
        Rect textBox;
        bool focused;
        Rect sayFocused;

    private:
        std::string text;


};

#endif