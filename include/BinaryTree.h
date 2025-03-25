#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Form.h"
#include "GUI.h"
#include "Global.h"

enum CommandCode {
    add = 0,
    choose = 1,
    unchoose = 2,
    redraw = 3,
    erase = 4
};
class BinaryTreeForm :public Form {
public:
    BinaryTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size);
    void            add(const vector<std::string>& x)   override,
                    remove(const std::string& x)override,
                    FetchNextCommand(const std::vector<float>& codes)  override,
                    FetchPrevCommand(const std::vector<float>& codes)  override,
                    draw()                      override,
                    handle()                    override;
    ~BinaryTreeForm();
private:
    Node*           m_root;
    void            insert(Node*& root, const Vector2& par, const int& x),
                    remove(Node*& root, const int& x),
                    rePosition(),
                    draw(Node* root),
                    handle(Node* root),
                    free(),
                    free(Node* root);
    int             rePosition(Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board);
    std::vector<Node*> m_list;
};
#endif