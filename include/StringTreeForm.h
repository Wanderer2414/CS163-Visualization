#ifndef STRINGTREEFORM_H
#define STRINGTREEFORM_H

#include "Form.h"
#include "SlowMotion.h"
#include "TextButton.h"
#include <string>
#include <vector>
using namespace std;

namespace Ex {
    class Branch;
    class Node;

    class Node:public TextButton {
    public:
        friend class NameTree;
        string          value;
        Node            *next   = 0;
        Branch          *child  = 0;
        void            init() override,
                        handle() override,
                        draw() override;
        Node(): next(0), child(0) {
            init();
        }
        Node(string name): value(name), next(0), child(0) {
            init();
            setText(name);
        };
        Node(string name, Node* m_next): value(name), next(m_next), child(0) {
            init();
            setText(name);
        };
        Node(Branch* m_child): child(m_child), next(0) {init();};
        Node(Node* m_next): next(m_next), child(0) {init();};
        
    protected:
        void update_text() override;
    };
    class Branch {
    public:
        Branch();
        Branch(string name);
        Branch(Branch* cur);
        Branch(Node* m_head, Node* m_tail, const unsigned char& size);
        unsigned char   size();
        Node            *getHead(),
                        *getTail(),
                        *getMiddlePrev();
        bool            empty();
        void            push_front(Node* node),
                        insert(Node* prev, Node* node),
                        free();
        Branch          *next   = 0,
                        *prev   = 0;
        unsigned char   m_size  = 0;
        Node            *head = 0,
                        *tail = 0;
        Vector2         vertex;
        ~Branch();
    private:
        void            free(Branch* root);

    };

class NameTree:public Form {
    public:
        NameTree(const Vector2& window_size);
        virtual void add(const std::string& str) override,
                add_from_file(const std::string &source) override;
        void    insert(string name),
                init() override,
                show(),
                free(),
                close() override,
                draw() override,
                handle() override;
        Branch* m_root;
        int     m_height    = 1;
        ~NameTree();
    private:
        void    ReLocate();
        float   ReLocate(Branch* root, const float& left, const float& y);
        void    insert(Branch*& root, string name),
                show(Branch* root, const int& indent),
                free(Branch* root),
                draw(Branch* root),
                handle(Branch* root);
        int     max_size    = 32;
        Ex::Node* split(Branch* root, const bool& isLeaf);
    };    
}
#endif