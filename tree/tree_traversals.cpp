#include "tree.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

class Tree {

public:
    TreeNode* head{};
    vector<TreeNode*> nodes;
    int N = 0;

    void initialize_parents(TreeNode* node){
        for(auto& child: node->children) {
            child->parent = node;
            initialize_parents(child);
        }
    }

    void read_graph(){

        int key;
        cin >> N;

        for(int i = 0; i < N; i++){
            cin >> key;

            int c;
            vector<TreeNode*> children;
            cin >> c;
            while(c >= 0){
                children.push_back(nodes.at(c));
                cin >> c;
            }
            nodes.push_back(new TreeNode(key, children, nullptr));
        }
        head = nodes.back();
    }

    void pre_order(TreeNode* node){
        cout << node->key << " ";
        for(auto& child: node->children)
            pre_order(child);
    }

    void post_order(TreeNode* node){
        for(auto& child: node->children)
            post_order(child);
        cout << node->key << " ";
    }

    std::string encode_tree(TreeNode* node){
        if(node->children.empty())
            return "()";

        vector<std::string> subtree_enc;
        subtree_enc.reserve(node->children.size());

        for(auto& child: node->children)
            subtree_enc.push_back(encode_tree(child));

        sort(subtree_enc.begin(), subtree_enc.end());

        std::string enc;
        for(auto& child_enc: subtree_enc)
            enc += child_enc;
        enc = "(" + enc + ")";

        return enc;
    }
};

int main(){

    auto* tree = new Tree();
    tree->read_graph();
    tree->initialize_parents(tree->head);

    cout << "Pre Order: ";
    tree->pre_order(tree->head);
    cout << "\n";

    cout << "Post Order: ";
    tree->post_order(tree->head);
    cout << "\n";

    cout << "Tree Encoding: " << tree->encode_tree(tree->head) << "\n";

    free(tree);
    return 0;
}