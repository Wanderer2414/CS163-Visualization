#include "../include/Menu.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/Colors.h"
#include "../include/Mode.h"
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

    // BSTForm.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    BSTForm.setSize(main_button_width, main_button_height);
    BSTForm.setText("BST");
    BSTForm.setRoundness(0.3);

    GraphForm.setSize(main_button_width, main_button_height);
    GraphForm.setText("Graph");
    GraphForm.setRoundness(0.3);

    HashTableForm.setSize(main_button_width, main_button_height);
    HashTableForm.setText("HashTable");
    HashTableForm.setRoundness(0.3);

    SLLForm.setSize(main_button_width, main_button_height);
    SLLForm.setText("Singly Linked List");
    SLLForm.setRoundness(0.3);

    Vector2 center = m_windowSize / 2;
    Vector2 origin = { center.x - 0.5f * (main_button_width + 2) * button_count, center.y - main_button_height / 2 };
    for (int i = 0; i < children.size(); i++) {
        children[i]->setPosition(origin.x + (main_button_width + 50) * i, origin.y);
    }

}
int Menu::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
        ColorScheme currentTheme = DarkTheme;
        ClearBackground(currentTheme.background);

        draw();
        EndDrawing();
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
    children.clear();
}