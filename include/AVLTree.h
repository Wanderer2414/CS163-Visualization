#ifndef AVLTREE_H
#define AVLTREE_H

#include "Form.h"
#include "GUI.h"
#include <map>
#include "Global.h"
#include "CommandCode.h"

class AVLTreeForm : public Form {
public:
    AVLTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size);
    void            add(const vector<std::string>& x)   override,
                    remove(const std::string& x)override,
                    FetchNextCommand(const std::vector<float>& codes)  override,
                    FetchPrevCommand(const std::vector<float>& codes)  override,
                    draw()                      override,
                    handle()                    override;
    ~AVLTreeForm();
private:
    Node* m_root;
    Node* rotateRight(Node* root);
    Node* rotateLeft(Node* root);
    Node* insert(Node*& root, const Vector2& par, const int& x);
    Node*& findNode(Node*& root, int value);
    void            remove(Node*& root, const int& x),
                    rePosition(),
                    draw(Node* root),
                    handle(Node* root),
                    free(),
                    free(Node* root);
    int             rePosition(Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board);
    int             getHeight(Node* root), getBalanceFactor(Node* root);
    std::vector<Node*> m_list;
};

#endif