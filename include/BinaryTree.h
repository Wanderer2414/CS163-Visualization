#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Form.h"
#include "GUI.h"
#include <vector>
#include <map>

enum CommandCode {
    add = 0,
    choose = 1,
    unchoose = 2,
    compare = 3
};
class BinaryTreeForm:public Form {
public:
    BinaryTreeForm(const Vector2& window_size);
    void            add(const std::string& x)   override,
                    remove()                    override,
                    update(const int& x)        override,
                    search(const int& x)        override,
                    FetchCommandQueue()         override,
                    draw()                      override,
                    handle()                    override,
                    close()                     override;
    ~BinaryTreeForm();
private:
    Node            *m_root;
    void            insert(Node*& root, const Vector2& par, const int& x),
                    rePosition(),
                    free(),
                    free(Node* root);
    int             rePosition(Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board);
    std::vector<Node*> m_list;
};
#endif