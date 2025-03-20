#include "../include/Menu.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/Colors.h"
#include "../include/Mode.h"
#include "../include/Form.h"
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
    // BSTForm.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    BSTForm.setSize(main_button_width, main_button_height);
    BSTForm.setTexture(menu_avltree_normal, menu_avltree_hovered);
    BSTForm.setRoundness(0.3);

    GraphForm.setSize(main_button_width, main_button_height);
    GraphForm.setTexture(menu_graph_normal, menu_graph_hovered);
    GraphForm.setRoundness(0.3);

    HashTableForm.setSize(main_button_width, main_button_height);
    HashTableForm.setTexture(menu_hash_normal, menu_hash_hoverd);
    HashTableForm.setRoundness(0.3);

    SLLForm.setSize(main_button_width, main_button_height);
    SLLForm.setTexture(menu_sll_normal, menu_sll_hovered);
    SLLForm.setRoundness(0.3);

    Back.setTexture(back_normal, back_hovered);
    Back.setPosition(10, 10);
    Back.setSize(20, 20);

    // Define spacing and button size
    int spacingX = main_button_width + 20;
    int spacingY = main_button_height + 20;
    int centerX = m_windowSize.x / 2;
    int centerY = m_windowSize.y / 2;

    // Position elements properly within bounds
    BSTForm.setPosition(centerX - spacingX, centerY - spacingY); // Top-left
    HashTableForm.setPosition(centerX - spacingX, centerY + spacingY); // Bottom-left
    GraphForm.setPosition(centerX + spacingX, centerY - spacingY); // Top-right
    SLLForm.setPosition(centerX + spacingX, centerY + spacingY); // Bottom-right


}
int Menu::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
        ColorScheme currentTheme = DarkTheme;
        ClearBackground(currentTheme.background);

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
void Menu::close() {
    children.clear();
}