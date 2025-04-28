#include "../include/Menu.h"
#include "../include/General.h"
#include "../include/IncludePath.h"

Menu::Menu(FormSetting f_setting, const Vector2& windowSize) :
    form_setting(f_setting),
    m_windowSize(windowSize),
    return_value(-1)
{
    form_button.resize(form_name.size(), MoveButton(&form_setting, &form_setting));

    children.push_back(&Back);
    children.push_back(&MenuDSA);
    for (auto& i:form_button) children.push_back(&i);

    float old_y = 100;
    for (int i = 0; i<form_button.size(); i++) {
        if (i%2) {
            form_button[i].setSize(m_windowSize.x-20, 40);
            form_button[i].setPosition(-form_button[i].getSize().x*(i+1)-100, old_y);
            form_button[i].add_vertex({form_button[i].getSize().x, old_y});
            form_button[i].add_vertex({0, old_y});
            form_button[i].setText(form_name[i]);
            form_button[i].moveNext();
        }
        else {
            form_button[i].setSize(m_windowSize.x-20, 40);
            form_button[i].setPosition(m_windowSize.x+100, old_y);
            form_button[i].add_vertex({m_windowSize.x*(i+1)+100, old_y});
            form_button[i].add_vertex({m_windowSize.x - form_button[i].getSize().x, old_y});
            form_button[i].setText(form_name[i]);
            form_button[i].moveNext();
        }
        old_y+=form_button[i].getSize().y + 10;
    }

    Back.setButtonStage(0, form_setting.back_normal, form_setting.back_hovered);
    Back.setSize(40, 40);
    Back.setPosition(-100, 10);
    Back.add_vertex({-100, 10});
    Back.add_vertex({10, 10});
    Back.moveNext();

    MenuDSA.setButtonStage(0, form_setting.TitleMenu, form_setting.TitleMenu);
    MenuDSA.setSize(600, 60);
    MenuDSA.setPosition( m_windowSize.x / 2 - 300 , -100);
    MenuDSA.add_vertex({MenuDSA.getPosition().x, -100});
    MenuDSA.add_vertex({MenuDSA.getPosition().x, 10});
    MenuDSA.moveNext();

    zoom.setPosition(m_windowSize.x/2, m_windowSize.y/2);
    zoom.setSize(m_windowSize.x*10, m_windowSize.y*10);
    zoom.color = form_setting.reverse_color;
}

int Menu::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
        ClearBackground(form_setting.background_color);
        if (MenuDSA.getProgress()<0.05) return return_value;
        draw();
        EndDrawing();
        if ((zoom.getProgress() == 1 || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && return_value > 0) 
            return return_value;
    };
    return 0;
};
void Menu::handle() {
    zoom.handle();
    for (int i = 0; i<children.size() ;i++) {
        children[i]->handle();
        if (zoom.host == children[i] && i) {
            swap(children[i],children[0]);
        }
    }
    if (Back.isPressed()) {
        return_value = 0;
        Back.moveNext();
        for (auto& i:form_button) i.moveNext();
        MenuDSA.moveNext();
    }
    if (zoom.getProgress()==1) {
        for (int i = 0; i<form_button.size(); i++) {
            if (form_button[i].isPressed()) {
                return_value = i+3;
                form_button[i].skip();
                zoom.host = &form_button[i];
                zoom.start();
            }
        }
    }
}
void Menu::draw() {
    for (int i = children.size()-1; i>=0; i--) {
        children[i]->draw();
    }
    zoom.draw();
}