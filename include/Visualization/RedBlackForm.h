#ifndef RED_BACK_H
#define RED_BACK_H
#include "Form.h"
#include "GUI.h"
#include "Label.h"
#include "SettingPackage.h"
#include "raylib.h"
#include <cstddef>

class RBList: public Controller {
public:
    RBList();
    RBList(const int& value);
    virtual void    handle()    override,
                    draw()      override,
                    update()    override;
    bool            empty();
    size_t          size() const;
    int             operator[](const int& index);
    void            insert(const int& value),
                    erase(const int& value);
    ~RBList();
private:
    class RBNode: public Node {
        public:
            RBNode(const int& value = 0);
            int             getValue() const            override;
            bool            red;
            RBNode          *right, *left;
            int             value;
        private:
    };
    RBNode* root;
    int     defaultValue;
    size_t  m_size;

    void    draw(RBNode* root),
            handle(RBNode* root);
    float   update(RBNode* root, float left, int level);

    bool    insert(RBNode*& root, const int& val);

    RBNode*&find(RBNode*& root, const int& val);

    void    rotateRight(RBNode*& root),
            rotateLeft(RBNode*& root),
            rotateLeftRight(RBNode*& root),
            rotateRightLeft(RBNode*& root),
            free(RBNode*& root),
            erase(RBNode*& root),
            erase(RBNode* root, RBNode*& k);
};

class RedBlackForm: public Form {
public:
    RedBlackForm(const int& index);
    enum Code {
        insert,
    };
    void updateLocate();

    virtual void    add(const vector<string>& input) override,
                    remove(const string& input) override;

    virtual void    FetchNextCommand(const vector<float>& commands) override,
                    FetchPrevCommand(const vector<float>& commands) override,
                    
                    draw()      override,
                    handle()    override;

    private:
        Label       size_label;
        RBList list;
};
#endif