#include "DSU.h"

DSU::DSU(const int& size) {
    data.resize(size,0);
    for (int i = 0; i<size; i++) data[i] = new Node(i);
}
bool DSU::check(const int& i, const int& j) {
    int root_i = root(i), root_j = root(j);
    return root_i == root_j;
}
int DSU::parent(const int& i) const {
    if (data[i]->next) return data[i]->next->value;
    else return -1;
}
int DSU::root(const int& i) {
    Node* cur = data[i];
    while (cur->next) cur = cur->next;
    if (cur != data[i]) data[i]->next = cur;
    return cur->value;
}
void DSU::match(const int& i, const int& j) {
    data[i]->next = data[j];
}
void DSU::join(const int& i, const int& j) {
    int root_i = root(i);
    int root_j = root(j);
    if (root_i!=root_j) data[root_i]->next = data[root_j];
}
void DSU::clear() {
    for (int i = 0; i<data.size(); i++) delete data[i];
    data.clear();
}
DSU::~DSU() {
    for (int i = 0; i<data.size(); i++) delete data[i];
    data.clear();
}