#ifndef COMPETITIVE_PROGRAMMING_TREE_H
#define COMPETITIVE_PROGRAMMING_TREE_H

#include <vector>

class BinaryTreeNode{
public:
    int key;
    BinaryTreeNode* left{}, *right{}, *parent{};

    inline BinaryTreeNode(int k, BinaryTreeNode* l, BinaryTreeNode* r, BinaryTreeNode* p){
        key = k;
        left = l;
        right = r;
        parent = p;
    }
};

#endif
