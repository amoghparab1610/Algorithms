#include <iostream>
#include <vector>

using namespace std;

/*
    Each Binary Tree node has links to left and right subtrees, and its parent
*/
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

/*
    Binary Tree consists of
        i. head or root node,
        ii. vector of all the nodes in the tree,
        iii. total number of nodes
*/
class BinaryTree {

public:
    BinaryTreeNode* head{};
    vector<BinaryTreeNode*> nodes;
    int N = 0;

    /*
        Initialize links to parent node 
    */
    void initialize_parents(BinaryTreeNode* node){
        if(node->left) {
            node->left->parent = node;
            initialize_parents(node->left);
        }
        if(node->right) {
            node->right->parent = node;
            initialize_parents(node->right);
        }
    }


    /*
        N: No of nodes in the binary tree
        key: Integer value
        left: Index (into the vector) of the left child of this node
                -1 if left child doesn't exist
        right: Index (into the vector) of the right child of this node
                -1 if right child doesn't exist
    */
    void read_graph(){

        int key, left, right;

        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> key >> left >> right;
            nodes.push_back(new BinaryTreeNode(key, (left == -1 ? nullptr : nodes.at(left)),
                                         (right == -1 ? nullptr : nodes.at(right)), nullptr));
        }
        head = nodes.back();
    }

    /*
        Visit the current node before visiting the left and right subtrees
    */
    void pre_order(BinaryTreeNode* node){
        cout << node->key << " ";
        if(node->left)
            pre_order(node->left);
        if(node->right)
            pre_order(node->right);
    }

    /*
        Visit the left subtree, current node and then the right subtree
    */
    void in_order(BinaryTreeNode* node){
        if(node->left)
            in_order(node->left);
        cout << node->key << " ";
        if(node->right)
            in_order(node->right);
    }

    /*
        Visit the current node after visiting the left and right subtrees
    */
    void post_order(BinaryTreeNode* node){
        if(node->left)
            post_order(node->left);
        if(node->right)
            post_order(node->right);
        cout << node->key << " ";
    }
};

int main(){

    auto* tree = new BinaryTree();
    tree->read_graph();
    tree->initialize_parents(tree->head);

    cout << "Pre Order: ";
    tree->pre_order(tree->head);
    cout << "\n";

    cout << "In Order: ";
    tree->in_order(tree->head);
    cout << "\n";

    cout << "Post Order: ";
    tree->post_order(tree->head);
    cout << "\n";

    free(tree);
    return 0;
}