#include "../include/LinearHashTable.h"
#include <string>
#include "../include/General.h"
HT::Node::Node() {
    TextButton::init();
    m_value = 0;
    m_index = 0;
    setSize(50, 50);
    setText(std::to_string(m_value));
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
    TextButton::draw();
    Vector2 index_pos = m_text_position;
    index_pos.y -= m_font_size + 5;
    DrawTextEx(m_font, std::to_string(m_index).c_str(),index_pos, m_font_size/1.5, m_spacing, WHITE);
}
void HT::Node::handle() {
    TextButton::handle();
}

HT::HashTable::HashTable(const Vector2& window_size): Form(window_size) {

}
void HT::HashTable::init() {
    children.push_back(&m_memory_sz_textBox);
    Form::init();

    m_node_size = 50;
    m_node_spacing = 5;
    max_size = 0;

    m_memory_sz_textBox.setPosition(m_window_size.x-100, 10);
    m_memory_sz_textBox.setSize(70, 50);
    m_memory_sz_textBox.setRoundness(0.4);

    setMemorySize(10);

    m_camera.offset.y = m_workspace.y+20;
}
void HT::HashTable::setMemorySize(const int& sz) {
    m_memory.resize(sz);
    for (int i = 0; i<sz; i++) {
        m_memory[i].setSize(m_node_size, m_node_size);
        m_memory[i].setIndex(i);
    }
}
void HT::HashTable::draw() {
    Form::draw();
    BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
    for (int i = 0; i<m_memory.size(); i++) m_memory[i].draw();
    EndScissorMode();
    EndMode2D();
}
void HT::HashTable::handle() {
    Form::handle();
    m_camera.offset.x = m_workspace.x+10;
    if (m_memory_sz_textBox.isEnter()) {
        setMemorySize(to_int(*m_memory_sz_textBox.getText()));
    }
    int count = m_workspace.width/m_camera.zoom/(m_node_size+m_node_spacing);
    if (count!=max_size || m_memory_sz_textBox.isEnter()) {
        max_size = count;
        int i = 0;
        int y = 0;
        while (i<m_memory.size()) {
            int offset = i;
            for (; i<m_memory.size() && (i-offset)<count; i++) 
                m_memory[i].setPosition((m_node_size+m_node_spacing)*(i-offset), y);
            y+=m_node_size+m_font_size+10;
        }
    }
};
HT::HashTable::~HashTable() {

}
int HT::HashTable::index(const int& value) {
    return value%m_memory.size();
}
void HT::HashTable::add(const std::string& data) {
    InsertNextMainCommand({_insert, (float)to_int(data)});
}
void HT::HashTable::remove(const std::string& data) {
    InsertNextMainCommand({_delete, (float)to_int(data)});
}
void HT::HashTable::insert(const int& value) {
    int pos = index(value);
    InsertNextSubCommand({_choose, (float)pos, 1});
    InsertNextSubCommand({_unchoose, (float)pos, 1});
    if (m_memory[pos].getValue()==value) return ;   
    if (!m_memory[pos].getValue()) {
        InsertNextSubCommand({_add, (float)pos, (float)value, 1});
    }
    else {
        int cur = pos + 1;
        if (cur==m_memory.size()) cur = 0;
        while (cur!=pos && m_memory[cur].getValue() && m_memory[cur].getValue()!=value) {
            InsertNextSubCommand({_choose, (float)cur, 1});
            InsertNextSubCommand({_unchoose, (float)cur, 1});
            cur++;
            if (cur==m_memory.size()) cur = 0;
        }
        if (!m_memory[cur].getValue()) {
            InsertNextSubCommand({_choose, (float)cur, 1});
            InsertNextSubCommand({_unchoose, (float)cur, 1});
            InsertNextSubCommand({_add, (float)cur, (float)value, 1});
        }
    }
}
void HT::HashTable::remove(const int& value, const bool& isShow) {
    int pos = index(value);
    if (isShow) {
        InsertNextSubCommand({_choose, (float)pos, 1});
        InsertNextSubCommand({_unchoose, (float)pos, 1});
    }
    if (m_memory[pos].getValue()==value) {
        if (isShow)
            InsertNextSubCommand({_remove, (float)pos, (float)value, 1});
        else m_memory[pos].setValue(0);
    }
    else {
        int cur = pos + 1;
        if (cur==m_memory.size()) cur = 0;
        while (cur!=pos && m_memory[cur].getValue()!=value) {
            if (isShow) {
                InsertNextSubCommand({_choose, (float)cur, 1});
                InsertNextSubCommand({_unchoose, (float)cur, 1});
            }
            cur++;
            if (cur==m_memory.size()) cur = 0;
        }
        if (m_memory[cur].getValue()==value) {
            if (isShow) {
                InsertNextSubCommand({_choose, (float)cur, 1});
                InsertNextSubCommand({_unchoose, (float)cur, 1});
                InsertNextSubCommand({_remove, (float)cur, (float)value, 1});
            } else m_memory[cur].setValue(0);
        }
    }
}
void HT::HashTable::FetchNextCommand(const std::vector<float>& command) {
    if (command.empty()) return;
    switch ((int)command[0]) {
        case _insert: {
            insert(int(command[1]));
            setDuration(0);
        }
            break;
        case _delete: {
            remove(int(command[1]));
            setDuration(0);
        }
            break;
        case _choose: {
            m_memory[(int)command[1]].m_normal_color = RED;
            setDuration(command[2]);
        }
            break;
        case _unchoose: {
            m_memory[(int)command[1]].m_normal_color = WHITE;
            setDuration(0);
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
        }
            break;
    }
}
void HT::HashTable::FetchPrevCommand(const std::vector<float>& command) {
    if (command.empty()) return;
    switch ((int)command[0]) {
        case _insert: {
            remove(int(command[1]), false);
            setDuration(1);
        }
            break;
        case _delete: {
            insert(int(command[1]));
            setDuration(0);
        }
        case _choose: {
            m_memory[(int)command[1]].m_normal_color = WHITE;
            setDuration(0);
        }
            break;
        case _unchoose: {
            m_memory[(int)command[1]].m_normal_color = RED;
            setDuration(0);
        }
            break;
        case _add: {
            m_memory[(int)command[1]].setValue(command[2]);
            setDuration(command[3]);
        }
            break;
    }
}