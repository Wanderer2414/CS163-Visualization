#include "../include/Menu.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/General.h"
#include <cmath>
#include <string>

Menu::Menu(const Vector2& windowSize):
        m_windowSize(windowSize) 
{
}

int Menu::run() {
    while (!WindowShouldClose()) {
        handle();
        for (auto i:children) i->handle();
        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
        if (BSTForm.isPressed()) return 1;
        if (GraphForm.isPressed()) return 2;
        if (StringTree.isPressed()) return 3;
    };
    return 0;
};
void Menu::init() {
    children.push_back(&BSTForm);
    children.push_back(&GraphForm);
    children.push_back(&StringTree);
    for (auto i:children) i->init();

    // BSTForm.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    BSTForm.setSize(main_button_width,main_button_height);
    BSTForm.setText("BST");
    BSTForm.setRoundness(0.3);

    GraphForm.setSize(main_button_width,main_button_height);
    GraphForm.setText("Graph");
    GraphForm.setRoundness(0.3);

    StringTree.setSize(main_button_width, main_button_height);
    StringTree.setText("String");
    StringTree.setRoundness(0.3);

    Vector2 center = m_windowSize/2;
    Vector2 origin = {center.x - 0.5f*(main_button_width+2)*button_count, center.y - main_button_height/2};
    for (int i = 0; i<children.size(); i++) {
        children[i]->setPosition(origin.x + (main_button_width + 50)*i, origin.y);
    }


}
void Menu::loadAsset() {
    
}
void Menu::handle() {
    
}
void Menu::draw() {
    for (auto i:children) i->draw();
}
void Menu::unloadAsset() {

}
void Menu::close() {
    children.clear();
}