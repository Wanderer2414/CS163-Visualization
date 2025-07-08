#include "AboutUsForm.h"
#include "IncludePath.h"
#include "General.h"

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

    main_container.setSize(TransX(700), m_window_size.y - 20);
    main_container.setPosition(m_window_size.x/2-main_container.getSize().x/2, 10);
    main_container.add_vertex(main_container.getPosition());

    main_letter.setSize(main_container.getSize().x-20, main_container.getSize().y - 20);

    clock.setDuration(1);
    music = LoadMusicStream(about_us_sound);
    wave = LoadWave(about_us_sound);
    music_sample = LoadWaveSamples(wave);

    samples_size = wave.frameCount*wave.channels;

    music_length = GetMusicTimeLength(music);
    music_show.resize(m_window_size.x, 0);
    bubble_velocity = 0;
}
int AboutUsForm::run() {
    float init = 0;
    PlayMusicStream(music);
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
        ClearBackground(form_setting.background_color);
        draw();
        if (init<50) {
            Color color = form_setting.background_color;
            color.a = 255-init/50*255;
            DrawRectangle(0, 0, m_window_size.x, m_window_size.y, color);
            init++;
        }
        else if (init > 50) {
            Color color = form_setting.background_color;
            color.a = (init-50)/150*255;
            DrawRectangle(0, 0, m_window_size.x, m_window_size.y, color);
            if (init == 200) return 0;
            init++;
        }
        EndDrawing();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !main_container.isHovered()) init++;
    }
    return 0;
}
void AboutUsForm::handle() {
    for (auto i:children) i->handle();
    UpdateMusicStream(music);

    music_current = GetMusicTimePlayed(music);
    int index = music_current/music_length*samples_size;
    if (index != current_index) {
        current_index = index;
        for (int i = m_window_size.x-1; i>=1; i--) music_show[i] = music_show[i-1];
        music_show[0] = music_sample[index];
        if (music_sample[index]*100 > 2) {
            bubble_velocity += music_sample[index]*10;
            main_letter.Push();
        }
        if (music_sample[index]*100 > 3.5) {
            bubbles.push_back(Bubble());
            float radius = 15 + 5*(music_sample[index]*100-3.5);
            bubbles.back().setRadius(radius);
            bubbles.back().setColor(form_setting.reverse_color);
            if (rand()%2) 
                bubbles.back().setPosition(rand()%int(m_window_size.x/2 - 350), m_window_size.y+radius);
            else bubbles.back().setPosition(rand()%int(m_window_size.x/2 - 350) + m_window_size.x/2 + 350, m_window_size.y+radius);
        }
    }
    
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
    bubble_velocity/=1.05;
    for (int i = bubbles.size()-1; i>=0; i--) {
        Vector2 pos = bubbles[i].getPosition();
        float radius = bubbles[i].getRadius();
        if (pos.y<=10) {
            bubbles.erase(bubbles.begin() + i);
            continue;
        } else {
            radius = radius*exp(1.0/3*log(pos.y/(pos.y-1-bubble_velocity)));
            bubbles[i].setRadius(radius);
            pos.y = pos.y-1-bubble_velocity;
            bubbles[i].setPosition(pos.x, pos.y);
        }
    }
}
void AboutUsForm::draw() {
    for (const auto& child:children) child->draw();
    for (auto& i:bubbles) i.draw();

    for (int i = 0; i<m_window_size.x; i++) {
        DrawLine(i, m_window_size.y-music_show[i]*200, i, m_window_size.y, form_setting.hightlight_color1);
    }
}
AboutUsForm::~AboutUsForm() {
    UnloadMusicStream(music);
    UnloadWaveSamples(music_sample);
    UnloadWave(wave);
}