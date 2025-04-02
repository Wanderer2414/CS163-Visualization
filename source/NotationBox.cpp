#include "../include/NotationBox.h"
#include <sstream>
#include <string>

NotationBox::NotationBox(FormSetting* f_setting): 
        m_address(f_setting), 
        m_pos(f_setting),
        m_value(f_setting),
        m_index(f_setting) {
    form_setting = f_setting;
    m_address.setAlignText(Label::Middle);
    m_pos.setAlignText(Label::Left);
    m_value.setAlignText(Label::Left);
    m_index.setAlignText(Label::Left);

    main_text_setting = other_text_setting = *f_setting;
    other_text_setting.font_size/=1.3;

    m_address.text_setting = &main_text_setting;
    m_pos.text_setting = &other_text_setting;
    m_value.text_setting = &other_text_setting;
    m_index.text_setting = &other_text_setting;
    
    isVisible = false;
    setSize(250, 150);
    setPosition(0, 0);
}

void NotationBox::handle() {
    if (isVisible) {
        stringstream ss;
        ss << vertex;
        m_address.setText(ss.str());
        m_index.setText("Index: " + to_string(vertex->getIndex()));
        m_value.setText("Value: "+to_string(vertex->getValue()));
        ss.str("");
        ss << "X: " << int(vertex->getPosition().x) << ", Y: " << int(vertex->getPosition().y) << endl;
        m_pos.setText(ss.str());
        ss.clear();
    }
}
void NotationBox::draw() {
    if (isVisible) {
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, 0.1,form_setting->segment, form_setting->normal_color);
        DrawRectangleRounded({m_position.x+2, m_position.y+2, m_size.x-4, m_size.y-4}, 0.1,form_setting->segment, form_setting->hover_color);
        m_address.draw();
        m_value.draw();
        m_index.draw();
        m_pos.draw();
    }
}
void NotationBox::setPosition(const float& x, const float& y) {
    m_address.setPosition(x+10, y + 5);
    m_value.setPosition(x+10, m_address.getPosition().y + m_address.getSize().y + 5);
    m_index.setPosition(x+10, m_value.getPosition().y + m_value.getSize().y);
    m_pos.setPosition(x+10, m_index.getPosition().y + m_index.getSize().y + 15);

    Controller::setPosition(x, y);
}
void NotationBox::setSize(const float& width, const float& height) {
    m_address.setSize(width-20, m_address.text_setting->font_size);
    m_pos.setSize(width-20, m_pos.text_setting->font_size + 10);
    m_index.setSize(width-20, m_index.text_setting->font_size + 10);
    m_value.setSize(width-20, m_value.text_setting->font_size + 10);
    Controller::setSize(width, height);
}

void NotationBox::show() {
    isVisible = true;
}
void NotationBox::hide() {
    isVisible = false;
}