#include "../include/Menu.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/IncludePath.h"
#include <cmath>
#include <string>

Menu::Menu(const Vector2& windowSize) :
    m_windowSize(windowSize)
{
}

void Menu::init() {
    children.push_back(&BSTForm);
    children.push_back(&GraphForm);
    children.push_back(&HashTableForm);
    children.push_back(&SLLForm);
    for (auto i : children) i->init();
    Back.init();

    BSTForm.button_setting = &form_setting;
    BSTForm.text_setting = &form_setting;
    BSTForm.setSize(main_button_width, main_button_height);
    BSTForm.setText("BST");

    GraphForm.button_setting = &form_setting;
    GraphForm.text_setting = &form_setting;
    GraphForm.setSize(main_button_width, main_button_height);
    GraphForm.setText("Graph");

    HashTableForm.button_setting = &form_setting;
    HashTableForm.text_setting = &form_setting;
    HashTableForm.setSize(main_button_width, main_button_height);
    HashTableForm.setText("HashTable");

    SLLForm.button_setting = &form_setting;
    SLLForm.text_setting = &form_setting;
    SLLForm.setSize(main_button_width, main_button_height);
    SLLForm.setText("Singly Linked List");
    
    Back.button_setting = &form_setting;
    Back.setPosition(30, 30);
    Back.setButtonStage(0, back_normal, back_hovered);
    Back.setSize(30, 30);


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
    children.push_back(&Back);
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
}
void Menu::draw() {
    for (auto i : children) i->draw();
}
void Menu::close() {
    for (auto& i:children) i->close();
    children.clear();
}