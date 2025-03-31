#include "../include/MinHeap.h"
#include <utility>

MinHeap::MinHeap(){

}
void MinHeap::MinHeapify(const int& index) {
    int i = index;
    while (true) {
        int right = 2*i+1;
        int left = 2*i+2;
        if (right< data.size() && data[right] < data[i]) {
            if (left < data.size() && data[left]<data[right]) {
                swap(data[left], data[i]);
                i = left;
            } else {
                swap(data[right], data[i]);
                i = right;
            }
        } else if (left < data.size() && data[left] < data[i]) {
            swap(data[left], data[i]);
            i = left;
        } else break;
    }
}
void MinHeap::Insert(const Path& path) {
    data.push_back(path);
    int i = data.size()-1;
    while (i) {
        int par = (i-1)/2;
        if (data[i]<data[par]) swap(data[i], data[par]);
        i = par;
    }
}
void MinHeap::swap(Path& a, Path& b) {
    std::swap(a, b);
}
void MinHeap::erase(const int& index) {
    swap(data[index], data.back());
    data.pop_back();
    MinHeapify(index);
}
void MinHeap::clear() {
    data.clear();
}
Path MinHeap::front() const {
    return data[0];
}
Path MinHeap::pop() {
    Path ans = data[0];
    swap(data[0], data.back());
    data.pop_back();
    MinHeapify(0);
    return ans;
}
Path MinHeap::operator[](const int& index) const {
    return data[index];
}
bool Path::operator<(const Path& a) {
    if (weight<a.weight) return true;
    else if (weight > a.weight) return false;
    else if (start < a.start) return true;
    else if (start > a.start) return false;
    else if (end < a.end) return true;
    else return false;
}
bool Path::operator>(const Path& a) {
    if (weight > a.weight) return true;
    else if (weight < a.weight) return false;
    else if (start > a.start) return true;
    else if (start < a.start) return false;
    else if (end > a.end) return true;
    else return false;
}
bool Path::operator==(const Path& a) {
    return weight==a.weight && start == a.start && end == a.end;
}
int MinHeap::size() const {
    return data.size();
}
