#ifndef FILEDROPBOX_H
#define FILEDROPBOX_H

#include "Button.h"
#include "TextButton.h"
#include <string>
#include <vector>
using namespace std;
class DropBox:public TextButton {
public:
    DropBox();
    bool            isVisible() const,
                    IsFileAdd() const;
    virtual void    handle() override,
                    draw() override,
                    setVisible(const bool& visible);
    vector<string>  getFiles();
    ~DropBox();
private:
    bool            m_file_add,
                    m_is_visible;
    int             m_file_count;
    vector<string>  files;
    Vector2         m_textfile_position;
};

#endif