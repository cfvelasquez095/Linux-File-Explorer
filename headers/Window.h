#ifndef WINDOW_H
#define WINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <unistd.h>   // So we got the profile for 10 seconds
#include "../headers/Rect.h"
#include "../headers/TextView.h"

#define NIL (0)

struct window_attr
{
    int width;
    int height;
    int size;
};

class RenderWindow
{
    public:
        RenderWindow();
        void createWindow(int width, int height,std::string title);
        void clear(int color);
        void close();
        XEvent pollEvent(XEvent e);
        bool isOpen();
        struct window_attr getAttributes();
        void draw(Rect r);
        void draw(TextView t);
        struct vector2 getPointerPos();
        Display *dpy;



        int BLACKCOLOR;
        int WHITECOLOR;

    private:
        Window w;
        GC gc;
        bool open;
        Atom WM_DELETE_WINDOW;
        XWindowAttributes window_attributes;
        XFontStruct *font;
        struct vector2 pointerPos;


};

#endif