#include "../include/AboutUsForm.h"
#include "../include/General.h"

AboutUsForm::AboutUsForm(FormSetting f_setting, const Vector2& window_size):
    form_setting(f_setting),
    m_window_size(window_size),
    main_letter(&form_setting),
    main_container(&form_setting) {
    form_setting.roundness = 0.05f;

    children.push_back(&main_container);

    main_container.push_back(&main_letter);

    main_letter.setPosition(10, 10);
    main_letter.setText(main_letter_content);

    main_container.setSize(700, m_window_size.y - 20);
    main_container.setPosition(m_window_size.x/2-main_container.getSize().x/2, 10);
    main_container.add_vertex(main_container.getPosition());

    main_letter.setSize(680, main_container.getSize().y - 20);

    clock.setDuration(1);
}
int AboutUsForm::run() {
    float init = 0;
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
        if (init<50) {
            Color color = form_setting.background_color;
            if (init < 50) color.a = init/50*255;
            else color.a = 255-(init-50)/50*255;
            DrawRectangle(0, 0, m_window_size.x, m_window_size.y, color);
            init++;
        } else {
            ClearBackground(form_setting.background_color);
            draw();
        }
        EndDrawing();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !main_container.isHovered()) return 0;
    }
    return 0;
}
void AboutUsForm::handle() {
    for (auto i:children) i->handle();
    if (GetMouseWheelMoveV().y != 0) {
        Vector2 pos = main_letter.getPosition();
        pos.y = pos.y+GetMouseWheelMoveV().y*10;
        main_letter.setPosition(pos.x, pos.y);
    } 
    if ((main_letter.getCursorPosition().y + 100 > main_container.getPosition().y + main_container.getSize().y) && (main_letter.getTextSize()!=main_letter.getCurrentTextSize())) {
        Vector2 pos = main_letter.getPosition();
        pos.y = pos.y-5;
        main_letter.setPosition(pos.x, pos.y);
    }
    if (main_container.isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        main_letter.skip();
        Vector2 pos = main_letter.getPosition();
        pos.y = pos.y + main_container.getPosition().y + main_container.getSize().y - main_letter.getAutoHeight();
        main_letter.setPosition(pos.x, pos.y);
    }
    if (clock.get() && rand()%4 && bubbles.size()<20) {
        bubbles.push_back(Bubble());
        bubbles.back().setRadius(10 + rand()%10);
        bubbles.back().setColor(form_setting.reverse_color);
        if (rand()%2) 
            bubbles.back().setPosition(rand()%int(m_window_size.x/2 - 350), m_window_size.y+20);
        else bubbles.back().setPosition(rand()%int(m_window_size.x/2 - 350) + m_window_size.x/2 + 350, m_window_size.y+20);
    }
    for (int i = 0; i<bubbles.size(); i++) {
        Vector2 pos = bubbles[i].getPosition();
        float radius = bubbles[i].getRadius();
        if (pos.y<=10) {
            bubbles[i].setRadius(10 + rand()%10);
            pos.x = rand()%int(m_window_size.x/2 - 350);
            pos.y = m_window_size.y+20;
            if (rand()%2)
                bubbles[i].setPosition(pos.x, pos.y);
            else {
                pos.x += m_window_size.x/2 + 350;
                bubbles[i].setPosition(pos.x, pos.y);
            }
            continue;
        } else {
            radius = radius*exp(1.0/3*log(pos.y/(pos.y-(1.5 - pos.y/m_window_size.y))));
            bubbles[i].setRadius(radius);
            pos.y = pos.y-(1.5 - pos.y/m_window_size.y);
            bubbles[i].setPosition(pos.x, pos.y);
        }
    }
}
void AboutUsForm::draw() {
    for (const auto& child : children) child->draw();
    for (auto& i : bubbles) i.draw();
}