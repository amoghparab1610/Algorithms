#include <iostream>
#include <vector>

using namespace std;

class BinaryTreeNode{

public:
    int key=0;
    BinaryTreeNode *left{}, *right{}, *parent{};
    BinaryTreeNode(int k, BinaryTreeNode *l, BinaryTreeNode *r, BinaryTreeNode *p){
        key = k;
        left = l;
        right = r;
        parent = p;
    }
};

class BinarySearchTree{

    BinaryTreeNode *root{};
    unsigned int N=0;

    bool findNode(BinaryTreeNode *node, int k){
        if(!node)
            return false;
        if(node->key == k)
            return true;
        return (k < node->key ? findNode(node->left, k) : findNode(node->right, k));
    }

    BinaryTreeNode* insertNode(BinaryTreeNode *node, int k){
        if(!node)
            return new BinaryTreeNode(k, nullptr, nullptr, nullptr);

        BinaryTreeNode* child{};
        if(k < node->key) {
            child = insertNode(node->left, k);
            node->left = child;
        }
        else if(k > node->key) {
            child = insertNode(node->right, k);
            node->right = child;
        }
        if (child)
            child->parent = node;

        return node;
    }

    BinaryTreeNode* removeNode(BinaryTreeNode *node, int k){
        BinaryTreeNode* child{};
        if(k < node->key) {
            child = removeNode(node->left, k);
            node->left = child;
        }
        else if(k > node->key) {
            child = removeNode(node->right, k);
            node->right = child;
        } else
            return findSuccessor(node);

        if(child)
            child->parent = node;

        return node;
    }

    BinaryTreeNode* findSuccessor(BinaryTreeNode* node){

        if(!(node->left || node->right)) {
            free(node);
            return nullptr;
        }
        else if(!node->right) {
            auto successor = node->left;
            free(node);
            return successor;
        }
        else if(!node->left) {
            auto successor = node->right;
            free(node);
            return successor;
        }
        else{
            // Successor is the leftmost node of right subtree if both subtrees are non-empty
            auto successor = node->right;
            while((successor->left))
                successor = successor->left;

            node->key = successor->key;

            if(node->right == successor){
                node->right = successor->right;
                if(successor->right)
                    successor->right->parent = node;
                free(successor);
            }else
                removeNode(successor->parent, successor->key);

            return node;
        }
    }

public:
    void insert(int k){
        root = insertNode(root, k);
        N += 1;
    }

    bool remove(int k){
        if(find(k)){
            root = removeNode(root, k);
            N -= 1;
            return true;
        }
        return false;
    }

    void preorder(BinaryTreeNode* node){
        if(!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(BinaryTreeNode* node){
        if(!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void postorder(BinaryTreeNode* node){
        if(!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }

    bool find(int k){
        return findNode(root, k);
    }

    BinaryTreeNode* getRoot(){
        return root;
    }

    [[nodiscard]] unsigned int getNumberOfNodes() const{
        return N;
    }
};

int main(){

    auto bst = new BinarySearchTree();
    bst->insert(5);
    bst->insert(2);
    bst->insert(4);
    bst->insert(8);
    bst->insert(1);
    bst->insert(3);

    cout << "InOrder: ";
    bst->inorder(bst->getRoot());
    cout << "\nPreOrder: ";
    bst->preorder(bst->getRoot());
    cout << "\nPostOrder: ";
    bst->postorder(bst->getRoot());

    vector<int> removal_order = {2, 3, 5, 4, 8, 1};
    for(auto val: removal_order){
        auto res = bst->remove(val);
        if(res)
            cout << "\nNode with value " << val << " removed successfully\n";
        else
            cout << "Node with value " << val << " not found\n";

        cout << "InOrder: ";
        bst->inorder(bst->getRoot());
        cout << "\nPreOrder: ";
        bst->preorder(bst->getRoot());
        cout << "\nPostOrder: ";
        bst->postorder(bst->getRoot());
    }

    return 0;
}