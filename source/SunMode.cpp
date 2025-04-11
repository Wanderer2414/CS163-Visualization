#include "../include/SunMode.h"
#include "../include/General.h"

SunMode::SunMode(ButtonSetting* light_setting, ButtonSetting* dark_setting) {
    light_button_setting = light_setting;
    dark_button_setting = dark_setting;
    m_is_light = false,
    m_is_pressed = m_is_hovered = false;
    percent = 1;
    percent_alpha = 255;
    m_point = {0,0};
    sun_light_texture = LoadTexture(LightTheme.sun);
    sun_dark_texture = LoadTexture(DarkTheme.sun);
}
float SunMode::getPercent() const {
    return percent;
}
void SunMode::setMode(const int& mode) {
    m_is_light = !mode;
    percent = mode;
    percent_alpha = percent*255;
}
void SunMode::draw() {
    if (light_button_setting && dark_button_setting) {
        Color color = light_button_setting->normal_color*(1-percent)+dark_button_setting->normal_color*percent;
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, 0.5f, 30, color);

        DrawRectangleRounded({m_point.x, m_point.y, m_size.y, m_size.y}, 0.5f, 30, color_start*(1-percent)+color_end*percent);
        
        DrawTexture(sun_light_texture, m_point.x, m_point.y, {255, 255, 255, (unsigned char)(255-percent_alpha)});
        DrawTexture(sun_dark_texture, m_point.x, m_point.y, {255,255,255, percent_alpha});
    }
}
void SunMode::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    m_is_pressed = m_is_hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (m_is_pressed) {
        m_is_light = !m_is_light;
    }
    if (m_is_light && percent > 0) {
        percent -= percent/10;
        if (percent < 10e-5) percent = 0;
        m_point.x = m_position.x + (m_size.x-m_size.y)*percent;
        percent_alpha = 255*percent;
    } else if (!m_is_light && percent<1) {
        percent += (1-percent)/10;
        if (percent > 1 - 10e-5) percent = 1;
        m_point.x = m_position.x + (m_size.x-m_size.y)*percent;
        percent_alpha = 255*percent;
    }
}
void SunMode::setPosition(const float& x, const float& y) {
    Controller::setPosition(x,y);
    m_point.x = m_position.x + (m_size.x-m_size.y)*percent;
    m_point.y = y;
}
void SunMode::setSize(const float& x, const float& y) {
    Controller::setSize(x,y);
    sun_dark_texture.width = sun_light_texture.width = y;
    sun_dark_texture.height = sun_light_texture.height = y;
    m_point.x = m_position.x + (m_size.x-m_size.y)*percent;
    m_point.y = y;
}
SunMode::~SunMode() {
    UnloadTexture(sun_light_texture);
    UnloadTexture(sun_dark_texture);
}