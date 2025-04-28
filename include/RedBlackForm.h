#ifndef RED_BACK_H
#define RED_BACK_H
#include "Form.h"
#include "GUI.h"
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
            RBNode();
            int             getValue() const            override;
            virtual void    setValue(const int& val)    override;
            Node            *right, *left;
            int             value;
        private:
    };
    RBNode* root;
    int     defaultValue;
    size_t  m_size;
};

class RedBlackForm: public Form {
public:
    RedBlackForm(const int& index);

    void updateLocate();

    virtual void add(const vector<string>& input) override;

    virtual void FetchNextCommand(const vector<float>& commands) override,
                FetchPrevCommand(const vector<float>& commands) override;

    private:
        RBList list;
};
#endif