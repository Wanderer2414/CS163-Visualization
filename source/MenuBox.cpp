#include "../include/MenuBox.h"
#include "../include/General.h"

MenuBox::MenuBox(FormSetting& f_setting): 
        form_setting(f_setting), 
        sun(&LightTheme, &DarkTheme), 
        window_size(&form_setting, &form_setting),
        window_size_label(&form_setting),
        font_size_label(&form_setting),
        medium_font_size_label(&form_setting),
        small_font_size_label(&form_setting),
        submit_button(&form_setting, &form_setting) {
    window_size_index = 0;
    m_position = {0, 0};
    children.push_back(&sun);
    children.push_back(&window_size);
    children.push_back(&window_size_label);
    children.push_back(&font_size_label);
    children.push_back(&medium_font_size_label);
    children.push_back(&small_font_size_label);
    children.push_back(&submit_button);

    sun.setPosition(TransX(270), TransY(20));
    sun.setSize(TransX(200), TransY(50));

    window_size_label.setPosition(TransX(10),TransY(80));
    window_size_label.setSize(TransX(150), TransY(40));
    window_size_label.setText("Resolution: ");
    window_size_label.setAlignText(Label::Left);

    font_size_label.setPosition(TransX(10),TransY(130));
    font_size_label.setSize(TransX(150), TransY(40));
    font_size_label.setText("Font size: ");
    font_size_label.setAlignText(Label::Left);

    medium_font_size_label.setPosition(TransX(10),TransY(180));
    medium_font_size_label.setSize(TransX(150), TransY(40));
    medium_font_size_label.setText("Medium font size: ");
    medium_font_size_label.setAlignText(Label::Left);

    small_font_size_label.setPosition(TransX(10),TransY(230));
    small_font_size_label.setSize(TransX(150), TransY(40));
    small_font_size_label.setText("Small font size: ");
    small_font_size_label.setAlignText(Label::Left);

    window_size.setPosition(TransX(270), TransY(80));
    window_size.setSize(TransX(200), TransY(40));
    window_size.push_back("1366x768");
    window_size.push_back("1820x980");
    window_size.push_back("1024x600");
    window_size.setSelection(window_size_index);

    submit_button.setSize(TransX(210), TransY(50));
    submit_button.setPosition(TransX(280), TransY(540));
    submit_button.setText("Done");

    window_size.setSelection(0);
    is_size_changed = false;
}
bool MenuBox::isHovered() const {
    return m_is_hovered && m_is_visible;
}
bool MenuBox::isSizeChanged() const {
    return is_size_changed;
}
int MenuBox::getMode() const {
    return round(sun.getPercent());
}
void MenuBox::setMode(const int& mode) {
    sun.setMode(mode);
}
void MenuBox::setWindowSize(const int& index) {
    window_size.setSelection(index);
    window_size_index = index;
}
void MenuBox::handle() {
    if (!m_is_visible) return;
    is_size_changed = false;
    VerticalOpen::handle();
    for (auto& i:children) i->handle();
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    if (sun.getPercent() < 0.3) {
        window_size_label.text_setting = &DarkTheme;
        font_size_label.text_setting = &DarkTheme;
        medium_font_size_label.text_setting = &DarkTheme;
        small_font_size_label.text_setting = &DarkTheme;
    }
    else if (sun.getPercent() > 0.7) {
        window_size_label.text_setting = &LightTheme;
        font_size_label.text_setting = &LightTheme;
        medium_font_size_label.text_setting = &LightTheme;
        small_font_size_label.text_setting = &LightTheme;
    }
    if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || submit_button.isPressed()) {
        if (submit_button.isPressed()) if (window_size_index != window_size.GetSelection()) is_size_changed = true;
        VerticalOpen::close();
    }
}
void MenuBox::draw() {
    if (m_is_visible) {
        Color color = LightTheme.background_color*sun.getPercent() + DarkTheme.background_color*(1-sun.getPercent());
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, form_setting.roundness, form_setting.segment, color);
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (auto& i:children) i->draw();
        EndScissorMode();
    }
}
void MenuBox::setVisible(const bool& visible) {
    m_is_visible = visible;
} 
void MenuBox::setPosition(const float& x, const float& y) {
    for (auto& i:children) {
        Vector2 tmp = i->getPosition() - m_position + Vector2({x,y});
        i->setPosition(tmp.x, tmp.y);
    }
    Controller::setPosition(x, y);
}
void MenuBox::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
}
int MenuBox::getWindowSizeIndex() {
    return window_size.GetSelection();
}
Vector2 MenuBox::getSize() const {
    return Controller::getSize();
}
Vector2 MenuBox::getPosition() const {
    return Controller::getPosition();
}
MenuBox::~MenuBox() {

}