#ifndef COMPETITIVE_PROGRAMMING_HEAP_H
#define COMPETITIVE_PROGRAMMING_HEAP_H

#include <vector>
#include <cassert>

class HeapNode{

public:
    long key;
    std::pair<unsigned int, unsigned int> edge;

    inline HeapNode(long k, std::pair<unsigned int, unsigned int> p){
        key = k;
        edge = p;
    }
};

class Heap{

public:
    std::vector<HeapNode*> heap;

    void insert(HeapNode*);

    HeapNode* remove();

    [[nodiscard]] unsigned int inline getSize() const{
        return heap.size();
    }
};

#endif //COMPETITIVE_PROGRAMMING_HEAP_H
