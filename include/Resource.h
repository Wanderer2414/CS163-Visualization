#ifndef RESOURCE_H
#define RESOURCE_H

#include "../raylib/raylib.h"
#include "Global.h"

class Theme {
    public:
    void change();

    private:
    Color BACKGROUND;
    Color MENUBUTTON;
    Color HOVERMENU;
    Color BUTTON;
    Color HOVERBUTTON;
    Color HIGHLIGHTTEXT;
    Color HIGHLIGHTNODE;
    Color COLORNODE;
    Color COLORLINE;
    Color COLORPROGRESSBAR;
    Color WEIGHT;
    bool isDarkMode = true;

};

#endif //RESOURCE_H