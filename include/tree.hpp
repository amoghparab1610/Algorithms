#ifndef COMPETITIVE_PROGRAMMING_TREE_HPP
#define COMPETITIVE_PROGRAMMING_TREE_HPP

#include <vector>

class TreeNode{
public:
    int key;
    std::vector<TreeNode*> children;
    TreeNode* parent{};

    inline TreeNode(int k, std::vector<TreeNode*>& c, TreeNode* p){
        key = k;
        children = c;
        parent = p;
    }

    inline TreeNode(int k, TreeNode* p){
        key = k;
        parent = p;
    }

    inline void setChildren(std::vector<TreeNode*>& c) { children = c; }
};

#endif
