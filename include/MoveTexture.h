#ifndef MOVETEXTURE_H
#define MOVETEXTURE_H

#include "Move.h"
#include "TextureButton.h"

class MoveTexture : public TextureButton, public Move {
public:
    MoveTexture();
    virtual void    setPosition(const float& x, const float& y) override,
                    handle()    override;
    virtual Vector2 getPosition() const override;
};

#endif