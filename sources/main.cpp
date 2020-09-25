#include <X11/Xlib.h> // Every Xlib program must include this
#include <X11/Xutil.h>
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include "../headers/Window.h"
#include "../headers/FileSys.h"
#include <vector>

int main()
{
    RenderWindow x;
    TextView createFolderBtn = TextView("Create Directory",230,555);
    TextView createArchivoBtn = TextView("Create File",230,585);
    TextView copyBtn = TextView("Copy File/Dir",400,555);
    TextView deleteBtn = TextView("Remove File/Dir",400,585);
    TextView mvBtn = TextView("Move File/Dir",570,555);
    TextView lnHBtn = TextView("Create Hard Link",570,585);
    TextView lnSBtn = TextView("Create Soft Link",740,555);
    TextView returnBtn = TextView("<-Back",220,25);
    TextView forwardBtn = TextView("Forward->",280,25);
    x.createWindow(900,600,"Linux File Explorer");
    

    while(x.isOpen())
    {
        XEvent e;
        e = x.pollEvent(e);

        x.drawSidebar(Rect(0,0,190,525));
        x.draw(Rect(0,525,900,74));
        x.draw(createFolderBtn);
        x.draw(createArchivoBtn);
        x.draw(deleteBtn);
        x.draw(copyBtn);
        x.draw(returnBtn);
        x.draw(forwardBtn);
        x.draw(mvBtn);
        x.draw(lnHBtn);
        x.draw(lnSBtn);  
    }

    return 0;
}