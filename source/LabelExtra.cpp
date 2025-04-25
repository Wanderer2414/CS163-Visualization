#include "../include/LabelExtra.h"
#include "../include/IncludePath.h"

LabelEx::LabelEx(TextSetting* t_setting) {
    text_setting = t_setting;
    m_text = {{""}};
    m_text_position = {{{0, 0}}};
    number_word = {{0}};
    text_size = {{0}};
    spacing = {{5}};
    align = {Top | Middle};
    margin = 5;
    size = 0;

    wave1 = LoadSound(keyboard_press_1);
    wave2 = LoadSound(keyboard_press_2);
    wave3 = LoadSound(keyboard_press_3);

    clock.setDuration(0.1);
    cursor_position = {0, 0};
    total_text_length = 0;
    canReset = is_push = false;
    update_text();
}
bool LabelEx::empty() const {
    return (m_text.size()<=1) && (m_text[0].empty());
}
int LabelEx::getTextSize() const {
    return total_text_length;
}
int LabelEx::getCurrentTextSize() const {
    return size;
}
void LabelEx::clear() {
    m_text.clear();
    m_text_position.clear();
    m_text = {{""}};
    m_text_position = {{{0, 0}}};
    number_word = {{0}};
    spacing = {{5}};
    text_size = {{0}};
    align = {Left | Top};
    update_line(0);
}
void LabelEx::draw() {
    if (text_setting) {
        int n = size;
        for (int i = 0; i<m_text_position.size() && n; i++) {
            int index = 0;
            for (int j = 0; j<number_word[i].size() && n; j++) {
                Vector2 pos = m_text_position[i][j];
                for (int count = 0; count< number_word[i][j] && n; count++) {
                    if (n>=m_text[i][index+count].size()) {
                        DrawTextEx(text_setting->font, m_text[i][index+count].c_str(), pos, text_setting->font_size, text_setting->spacing,text_setting->color);
                        if (n == m_text[i][index+count].size()) {
                            float x = pos.x;
                            x += MeasureTextEx(text_setting->font, m_text[i][index+count].c_str(), text_setting->font_size, text_setting->spacing).x;
                            if (dummy_string.size()) {
                                DrawTextEx(text_setting->font, dummy_string.c_str(), {x, pos.y}, text_setting->font_size, text_setting->spacing,text_setting->color);
                                x += MeasureTextEx(text_setting->font, dummy_string.c_str(), text_setting->font_size, text_setting->spacing).x;
                            }
                            cursor_position = {x, pos.y};
                            DrawLineEx(cursor_position, {x, pos.y + text_setting->font_size}, 3.f, text_setting->color);
                        }
                        n-=m_text[i][index+count].size();
                        if (!n && canReset) {
                            clock.setDuration(1.0f*(rand()%3+5)/10);
                            canReset = false;
                        }
                    }
                    else { 
                        DrawTextEx(text_setting->font, m_text[i][index+count].substr(0, n).c_str(), pos, text_setting->font_size, text_setting->spacing,text_setting->color);
                        float x = pos.x;
                        x += MeasureTextEx(text_setting->font, m_text[i][index+count].substr(0, n).c_str(), text_setting->font_size, text_setting->spacing).x;
                        if (dummy_string.size()) {
                            DrawTextEx(text_setting->font, dummy_string.c_str(), {x, pos.y}, text_setting->font_size, text_setting->spacing,text_setting->color);
                            x += MeasureTextEx(text_setting->font, dummy_string.c_str(), text_setting->font_size, text_setting->spacing).x;
                        }
                        cursor_position = {x, pos.y};
                        DrawLineEx(cursor_position, {x, pos.y + text_setting->font_size}, 3.f, text_setting->color);
                        n = 0;
                        if (canReset) {
                            clock.setDuration(1.0f*(rand()%3+2)/10);
                            canReset = false;
                        }
                    }
                    pos.x += text_size[i][index+count] + spacing[i][j];
                }
                index += number_word[i][j];
            }
        }
    }
}
void LabelEx::handle() {
    if ((clock.get() || is_push) && size < total_text_length) {
        is_push = false;
        int r = rand()%20;
        canReset = true;
        if (r>16 && dummy_string.size()<5) {
            dummy_string=rand()%26+'a';
        }
        else {
            if (dummy_string.empty()) {
                if (rand()%2) PlaySound(wave1);
                else PlaySound(wave2);
                size++;
            }
            else {
                dummy_string.pop_back();
                PlaySound(wave3);
            }
        }
    }
}
void LabelEx::Push()  {
    is_push = true;
}
void LabelEx::setText(const std::string& str) {
    m_text.clear();
    m_text.push_back({""});
    m_text_position.clear();
    m_text_position.push_back({{0, 0}});
    text_size = {{0}};
    number_word = {{0}};
    spacing = {{5}};
    align = {Left | Top};
    int i = 0;
    while(i<str.size()) {
        if (str[i]=='\n') {
            m_text_position.push_back({{0, 0}});
            m_text.push_back({""});
            align.push_back(Left | Top);
            number_word.push_back({0});
            spacing.push_back({0});
            text_size.push_back({});
        }
        else if (str[i] == ' ' && i+1<str.size() && str[i+1]!=' ') {
            m_text.back().push_back("");
        }
        else {
            if (str[i]=='\\' && i+6<str.size() && str.substr(i, 6) == "\\right") {
                align.back() = Right | Top;
                i+=5;
            }
            else if (str[i]=='\\' && i+5<str.size() && str.substr(i, 5) == "\\left") {
                align.back() = Left | Top;
                i+=4;
            }
            else if (str[i]=='\\' && i+7<str.size() && str.substr(i, 7) == "\\center") {
                align.back() = Middle | Top;
                i+=6;
            }
            else {
                m_text.back().back().push_back(str[i]);
                total_text_length++;
            }
        }
        i++;
    }
    update_text();
}
void LabelEx::skip() {
    size = total_text_length;
    dummy_string = "";
}
void LabelEx::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    update_text();
}
void LabelEx::setPosition(const float& x, const float& y) {
    for (auto& j:m_text_position) {
        for (auto& i:j) {
            i.x = i.x - getPosition().x + x;
            i.y = i.y - getPosition().y + y;
        }
    }
    Controller::setPosition(x, y);
}
void LabelEx::update_text() {
    if (!text_setting) return;
    float new_y = m_position.y + margin;
    for (int i = 0; i<m_text_position.size(); i++) {
        m_text_position[i][0].y = new_y;
        update_line(i);
        new_y = m_text_position[i].back().y + text_setting->font_size;
    }
}
void LabelEx::update_line(const int& line) {
    if (!text_setting) return ;
    if (line>=m_text.size()) return ;
    m_text_position[line].resize(1);
    m_text_position[line][0].x = m_position.x + margin;
    number_word[line] = {0};
    spacing[line] = {10};
    text_size[line] = {};
    float width = 0;
    int n = m_text[line].size();
    for (int i = 0; i<n; i++) {
        Vector2 size = MeasureTextEx(text_setting->font, m_text[line][i].c_str(),text_setting->font_size,text_setting->spacing);
        text_size[line].push_back(size.x);
        if (width + size.x + margin*2>m_size.x) {
            spacing[line].back() = (m_size.x - margin*2 - width)/(number_word[line].back() - 1) + 10;
            if ((align[line] & Left)  == Left) ;
            else if ((align[line] & Right) == Right) m_text_position[line].back().x = m_position.x + m_size.x - width - margin;
            else m_text_position[line].back().x += m_size.x/2 - width/2;

            Vector2 pos = m_text_position[line].back();
            pos.y += size.y;
            m_text_position[line].push_back(pos);
            width = 0;
            number_word[line].push_back(0);
            spacing[line].push_back(10);
        }
        number_word[line].back()++;
        width += size.x + 10;
    }
    if ((align[line] & Left)  == Left) ;
    else if ((align[line] & Right) == Right) m_text_position[line].back().x = m_position.x + m_size.x - width - margin;
    else m_text_position[line].back().x += m_size.x/2 - width/2;

}
void LabelEx::setAlignText(const int& line, const int& m_align) {
    align[line] = m_align;
    update_line(line);
}
void LabelEx::update() {
    update_text();
}
float LabelEx::getAutoHeight() const {
    return m_text_position.back().back().y + text_setting->font_size;
}
Vector2 LabelEx::getCursorPosition() const {
    return cursor_position;
}
LabelEx::~LabelEx() {
    UnloadSound(wave1);
    UnloadSound(wave2);
    UnloadSound(wave3);
}