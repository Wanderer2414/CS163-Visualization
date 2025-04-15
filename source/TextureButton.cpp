#include "../include/TextureButton.h"

TextureButton::TextureButton() {
    source_pointer = -1;
    m_sources.clear();
    m_sources_hover.clear();
    hover_remain_time = 0;
}
int TextureButton::getStage() const {
    return source_pointer;
}
void TextureButton::Hover() {
    hover_remain_time = 10;
}
void TextureButton::setSize(const float& x, const float& y) {
    Controller::setSize(x, y);
    for (int i = 0; i < m_sources.size(); i++) {
        m_sources[i].width = x;
        m_sources[i].height = y;
        m_sources_hover[i].width = x;
        m_sources_hover[i].height = y;
    }
}
void TextureButton::handle() {
    Button::handle();
    if (hover_remain_time) m_is_hovered = hover_remain_time--;
}
void TextureButton::back() {
    source_pointer--;
    if (source_pointer < 0) source_pointer = 0;
}
void TextureButton::next() {
    source_pointer++;
    if (source_pointer == m_sources.size()) source_pointer = 0;
}
void TextureButton::go(const int& index) {
    if (index >= 0 && index < m_sources.size()) source_pointer = index;
}
void TextureButton::draw() {
    if (source_pointer != -1) {
        if (m_is_hovered) {
            DrawTexture(m_sources_hover[source_pointer], m_position.x, m_position.y, WHITE);
        }
        else {
            DrawTexture(m_sources[source_pointer], m_position.x, m_position.y, WHITE);
        }
    }
}
void TextureButton::setButtonStage(const int& index, const string& source, const string& hover_source) {
    if (index >= m_sources.size()) {
        m_sources.push_back(LoadTexture(source.c_str()));
        m_sources_hover.push_back(LoadTexture(hover_source.c_str()));
        m_sources.back().width = m_size.x;
        m_sources.back().height = m_size.y;
        m_sources_hover.back().width = m_size.x;
        m_sources_hover.back().height = m_size.y;
    }
    else if (index < 0) setButtonStage(0, source, hover_source);
    else {
        UnloadTexture(m_sources[index]);
        UnloadTexture(m_sources_hover[index]);
        m_sources[index] = LoadTexture(source.c_str());
        m_sources_hover[index] = LoadTexture(source.c_str());
        m_sources[index].width = m_size.x;
        m_sources[index].height = m_size.y;
        m_sources_hover[index].width = m_size.x;
        m_sources_hover[index].height = m_size.y;
    }
    if (source_pointer == -1) source_pointer = 0;
}
TextureButton::~TextureButton() {
    for (int i = 0; i<m_sources.size(); i++) {
        UnloadTexture(m_sources[i]);
        UnloadTexture(m_sources_hover[i]);
    }
}