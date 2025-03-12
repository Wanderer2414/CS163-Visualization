#include "../include/BinaryTree.h"
#include "../include/General.h"
BinaryTreeForm::BinaryTreeForm(const Vector2& window_size):Form(window_size) {
    m_root = 0;
};
void BinaryTreeForm::add(const std::string& x) {
    insert(m_root, {0,0}, to_int(x));
}
void BinaryTreeForm::insert(Node*& root, const Vector2& par, const int& x) {
    if (!root) {
        root = new Node(m_list.size(), &m_origin, x);
        root->setPosition(par.x, par.y);
        m_list.push_back(root);
        console.push_back("Add " + *root->getText());
        PushCommand({CommandCode::add, 1.0f*root->getIndex(), 1});
        return ;
    }
    PushCommand({CommandCode::choose, 1.0f*root->getIndex(), 1});
    console.push_back("Comparing " + *root->getText());
    PushCommand({CommandCode::unchoose, 1.0f*root->getIndex(), 0});
    if (x<root->getValue()) {
        console.push_back("Go to left");
        insert(root->left, root->getPosition(), x);
    }
    else {
        console.push_back("Go to right");
        insert(root->right, root->getPosition(), x);
    }
}
void BinaryTreeForm::add(std::vector<int>& x) {

}
void BinaryTreeForm::remove() {

}
void BinaryTreeForm::update(const int& x) {

}
void BinaryTreeForm::search(const int& x) {

}
void BinaryTreeForm::FetchCommandQueue() {
    int command = PullCommand();
    if (command == -1) return ;
    float dur = 0;
    switch (command)
    {
    case CommandCode::add: {
        int index = PullCommand();
        dur = PullCommand();
        console.setFillLine(console.getFillLine()+1);
        m_list[index]->isVisible = true;
        rePosition();
        m_clock.setDuration(dur*m_speed);
    }
        break;
    case CommandCode::choose: {
        int index = PullCommand();
        dur = PullCommand();
        console.setFillLine(console.getFillLine()+1);
        m_list[index]->m_normal_color = RED;
        m_clock.setDuration(dur*m_speed);
    }
        break;
    case CommandCode::unchoose: {
        int index = PullCommand();
        dur = PullCommand();
        console.setFillLine(console.getFillLine()+1);
        m_list[index]->m_normal_color = WHITE;
        m_clock.setDuration(dur*m_speed);
    }
        break;
    case CommandCode::compare: {
    }
        break;
    default:
        break;
    }
    if (!dur) FetchCommandQueue();
}
int BinaryTreeForm::rePosition(Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board) {
    if (!root) return index;
    if (board[{index,level}]) {
        while (board[{index, level}]) index+=2;
    }
    float left = rePosition(root->left, level+1, index-1, board) + 1;
    float right = rePosition(root->right, level+1, left+1, board) - 1;
    index = (left+right)/2;
    board[{index, level}] = true;
    if (root->isVisible) {
        root->setDuration(m_speed/2);
        root->setSlowPosition(index*50, level*50);
    }
    return right;
}
void BinaryTreeForm::rePosition() {
    if (!m_root) return;
    std::map<std::pair<float, int>, bool> board;
    rePosition(m_root, 0, 0, board);
}
void BinaryTreeForm::draw() {
    Form::draw();
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
        for (int i =0; i<m_list.size(); i++)
            if (m_list[i]->isVisible) m_list[i]->draw();
    EndScissorMode();
}
void BinaryTreeForm::handle() {
    Form::handle();
    for (int i = 0; i<m_list.size(); i++) m_list[i]->handle();
}
void BinaryTreeForm::free() {
    free(m_root);
    m_root = 0;
    m_list.clear();
}
void BinaryTreeForm::free(Node* root) {
    if (!root) return ;
    free(root->left);
    free(root->right);
    delete root;
}
void BinaryTreeForm::close() {
    Form::close();
    free();
}
BinaryTreeForm::~BinaryTreeForm() {

}