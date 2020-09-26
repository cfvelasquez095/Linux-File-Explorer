# Linux File Explorer

A small linux file explorer created in C++ using the X Window System (X11). With this file explorer you will be able to view the contents of your root partition '/', navigate through all of your directories, open files, create, copy, move and delete files and folders as well as creating links and hard links.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Installing

Linux
```
cd sources/
g++ main.cpp FileSys.cpp Rect.cpp TextEdit.cpp TextView.cpp Utilities.cpp Window.cpp -o main -L/usr/X11/lib -lX11 -lstdc++
./main
```