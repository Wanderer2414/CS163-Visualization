#ifndef TEXTUREBUTTON_H
#define TEXTUREBUTTON_H

#include "Button.h"
#include <cmath>
#include "../raylib/raylib.h"
#include <string>
class TextureButton: public Button {
public:
    TextureButton(const std::string& texture);
    virtual void    draw()                                              override,
                    setSize(const float& width, const float& height)    override,
                    setTexture(const std::string& texture);
    ~TextureButton();
private:
    float           m_rotate,
                    m_scale;
    Texture2D       m_texture;
};

#endif //TEXTUREBUTTON_H