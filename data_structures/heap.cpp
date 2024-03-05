#include "heap.hpp"

void Heap::insert(HeapNode* entry){

    if(!entry)
        return;

    heap.push_back(entry);
    auto n = heap.size();
    unsigned int parentIndex, childIndex = n - 1;

    while (childIndex != 0){

        parentIndex = (childIndex - 1) / 2;

        auto child = heap.at(childIndex);
        auto parent = heap.at(parentIndex);

        if(parent->key <= child->key)
            break;

        iter_swap(heap.begin() + parentIndex, heap.begin() + childIndex);
        childIndex = parentIndex;
    }
}

HeapNode* Heap::remove(){

    auto n = heap.size();
    if (n == 0)
        return nullptr;

    auto node = heap.at(0);
    iter_swap(heap.begin(), heap.begin()+n-1);
    heap.pop_back();
    n -= 1;
    unsigned int parent = 0, l_child = 1, r_child = 2, indx;

    while(l_child < n){

        indx = l_child;
        auto lChild = heap.at(l_child);

        if(r_child < n){

            auto rChild = heap.at(r_child);
            if(lChild->key > rChild->key)
                indx = r_child;
        }

        auto min_node = heap.at(indx);
        auto parent_node = heap.at(parent);

        if(min_node->key < parent_node->key){
            iter_swap(heap.begin() + parent, heap.begin() + indx);
            parent = indx;
            l_child = 2*parent+1;
            r_child = 2*parent+2;
        }else
            break;
    }
    return node;
}