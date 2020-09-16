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
    TextEdit fName = TextEdit(10,535,180);
    TextView createFolderBtn = TextView("Create Directory",230,555);
    TextView createFileBtn = TextView("Create File",230,585);
    TextView copyBtn = TextView("Copy File/Dir",400,555);
    TextView deleteBtn = TextView("Remove File/Dir",400,585);
    TextView mvBtn = TextView("Move File/Dir",570,555);
    TextView lnHBtn = TextView("Create Hard Link",570,585);
    TextView lnSBtn = TextView("Create Soft Link",740,555);
    TextView returnBtn = TextView("<-Back",15,23);
    TextView forwardBtn = TextView("Forward->",75,23);
    TextView statusMsg = TextView("",300,23);

    bool foundClicked = false;// esta variable me dice si ya encontro lo que fue clickeado
    bool usingMove = false;//booleano para saber cuando di click al mvBtn
    struct entry entryMove;// esta variable es la que uso para guardar la data del entry a mover.

    x.createWindow(900,600,"Linux File Explorer");
    
    while(x.isOpen())
    {
        XEvent e;
        e = x.pollEvent(e);
        fName.handleEvent(e,x.dpy);

        switch (e.type)
        {
            case (ButtonPress):
            {
                statusMsg.setText("");
                struct vector2 pos = x.getPointerPos();
                if(!foundClicked)
                {
                    if(createFolderBtn.isClicked(pos.x,pos.y))
                    {
                        if(fName.getText().length() < 1)
                        {
                            statusMsg.setText("Folder name is empty");
                        }
                        else
                        {
                            if(f.createFolder(fName.getText()))
                            {
                                statusMsg.setText("Folder created");
                                fName.setText("");
                                f.updateActualDirEntries();
                                filesInPath = getTextViewsFiles(f.entriesInDir);
                            }
                            else
                            {
                                statusMsg.setText("Unable to create folder");
                            }
                            
                        }
                        
                        foundClicked = true;
                    } else if (createFileBtn.isClicked(pos.x, pos.y))
                    {
                        if(fName.getText().length() < 1)
                        {
                            statusMsg.setText("File name is empty");
                        }
                        else
                        {
                            if(f.createFile(fName.getText()))
                            {
                                statusMsg.setText("File created");
                                fName.setText("");
                                f.updateActualDirEntries();
                                filesInPath = getTextViewsFiles(f.entriesInDir);
                            }
                            else
                            {
                                statusMsg.setText("Unable to create file");
                            }
                        }
                        
                        foundClicked = true;
                    } else if(returnBtn.isClicked(pos.x,pos.y))
                    {
                        if(f.actualDir.name == "/")
                        {

                        }
                        else
                        {
                            f.changePartition(f.actualDir.parentPath);
                            filesInPath = getTextViewsFiles(f.entriesInDir);
                        }
                        foundClicked = true;
                    }
                }

                for(int i = 0; i < partitionsNames.size(); i++)
                {
                    if(partitionsNames[i].isDoubleClicked(pos.x,pos.y))
                    {
                        f.changePartition(partitionsNames[i].getText());
                        filesInPath = getTextViewsFiles(f.entriesInDir);
                        foundClicked = true;
                        break;
                    }
                }

                if(!foundClicked)
                {
                    for(int i = 0; i < filesInPath.size(); i++)
                    {
                        if(filesInPath[i].isDoubleClicked(pos.x,pos.y))
                        {
                            if(f.entriesInDir[i].isDir)
                            {
                                f.changeDir(filesInPath[i].getText());
                                filesInPath = getTextViewsFiles(f.entriesInDir);
                            }
                            else
                            {
                                f.openFile(i);
                            }
                            foundClicked = true;
                            break;
                        }
                    }   
                }
                fName.isClicked(pos.x, pos.y);
                break;
            }
            default:
                break;
        }
        
        foundClicked = false;

        x.clear(x.WHITECOLOR);
        x.drawNavbar(Rect(0,0,900,35));
        x.drawSidebar(Rect(0,36,190,489));
        x.draw(Rect(0,525,900,74));
        x.draw(fName);
        x.draw(createFolderBtn);
        x.draw(createFileBtn);
        x.draw(deleteBtn);
        x.draw(copyBtn);
        x.drawNavbuttons(returnBtn);
        x.drawNavbuttons(forwardBtn);
        x.drawNavbuttons(statusMsg);
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