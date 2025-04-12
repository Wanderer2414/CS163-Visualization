#include "../include/Menu.h"
#include "../include/General.h"
#include "../include/IncludePath.h"
#include <utility>

Menu::Menu(FormSetting f_setting, const Vector2& windowSize) :
    form_setting(f_setting),
    m_windowSize(windowSize),
    return_value(-1)
{

    children.push_back(&BSTForm);
    children.push_back(&GraphForm);
    children.push_back(&HashTableForm);
    children.push_back(&Back);
    children.push_back(&SLLForm);
    children.push_back(&MenuDSA);

    BSTForm.setSize(m_windowSize.x/2-10, m_windowSize.y/2-70);
    BSTForm.setButtonStage(0, AVL0, AVL_hovered);    
    BSTForm.setPosition(-BSTForm.getSize().x-100, 100);
    BSTForm.add_vertex({-BSTForm.getSize().x-100, 100});
    BSTForm.add_vertex({0, 100});
    BSTForm.moveNext();

    GraphForm.setSize(m_windowSize.x/2-10, m_windowSize.y/2-70);
    GraphForm.setButtonStage(0, Graph0, Graph2_hovered);
    GraphForm.setPosition(m_windowSize.x+100, 100);
    GraphForm.add_vertex({m_windowSize.x+100, 100});
    GraphForm.add_vertex({m_windowSize.x/2+10, 100});
    GraphForm.moveNext();

    HashTableForm.setSize(m_windowSize.x/2-10, m_windowSize.y/2-70);
    HashTableForm.setButtonStage(0, HT0, HT_hovered);
    HashTableForm.setPosition(-HashTableForm.getSize().x*2, m_windowSize.y/2+50);
    HashTableForm.add_vertex({-HashTableForm.getSize().x*2, HashTableForm.getPosition().y});
    HashTableForm.add_vertex({0, HashTableForm.getPosition().y});
    HashTableForm.moveNext();

    SLLForm.setSize(m_windowSize.x/2-10, m_windowSize.y/2-70);
    SLLForm.setButtonStage(0, SLL0, SLL_hovered);
    SLLForm.setPosition(m_windowSize.x*2, m_windowSize.y/2+50);
    SLLForm.add_vertex({m_windowSize.x*2, SLLForm.getPosition().y});
    SLLForm.add_vertex({m_windowSize.x/2+10, SLLForm.getPosition().y});
    SLLForm.moveNext();
    
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
        if (children[i]->isFocus() && i) {
            swap(children[i], children[0]);
        };
    }
    if (Back.isPressed()) {
        return_value = 0;
        Back.moveNext();
        BSTForm.moveNext();
        GraphForm.moveNext();
        HashTableForm.moveNext();
        SLLForm.moveNext();
        MenuDSA.moveNext();
    }
    if (zoom.getProgress()==1) {
        if (BSTForm.isPressed()) {
            return_value = 3;
            BSTForm.skip();
            zoom.host = &BSTForm;
            zoom.start();
        }
        if (GraphForm.isPressed()) {
            return_value = 4;
            GraphForm.skip();
            zoom.host = &GraphForm;
            zoom.start();
        }
        if (HashTableForm.isPressed()) {
            return_value = 5;
            HashTableForm.skip();
            zoom.host = &HashTableForm;
            zoom.start();
        }
        if (SLLForm.isPressed()) {
            return_value = 6;
            SLLForm.skip();
            zoom.host = &SLLForm;
            zoom.start();
        }
    }
}
void Menu::draw() {
    for (int i = children.size()-1; i>=0; i--) children[i]->draw();
    zoom.draw();
}