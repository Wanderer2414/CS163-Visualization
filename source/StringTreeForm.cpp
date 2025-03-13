#include "../include/StringTreeForm.h"
#include "../include/General.h"
#include <cstring>
#include <iostream>

using namespace std;
using namespace Ex;
void Node::init() {
    TextButton::init();
    m_text = "#";
}
void Node::update_text() {
    m_size = MeasureTextEx(m_font, m_text.c_str(), m_font_size, m_spacing);
    m_size = m_size + Vector2{20, 20};
    TextButton::update_text();
}
void Node::draw() {
    TextButton::draw();
    DrawRectangleRoundedLines({m_position.x, m_position.y, m_size.x, m_size.y}, m_roundness, m_segment, 1.0f, BLACK);
}
void Node::handle() {
    TextButton::handle();
}
Branch::Branch() {
    head = tail = new Node();
    m_size = 1;
};
Branch::Branch(string name) { 
    head = tail = new Node();
    head = new Node(name, head);
    m_size = 2;
}
Branch::Branch(Branch* cur) {
    head = tail = new Node();
    head->child = cur;
    m_size = 1;
}
Branch::Branch(Node* m_head, Node* m_tail, const unsigned char& size) {
    head = m_head;
    tail = m_tail;
    m_size = size;
}
unsigned char Branch::size() {
    return m_size;
}
Node* Branch::getHead() {
    return head;
}
Node* Branch::getTail() {
    return tail;
}

void Branch::push_front(Node* node) {
    node->next = head;
    head = node;
    m_size++;
}

void Branch::insert(Node* prev, Node* node) {
    node->next = prev->next;
    if (prev->next == head) head = node;
    prev->next = node;
    m_size++;
}
void Branch::free() {
    free(this);
}
void Branch::free(Branch* root) {
    if (!root) return;
    Node* cur = root->head, *prev = 0;
    while (cur!=root->getTail()) {
        free(cur->child);
        prev = cur;
        cur = cur->next;
        delete prev;
    }
    free(cur->child);
    delete cur;
    delete root;
}

Branch::~Branch() {
}

Node* Branch::getMiddlePrev() {
    if (!head) return 0;
    if (!head->next) return head;
    Node* cur = head;
    for (int i = (m_size-1)/2-1; i>0; i--) {
        cur = cur->next;
    }
    return cur;
}
Node* Ex::NameTree::split(Branch* root, const bool& isLeaf) {
    Node* prev = root->getMiddlePrev(), *mid = prev->next;
    if (!mid) return prev;
    if (isLeaf) {
        Node* ans = new Node(mid->value);
        prev = prev->next = new Node();

        int sum = root->m_size+1;
        root->m_size = root->m_size/2+1;
        ans->child = new Branch(root->head, prev, sum-root->m_size);
        root->head = mid;
        ans->child->next = root;
        ans->child->prev = root->prev;
        if (root->prev) root->prev->next = ans->child;
        root->prev = ans->child;
        return ans;
    } else {
        root->m_size/=2;
        Branch* first = new Branch(root->head, prev, root->m_size);
        first->tail = first->tail->next = new Node();

        first->tail->child = mid->child;
        mid->child = first;
        root->head = mid->next;
        mid->next = 0;
        first->next = root;
        first->prev = root->prev;
        root->prev = first;
        return mid;
    }
}

Ex::NameTree::NameTree(const Vector2& window_size): Form(window_size) {
}
void Ex::NameTree::init() {
    Form::init();
    m_root = new Branch();
}
void Ex::NameTree::insert(string name) {
    insert(m_root, name);
}
void Ex::NameTree::add(const std::string& str) {
    insert(str);
    show();
    ReLocate();
}
void Ex::NameTree::insert(Branch*& root, string name) {
    if (root->size() == max_size) {
        Node* tmp = split(root, m_height==1);
        Branch* branch = new Branch(root);
        branch->push_front(tmp);
        root = branch;
        m_height++;
    }
    int i = 0;
    Node* cur = new Node(root->getHead()), *tmp = cur;
    while (cur->next && cur->next!=root->getTail() && name >= cur->next->value)
        if (name == cur->next->value) return ; 
        else cur = cur->next;
    if (!cur->next->child) {
        root->insert(cur,new Node(name));
    } else {
        if (cur->next->child->size() == max_size) {
            Node* tmp = split(cur->next->child, !cur->next->child->getHead()->child);
            root->insert(cur, tmp);
            if (tmp->value > name) insert(tmp->child, name);   
            else insert(tmp->next->child, name);
        } else insert(cur->next->child, name);
    }
    delete tmp;
}
void Ex::NameTree::add_from_file(const std::string& link) {
    vector<string> ans = readFromFileStr(link);
    for (auto& i:ans) insert(i);
    ReLocate();
}
void Ex::NameTree::draw(Branch* root) {
    if (!root) return;
    Node* head = root->head;
    if (root->next) {
        if (root->head->child) {
            Vector2 sz = {0, root->head->getSize().y/2};
            DrawLineEx(root->vertex+sz, root->next->vertex+sz, 1.5f, WHITE);
        }
    }
    while (head) {
        if (head->child) {
            draw(head->child);
            DrawLineEx(head->getPosition()+Vector2({0, head->getSize().y}), head->child->vertex, 1.5f, WHITE);
        }
        head->draw();
        head = head->next;
    }
}
void Ex::NameTree::show() {
    show(m_root, 1);
}
void Ex::NameTree::ReLocate() {
    ReLocate(m_root, 0, 0);
}
float Ex::NameTree::ReLocate(Branch* root, const float& left, const float& y) {
    float start = left;
    Node* head = root->getHead();
    if (head->child) 
        while (head) {
            start = ReLocate(head->child, start, y+100);
            start+=50;
            head = head->next;
        }
    float mid = (left+start)/2, end = mid;
    head = root->getHead();
    while (head) {
        head->setPosition(end, y);
        end+=head->getSize().x;
        head = head->next;
    }
    root->vertex = {(end+mid)/2, y};
    if (root->head->child) return start;
    else return end;
}
void Ex::NameTree::handle() {
    Form::handle();
    handle(m_root);
}
void Ex::NameTree::close() {
    if (m_root) {
        m_root->free();
        m_root = 0;
    }
}
void Ex::NameTree::handle(Branch* root) {
    if (!root) return ;
    Node* head = root->head;
    while (head) {
        Rectangle rec = {head->getPosition().x, head->getPosition().y, head->getSize().x, head->getSize().y};
        head->m_is_hovered = CheckCollisionPointRec(GetMousePosition(), TransToCameraRec(m_camera, rec));
        head->m_is_pressed = head->isHovered() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        head = head->next;
    }
    head = root->head;
    if (head->child) {
        while (head) {
            handle(head->child);
            head = head->next;
        }
    };
}
void Ex::NameTree::draw() {
    Form::draw();
    BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
        draw(m_root);
    EndScissorMode();
    EndMode2D();
}
void Ex::NameTree::show(Branch* root, const int& indent) {
    if (!root) return;
    Node* cur = root->getHead();
    while (cur) {
        show(cur->child, indent+1);
        if (cur->value.size() && indent==m_height) {
            cout << cur->value << endl;
        }
        cur = cur->next;
    }
}
Ex::NameTree::~NameTree() {
    if (m_root) {
        m_root->free();
        m_root = 0;
    }
}