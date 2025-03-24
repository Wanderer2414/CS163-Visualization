#include "../include/Menu.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/IncludePath.h"
#include <cmath>
#include <string>

Menu::Menu(FormSetting f_setting, const Vector2& windowSize) :
    form_setting(f_setting),
    m_windowSize(windowSize),
    BSTForm(&form_setting, &form_setting),
    GraphForm(&form_setting, &form_setting),
    HashTableForm(&form_setting, &form_setting),
    SLLForm(&form_setting,&form_setting)
{

    children.push_back(&BSTForm);
    children.push_back(&GraphForm);
    children.push_back(&HashTableForm);
    children.push_back(&SLLForm);

    BSTForm.setSize(main_button_width, main_button_height);
    BSTForm.setText("BST");

    GraphForm.setSize(main_button_width, main_button_height);
    GraphForm.setText("Graph");

    HashTableForm.setSize(main_button_width, main_button_height);
    HashTableForm.setText("HashTable");

    SLLForm.setSize(main_button_width, main_button_height);
    SLLForm.setText("Singly Linked List");
    
    Back.setPosition(10, 10);
    Back.setButtonStage(0, back_normal, back_hovered);
    Back.setSize(30, 30);
    Back.setSize(40, 40);

    MenuDSA.setPosition( m_windowSize.x / 2 - 200 , 30);
    MenuDSA.setSize(400, 50);
    MenuDSA.setButtonStage(0, TitleMenu, TitleMenu);

    Vector2 center = m_windowSize / 2;
    int cols = 2;
    int rows = (children.size() + cols - 1) / cols;
    float spacing_x = main_button_width + 50;
    float spacing_y = main_button_height + 50;
    float total_width = cols * spacing_x - 50;
    float total_height = rows * spacing_y - 50;
    // Corrected origin calculation
    Vector2 origin = {
        center.x - total_width / 2, center.y - total_height / 2
    };

    for (int i = 0; i < children.size(); i++) {
        int row = i / cols;
        int col = i % cols;
        children[i]->setPosition(origin.x + col * spacing_x, origin.y + row * spacing_y);
    }
}

int Menu::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
        ClearBackground(form_setting.background_color);

        draw();
        EndDrawing();
        if (Back.isPressed()) return 0;
        if (BSTForm.isPressed()) return 3;
        if (GraphForm.isPressed()) return 4;
        if (HashTableForm.isPressed()) return 5;
        if (SLLForm.isPressed()) return 6;
    };
    return 0;
};
void Menu::handle() {
    for (auto i : children) i->handle();
    Back.handle();
}
void Menu::draw() {
    for (auto i : children) i->draw();
    Back.draw();
}