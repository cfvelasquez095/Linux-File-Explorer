#include "../headers/Window.h"

RenderWindow::RenderWindow()
{
    dpy = (XOpenDisplay(NIL));
    BLACKCOLOR = BlackPixel(dpy, DefaultScreen(dpy));
    WHITECOLOR = WhitePixel(dpy, DefaultScreen(dpy));
    
}

bool RenderWindow::isOpen()
{
    return open;
}

void RenderWindow::createWindow(int width, int height,std::string title)
{
    w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
	 			     width, height, 0, BLACKCOLOR, BLACKCOLOR);
    WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSelectInput(dpy, w,ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask |
        ButtonPressMask | ButtonReleaseMask  | StructureNotifyMask ); 
    XMapWindow(dpy, w);
    gc = XCreateGC(dpy, w, 0, NIL);
    XSetForeground(dpy, gc, BLACKCOLOR);
    XStoreName(dpy,w,title.c_str());
    XSetWMProtocols(dpy, w, &WM_DELETE_WINDOW, 1);
    //setting font:
    const char * fontname = "12x24";
    font = XLoadQueryFont(dpy,fontname);
    if (!font) {
        std::cout<<"unable to load font "<<fontname<<" using fixed\n"<<std::endl;
        font = XLoadQueryFont (dpy, "fixed");
    }
    XSetFont (dpy, gc, font->fid);
    open = true;
}

struct vector2 RenderWindow::getPointerPos()
{
    return pointerPos;
}

void RenderWindow::close()
{
    open = false;
    XFreeGC(dpy,gc);
    XDestroyWindow(dpy,w);
    XCloseDisplay(dpy);
}

void RenderWindow::clear(int color)
{
    XClearWindow(dpy,w);
    XSetWindowBackground(dpy,w,color);
}

XEvent RenderWindow::pollEvent(XEvent e)
{
    XNextEvent(dpy, &e);
    pointerPos.x = e.xbutton.x;
    pointerPos.y = e.xbutton.y;
    if(e.type == ClientMessage){
        close();
    }
    return e;
}

struct window_attr RenderWindow::getAttributes()
{
    XGetWindowAttributes(dpy, w, &window_attributes);
    struct window_attr x;
    x.height = window_attributes.height;
    x.width = window_attributes.width;
    return x;
}

void RenderWindow::draw(Rect r)
{
    struct vector2 pos = r.getPosition();
    struct vector2 attr = r.getAttributes();
    XDrawRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
}

void RenderWindow::draw(TextView t)
{
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;

    struct vector2 pos = t.getPosition();
    std::string texto = t.getText();
    XTextExtents(font,texto.c_str(),texto.length(),&direction,&ascent,&descent,&overall);
    XDrawString(dpy,w,gc,pos.x,pos.y,texto.c_str(),texto.length());
}