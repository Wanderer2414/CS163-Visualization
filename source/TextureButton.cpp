#include "../include/TextureButton.h"
#include "../raylib/raylib.h"
TextureButton::TextureButton(const std::string& texture) {
    m_texture = LoadTexture(texture.c_str());
}
void TextureButton::draw() {
    if (m_is_hovered)
        DrawTextureEx(m_texture, m_position, m_rotate, m_scale, m_hover_color);
    else DrawTextureEx(m_texture, m_position, m_rotate, m_scale, m_normal_color);
}
void TextureButton::setSize(const float& width, const float& height) {
    m_size = {width, height};
    m_texture.width = width;
    m_texture.height = height;
}
void TextureButton::setTexture(const std::string& texture) {
    UnloadTexture(m_texture);
    m_texture = LoadTexture(texture.c_str());
}
TextureButton::~TextureButton() {
    UnloadTexture(m_texture);
}