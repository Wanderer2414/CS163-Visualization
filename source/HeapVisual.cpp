#include "../include/HeapVisual.h"
#include "../include/General.h"

HeapBlock::HeapBlock(ButtonSetting *b_setting, TextSetting* t_setting) {
    button_setting = b_setting;
    text_setting = t_setting;
    setDuration(0.5);
}
void HeapBlock::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    m_des_position = m_weight_position = m_position;
    Vector2 sz = MeasureTextEx(text_setting->font, weight_text.c_str(), text_setting->font_size,text_setting->spacing);
    m_weight_position.x += m_size.x/2 - sz.x/2;
    m_weight_position.y = 5;
    m_des_position.y += 10 + sz.y;
    sz = MeasureTextEx(text_setting->font, des_text.c_str(), text_setting->font_size/1.3,text_setting->spacing);
    m_des_position.x += m_size.x/2 - sz.x/2;
}
void HeapBlock::setPosition(const float& x, const float& y) {
    m_des_position = m_des_position - m_position + Vector2({x,y});
    m_weight_position = m_weight_position - m_position + Vector2({x,y});
    Controller::setPosition(x, y);
}
void HeapBlock::draw() {
    DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, 0.2f, button_setting->segment, button_setting->hover_color);
    DrawRectangleRounded({m_position.x+2, m_position.y+2, m_size.x-4, m_size.y-4}, 0.1f, button_setting->segment, button_setting->normal_color);
    DrawTextEx(text_setting->font, des_text.c_str(), m_des_position, text_setting->font_size/1.3, text_setting->spacing, text_setting->color);
    DrawTextEx(text_setting->font, weight_text.c_str(), m_weight_position, text_setting->font_size, text_setting->spacing, text_setting->color);
}
void HeapBlock::handle() {
    SlowMotion::handle();
}
void HeapBlock::setValue(const int& start, const int& end, const int& weight) {
    des_text = "(" + to_string(start) + ", " + to_string(end) + ")";
    weight_text = to_string(weight);

    m_des_position = m_weight_position = m_position;
    Vector2 sz = MeasureTextEx(text_setting->font, weight_text.c_str(), text_setting->font_size, text_setting->spacing);
    m_weight_position.x += m_size.x/2 - sz.x/2;
    m_weight_position.y = 5;
    m_des_position.y += 10 + sz.y;
    sz = MeasureTextEx(text_setting->font, des_text.c_str(),text_setting->font_size/1.3, text_setting->spacing);
    m_des_position.x += m_size.x/2 - sz.x/2;
}
Vector2 HeapBlock::getPosition() const {
    return m_position;
}

HeapVisual::HeapVisual(FormSetting* f_setting) {
    form_setting = f_setting;
    m_visible = true;
    choose_setting = *f_setting;
    choose_setting.normal_color = RED;
}
bool HeapVisual::isVisible() const {
    return m_visible;
}
void HeapVisual::handle() {
    for (int i = 0; i<heap.size(); i++) heap[i].handle();
}
void HeapVisual::draw() {
    if (!m_visible) return ;
    BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
    DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, 0.1, form_setting->segment, form_setting->middle_color);
    if (heap.size()) for (int i = 0; i<heap.size(); i++) heap[i].draw();
    else {
        Vector2 sz = MeasureTextEx(form_setting->font, "(Empty)", form_setting->font_size, form_setting->spacing);
        DrawTextEx(form_setting->font, "(Empty)", m_position + m_size/2 - sz/2, form_setting->font_size, form_setting->spacing, form_setting->color);
    }
    EndScissorMode();
}
void HeapVisual::Insert(const Path& path) {
    Vector2 pos;
    if (heap.size()) {
        pos = heap.back().getEndPoint();
        pos.y += heap.back().getSize().y + 5;
    } else {
        pos = m_position;
        pos.x += 2;
        pos.y += 2;
    }
    heap.push_back(HeapBlock(form_setting, form_setting));
    heap.back().setValue(path.start, path.end, path.weight);
    heap.back().setSize(m_size.x-4, 65);
    heap.back().setPosition(pos.x, pos.y);
    MinHeap::Insert(path);
}
void HeapVisual::clear() {
    data.clear();
    heap.clear();
}
void HeapVisual::erase(const int& index) {
    MinHeap::erase(index);
    heap.pop_back();
}
void HeapVisual::setPosition(const float &x, const float &y) {
    Controller::setPosition(x, y);
}
void HeapVisual::setSize(const float &width, const float &height) {
    Controller::setSize(width, height);
}
void HeapVisual::setVisible(const bool& visible) {
    m_visible = visible;
}
Path HeapVisual::pop() {
    auto ans = MinHeap::pop();
    heap.pop_back();
    return ans;
}
void HeapVisual::swap(Path& a, Path& b) {
    std::swap(a,b);
    int index_a = (&a - &data[0]), index_b = (&b - &data[0]);
    Vector2 pos_a = heap[index_a].getEndPoint(), pos_b = heap[index_b].getEndPoint();
    heap[index_a].setSlowPosition(pos_b.x, pos_b.y);
    heap[index_b].setSlowPosition(pos_a.x, pos_a.y);
    std::swap(heap[index_a],heap[index_b]);
}