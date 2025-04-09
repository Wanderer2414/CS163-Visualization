#include "../include/LinearHashTable.h"
#include "../include/General.h"
#include "../include/IncludePath.h"

HT::Node::Node(): TextButton(0, 0) {
    m_value = 0;
    m_index = 0;
    is_animating = false;
    anim_color = WHITE;
    found_color = ORANGE;
}
int HT::Node::getValue() const {
    return m_value;
};
void HT::Node::setIndex(const int& index) {
    m_index = index;
}
void HT::Node::setValue(const int& value) {
    m_value = value;
    setText(std::to_string(value));
}
void HT::Node::draw() {
    Color curr;
    if (is_found) curr = found_color;
    else if (is_animating) curr = anim_color;
    else curr = button_setting->normal_color;

    if (button_setting) DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, button_setting->roundness, button_setting->segment, curr);

    if (text_setting) {
        DrawTextEx(text_setting->font, m_text.c_str(), m_text_position, text_setting->font_size, text_setting->spacing, text_setting->color);
        
        Vector2 index_pos = m_position;
        float x = MeasureTextEx(text_setting->font, std::to_string(m_index).c_str(), text_setting->font_size/1.7, text_setting->spacing).x;
        index_pos.x = index_pos.x + m_size.x / 2 - x / 2;
        index_pos.y -= text_setting->font_size/1.7 + 5;
        DrawTextEx(text_setting->font, std::to_string(m_index).c_str(), index_pos, text_setting->font_size / 1.7, text_setting->spacing, text_setting->color);
    }
    else {
        std::cerr << "Error: text_setting is null" << std::endl;
    }
}
void HT::Node::handle() {
    TextButton::handle();
}

HT::HashTable::HashTable(const int& index, FormSetting f_setting, const Vector2& window_size) : 
    Form(index, f_setting, window_size),
    size_label(&form_setting),
    m_memory_sz_textBox(&form_setting, &form_setting) {
        
    m_node_size = 50;
    m_node_spacing = 30;
    max_size = 0;

    m_memory_sz_textBox.setPosition(95, 45);
    m_memory_sz_textBox.setSize(170, 40);

    size_label.setPosition(5, 45);
    size_label.setSize(100, 40);
    size_label.setText("Size: ");
    size_label.setAlignText(Label::Left);

    random_size_button.setButtonStage(0, Rand, Rand);
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

    setMemorySize(50);

    m_camera.offset.y = m_workspace.y + 20;
}
void HT::HashTable::setMemorySize(const int& sz) {
    m_memory.resize(sz);
    for (int i = 0; i < sz; i++) {
        m_memory[i].button_setting = &form_setting;
        m_memory[i].text_setting = &form_setting;
        m_memory[i].setSize(m_node_size, m_node_size);
        m_memory[i].setValue(0);
        m_memory[i].setIndex(i);
    }
}
void HT::HashTable::draw() {
    BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
    for (int i = 0; i < m_memory.size(); i++) m_memory[i].draw();
    EndScissorMode();
    EndMode2D();
    Form::draw();
}
void HT::HashTable::handle() {
    Form::handle();
    for (auto& i:m_memory) i.handle();
    
    m_camera.offset.x = m_workspace.x + 10;
    if (m_memory_sz_textBox.isEnter()) {
        setMemorySize(to_int(m_memory_sz_textBox.getText()));
    }
    int count = m_workspace.width / m_camera.zoom / (m_node_size + m_node_spacing);
    if (count != max_size || m_memory_sz_textBox.isEnter()) {
        max_size = count;
        int i = 0;
        int y = 0;
        while (i < m_memory.size()) {
            int offset = i;
            for (; i < m_memory.size() && (i - offset) < count; i++)
                m_memory[i].setPosition((m_node_size + m_node_spacing) * (i - offset), y);
            y += m_node_size + form_setting.font_size + 10;
        }
    }
};
HT::HashTable::~HashTable() {

}
int HT::HashTable::index(const int& value) {
    return value % m_memory.size();
}
void HT::HashTable::add(const vector<std::string>& data) {
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
}
void HT::HashTable::search_console_add()
{
}
void HT::HashTable::update_console_add()
{
}
void HT::HashTable::insert_console_add()
{
    console.InsertNextSubCommand("index = key % table.size                                              ");
    console.InsertNextSubCommand("if (table[index] = value) return                                      ");
    console.InsertNextSubCommand("if table[index] not have value -> table[index] = value & return       ");
    console.InsertNextSubCommand("else {                                                                ");
    console.InsertNextSubCommand("   cur = index + 1                                                    ");
    console.InsertNextSubCommand("   while ( table[cur] != 0 & table[cur] != value & cur != pos) cur++  ");
    console.InsertNextSubCommand("if table[cur] = 0 -> table[cur] = value                               ");
    console.InsertNextSubCommand("else if table[cur] = value -> return                                  ");
    console.InsertNextSubCommand("}                                                                     ");
}
void HT::HashTable::update(const std::string& old_value, const std::string& new_value)
{
    console.InsertNextMainCommand("Update " + old_value);
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
void HT::HashTable::insert(const int& value) {
 
    int pos = index(value);
    InsertNextSubCommand({ _choose, (float)pos, 1 });

    InsertNextSubCommand({ _goDown, 1, 1 });

    if (m_memory[pos].getValue() == value) {
        InsertNextSubCommand({ _found, (float)pos, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });
        InsertNextSubCommand({ _goDown, 7, 1 });
        return;
    }

    InsertNextSubCommand({ _goDown, 1, 1 });
    if (!m_memory[pos].getValue()) {

        InsertNextSubCommand({ _found, (float)pos, 1 });
        InsertNextSubCommand({ _add, (float)pos, (float)value, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });
        InsertNextSubCommand({ _goDown, 6, 1 });
    }
    else {

        InsertNextSubCommand({ _goDown, 1, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });

        int cur = pos + 1; 
        if (cur == m_memory.size()) cur = 0;
        InsertNextSubCommand({ _goDown, 1, 1 });

        InsertNextSubCommand({ _choose, (float)cur, 1 });

        InsertNextSubCommand({ _goDown, 1, 1 });

        while (cur != pos && m_memory[cur].getValue() && m_memory[cur].getValue() != value) {
            
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });
            cur++;
            if (cur == m_memory.size()) {
                cur = 0;
            }
        }
        InsertNextSubCommand({ _goDown, 1, 1 });

        if (!m_memory[cur].getValue()) {
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _found, (float)cur, 1 });
            InsertNextSubCommand({ _add, (float)cur, (float)value, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });
            InsertNextSubCommand({ _goDown, 2, 1 });
        }
        else if (m_memory[cur].getValue() == value) {
            InsertNextSubCommand({ _goDown, 1, 1 });
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _found, (float)cur, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });
            InsertNextSubCommand({ _goDown, 1, 1 });
        }
    }

}

void HT::HashTable::update(const int& oldvalue, const int& newvalue)
{
    int pos = index(oldvalue);
    
    if (m_memory[pos].getValue() == oldvalue) {
        InsertNextSubCommand({ _choose, (float)pos, 1 });
        InsertNextSubCommand({ _found, (float)pos, 1 });
        InsertNextSubCommand({ _remove, (float)pos, (float)oldvalue, 1 });
        InsertNextSubCommand({ _add, (float)pos, (float)newvalue, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });
        //console.InsertNextSubCommand("Update value at index " + std::to_string(pos));
        //console.goDown();
    }
    else {
        InsertNextSubCommand({ _choose, (float)pos, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });

        int cur = pos + 1;

        if (cur == m_memory.size()) cur = 0;

        while (cur != pos && m_memory[cur].getValue() != oldvalue) {
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });
            cur++;
            if (cur == m_memory.size()) cur = 0;
        }

        if (m_memory[cur].getValue() == oldvalue) {
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _found, (float)cur, 1 });
            InsertNextSubCommand({ _remove, (float)cur, (float)oldvalue, 1 });
            InsertNextSubCommand({ _add, (float)cur, (float)newvalue, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });

            //console.InsertNextSubCommand("Updated value at index " + std::to_string(cur));
            //console.goDown();
        }
        else {
            //console.InsertNextSubCommand("Value not found to update");
            //console.goDown();
        }
    }
}
bool HT::HashTable::checkAnimationsComplete()
{
    for (const auto& node : m_memory) {
        if (node.is_animating == true) {
            return false;
        }
    }
    return true;
}
void HT::HashTable::search(const int& value)
{
    int pos = index(value);
    //console.InsertNextSubCommand( "Index = value % table_size" );
    //console.InsertNextSubCommand("if (table[index] == value) return");
    if (m_memory[pos].getValue() == value) {
        InsertNextSubCommand({ _choose, (float)pos, 1 });
        InsertNextSubCommand({ _found, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _found, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0.25 });
        InsertNextSubCommand({ _found, (float)pos, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)pos, 0 });

        //console.InsertNextSubCommand("Value found at index " + std::to_string(pos));
        //console.goDown(); 
        return;
    }
    //console.InsertNextSubCommand("if (table[index] is empty or value not found) traverse through the table");

    int cur = pos + 1; 
    if (cur == m_memory.size()) cur = 0; 

    while (cur != pos && m_memory[cur].getValue() != value) {
        //console.InsertNextSubCommand("Checking index " + std::to_string(cur));
        InsertNextSubCommand({ _choose, (float)cur, 1 }); 
        InsertNextSubCommand({ _unchoose, (float)cur, 1 });
        cur++;  
        if (cur == m_memory.size()) cur = 0; 
    }
    if (m_memory[cur].getValue() == value) {
        InsertNextSubCommand({ _choose, (float)cur, 1 });
        InsertNextSubCommand({ _found, (float)cur, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
        InsertNextSubCommand({ _found, (float)cur, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)cur, 0.25 });
        InsertNextSubCommand({ _found, (float)cur, 0.25 });
        InsertNextSubCommand({ _unchoose, (float)cur, 0 });


        //console.InsertNextSubCommand("Value found at index " + std::to_string(cur));  // Visualize the found value
        //console.goDown();  // Move to the next step
    }
    else {
        //console.InsertNextSubCommand("Value not found in table");  // Value not found, show message
        //console.goDown();  // Move to the next step
    }
}
void HT::HashTable::remove(const int& value) {
    int pos = index(value);

    
    if (m_memory[pos].getValue() == value) {
        InsertNextSubCommand({ _choose, (float)pos, 1 });  
        InsertNextSubCommand({ _found, (float)pos, 1 });
        InsertNextSubCommand({ _remove, (float)pos, (float)value, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });
        //console.goDown();
    }
    else {
        InsertNextSubCommand({ _choose, (float)pos, 1 });
        InsertNextSubCommand({ _unchoose, (float)pos, 1 });

        int cur = pos + 1;
        if (cur == m_memory.size()) cur = 0;
        while (cur != pos && m_memory[cur].getValue() != value) {
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });
            cur++;
            if (cur == m_memory.size()) cur = 0;
        }
        if (m_memory[cur].getValue() == value) {
            InsertNextSubCommand({ _choose, (float)cur, 1 });
            InsertNextSubCommand({ _found, (float)cur, 1 });
            InsertNextSubCommand({ _remove, (float)cur, (float)value, 1 });
            InsertNextSubCommand({ _unchoose, (float)cur, 1 });
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
        remove(int(command[1]));
        setDuration(0);
    }
                break;
    case _search: {
        search((int)command[1]);
        setDuration(0);
        InsertNextSubCommand({ _goDown, 1, 1 });
    }
                break;
    case _choose: {
        m_memory[(int)command[1]].anim_color = RED;
        m_memory[(int)command[1]].is_animating = true;
        setDuration(command[2]);
    }
                break;
    case _unchoose: {
        m_memory[(int)command[1]].anim_color = WHITE;
        m_memory[(int)command[1]].is_animating = false;
        m_memory[(int)command[1]].is_found = false;
        setDuration(0.2);
    }
                  break;
    case _add: {
        m_memory[(int)command[1]].setValue(command[2]);
        setDuration(command[3]);
    }
             break;
    case _remove: {
        m_memory[(int)command[1]].setValue(0);
        setDuration(command[3]);
        InsertNextSubCommand({_goDown, 1, 1});
    }
                break;
    case _update: {
        int oldvalue = (int)command[1];
        int newvalue = (int)command[2];
        update(oldvalue, newvalue);
        /*InsertNextSubCommand({ _goDown, 1, 1 });*/
    }
                break;
    case _found: {
        m_memory[(int)command[1]].is_found = true;
        setDuration(command[2]);
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
        setDuration(0);
        console.goUp();
    }
                break;
    case _search: {
        int value = (int)command[1];
        setDuration(0);
        console.goUp();
    }  
                break;
    case _choose: {
        m_memory[(int)command[1]].anim_color = WHITE;
        m_memory[(int)command[1]].is_animating = false;
        m_memory[(int)command[1]].is_found = false;
        setDuration(0.2);
    }
                break;
    case _unchoose: {
        m_memory[(int)command[1]].anim_color = RED;
        m_memory[(int)command[1]].is_animating = true;
        setDuration(0.2);
    }
                break;
    case _add: {
        m_memory[(int)command[1]].setValue(0);
        setDuration(command[3]);
    }
                break;
    case _insert_end_code: {
        console.goUp();
        insert_console_add();
        for (int i = 0; i < 9; i++) {
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