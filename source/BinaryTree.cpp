#include "../include/BinaryTree.h"
#include "../include/General.h"
#include <cmath>
using namespace BST;
BinaryTreeForm::BinaryTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size) :
    Form(index, form_setting, window_size) {
    m_root = 0;
};
void BinaryTreeForm::add(const vector<std::string>& vec) {
    for (int i = vec.size()-1; i>=0; i--) {
        console.InsertNextMainCommand("Add " + vec[i]);
        InsertNextMainCommand({ CommandCode::add, 1.0f * to_int(vec[i]), 1 });
    }
}
void BinaryTreeForm::insert(Node*& root, const Vector2& par, const int& x) {
    if (!root) {
        root = new Node(m_list.size(), x);
        root->button_setting = &form_setting;
        root->text_setting = &form_setting;
        root->setPosition(par.x, par.y);
        m_list.push_back(root);
        InsertNextSubCommand({ CommandCode::redraw, 1.0f });
        return;
    }
    console.InsertNextSubCommand("Compare with " + std::to_string(root->getValue()));
    InsertNextSubCommand({ CommandCode::choose, 1.0f * root->getIndex(), 1 });
    InsertNextSubCommand({ CommandCode::unchoose, 1.0f * root->getIndex(), 0 });
    if (x < root->getValue()) {
        insert(root->left, root->getEndPoint(), x);
    }
    else {
        insert(root->right, root->getEndPoint(), x);
    }
}
void BinaryTreeForm::remove(Node*& root, const int& x) {
    if (!root) return;
    if (root->getValue() < x)  remove(root->right, x);
    else if (root->getValue() > x) remove(root->left, x);
    else {
        delete root;
        root = 0;
    }
}
void BinaryTreeForm::remove(const std::string& str) {
    InsertNextMainCommand({ CommandCode::erase,1.0f * to_int(str) });
}

void BinaryTreeForm::FetchNextCommand(const std::vector<float>& command) {
    if (command.empty()) return;
    switch ((int)command[0])
    {
        case CommandCode::add: {
            insert(m_root, { 0,0 }, command[1]);
            setDuration(0);
        }
            break;
        case CommandCode::choose: {
            console.goDown();
            // m_list[command[1]]->m_normal_color = RED;
            setDuration(command[2]);
        }
            break;
        case CommandCode::unchoose: {
            // m_list[command[1]]->m_normal_color = WHITE;
            setDuration(command[2]);
        }
            break;
        case CommandCode::redraw: {
            console.goDown();
            rePosition();
            setDuration(command[1]);
        }
            break;
        case CommandCode::erase: {
            remove(m_root, command[1]);
        }
            break;
        default:
            break;
    }
}
void BinaryTreeForm::FetchPrevCommand(const std::vector<float>& command) {
    switch ((int)command[0])
    {
    case CommandCode::add: {
        remove(m_root, command[1]);
        rePosition();
        setDuration(command[2]);
        console.goUp();
    }
                         break;
    case CommandCode::choose: {
        // m_list[command[1]]->m_normal_color = WHITE;
        setDuration(0);
    }
                            break;
    case CommandCode::unchoose: {
        // m_list[command[1]]->m_normal_color = RED;
        setDuration(command[2]);
    }
                              break;
    case CommandCode::erase: {
        insert(m_root, { 0,0 }, command[1]);
        rePosition();
        console.goUp();
    }
                           break;
    default:
        break;
    }
}
int BinaryTreeForm::rePosition(Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board) {
    if (!root) return index;
    if (board[{index, level}]) {
        while (board[{index, level}]) index += 2;
    }
    float left = rePosition(root->left, level + 1, index - 1, board) + 1;
    float right = rePosition(root->right, level + 1, left + 1, board) - 1;
    index = (left + right) / 2;
    board[{index, level}] = true;
    root->setDuration(getSpeed() / 2);
    root->setSlowPosition(index * 50, level * 50);
    return right;
}
void BinaryTreeForm::rePosition() {
    if (!m_root) return;
    std::map<std::pair<float, int>, bool> board;
    rePosition(m_root, 0, 0, board);
}
void BinaryTreeForm::draw() {
    Form::draw();
    BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
    draw(m_root);
    EndScissorMode();
    EndMode2D();
}
void BinaryTreeForm::draw(Node* root) {
    if (!root) return;
    if (root->left) {
        DrawLineEx(root->getCenter(), root->left->getCenter(), 2.0f, root->button_setting->normal_color);
        draw(root->left);
    }
    if (root->right) {
        DrawLineEx(root->getCenter(), root->right->getCenter(), 2.0f, root->button_setting->normal_color);
        draw(root->right);
    }
    root->draw();
}
void BinaryTreeForm::handle() {
    Form::handle();
    handle(m_root);
}
void BinaryTreeForm::handle(Node* root) {
    if (!root) return;
    root->handle();
    if (root->left) handle(root->left);
    if (root->right) handle(root->right);
}
void BinaryTreeForm::free() {
    free(m_root);
    m_root = 0;
    m_list.clear();
}
void BinaryTreeForm::free(Node* root) {
    if (!root) return;
    free(root->left);
    free(root->right);
    delete root;
}

BinaryTreeForm::~BinaryTreeForm() {
    free();
}