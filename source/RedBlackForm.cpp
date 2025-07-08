#include "RedBlackForm.h"
#include "SettingPackage.h"
#include "raylib.h"
#include "General.h"
#include <string>
FormSetting red_fill;
extern FormSetting* setting;
extern Camera2D m_camera;

RBList::RBList() {
    root = 0;
    m_size = 0;
}
void RBList::handle() {
    handle(root);
}
void RBList::draw() {
    draw(root);
}
void RBList::update() {
    update(root, 0, 0);
}
bool RBList::empty() {
    return !m_size;
}
size_t RBList::size() const {
    return m_size;
}
int RBList::operator[](const int& index) {
    return 0;
}
void RBList::insert(const int& value) {
    if (insert(root, value)) m_size++;
}
float RBList::update(RBNode* root, float left, int level) {
	if (!root) return 0;
	float right = left+100, right_right = left;
	if (root->left) right_right = right = update(root->left, left, level+1) + 100;
	if (root->right) right_right = update(root->right, right, level+1);
	float middle;
	if (!root->left && !root->right) middle = left;
	else if (root->left && root->right) {
		middle = (root->left->getEndPoint().x + root->right->getEndPoint().x)/2;
	} else if (root->left) {
		middle = (root->left->getEndPoint().x + 50);
	} else if (root->right) {
		middle = root->right->getEndPoint().x - 50;
	}
	root->setDuration(1);
	root->setSlowPosition(middle, 100*level);
	return right_right;
}
void RBList::erase(const int& value) {
    RBNode*& tmp = find(root, value);
    if (tmp->right) {
        if (tmp->left) erase(tmp->left, tmp);
        else {
            
        }
    }
}
void RBList::free(RBNode*& root) {
    if (!root) return;
    free(root->left);
    free(root->right);
    delete root;
    root = 0;
}
RBList::~RBList() {
    free(root);
}

RBList::RBNode::RBNode(const int& val) {
    right = left = 0;
    red = false;
    value = val;
}
int RBList::RBNode::getValue() const {
    return value;
}

void RBList::draw(RBNode* root) {
    if (!root) return;
    if (root->left) DrawLineEx(root->getCenter(), root->left->getCenter(), 3, RED);
    if (root->right) DrawLineEx(root->getCenter(), root->right->getCenter(), 3, RED);
    root->draw();
    draw(root->left);
    draw(root->right);
}

void RBList::handle(RBNode* root) {
    if (!root) return;
    root->handle();
    if (root->red) root->button_setting = &red_fill;
    else root->button_setting = setting;
    handle(root->left);
    handle(root->right);    
}
void RBList::rotateLeft(RBNode*& root) {
    RBNode* tmp = root;
    root = root->right;
    tmp->right = root->left;
    root->left = tmp;
}
void RBList::rotateRight(RBNode*& root) {
    RBNode* tmp = root;
    root = root->left;
    tmp->left = root->right;
    root->right = tmp;
}
bool RBList::insert(RBNode*& root, const int& value) {
    bool ans = false;
    if (!root) {
        root = new RBNode(value);
        if (root != RBList::root) root->red = true;
        ans = true;
    }
    else {
        if (!root->red && root->right && root->right->red && root->left && root->left->red) {
            root->right->red = root->left->red = false;
            if (root!=RBList::root) root->red = true;
        }
        if (value>root->value) {
            ans = insert(root->right, value);
            if (!root->red && root->right->red) {
                if (root->right->right && root->right->right->red) {
                    rotateLeft(root);
                }
                else if (root->right->left && root->right->left->red) {
                    rotateRight(root->right);
                    rotateLeft(root);
                }
                root->red = false;
                if (root->left) root->left->red = true;
                if (root->right) root->right->red = true;
            }
        }
        else if (value<root->value)  {
            ans = insert(root->left, value);
            if (!root->red && root->left->red) {
                if (root->left->left && root->left->left->red) {
                    rotateRight(root);
                }
                else if (root->left->right && root->left->right->red) {
                    rotateLeft(root->left);
                    rotateRight(root);
                }
                root->red = false;
                if (root->left) root->left->red = true;
                if (root->right) root->right->red = true;
            }
        }
    }
    return ans;
}
void RBList::erase(RBNode*& parent) {
    if (!parent->right->left) {
        if (parent->right->red) {
            delete parent->right;
            parent->right = 0;
        }
        else {
            delete parent->right;
            parent->right = 0;
            rotateRight(parent);
        }
    }
    else {

    }
}
void RBList::erase(RBNode* root, RBNode*& k) {
    if (!root || !root->right) return;
    if (root->right->right) {
        erase(root->right, k);
    }
    else {
        swap(root->right->right, k->right);
        swap(root->right->left, k->left);
        swap(k, root->right);
        erase(root);
    }
    
}
RBList::RBNode*& RBList::find(RBNode*& root, const int& val) {
    if (!root) return root;
    if (val>root->value) return find(root->right, val);
    else if (val<root->value) return find(root->left,val);
    else return root;
}

RedBlackForm::RedBlackForm(const int& index): Form(index), size_label(&form_setting) {
    red_fill = form_setting;
    red_fill.normal_color = form_setting.hightlight_color1;

    children.push_back(&size_label);

    size_label.setPosition(m_window_size.x - 200, 100);
    size_label.setSize(150, 50);
}

void RedBlackForm::add(const vector<string>& args) {
    for (auto& i:args) 
        InsertNextMainCommand({insert, 1.0f*to_int(i), 1});
}
void RedBlackForm::remove(const string& input) {
    list.erase(to_int(input));
}
void RedBlackForm::FetchNextCommand(const vector<float>& commands) {
    int command = commands.front();
    float dur = commands.back();
    switch (command) {
        case insert: {
            list.insert(commands[1]);
            list.update();
            setDuration(dur);
        }
        break;
    }
}
void RedBlackForm::FetchPrevCommand(const vector<float>& commands) {

}
void RedBlackForm::draw() {
    BeginMode2D(m_camera);
    list.draw();
    EndMode2D();

    Form::draw();
}
void RedBlackForm::handle() {
    list.handle();
    size_label.setText(to_string(list.size()));
    Form::handle();
}