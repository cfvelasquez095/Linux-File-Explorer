#include "../headers/TextEdit.h"

TextEdit::TextEdit(int x, int y, int width)
{
    textBox = Rect(x,y,width,50);
    text = "";
    sayFocused = Rect(x-30,y,30,1);
}

bool TextEdit::isClicked(int posX, int posY)
{
    focused = false;
    struct vector2 position = textBox.getPosition();
    struct vector2 attrs = textBox.getAttributes();
    if(posX > position.x && posX < (position.x + attrs.x))
    {
        if(posY > position.y && posY < (position.y + attrs.y))
        {
            focused = true;
            return true;
        }
    }
    return false;
}

void TextEdit::setText(std::string txt)
{   
    text = txt;
}

void TextEdit::handleEvent(XEvent e, Display *dpy)
{
    if(focused)
    {
        if(e.type == KeyPress)
        {
            KeySym id = XkbKeycodeToKeysym(dpy,e.xkey.keycode,0,
                e.xkey.state & ShiftMask ? 1 : 0);
            char stringData[1];
            XComposeStatus x;
            XLookupString(&e.xkey,stringData,1,&id,&x);
            if(id == 65288)
            {
                handleBackspace();
            }
            else
            {
                setText(getText() + stringData);
                
            }
            

        }
    }
}

void TextEdit::handleBackspace()
{
    if(text.length() > 0)
    {
        std::string textACt = getText();
        setText(textACt.substr(0,textACt.size() - 1));
    }
}

std::string TextEdit::getText()
{
    return text;
}