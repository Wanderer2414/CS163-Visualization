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
    BST::Node*      m_root;
    void            insert(BST::Node*& root, const Vector2& par, const int& x),
                    remove(BST::Node*& root, const int& x),
                    rePosition(),
                    draw(BST::Node* root),
                    handle(BST::Node* root),
                    free(),
                    free(BST::Node* root);
    int             rePosition(BST::Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board);
    std::vector<BST::Node*> m_list;
};
#endif