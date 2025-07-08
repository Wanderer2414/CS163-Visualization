#include "Container.h"
#include "General.h"

Container::Container(FormSetting* f_setting) {
    m_is_hover = false;
    form_setting = f_setting;
    m_is_visible = true;
    m_position = {0, 0};
}
bool Container::isHovered() const {
    return m_is_hover;
}
bool Container::isFocus() const {
    return m_is_focus;
}
void Container::draw() {
    if (form_setting) {
        if (m_is_visible) {
            BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
            DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, form_setting->roundness, form_setting->segment,  form_setting->middle_color);
            for (auto& i:children) i->draw();
            EndScissorMode();
        }
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
    i->setPosition(m_position.x+i->getPosition().x, m_position.y+i->getPosition().y);
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
    m_is_focus = false;
    if (m_is_visible && form_setting) {
        m_is_hover = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
        for (auto& i:children) {
            i->handle();
            m_is_focus = m_is_focus || i->isFocus();
        }
    } else if (!form_setting) std::cerr << "[FORM SETTING DOES NOT EXIST IN CONTAINER!]" << endl;
}
void Container::setVisible(const bool& visible) {
    m_is_visible = visible;
}
Container::~Container() {

}