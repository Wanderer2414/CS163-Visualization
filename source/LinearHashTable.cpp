#include "../include/LinearHashTable.h"
#include "../include/General.h"
#include "../include/RaylibExtra.h"

HT::Node::Node(ButtonSetting* b_setting, TextSetting* t_setting, Camera2D& c): 
    button_setting(b_setting), text_setting(t_setting), camera(c) {
    m_value = 0;
    m_index = 0;
    is_animating = false;
    m_is_hovered = m_is_pressed = m_is_focus = false;
    percent = 1;
}
bool HT::Node::isFocus() const {
    return m_is_focus;
}
int HT::Node::getValue() const {
    return m_value;
};
Vector2 HT::Node::getPosition() const { 
    return Controller::getPosition();
}
void HT::Node::setIndex(const int& index) {
    m_index = index;
    index_text = to_string(index);
    m_index_position = m_position + m_size/2 - MeasureSmallText(text_setting, index_text)/2;
    m_index_position.y -= m_size.y/2 + 10;
}
void HT::Node::setValue(const int& value) {
    m_value = value;
    text = std::to_string(value);
    m_text_size = MeasureText(text_setting, text);
    setSize(max(m_text_size.x + 10, 50.f), max(m_text_size.y + 10, 50.f));
    percent = 0.1;
    m_text_position = m_position + m_size/2 - m_text_size*percent/2;
}
void HT::Node::setPosition(const float &x, const float &y) {
    m_text_position = m_text_position - m_position + Vector2({x, y});
    m_index_position = m_index_position - m_position + Vector2({x, y});
    Controller::setPosition(x, y);
}
void HT::Node::setSize(const float &width, const float &height) {
    m_index_position = m_index_position - m_size/2 + Vector2({width, height})/2;
    m_text_position = m_text_position - m_size/2 + Vector2({width, height})/2;
    Controller::setSize(width, height);
}
void HT::Node::update() {
    
}
void HT::Node::draw() {
    if (is_animating) DrawRectangleRounded(button_setting, m_position, m_size, button_setting->hightlight_color1);
    else if (m_is_hovered) DrawRectangleRoundedHover(button_setting, m_position, m_size);
    else if (m_is_focus) DrawRectangleRoundedClick(button_setting, m_position, m_size); 
    else DrawRectangleRoundedNormal(button_setting, m_position, m_size);

    if (text_setting) {
        DrawText(text_setting, m_text_position, text, text_setting->font_size*percent);
        DrawSmallText(text_setting, m_index_position, index_text);
    }
    else {
        std::cerr << "Error: text_setting is null!" << std::endl;
    }
}
void HT::Node::handle() {
    SlowMotion::handle();
    m_is_hovered = CheckCollisionPointRec(TransToGlobalPoint(camera,GetMousePosition()), { m_position.x, m_position.y, m_size.x, m_size.y });
    m_is_pressed = m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        m_is_focus = m_is_pressed;
    }
    if (percent < 1) {
        m_text_position = m_text_position + m_text_size*percent/2;
        percent *= 1.1;
        if (percent > 1) percent = 1;
        m_text_position = m_text_position - m_text_size*percent/2;
    }
}

HT::HashTable::HashTable(const int& index, FormSetting f_setting, const Vector2& window_size) : 
    Form(index, f_setting, window_size),
    size_label(&form_setting),
    m_memory_sz_textBox(&form_setting, &form_setting) {
    m_node_spacing = 10;

    m_memory_sz_textBox.setPosition(95, 45);
    m_memory_sz_textBox.setSize(170, 40);

    size_label.setPosition(5, 45);
    size_label.setSize(100, 40);
    size_label.setText("Size: ");
    size_label.setAlignText(Label::Left);

    random_size_button.setButtonStage(0, form_setting.Rand, form_setting.Rand_hovered);
    random_size_button.setPosition(275, 50);
    random_size_button.setSize(30, 30);

    create_textbox.setPosition(5, 90);
    create_button.setPosition(5, 200);

    create_box.setSize(310, 250);

    create_box.push_back(&m_memory_sz_textBox);
    create_box.push_back(&size_label);
    create_box.push_back(&random_size_button);
    create_box.reLocate(&create_textbox);
    create_box.reLocate(&create_button);

    m_memory_sz_textBox.setText(std::to_string(50));
    true_width = m_workspace.width/m_camera.zoom;
    min_width = 0, max_width = numeric_limits<float>::max();

    m_camera.offset.y = m_workspace.y + 20;
    line = 0;
}
void HT::HashTable::setMemorySize(const int& sz) {
    int old_size = m_memory.size();
    if (sz > old_size) {
        for (int i = old_size; i < sz; i++) {
            m_memory.push_back(Node(&form_setting, &form_setting, m_camera));
            m_memory.back().setSize(50, 50);
            m_memory.back().setValue(0);
            m_memory.back().setIndex(i);
        }
    }
    reLocate();
}
void HT::HashTable::draw() {
    BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
    for (int i = 0; i < m_memory.size(); i++) m_memory[i].draw();
    EndScissorMode();
    EndMode2D();
    Form::draw();
}
string HT::HashTable::RandomCreateSize(int _max, int _min)
{
    srand(clock());
    return std::to_string(_min + std::rand() % (_max - _min + 1));
}
void HT::HashTable::reLocate(const bool& visual) {
    float width = 0;
    line = form_setting.small_font_size + 10;
    min_width = 0, max_width = numeric_limits<float>::max();
    for (int i = 0; i<m_memory.size(); i++) {
        if (width + m_memory[i].getSize().x > true_width) {
            min_width = max(width, min_width);
            if (width + m_memory[i].getSize().x > min_width) max_width = min(width + m_memory[i].getSize().x, max_width);
            width = 0;
            line += form_setting.small_font_size + 10 + m_memory[i].getSize().y;
        }
    
        if (m_memory[i].getPosition() != Vector2({width, line})) {
            if (visual) {
                if (m_memory[i].getPosition().y != line) m_memory[i].setPosition(0, line);
                m_memory[i].setDuration(getSpeed()/2);
                m_memory[i].setSlowPosition(width, line);
            }
            else m_memory[i].setPosition(width, line);
        }
        width += m_memory[i].getSize().x + m_node_spacing;
    }
    min_width = max(width, min_width);
    if (min_width > max_width) max_width = min(width, max_width);
    line += form_setting.small_font_size + 10 + m_memory.back().getSize().y;
}
void HT::HashTable::handle() {
    Form::handle();
    int chosen = -1;
    for (int i = 0; i<m_memory.size(); i++) {
        m_memory[i].handle();
        if (m_memory[i].isFocus()) chosen = i;
    }
    if (chosen != -1) {
        if (IsKeyDown(KEY_DELETE)) {
            main_box_show();
            option_box.select(4);
            remove_textbox.setText(to_string(m_memory[chosen].getValue()));
            remove_textbox.setFocus(true);
        }
        else if (IsKeyDown(KEY_F2)) {
            main_box_show();
            option_box.select(2);
            update_textbox_choice.setText(to_string(m_memory[chosen].getValue()));
            update_textbox_value.setFocus(true);
        }
    }
    
    m_camera.offset.x = m_workspace.x + 10;
    float bound = m_workspace.y + m_workspace.height - line * m_camera.zoom;
    if (bound < m_workspace.y) m_camera.offset.y = clamp(m_camera.offset.y, bound, m_workspace.y);
    else m_camera.offset.y = m_workspace.y;
    if (random_size_button.isPressed()) {
        m_memory_sz_textBox.setText(RandomCreateSize(200, 50));
    }
    m_camera.zoom = std::clamp(m_camera.zoom, 0.1f, 10.f);
    true_width = m_workspace.width/m_camera.zoom;
    if (true_width < min_width || true_width>max_width) {
        reLocate(false);
    }
};
HT::HashTable::~HashTable() {
    
}
int HT::HashTable::index(const int& value) {
    return value % m_memory.size();
}
void HT::HashTable::add(const vector<std::string>& data) {
    setMemorySize(to_int(m_memory_sz_textBox.getText()));
    int cnt = 0;
    for (auto& i:data) {
        if (cnt > m_memory.size()) return;
        console.InsertNextMainCommand("Insert " + i);
        InsertNextMainCommand({ _insert, (float)to_int(i) });
        cnt++;
    }
}

void HT::HashTable::remove_console_add()
{
    console.InsertNextSubCommand("index = key % table.size                                              ");
    console.InsertNextSubCommand("if (table[index] = value) -> remove table[index]                      ");
    console.InsertNextSubCommand("else {                                                                ");
    console.InsertNextSubCommand("   cur = index + 1                                                    ");
    console.InsertNextSubCommand("   while (table[cur] != value & cur != pos) cur++                     ");
    console.InsertNextSubCommand("   if table[cur] = value -> remove table[cur]                         ");
    console.InsertNextSubCommand("   else value is not found in table -> return                         ");
    console.InsertNextSubCommand("}                                                                     ");
}
void HT::HashTable::search_console_add()
{
    console.InsertNextSubCommand("index = key % table.size                                              ");
    console.InsertNextSubCommand("if (table[index] = value) -> found                                    ");
    console.InsertNextSubCommand("else {                                                                ");
    console.InsertNextSubCommand("   cur = index + 1                                                    ");
    console.InsertNextSubCommand("   while (table[cur] != value & cur != pos) cur++                     ");
    console.InsertNextSubCommand("   if table[cur] = value -> found                                     ");
    console.InsertNextSubCommand("   else not found                                                     ");
    console.InsertNextSubCommand("}                                                                     ");
}
void HT::HashTable::update_console_add()
{
    console.InsertNextSubCommand("index = key % table.size                                              ");
    console.InsertNextSubCommand("if (table[index] = oldValue) -> update to newValue                    ");
    console.InsertNextSubCommand("else {                                                                ");
    console.InsertNextSubCommand("   cur = index + 1                                                    ");
    console.InsertNextSubCommand("   while (table[cur] != value & cur != pos) cur++                     ");
    console.InsertNextSubCommand("   if table[cur] = oldValue -> update new value                       ");
    console.InsertNextSubCommand("   else oldValue is not found in table -> return                      ");
    console.InsertNextSubCommand("}                                                                     ");
}
void HT::HashTable::insert_console_add()
{
    console.InsertNextSubCommand("index = key % table.size                                              ");
    console.InsertNextSubCommand("if (table[index] = value) value is already in table                   ");
    console.InsertNextSubCommand("if table[index] does not have value -> table[index] = value & return  ");
    console.InsertNextSubCommand("else {                                                                ");
    console.InsertNextSubCommand("   cur = index + 1                                                    ");
    console.InsertNextSubCommand("   while ( table[cur] != 0 & table[cur] != value & cur != pos) cur++  ");
    console.InsertNextSubCommand("   if table[cur] = 0 -> table[cur] = value                            ");
    console.InsertNextSubCommand("   else if table[cur] = value -> value is already in table            ");
    console.InsertNextSubCommand("   else table is full -> return                                       ");
    console.InsertNextSubCommand("}                                                                     ");
}
void HT::HashTable::update(const std::string& old_value, const std::string& new_value)
{
    console.InsertNextMainCommand("Update " + old_value + " to " + new_value);
    InsertNextMainCommand({ _update, (float)to_int(old_value), (float)to_int(new_value) });
}
void HT::HashTable::search(const std::string& x)
{
    console.InsertNextMainCommand("Search " + x);
    InsertNextMainCommand({ _search, (float)to_int(x) });
}
void HT::HashTable::remove(const std::string& data) {
    console.InsertNextMainCommand("Remove " + data);
    InsertNextMainCommand({ _delete, (float)to_int(data) });
}
void HT::HashTable::update(const int& oldvalue, const int& newvalue)
{
    int pos = index(oldvalue);
    InsertNextSubCommand({ _choose, float(pos), 0.5 });
    InsertNextSubCommand({ _goDown, 1, 0.5 });

    if (m_memory[pos].getValue() == oldvalue) {
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.5 });
        InsertNextSubCommand({ _remove, (float)pos, (float)oldvalue, 0.5 });
        InsertNextSubCommand({ _add, (float)pos, (float)newvalue, 0.5 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });
        InsertNextSubCommand({ _goDown, 6, 1 });
    }
    else {
        InsertNextSubCommand({ _goDown, 1, 0.5 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });
        int cur = pos + 1;
        if (cur == m_memory.size()) cur = 0;
        InsertNextSubCommand({ _goDown, 1, 0.5 });

        InsertNextSubCommand({ _choose, (float)cur, 0.5 });
        InsertNextSubCommand({ _goDown, 1, 0.5 });

        while (cur != pos && m_memory[cur].getValue() != oldvalue) {
            InsertNextSubCommand({ _choose, (float)cur, 0.5 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
            cur++;
            if (cur == m_memory.size()) cur = 0;
        }
        InsertNextSubCommand({ _goDown, 1, 0.5 });

        if (m_memory[cur].getValue() == oldvalue) {
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.5 });
            InsertNextSubCommand({ _remove, (float)cur, (float)oldvalue, 0.5 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });

            pos = index(newvalue);
            InsertNextSubCommand({ _choose, (float)pos, 0.5 });
            if (m_memory[pos].getValue() == newvalue) {
                InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
                InsertNextSubCommand({ _choose, (float)pos, 0.25 });
                InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
                InsertNextSubCommand({ _choose, (float)pos, 0.25 });
                InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
                InsertNextSubCommand({ _goDown, 2, 1 });
                return;
            }
            if (!m_memory[pos].getValue()) {
                InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
                InsertNextSubCommand({ _choose, (float)pos, 0.25 });
                InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
                InsertNextSubCommand({ _choose, (float)pos, 0.5 });
                InsertNextSubCommand({ _add, (float)pos, (float)newvalue, 0.5 });
                InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });
                InsertNextSubCommand({ _goDown, 2, 1 });
                return;
            }
            else {
                InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });

                cur = pos + 1;
                if (cur == m_memory.size()) cur = 0;
                InsertNextSubCommand({ _choose, (float)cur, 0.5 });

                while (cur != pos && m_memory[cur].getValue() && m_memory[cur].getValue() != newvalue) {

                    InsertNextSubCommand({ _choose, (float)cur, 0.5 });
                    InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
                    cur++;
                    if (cur == m_memory.size()) {
                        cur = 0;
                    }
                }
                if (!m_memory[cur].getValue()) {
                    InsertNextSubCommand({ _choose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _choose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _choose, (float)cur, 0.5 });
                    InsertNextSubCommand({ _add, (float)cur, (float)newvalue, 0.5 });
                    InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
                }
                else if (m_memory[cur].getValue() == newvalue) {
                    InsertNextSubCommand({ _choose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _choose, (float)cur, 0.25 });
                    InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
                }
            }
            InsertNextSubCommand({ _goDown, 2, 1 });
        }
        else {
            InsertNextSubCommand({ _goDown, 1, 1 });
            InsertNextSubCommand({ _goDown, 1, 0.5 });
        }
    }
}

void HT::HashTable::insert(const int& value) {
    int pos = index(value);
    InsertNextSubCommand({ _choose, (float)pos, 0.5 });
    InsertNextSubCommand({ _goDown, 1, 0.5 });

    if (m_memory[pos].getValue() == value) {
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _goDown, 8, 1 });
        return;
    }

    InsertNextSubCommand({ _goDown, 1, 1 });
    if (!m_memory[pos].getValue()) {
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.5 });
        InsertNextSubCommand({ _add, (float)pos, (float)value, 0.5 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });
        InsertNextSubCommand({ _goDown, 7, 1 });
    }
    else {

        InsertNextSubCommand({ _goDown, 1, 0.5 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });

        int cur = pos + 1;
        if (cur == m_memory.size()) cur = 0;
        InsertNextSubCommand({ _goDown, 1, 0.5 });
        InsertNextSubCommand({ _choose, (float)cur, 0.5 });
        InsertNextSubCommand({ _goDown, 1, 0.5 });

        while (cur != pos && m_memory[cur].getValue() && m_memory[cur].getValue() != value) {

            InsertNextSubCommand({ _choose, (float)cur, 0.5 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
            cur++;
            if (cur == m_memory.size()) {
                cur = 0;
            }
        }
        InsertNextSubCommand({ _goDown, 1, 0.5 });

        if (!m_memory[cur].getValue()) {
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.5 });
            InsertNextSubCommand({ _add, (float)cur, (float)value, 0.5 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
            InsertNextSubCommand({ _goDown, 3, 1 });
        }
        else if (m_memory[cur].getValue() == value) {
            InsertNextSubCommand({ _goDown, 1, 1 });
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });

            InsertNextSubCommand({ _goDown, 2, 1 });
        }
        else {
            InsertNextSubCommand({ _goDown, 1, 0.5 });
            InsertNextSubCommand({ _goDown, 1, 0.5 });
            InsertNextSubCommand({ _goDown, 1, 1 });
        }
    }

}

void HT::HashTable::search(const int& value)
{
    int pos = index(value);
    InsertNextSubCommand({ _choose, (float)pos, 0.5});
    InsertNextSubCommand({ _goDown, 1, 0.5 });

    if (m_memory[pos].getValue() == value) {
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _goDown, 6, 1 });
        return;
    }

    int cur = pos + 1; 
    if (cur == m_memory.size()) cur = 0; 
    InsertNextSubCommand({ _goDown, 1, 0.5 });
    InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });
    InsertNextSubCommand({ _goDown, 1, 0.5 });
    InsertNextSubCommand({ _choose, (float)cur, 0.5 });
    InsertNextSubCommand({ _goDown, 1, 0.5 });

    while (cur != pos && m_memory[cur].getValue() != value) {
        InsertNextSubCommand({ _choose, (float)cur, 0.5 }); 
        InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
        cur++;  
        if (cur == m_memory.size()) cur = 0; 
    }
    InsertNextSubCommand({ _goDown, 1, 1 });

    if (m_memory[cur].getValue() == value) {
        InsertNextSubCommand({ _choose, (float)cur, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
        InsertNextSubCommand({ _choose, (float)cur, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
        InsertNextSubCommand({ _choose, (float)cur, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });

        InsertNextSubCommand({ _goDown, 2, 1 });
    }
    else {
        InsertNextSubCommand({ _goDown, 1, 1 });
        InsertNextSubCommand({ _goDown, 1, 1 });
    }
}
void HT::HashTable::remove(const int& value) {
    int pos = index(value);
    InsertNextSubCommand({ _choose, (float)pos, 0.5 });
    InsertNextSubCommand({ _goDown, 1, 0.5 });
    
    if (m_memory[pos].getValue() == value) {
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _choose, (float)pos, 0.5 });
        InsertNextSubCommand({ _remove, (float)pos, (float)value, 0.5 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });
        InsertNextSubCommand({ _goDown, 6, 1 });
    }
    else {
        int cur = pos + 1;
        if (cur == m_memory.size()) cur = 0;

        InsertNextSubCommand({ _goDown, 1, 0.5 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.5 });

        InsertNextSubCommand({ _goDown, 1, 0.5 });

        InsertNextSubCommand({ _choose, (float)cur, 0.5 });
        InsertNextSubCommand({ _goDown, 1, 0.5 });
 
        while (cur != pos && m_memory[cur].getValue() != value) {
            InsertNextSubCommand({ _choose, (float)cur, 0.5 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
            cur++;
            if (cur == m_memory.size()) cur = 0;
        }
        InsertNextSubCommand({ _goDown, 1, 0.5 });

        if (m_memory[cur].getValue() == value) {
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.25 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
            InsertNextSubCommand({ _choose, (float)cur, 0.5 });
            InsertNextSubCommand({ _remove, (float)cur, (float)value, 0.5 });
            InsertNextSubCommand({ _unchoose, (float)cur, 0.5 });
            InsertNextSubCommand({ _goDown, 2, 1 });
        }
        else {
            InsertNextSubCommand({ _goDown, 1, 1 });
            InsertNextSubCommand({ _goDown, 1, 1 });
        }
    }
}
void HT::HashTable::FetchNextCommand(const std::vector<float>& command) {
    if (command.empty()) return;

    switch ((int)command[0]) {
    case _insert: {
        insert_console_add();
        console.goDown();
        insert(int(command[1]));
        InsertNextSubCommand({ _insert_end_code, 1});
        setDuration(0.2);
    }
                break;
    case _delete: {
        remove_console_add();
        console.goDown();
        remove(int(command[1]));
        InsertNextSubCommand({ _remove_end_code, 1 });
        setDuration(0.2);
    }
                break;
    case _search: {
        search_console_add();
        console.goDown();
        search((int)command[1]);
        InsertNextSubCommand({ _search_end_code, 1 });
        setDuration(0.2);
    }
                break;
    case _choose: {
        m_memory[(int)command[1]].is_animating = true;
        setDuration(command[2]);
    }
                break;
    case _unchoose: {
        m_memory[(int)command[1]].is_animating = false;
        setDuration(0.2);
    }
                 break;
    case _add: {
        m_memory[(int)command[1]].setValue(command[2]);
        reLocate();
        setDuration(command[3]);
    }
             break;
    case _remove: {
        m_memory[(int)command[1]].setValue(0);
        reLocate();
        setDuration(0.2);
    }
                break;
    case _update: {
        update_console_add();
        console.goDown();
        int oldvalue = (int)command[1];
        int newvalue = (int)command[2];
        update(oldvalue, newvalue);
        InsertNextSubCommand({ _update_end_code, 1 });
        setDuration(0.2);
    }
                break;
    case _goUp: {
        int n = command[1];
        for (int i = 0; i < n; i++) console.goUp();
        setDuration(command.back());
    }
             break;
    case _goDown: {
        int n = command[1];
        for (int i = 0; i < n; i++) console.goDown();
        setDuration(command.back());
    }
               break;
    case _insert_end_code: {
        console.goDown();
    }
               break;
    case _search_end_code: {
        console.goDown();
    }
               break;
    case _remove_end_code: {
        console.goDown();
    }
               break;
    case _update_end_code: {
        console.goDown();
    }
               break;

    }
}
void HT::HashTable::FetchPrevCommand(const std::vector<float>& command) {
    if (command.empty()) return;
    switch ((int)command[0]) {
    case _insert: {
        console.goUp();
        setDuration(1);
    }
                break;
    case _delete: {
        insert(int(command[1]));
        setDuration(0.2);
    }
                break;
    case _search: {
        console.goUp();
        setDuration(0.2);
    }  
                break;
    case _remove: {
        m_memory[(int)command[1]].setValue(command[2]);
        reLocate();
        setDuration((int)command[3]);
    }
                break;
    case _update: {
        console.goUp();
        setDuration(1);
    }
                break;
    case _choose: {
        m_memory[(int)command[1]].is_animating = false;
        setDuration(0.2);
    }
                break;
    case _unchoose: {
        m_memory[(int)command[1]].is_animating = true;
        setDuration(0.2);
    }
                break;
    case _add: {
        m_memory[(int)command[1]].setValue(0);
        reLocate();
        setDuration(command[3]);
    }
                break;
    case _insert_end_code: {
        console.goUp();
        insert_console_add();
        for (int i = 0; i < 10; i++) {
            console.goDown();
        }
        setDuration(0.2);
    }
                break;
    case _search_end_code: {
        console.goUp();
        search_console_add();
        for (int i = 0; i < 8; i++) {
            console.goDown();
        }
        setDuration(0.2);
    }
                break;
    case _remove_end_code: {
        console.goUp();
        remove_console_add();
        for (int i = 0; i < 8; i++) {
            console.goDown();
        }
        setDuration(0.2);
    }
               break;
    case _update_end_code: {
        console.goUp();
        update_console_add();
        for (int i = 0; i < 8; i++) {
            console.goDown();
        }
        setDuration(0.2);
    }
               break;
    case _goDown: {
        int n = command[1];
        for (int i = 0; i < n; i++) console.goUp();
        setDuration(command.back());
    }
              break;
    case _goUp: {
        int n = command[1];
        for (int i = 0; i < n; i++) console.goDown();
        setDuration(command.back());
    }
                break;
    }
}