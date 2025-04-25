#include "../include/FormStart.h"
#include "../include/IncludePath.h"
#include "../include/General.h"
extern Vector2 WindowSize;
MenuStart::MenuStart(FormSetting* f_setting, const Vector2& windowSize) :
    form_setting(f_setting),
    m_windowSize(windowSize),
    Title(&title_setting),
    Start(form_setting,form_setting),
    Setting(form_setting, form_setting),
    AboutUs(form_setting ,form_setting),
    Exit(form_setting,form_setting),
    setting_box(form_setting)
{
    children.push_back(&Start);
    children.push_back(&Setting);
    children.push_back(&Exit);
    children.push_back(&AboutUs);
    children.push_back(&image_list);
    children.push_back(&Title);
    children.push_back(&setting_box);

    image_list.setSize(TransX(550), TransY(325));
    image_list.setPosition(-image_list.getSize().x - 50, m_windowSize.y / 2 - TransY(115));
    image_list.add_vertex({-600,m_windowSize.y / 2 - TransY(115)});
    image_list.add_vertex({180,m_windowSize.y / 2 - TransY(115)});
    image_list.moveNext();
    
    title_setting = *form_setting;
    title_setting.font = GetFontDefault();
    title_setting.font_size = TransY(50);
    Title.setPosition(0, -120);
    Title.add_vertex({0, -120});
    Title.add_vertex({0, 70});
    Title.setSize(m_windowSize.x, TransY(120));
    Title.setAlignText(Label::Middle);
    Title.setText("DATA STRUCTURE\nVISUALIZATION");
    Title.moveNext();

    Start.setSize(TransX(400), TransY(60));
    Start.setText("Start");
    Start.setPosition(m_windowSize.x+100, m_windowSize.y / 2 - Start.getSize().y / 2 - TransY(90));
    Start.add_vertex({m_windowSize.x+100, m_windowSize.y / 2 - Start.getSize().y / 2 - TransY(90)});
    Start.add_vertex({m_windowSize.x - Start.getSize().x -100, m_windowSize.y / 2 - Start.getSize().y / 2 - TransY(90)});
    Start.moveNext();

    Setting.setSize(TransX(400), TransY(60));
    Setting.setText("Setting");
    Setting.setPosition(m_windowSize.x*2, m_windowSize.y / 2 - Setting.getSize().y / 2);
    Setting.add_vertex({m_windowSize.x*2, m_windowSize.y / 2 - Setting.getSize().y / 2});
    Setting.add_vertex({m_windowSize.x - Setting.getSize().x -100, m_windowSize.y / 2 - Setting.getSize().y / 2});
    Setting.moveNext();

    setting_box.setSize(TransX(500), TransY(600));
    setting_box.setPosition(m_windowSize.x/2-setting_box.getSize().x/2, m_windowSize.y/2-setting_box.getSize().y/2);
    setting_box.setDuration(0.2);
    setting_box.setVisible(false);

    AboutUs.setSize(TransX(400), TransY(60));
    AboutUs.setText("About Us");
    AboutUs.setPosition(m_windowSize.x*3, m_windowSize.y / 2 - AboutUs.getSize().y / 2 + TransY(90));
    AboutUs.add_vertex({m_windowSize.x*3, m_windowSize.y / 2 - AboutUs.getSize().y / 2 + TransY(90)});
    AboutUs.add_vertex({m_windowSize.x - AboutUs.getSize().x -100, m_windowSize.y / 2 - AboutUs.getSize().y / 2 + TransY(90)});
    AboutUs.moveNext();
    
    Exit.setSize(TransX(400), TransY(60));
    Exit.setText("Exit");
    Exit.setPosition(m_windowSize.x*4, m_windowSize.y / 2 - Exit.getSize().y / 2 + TransY(180));
    Exit.add_vertex({m_windowSize.x*4, m_windowSize.y / 2 - Setting.getSize().y / 2 + TransY(180)});
    Exit.add_vertex({m_windowSize.x - Exit.getSize().x -100, m_windowSize.y / 2 - Exit.getSize().y / 2 + TransY(180)});
    Exit.moveNext();

    LightAVL.push(LightTheme.AVL0);
    LightAVL.push(LightTheme.AVL1);
    LightAVL.push(LightTheme.AVL2);
    LightAVL.push(LightTheme.AVL3);
    LightSLL.push(LightTheme.SLL0);
    LightSLL.push(LightTheme.SLL1);
    LightSLL.push(LightTheme.SLL2);
    LightSLL.push(LightTheme.SLL3);
    LightGraph.push(LightTheme.Graph0);
    LightGraph.push(LightTheme.Graph1);
    LightGraph.push(LightTheme.Graph2);
    LightGraph.push(LightTheme.Graph3);
    LightHashTable.push(LightTheme.HT0);
    LightHashTable.push(LightTheme.HT1);
    LightHashTable.push(LightTheme.HT2);
    LightHashTable.push(LightTheme.HT3);


    DarkAVL.push(DarkTheme.AVL0);
    DarkAVL.push(DarkTheme.AVL1);
    DarkAVL.push(DarkTheme.AVL2);
    DarkAVL.push(DarkTheme.AVL3);
    DarkSLL.push(DarkTheme.SLL0);
    DarkSLL.push(DarkTheme.SLL1);
    DarkSLL.push(DarkTheme.SLL2);
    DarkSLL.push(DarkTheme.SLL3);
    DarkGraph.push(DarkTheme.Graph0);
    DarkGraph.push(DarkTheme.Graph1);
    DarkGraph.push(DarkTheme.Graph2);
    DarkGraph.push(DarkTheme.Graph3);
    DarkHashTable.push(DarkTheme.HT0);
    DarkHashTable.push(DarkTheme.HT1);
    DarkHashTable.push(DarkTheme.HT2);
    DarkHashTable.push(DarkTheme.HT3);
    update_gif();
}
int MenuStart::getMode() const {
    return setting_box.getMode();
}
int MenuStart::run() {
    while (!WindowShouldClose()) {
        handle();
        for (auto i : children) i->handle();
        BeginDrawing();
        ClearBackground(form_setting->background_color);
        draw();
        EndDrawing();
        if (!setting_box.isHovered() && Start.getProgress()<0.05) return return_value;
        if (!setting_box.isHovered() && setting_box.isEnd() && Setting.isPressed()) setting_box.open();
        if (!setting_box.isHovered() && Exit.isPressed()) return -1;
        if (setting_box.isSizeChanged()) return 0;
    };
    return 0;
};
void MenuStart::update() {
    Start.button_setting = form_setting;
    Start.text_setting = form_setting;
    Setting.button_setting = form_setting;
    Setting.text_setting = form_setting;
    AboutUs.button_setting = form_setting;
    AboutUs.text_setting = form_setting;
    Exit.button_setting = form_setting;
    Exit.text_setting = form_setting;
    title_setting.color = form_setting->color;

    for (auto i:children) i->update();
}
void MenuStart::update_gif() {
    image_list.clearGifs();
    if (form_setting == &LightTheme) {
        image_list.push(&LightAVL);
        image_list.push(&LightGraph);
        image_list.push(&LightSLL);
        image_list.push(&LightHashTable);
    } else {
        image_list.push(&DarkAVL);
        image_list.push(&DarkGraph);
        image_list.push(&DarkSLL);
        image_list.push(&DarkHashTable);
    }
}
void MenuStart::handle() {
    if (old_mode != setting_box.getMode()) {
        old_mode = setting_box.getMode();
        update();
        update_gif();
    }
    if (setting_box.isSubmit()) {
        update();
    }
    if (!setting_box.isHovered() && (Start.isPressed() || AboutUs.isPressed())) {
        if (Start.isPressed()) return_value = 1;
        else return_value = 2;
        Start.moveNext();
        AboutUs.moveNext();
        Setting.moveNext();
        Exit.moveNext();
        Title.moveNext();
        image_list.moveNext();
    }
}
void MenuStart::draw() {
    // Draw Title
    // Calculate the position to center the text
    for (auto i : children) i->draw();
}
void MenuStart::setMode(const int& mode) {
    setting_box.setMode(mode);
}
void MenuStart::setSizeIndex(const int& index) {
    setting_box.setWindowSize(index);
}
int MenuStart::getWindowSizeIndex() {
    return setting_box.getWindowSizeIndex();
}