#ifndef AVLTREE_H
#define AVLTREE_H

#include "Form.h"
#include "AVLNode.h"
#include <map>
#include "Global.h"
#include "CommandCode.h"
#include "Form.h"

class AVLTreeForm : public Form {
public:
    AVLTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size);
    void            add(const vector<std::string>& x)   override,
        remove(const std::string& x)override,
        FetchNextCommand(const std::vector<float>& codes)  override,
        FetchPrevCommand(const std::vector<float>& codes)  override,
        draw()                      override,
        handle()                    override;
    bool isAnimationDone = false;
    ~AVLTreeForm();
private:
    AVLNode* m_root;
    AVLNode* rotateRight(AVLNode* root);
    AVLNode* rotateLeft(AVLNode* root);
    AVLNode* insert(AVLNode*& root, const Vector2& par, const int& x);
    AVLNode*& findNode(AVLNode*& root, int value);
    void            remove(AVLNode*& root, const int& x),
        rePosition(),
        draw(AVLNode* root),
        handle(AVLNode* root),
        free(),
        free(AVLNode* root);
    int             rePosition(AVLNode* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board);
    int             getHeight(AVLNode* root), getBalanceFactor(AVLNode* root);
    std::vector<AVLNode*> m_list;
};

#endif