#include "MenuBox.h"
#include "General.h"

MenuBox::MenuBox(FormSetting*& f_setting, const std::vector<Vector2>& windowSizes): 
        form_setting(f_setting), 
        text_setting(*f_setting),
        sun(&LightTheme, &DarkTheme), 
        window_size(form_setting, form_setting),
        small_font_size(form_setting, form_setting),
        medium_font_size(form_setting, form_setting),
        font_size(form_setting, form_setting),

        window_size_label(&text_setting),
        font_size_label(&text_setting),
        medium_font_size_label(&text_setting),
        small_font_size_label(&text_setting),

        highlight_color_label1(&text_setting),
        highlight_color_label2(&text_setting),
        highlight_color_label3(&text_setting),

        button_color_label(&text_setting),
        text_color_label(&text_setting),

        color_pointer(form_setting),

        submit_button(form_setting, form_setting) {
    window_size_index = 0;
    m_position = {0, 0};
    children.push_back(&sun);
    children.push_back(&window_size);
    children.push_back(&font_size);
    children.push_back(&medium_font_size);
    children.push_back(&small_font_size);
    children.push_back(&window_size_label);
    children.push_back(&font_size_label);
    children.push_back(&medium_font_size_label);
    children.push_back(&small_font_size_label);

    children.push_back(&highlight_color_label1);
    children.push_back(&highlight_color_label2);
    children.push_back(&highlight_color_label3);

    children.push_back(&button_color_label);
    children.push_back(&text_color_label);

    children.push_back(&hightlight_color_button1);
    children.push_back(&hightlight_color_button2);
    children.push_back(&hightlight_color_button3);

    children.push_back(&button_color_button);
    children.push_back(&text_color_button);

    children.push_back(&color_pointer);

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

    highlight_color_label1.setPosition(TransX(10),TransY(280));
    highlight_color_label1.setSize(TransX(150), TransY(40));
    highlight_color_label1.setText("Highlight color 1: ");
    highlight_color_label1.setAlignText(Label::Left);

    highlight_color_label2.setPosition(TransX(10),TransY(330));
    highlight_color_label2.setSize(TransX(150), TransY(40));
    highlight_color_label2.setText("Highlight color 2: ");
    highlight_color_label2.setAlignText(Label::Left);

    highlight_color_label3.setPosition(TransX(10),TransY(380));
    highlight_color_label3.setSize(TransX(150), TransY(40));
    highlight_color_label3.setText("Highlight color 3: ");
    highlight_color_label3.setAlignText(Label::Left);

    button_color_label.setPosition(TransX(10),TransY(430));
    button_color_label.setSize(TransX(150), TransY(40));
    button_color_label.setText("Button color: ");
    button_color_label.setAlignText(Label::Left);

    text_color_label.setPosition(TransX(10),TransY(480));
    text_color_label.setSize(TransX(150), TransY(40));
    text_color_label.setText("Text color: ");
    text_color_label.setAlignText(Label::Left);

    window_size.setPosition(TransX(270), TransY(80));
    window_size.setSize(TransX(200), TransY(40));
    for (auto& size:windowSizes) window_size.push_back(MyBase::toString(size));

    font_size.setPosition(TransX(270), TransY(130));
    font_size.setSize(TransX(200), TransY(40));
    for (int i = 10; i< 40; i++) font_size.push_back(to_string(i));

    medium_font_size.setPosition(TransX(270), TransY(180));
    medium_font_size.setSize(TransX(200), TransY(40));
    for (int i = 10; i< 40; i++) medium_font_size.push_back(to_string(i));

    small_font_size.setPosition(TransX(270), TransY(230));
    small_font_size.setSize(TransX(200), TransY(40));
    for (int i = 10; i< 40; i++) small_font_size.push_back(to_string(i));

    hightlight_color_button1.setPosition(TransX(270), TransY(280));
    hightlight_color_button1.setSize(TransX(200), TransY(40));

    hightlight_color_button2.setPosition(TransX(270), TransY(330));
    hightlight_color_button2.setSize(TransX(200), TransY(40));

    hightlight_color_button3.setPosition(TransX(270), TransY(380));
    hightlight_color_button3.setSize(TransX(200), TransY(40));

    button_color_button.setPosition(TransX(270), TransY(430));
    button_color_button.setSize(TransX(200), TransY(40));

    text_color_button.setPosition(TransX(270), TransY(480));
    text_color_button.setSize(TransX(200), TransY(40));

    submit_button.setSize(TransX(200), TransY(50));
    submit_button.setPosition(TransX(270), TransY(530));
    submit_button.setText("Done");

    color_pointer.setSize(200, 150);
    color_pointer.setVisible(false);

    window_size.setSelection(0);
    text_setting.font_size = 30;
    is_size_changed = false;
    m_is_submit = false;
    color_pointer_index = -1;
    update();
}
bool MenuBox::isSubmit() {
    return m_is_submit;
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
    if (!mode) {
        update();
    }
    else if (mode == 1) {
        update();
    }
}
void MenuBox::setWindowSize(const int& index) {
    window_size.setSelection(index);
    window_size_index = index;
}
void MenuBox::update() {
    if (form_setting) {
        text_setting.color = form_setting->background_color;

        hightlight_color_button3.normal_color = form_setting->hightlight_color3;
        hightlight_color_button2.normal_color = form_setting->hightlight_color2;
        hightlight_color_button1.normal_color = form_setting->hightlight_color1;

        button_color_button.normal_color = form_setting->normal_color;
        text_color_button.normal_color = form_setting->color;

        small_font_size.setSelection(form_setting->small_font_size - 10);
        small_font_size.button_setting = form_setting;
        small_font_size.text_setting = form_setting;

        medium_font_size.setSelection(form_setting->medium_font_size - 10);
        medium_font_size.button_setting = form_setting;
        medium_font_size.text_setting = form_setting;

        font_size.setSelection(form_setting->font_size - 10);
        font_size.button_setting = form_setting;
        font_size.text_setting = form_setting;
        
        window_size.button_setting = form_setting;
        window_size.text_setting = form_setting;
        window_size.setSelection(window_size_index);
        for (auto i:children) i->update();
    }
}
void MenuBox::handle() {
    if (!m_is_visible) return;
    is_size_changed = false;
    VerticalOpen::handle();
    bool is_focus = false, is_hover = false;
    for (int i = 0; i<children.size(); i++) {
        if (!is_hover) children[i]->handle();
        if (children[i]->isFocus()) {
            if (i) swap(children[i], children[0]); 
            is_focus = true;
        }
        if (children[i]->isHovered()) {
            is_hover = true;
        }
    }
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    
    if (sun.getPercent() < 0.5 && form_setting!=&LightTheme) {
        form_setting = &LightTheme;
        update();
    }
    else if (sun.getPercent() >= 0.5 && form_setting!=&DarkTheme) {
        form_setting = &DarkTheme;
        update();
    }

    if (hightlight_color_button1.isPressed()) {
        color_pointer.setVisible(true);
        Vector2 pos = hightlight_color_button1.getPosition();
        pos.x -= color_pointer.getSize().x + 10;
        color_pointer.setPosition(pos.x, pos.y);
        color_pointer.setColor(hightlight_color_button1.normal_color);
        color_pointer_index = 0;
    }
    else if (hightlight_color_button2.isPressed()) {
        color_pointer.setVisible(true);
        Vector2 pos = hightlight_color_button2.getPosition();
        pos.x -= color_pointer.getSize().x + 10;
        color_pointer.setPosition(pos.x, pos.y);
        color_pointer.setColor(hightlight_color_button2.normal_color);
        color_pointer_index = 1;
    }
    else  if (hightlight_color_button3.isPressed()) {
        color_pointer.setVisible(true);
        Vector2 pos = hightlight_color_button3.getPosition();
        pos.x -= color_pointer.getSize().x + 10;
        color_pointer.setPosition(pos.x, pos.y);
        color_pointer.setColor(hightlight_color_button3.normal_color);
        color_pointer_index = 2;
    }
    else  if (button_color_button.isPressed()) {
        color_pointer.setVisible(true);
        Vector2 pos = button_color_button.getPosition();
        pos.x -= color_pointer.getSize().x + 10;
        color_pointer.setPosition(pos.x, pos.y);
        color_pointer.setColor(button_color_button.normal_color);
        color_pointer_index = 3;
    }
    else  if (text_color_button.isPressed()) {
        color_pointer.setVisible(true);
        Vector2 pos = text_color_button.getPosition();
        pos.x -= color_pointer.getSize().x + 10;
        color_pointer.setPosition(pos.x, pos.y);
        color_pointer.setColor(text_color_button.normal_color);
        color_pointer_index = 4;
    }
    if (!color_pointer.isFocus() && color_pointer.isVisible()) {
        color_pointer.setVisible(false);
        switch (color_pointer_index) {
            case 0: hightlight_color_button1.normal_color = color_pointer.getColor(); break;
            case 1: hightlight_color_button2.normal_color = color_pointer.getColor(); break;
            case 2: hightlight_color_button3.normal_color = color_pointer.getColor(); break;
            case 3: button_color_button.normal_color      = color_pointer.getColor(); break;
            case 4: text_color_button.normal_color        = color_pointer.getColor(); break;
        }
    }
    m_is_submit = false;
    if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || submit_button.isPressed()) {
        if (submit_button.isPressed()){ 
            if (window_size_index != window_size.GetSelection()) is_size_changed = true;

            form_setting->font_size = font_size.GetSelection() + 10;
            form_setting->medium_font_size = medium_font_size.GetSelection() + 10;
            form_setting->small_font_size = small_font_size.GetSelection() + 10;

            form_setting->hightlight_color1 = hightlight_color_button1.normal_color;
            form_setting->hightlight_color2 = hightlight_color_button2.normal_color;
            form_setting->hightlight_color3 = hightlight_color_button3.normal_color;

            form_setting->color = text_color_button.normal_color;
            form_setting->normal_color = button_color_button.normal_color;

            m_is_submit = true;
        }
        VerticalOpen::close();
    }
}
void MenuBox::open() {
    VerticalOpen::open();
    update();
}
void MenuBox::draw() {
    if (m_is_visible) {
        Color color = LightTheme.background_color*sun.getPercent() + DarkTheme.background_color*(1-sun.getPercent());
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, form_setting->roundness, form_setting->segment, color);
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (int i = children.size()-1; i>=0; i--) children[i]->draw();
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