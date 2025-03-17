#include "../include/FileDropBox.h"
#include "../include/General.h"

DropBox::DropBox() {
    m_file_count = 0;
    m_textfile_position = { 0,0, };
}
bool DropBox::IsFileAdd() const {
    return m_file_add;
}
vector<string> DropBox::getFiles() {
    return files;
}
void DropBox::handle() {
    TextButton::handle();
    m_file_add = false;
    if (IsFileDropped() && m_is_hovered) {
        FilePathList list = LoadDroppedFiles();
        files.clear();
        for (int i = 0; i < list.count; i++) {
            files.push_back(list.paths[i]);
        }
        m_file_add = true;
        UnloadDroppedFiles(list);
        m_file_count = list.count;
    }
}
void DropBox::draw() {
    TextButton::draw();
    BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
    Vector2 pos = m_textfile_position + m_position;
    for (auto i : files) {
        i = GetFileName(i.c_str());
        DrawTextEx(m_font, i.c_str(), pos, m_font_size, m_spacing, m_text_color);
        pos.y += m_font_size;
    }
    EndScissorMode();
}
DropBox::~DropBox() {

}