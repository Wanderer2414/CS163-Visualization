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
    main_letter.setSize(680, 480);
    main_letter.setText(main_letter_content);
    main_letter.setSize(680, main_letter.getAutoHeight());

    main_container.setSize(700, main_letter.getAutoHeight() + 20);
    main_container.setPosition(m_window_size.x/2-main_container.getSize().x/2, 10);
    main_container.add_vertex(main_container.getPosition());
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    camera.target = {0, 0};
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
    if (main_letter.getCursorPosition().y > m_window_size.y - 50 && main_container.getVertexDone() != -1) {
        main_container.add_vertex({main_container.getPosition().x, main_container.getPosition().y - 100});
        main_container.moveNext();
    }
    if (main_container.isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        main_letter.skip();
        main_container.add_vertex({main_container.getPosition().x, m_window_size.y - main_container.getSize().y - 10});
        main_container.moveNext();
    }
    if (GetMouseWheelMoveV().y != 0) {
        camera.offset = camera.offset + GetMouseWheelMoveV()*20;
    }
}
void AboutUsForm::draw() {
    BeginMode2D(camera);
    for (auto i:children) i->draw();
    EndMode2D();
}