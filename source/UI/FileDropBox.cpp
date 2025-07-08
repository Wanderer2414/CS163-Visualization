#include "FileDropBox.h"

DropBox::DropBox() {
    m_file_count = 0;
    m_textfile_position = { 0,0, };
    m_is_visible = true;
    m_file_add = false;
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
    Button::handle();
    m_file_add = false;
    if (IsFileDropped() && m_is_hovered) {
        FilePathList list = LoadDroppedFiles();
        files.clear();
        for (int i = 0; i < list.count; i++) {
            files.push_back(list.paths[i]);
        }
        m_file_add = true;
        m_file_count = list.count;
        UnloadDroppedFiles(list);
    }
}
void DropBox::draw() {
}
void DropBox::setVisible(const bool& visible) {
    m_is_visible = visible;
}
DropBox::~DropBox() {

}