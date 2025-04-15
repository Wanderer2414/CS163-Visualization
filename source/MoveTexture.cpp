#include "../include/MoveTexture.h"

MoveTexture::MoveTexture() {
        
}
void MoveTexture::setPosition(const float& x, const float& y) {
    TextureButton::setPosition(x, y);
}
void MoveTexture::handle() {
    Move::handle();
    TextureButton::handle();
}
Vector2 MoveTexture::getPosition() const {
    return TextureButton::getPosition();
}