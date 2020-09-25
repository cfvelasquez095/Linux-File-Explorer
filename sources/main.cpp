#include <X11/Xlib.h> // Every Xlib program must include this
#include <X11/Xutil.h>
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include "../headers/Window.h"
#include "../headers/FileSys.h"
#include <vector>

std::vector<TextView> getTextViewsFiles(std::vector<struct entry> files)
{
    std::vector<TextView> textos;
    int m = 1;
    int l = 1;
    for(int i = 0; i < files.size(); i++) {
        if(i > 12 && i < 36) {
            textos.push_back(TextView(files[i].name,335,(m+1)*35));
            m++;
        }
        else if(i > 35) {
            textos.push_back(TextView(files[i].name,445,(l+1)*35));
            l++;
        }
        else {
            textos.push_back(TextView(files[i].name,225,(i+2)*35));
        }
    }
    return textos;
}


std::vector<TextView> createTextViewsPartitions(std::vector<struct Mount> partitions)
{
    std::vector<TextView> textos;
    for(int i = 0; i < partitions.size(); i++) {
        textos.push_back(TextView(partitions[i].destination,20,(i+2)*35));
    }

    return textos;
}

std::string getEntryFocused(std::vector<TextView> entries)
{
    for(int i = 0; i < entries.size(); i++) {
        if(entries[i].isFocused())
            return entries[i].getText();
    }

    return "";
}

int main()
{
    FileSys f = FileSys();
    std::vector<TextView> partitionsNames = createTextViewsPartitions(f.partitions);
    std::vector<TextView> filesInPath = getTextViewsFiles(f.entriesInDir);

    RenderWindow x;
    TextView createFolderBtn = TextView("Create Directory",230,555);
    TextView createArchivoBtn = TextView("Create File",230,585);
    TextView copyBtn = TextView("Copy File/Dir",400,555);
    TextView deleteBtn = TextView("Remove File/Dir",400,585);
    TextView mvBtn = TextView("Move File/Dir",570,555);
    TextView lnHBtn = TextView("Create Hard Link",570,585);
    TextView lnSBtn = TextView("Create Soft Link",740,555);
    TextView returnBtn = TextView("<-Back",15,23);
    TextView forwardBtn = TextView("Forward->",75,23);
    x.createWindow(900,600,"Linux File Explorer");
    

    while(x.isOpen())
    {
        XEvent e;
        e = x.pollEvent(e);

        x.drawNavbar(Rect(0,0,900,35));
        x.drawSidebar(Rect(0,36,190,489));
        x.draw(Rect(0,525,900,74));
        x.draw(createFolderBtn);
        x.draw(createArchivoBtn);
        x.draw(deleteBtn);
        x.draw(copyBtn);
        x.drawNavbuttons(returnBtn);
        x.drawNavbuttons(forwardBtn);
        x.draw(mvBtn);
        x.draw(lnHBtn);
        x.draw(lnSBtn);

        for(int i = 0; i < partitionsNames.size(); i++) {
            x.drawPartitions(partitionsNames[i]);
        }

        for(int i = 0; i < filesInPath.size(); i++) {
            if(filesInPath[i].isFocused())
                x.draw(filesInPath[i].sayFocused);
            x.draw(filesInPath[i]);
        }
    }

    return 0;
}