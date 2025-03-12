#ifndef STRINGTREEFORM_H
#define STRINGTREEFORM_H

#include "Form.h"
#include "SlowMotion.h"
#include "TextButton.h"
#include <string>
#include <vector>
class SNode;
class Branch {
public:
    Branch(Vector2* origin);
    Branch(Vector2* origin, SNode* head, SNode* tail, const int& sz);
    int         size = 0;
    SNode       *head, *tail;    
    float       width = 0;
    void        insert(SNode* prev, SNode* n);
};
class SNode: public TextButton, public SlowMotion {
public:
    SNode(Vector2* origin, const int& index);
    bool        isVisible;
    char        *data;
    int         m_index = 0;
    void        setPosition(const float& x, const float& y) override,
                handle()                                    override,
                draw()                                      override,
                setText(const std::string &str)             override;
    Branch      *child;
    SNode       *next;
    Vector2     getPosition() const override;
};

class StringTreeForm: public Form {
public:
    enum Code {
        choose = 0,
        unchoose = 1,
        redraw = 2
    };
    StringTreeForm(const Vector2& window_size);
    int                 max_child = 7;
    virtual void        add(const std::string& str)     override,
                        FetchCommandQueue()             override,
                        handle()                        override,
                        draw()                          override;

    void                insert(const std::string& str),
                        insert(Branch* root, const std::string& str),
                        show(),
                        show(Branch* root);
    SNode*              split(Branch* root);
    Branch*             m_root;
    std::vector<SNode*> m_list;
    void                reLocate();
    float               reLocate(Branch* root);
    ~StringTreeForm();
};
#endif