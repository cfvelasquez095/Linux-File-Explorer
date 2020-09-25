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
    TextView movMsg = TextView("",360,23);
    TextView statusMsg = TextView("",400,23);

    bool foundClicked = false;
    bool usingCopy = false;
    bool usingMove = false;
    struct entry entryMove;

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
                    } else if(copyBtn.isClicked(pos.x,pos.y))
                    {
                        if(usingCopy)
                        {
                            if(f.copyFileFolder(entryMove.path+"/"+entryMove.name,f.actualDir.path+"/"+"copy of "+entryMove.name))
                            {
                                statusMsg.setText("Copied File/Dir");
                                f.updateActualDirEntries();
                                filesInPath = getTextViewsFiles(f.entriesInDir);
                            }
                            else
                            {
                                statusMsg.setText("Unable to copy File/Dir");
                            }
                            copyBtn.setText("Copy File/Dir");
                            movMsg.setText("");
                            usingCopy = false;
                        }
                        else
                        {
                            std::string nameEntry = getEntryFocused(filesInPath);
                            if(nameEntry.length() > 0)
                            {
                                usingCopy = true;
                                entryMove = f.getEntryByName(nameEntry);
                                copyBtn.setText("Paste File/Dir here");
                                movMsg.setText("cp: "+nameEntry);
                            }
                            else
                            {
                                statusMsg.setText("No File/Dir selected");
                            }   
                        }
                        foundClicked = true;
                        // std::string nameEntry = getEntryFocused(filesInPath);
                        // if(nameEntry.length() > 0)
                        // {
                        //     if(fName.getText().length() < 1)
                        //     {
                        //         statusMsg.setText("Name for copy is required");
                        //     }
                        //     else
                        //     {
                        //         if(f.copyFileFolder(nameEntry,fName.getText()))
                        //         {
                        //             statusMsg.setText("File/Dir Copied");
                        //             fName.setText("");
                        //             f.updateActualDirEntries();
                        //             filesInPath = getTextViewsFiles(f.entriesInDir);
                        //         }
                        //         else
                        //         {
                        //             statusMsg.setText("Unable to copy File/Dir");
                        //         }
                                
                        //     }
                            
                        // }
                        // else
                        // {
                        //     statusMsg.setText("No File/Dir has been selected");
                        // }
                        // foundClicked = true;   
                    } else if(deleteBtn.isClicked(pos.x,pos.y))
                    {
                        std::string nameEntry = getEntryFocused(filesInPath);
                        if(nameEntry.length() > 0)
                        {
                            if(f.deleteFileFolder(nameEntry))
                            {
                                statusMsg.setText("Deleted File/Dir");
                                f.updateActualDirEntries();
                                filesInPath = getTextViewsFiles(f.entriesInDir);
                            }
                            else
                            {
                                statusMsg.setText("Unable to delete File/Dir");
                            }
                        }
                        else
                        {
                            statusMsg.setText("No File/Dir has been selected");
                        }
                        foundClicked = true;
                    } else if(mvBtn.isClicked(pos.x,pos.y))
                    {
                        if(usingMove)
                        {
                            if(f.moveFileFolder(entryMove.path+"/"+entryMove.name,f.actualDir.path+"/"+entryMove.name))
                            {
                                statusMsg.setText("Moved File/Dir");
                                f.updateActualDirEntries();
                                filesInPath = getTextViewsFiles(f.entriesInDir);
                            }
                            else
                            {
                                statusMsg.setText("Unable to move File/Dir");
                            }
                            mvBtn.setText("Move File/Dir");
                            movMsg.setText("");
                            usingMove = false;
                        }
                        else
                        {
                            std::string nameEntry = getEntryFocused(filesInPath);
                            if(nameEntry.length() > 0)
                            {
                                usingMove = true;
                                entryMove = f.getEntryByName(nameEntry);
                                std::cout<<entryMove.path<<std::endl;
                                mvBtn.setText("Move File/Dir here");
                                movMsg.setText("mv: "+nameEntry);
                            }
                            else
                            {
                                statusMsg.setText("No File/Dir selected");
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
        x.drawNavbuttons(movMsg);
        x.draw(mvBtn);
        x.draw(lnHBtn);
        x.draw(lnSBtn);  
    }

    return 0;
}