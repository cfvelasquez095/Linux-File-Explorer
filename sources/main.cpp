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
    TextView createFolderBtn = TextView("Create Directory",1530,40);
    TextView createArchivoBtn = TextView("Create File",1530,80);
    TextView copyBtn = TextView("Copy File/Dir",1530,120);
    TextView deleteBtn = TextView("Remove File/Dir",1530,160);
    TextView mvBtn = TextView("Move File/Dir",1530,200);
    TextView lnHBtn = TextView("Create Hard Link",1530,240);
    TextView lnSBtn = TextView("Create Soft Link",1530,280);
    TextView returnBtn = TextView("<---Back",1300,760);
    x.createWindow(1800,800,"Linux File Explorer");
    

    while(x.isOpen())
    {
        XEvent e;
        e = x.pollEvent(e);

        x.clear(x.WHITECOLOR);
        x.draw(Rect(290,0,1,800));
        x.draw(Rect(290,700,1200,1));
        x.draw(Rect(1500,0,1,800));
        x.draw(createFolderBtn);
        x.draw(createArchivoBtn);
        x.draw(deleteBtn);
        x.draw(copyBtn);
        x.draw(returnBtn);
        x.draw(mvBtn);
        x.draw(lnHBtn);
        x.draw(lnSBtn);  
    }

    return 0;
}