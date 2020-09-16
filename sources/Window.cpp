#include "../headers/Window.h"

RenderWindow::RenderWindow()
{
    dpy = (XOpenDisplay(NIL));
    BLACKCOLOR = BlackPixel(dpy, DefaultScreen(dpy));
    WHITECOLOR = WhitePixel(dpy, DefaultScreen(dpy));
    SLATEGREYCOLOR = 3100495;    
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
    XSetWindowBackground(dpy, w, WHITECOLOR);
    XSetBackground(dpy, gc, WHITECOLOR);
    XSetForeground(dpy, gc, BLACKCOLOR);

    XStoreName(dpy,w,title.c_str());
    XMapRaised(dpy, w);
    XSetWMProtocols(dpy, w, &WM_DELETE_WINDOW, 1);
    //setting font:
    const char * fontname = "7x14";
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
    XSetForeground(dpy, gc, BLACKCOLOR);
    XDrawRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
}

void RenderWindow::drawNavbar(Rect r)
{
    struct vector2 pos = r.getPosition();
    struct vector2 attr = r.getAttributes();
    XSetFillStyle(dpy, gc, FillSolid);
    XSetForeground(dpy, gc, BLACKCOLOR);
    XDrawRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
    XSetForeground(dpy, gc, 11674146);
    XSetBackground(dpy, gc, BLACKCOLOR);
    XFillRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
}

void RenderWindow::drawSidebar(Rect r)
{
    struct vector2 pos = r.getPosition();
    struct vector2 attr = r.getAttributes();
    XSetFillStyle(dpy, gc, FillSolid);
    XSetForeground(dpy, gc, BLACKCOLOR);
    XDrawRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
    XSetForeground(dpy, gc, 8388608);
    XSetBackground(dpy, gc, BLACKCOLOR);
    XFillRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
}

void RenderWindow::draw(TextEdit t)
{
    if(t.focused)
        draw(t.sayFocused);
    
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;
    struct vector2 pos = t.textBox.getPosition();
    struct vector2 attr = t.textBox.getAttributes();

    XSetBackground(dpy, gc, WHITECOLOR);
    XSetForeground(dpy, gc, BLACKCOLOR);

    XDrawRectangle(dpy, w, gc, pos.x, pos.y, attr.x, attr.y);
    std::string texto = t.getText();
    XTextExtents(font,texto.c_str(),texto.length(),&direction,&ascent,&descent,&overall);
    XDrawString(dpy,w,gc,pos.x +5,pos.y + attr.y - 10,texto.c_str(),texto.length());
}

void RenderWindow::draw(TextView t)
{
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;

    struct vector2 pos = t.getPosition();
    std::string texto = t.getText();
    XSetForeground(dpy,gc, BLACKCOLOR);
    XTextExtents(font,texto.c_str(),texto.length(),&direction,&ascent,&descent,&overall);
    XDrawString(dpy,w,gc,pos.x,pos.y,texto.c_str(),texto.length());
}

void RenderWindow::drawNavbuttons(TextView t)
{
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;

    struct vector2 pos = t.getPosition();
    std::string texto = t.getText();
    XSetForeground(dpy,gc, WHITECOLOR);
    XTextExtents(font,texto.c_str(),texto.length(),&direction,&ascent,&descent,&overall);
    XDrawString(dpy,w,gc,pos.x,pos.y,texto.c_str(),texto.length());
}

void RenderWindow::drawPartitions(TextView t)
{
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;

    struct vector2 pos = t.getPosition();
    std::string texto = t.getText();
    XSetForeground(dpy,gc, WHITECOLOR);
    XTextExtents(font,texto.c_str(),texto.length(),&direction,&ascent,&descent,&overall);
    XDrawString(dpy,w,gc,pos.x,pos.y,texto.c_str(),texto.length());
}