#ifndef MINHEAP_H
#define MINHEAP_H

#include "Global.h"

struct Path {
    int start = 0, end = 0;
    int weight;
    int index;
    bool operator<(const Path& b);
    bool operator>(const Path& b);
    bool operator==(const Path& b);
};

class MinHeap {
public:
    MinHeap();
    int                     size() const;
    virtual void            MinHeapify(const int& index),
                            Insert(const Path& path),
                            erase(const int& index),
                            clear();
    
    virtual Path            front() const, pop(),
                            operator[](const int& index) const;
protected:
    vector<Path> data;
    virtual void swap(Path& a, Path& b);
};

#endif