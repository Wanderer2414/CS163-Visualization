#pragma once
#include "Button.h"
#include <raylib.h>
#include <string>
class TextureButton: public Button {
public:
    TextureButton();
    virtual void    draw()                                              override,
                    handle()                                            override,
                    setPosition(const float& x, const float& y)         override,
                    setSize(const float& width, const float& height)    override,
                    setTexture(Texture2D* texture);
    ~TextureButton();
private:
    Texture2D       *m_texture;
};