#include "../include/Container.h"
#include "../include/General.h"
#include <iostream>
Container::Container(FormSetting* f_setting) {
    m_is_hover = false;
    form_setting = f_setting;
    m_is_visible = true;
    m_position = {0, 0};
}
bool Container::isHovered() const {
    return m_is_hover;
}
void Container::draw() {
    if (form_setting) {
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, form_setting->roundness, form_setting->segment,  form_setting->middle_color);
        for (auto& i:children) i->draw();
    } else std::cerr << "[FORM SETTING DOES NOT EXIST IN CONTAINER!]" << endl;
}
void Container::setPosition(const float& x, const float& y) {
    for (auto& i:children) {
        Vector2 pos = i->getPosition()-getPosition() + Vector2({x,y});
        i->setPosition(pos.x, pos.y);
    }
    Controller::setPosition(x, y);
}
void Container::reLocate(Controller* i) {
    i->setPosition(m_position.x, m_position.y);
}
void Container::pop(Controller* control) {
    for (int i =0; i<children.size(); i++) {
        if (control == children[i]) children.erase(children.begin() + i);
    }
}
void Container::push_back(Controller* i) {
    children.push_back(i);
    reLocate(i);
}
void Container::handle() {
    if (m_is_visible) {
        m_is_hover = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
        for (auto& i:children) i->handle();
    } else if (!form_setting) std::cerr << "[FORM SETTING DOES NOT EXIST IN CONTAINER!]" << endl;
}
void Container::setVisible(const bool& visible) {
    m_is_visible = visible;
}
Container::~Container() {

}