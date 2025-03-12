#include "../include/StringTreeForm.h"
#include <cstring>
#include <iostream>
using namespace std;
SNode::SNode(Vector2* origin, const int& index):TextButton(origin) {
    init();
    setText("#");
    child = 0;
    next = 0;
    m_index = index;
    isVisible = false;
}
void SNode::setPosition(const float& x, const float& y) {
    TextButton::setPosition(x, y);
}
void SNode::setText(const std::string& str) {
    TextButton::setText(str);
    char* val = new char[str.size()+1];
    memcpy(val, str.c_str(), str.size()+1);
    data = val;
    Vector2 sz = MeasureTextEx(m_font, m_text.c_str(), m_font_size, m_spacing);
    setSize(sz.x+20, getSize().y);
}
void SNode::handle() {
    TextButton::handle();
    SlowMotion::handle();
}
void SNode::draw() {
    TextButton::draw();
    Rectangle rec = {m_position.x+1, m_position.y+1, m_size.x-2, m_size.y-2};
    if (m_origin) {
        rec.x+=m_origin->x;
        rec.y+=m_origin->y;
    }
    DrawRectangleRoundedLines(rec, m_roundness, m_segment, 1.0f, BLUE);
}
Vector2 SNode::getPosition() const {
    return TextButton::getPosition();
}
Branch::Branch(Vector2* origin) {
    size = 1;
    head = tail = new SNode(origin, -1);
    width = head->getSize().x;
}
Branch::Branch(Vector2* origin, SNode* h, SNode* t, const int& sz) {
    head = h;
    tail = t;
    tail->next = new SNode(origin, -1);
    tail->isVisible = true;
    tail = tail->next;
    size = sz+1;
    width = 0;
    while (h) {
        width+=h->getSize().x;
        h = h->next;
    }
}
void Branch::insert(SNode* prev, SNode* n) {
    size++;
    n->next = prev->next;
    prev->next = n;
    if (n->next == head) head = n;
    width += n->getSize().x;
}
StringTreeForm::StringTreeForm(const Vector2& window_size):Form(window_size) {
    m_root = 0;
}
void StringTreeForm::show() {
    show(m_root);
}
void StringTreeForm::show(Branch* root) {
    if (!root) return ;
    SNode* head = root->head;
    while (head->next) {
        cout << head->data << " " ;
        head = head->next;
    }
    cout << endl;
    head = root->head;
    if (head->child) {
        while (head) {
            show(head->child);
            head = head->next;
        }
    }
}
float StringTreeForm::reLocate(Branch* root) {
    SNode* cur = root->head;
    float old_x = cur->getPosition().x, y = cur->getPosition().y;
    float right = old_x;
    if (cur->child) {
        while (cur) {
            cur->child->head->setPosition(right, y+100);
            right = reLocate(cur->child)+50;
            cur = cur->next;
        }
        cur = root->head;
        right = right - 50;
        cout << right << " " << old_x<<" " <<root->width << endl;
        old_x  = (right + old_x)/2-root->width/2;
        cout << old_x<<endl;
    }
    while (cur) {
        cur->setDuration(m_speed/2);
        if (cur->isVisible) {
            if (root!=m_root || !root->head->child) cur->setSlowPosition(old_x, y);
            else cur->setPosition(old_x, y);
            old_x += cur->getSize().x;
        } else cur->setPosition(old_x, y);
        cur = cur->next;
    }
    return root->head->getPosition().x + root->width;
}
void StringTreeForm::reLocate() {
    m_root->head->setPosition(0, 0);
    reLocate(m_root);
}
void StringTreeForm::add(const std::string& str) {
    if (!m_root) {
        m_root = new Branch(&m_origin);
        m_root->head->m_index = 0;
        m_list.push_back(m_root->head);
    }
    insert(str);
}
void StringTreeForm::handle() {
    Form::handle();
    for (auto i:m_list) i->handle();
}
void StringTreeForm::draw() {
    Form::draw();
    for (int i = m_list.size()-1; i>=0; i--) 
        if (m_list[i]->isVisible) m_list[i]->draw();
}
void StringTreeForm::FetchCommandQueue() {
    int code = PullCommand();
    switch(code) {
        case choose: {
            int index = PullCommand();
            float dur = PullCommand();
            m_list[index]->m_normal_color = RED;
            m_clock.setDuration(dur*m_speed);
        }
            break;
        case unchoose: {
            int index = PullCommand();
            float dur = PullCommand();
            m_list[index]->m_normal_color = WHITE;
            m_clock.setDuration(dur*m_speed);
        }
            break;
        case redraw: {
            int index = PullCommand();
            float dur = PullCommand();
            m_list[index]->isVisible = true;
            reLocate();
            m_clock.setDuration(dur*m_speed);
        }
            break;
    }
}
void StringTreeForm::insert(const std::string& str) {
    if (m_root->size == max_child) {
        console.push_back("Split");
        SNode* node = split(m_root);
        PushCommand({redraw, 1.0f*node->m_index, 1});
        Branch* br = new Branch(&m_origin, node, node, 1);
        br->tail->m_index = m_list.size();
        br->tail->child = m_root;
        m_list.push_back(br->tail);
        m_root = br;
    }
    insert(m_root, str);
    show();
}
void StringTreeForm::insert(Branch* root, const std::string& str) {
    SNode* dummy = new SNode(0, -1);
    dummy->next = root->head;
    while ((dummy->next != root->tail) && (strcmp(str.c_str(), dummy->next->data)>0)) {
        PushCommand({choose, 1.0f*dummy->next->m_index,1});
        console.push_back("Next");
        PushCommand({unchoose, 1.0f*dummy->next->m_index,0});
        dummy = dummy->next;
    }
    cout << "|" << str<<endl;
    if (!dummy->next->child) {
        cout << "|" << str<<endl;
        m_list.push_back(new SNode(&m_origin, m_list.size()));
        m_list.back()->setText(str);
        console.push_back("Insert " + str);
        PushCommand({redraw, m_list.size()-1.0f, 1});
        root->insert(dummy, m_list.back());
    } else insert(dummy->next->child, str);
    cout << "|" << str<<endl;
}
SNode* StringTreeForm::split(Branch* root) {
    if (root->size!=max_child) return 0;
    SNode* cur = root->head;
    int n = max_child/2 -1;
    for (int i = 0; i<n; i++) cur = cur->next;
    SNode* head = root->head;
    root->head = cur->next;
    root->size = max_child-(n+1);

    Branch* branch = new Branch(&m_origin, head, cur, n+1);
    root->width -= branch->width - branch->tail->getSize().x;
    branch->tail->m_index = m_list.size();
    m_list.push_back(branch->tail);

    SNode* ans = new SNode(&m_origin, m_list.size());
    ans->setText(root->head->data);
    m_list.push_back(ans);
    ans->child = branch;

    return ans;
}
StringTreeForm::~StringTreeForm() {

}