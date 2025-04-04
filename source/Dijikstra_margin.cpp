#include "../include/Dijikstra_margin.h"

Dijikstra_Margin::Dijikstra_Margin(Vertex* vertex) {
    m_value = numeric_limits<float>::max();
    host = vertex;
}
float Dijikstra_Margin::getValue() const {
    return m_value;
}
void Dijikstra_Margin::setValue(const float& value) {
    m_value = value;
}
void Dijikstra_Margin::draw() {
    Vector2 pos = host->getCenter();
    pos.x += host->getSize().x/2;
    FormSetting* f = host->form_setting;
    pos.y -= f->font_size/1.5 + host->getSize().y/2;
    if (m_value < numeric_limits<float>::max()) DrawTextEx(f->font, to_string(int(m_value)).c_str(), pos, f->font_size, f->spacing, host->getColor());
    else {
        pos.x -= 5;
        DrawRing(pos, 3,5, 0, 360, 30, host->getColor());
        pos.x += 8;
        DrawRing(pos, 3,5, 0, 360, 30, host->getColor());
    }
}