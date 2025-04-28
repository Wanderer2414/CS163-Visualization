#include "RedBlackForm.h"
#include "SettingPackage.h"
#include "raylib.h"

RBList::RBList() {
    root = 0;
    m_size = 0;
}
void RBList::handle() {

}
void RBList::draw() {

}
void RBList::update() {

}
bool RBList::empty() {
    return !m_size;
}
size_t RBList::size() const {
    return m_size;
}
int RBList::operator[](const int& index) {

}
void RBList::insert(const int& value) {

}
void RBList::erase(const int& value) {

}
RBList::~RBList() {

}

RBList::RBNode::RBNode() {
    right = left = 0;
    value = 0;
}
int RBList::RBNode::getValue() const {

}
void RBList::RBNode::setValue(const int& val) {

}

RedBlackForm::RedBlackForm(const int& index):
    Form(index) {
}

void RedBlackForm::add(const vector<string>& args) {

}

void RedBlackForm::FetchNextCommand(const vector<float>& commands) {

}
void RedBlackForm::FetchPrevCommand(const vector<float>& commands) {

}