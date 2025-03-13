#pragma once
#include "Console.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#define main_button_width 400
#define main_button_height 60
#define button_count 3
class MenuStart {
public:
    MenuStart(const Vector2& windowSize);
    virtual int     run();
    virtual void    init(),
        loadAsset(),
        handle(),
        draw(),
        unloadAsset(),
        close();
private:
    TextButton      Start, Setting, Exit;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};