#include "../include/FileDropBox.h"
#include "../include/General.h"

DropBox::DropBox() {
    m_file_count = 0;
    m_textfile_position = { 0,0, };
    m_is_visible = true;
}
bool DropBox::IsFileAdd() const {
    return m_file_add;
}
bool DropBox::isVisible() const {
    return m_is_visible;
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
    if (m_is_visible && text_setting && button_setting) {
    TextButton::draw();
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        Vector2 pos = m_textfile_position + m_position;
        for (auto i : files) {
            i = GetFileName(i.c_str());
            DrawTextEx(text_setting->font, i.c_str(), pos, text_setting->font_size, text_setting->spacing, text_setting->color);
            pos.y += text_setting->font_size;
        }
        EndScissorMode();
    }
}
void DropBox::setVisible(const bool& visible) {
    m_is_visible = visible;
}
DropBox::~DropBox() {

}