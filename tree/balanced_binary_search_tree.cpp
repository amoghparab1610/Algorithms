#include <iostream>
#include <vector>

using namespace std;

class BinaryTreeNode{

public:
    int key=0, height=0, delta=0;
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

    void updateNode(BinaryTreeNode *node){
        if(!node) return;

        int l_height = -1, r_height = -1;
        if(node->left)
            l_height = node->left->height;
        if(node->right)
            r_height = node->right->height;
        node->height = (l_height > r_height ? l_height : r_height)+1;
        node->delta = l_height-r_height;
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

        updateNode(node);
        return rotate(node);
    }

    BinaryTreeNode* removeNode(BinaryTreeNode *node, int k){

        BinaryTreeNode* child;

        if(k < node->key) {
            child = removeNode(node->left, k);
            node->left = child;
        }
        else if(k > node->key) {
            child = removeNode(node->right, k);
            node->right = child;
        }
        else {
            auto successor = findSuccessor(node);
            updateNode(successor);
            return rotate(successor);
        }

        if(child)
            child->parent = node;

        updateNode(node);
        return rotate(node);
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
            }
            else
                removeNode(successor->parent, successor->key);

            return node;
        }
    }

    BinaryTreeNode* rightRotation(BinaryTreeNode* node){
        auto leftSubtreeOfNode = node->left;

        leftSubtreeOfNode->parent = node->parent;
        node->left = leftSubtreeOfNode->right;

        leftSubtreeOfNode->right = node;
        node->parent = leftSubtreeOfNode;

        if(leftSubtreeOfNode->right)
            leftSubtreeOfNode->right->parent = node;

        updateNode(node);
        updateNode(leftSubtreeOfNode);

        return leftSubtreeOfNode;
    }

    BinaryTreeNode* leftRotation(BinaryTreeNode* node){
        auto rightSubtreeOfNode = node->right;

        rightSubtreeOfNode->parent = node->parent;
        node->right = rightSubtreeOfNode->left;

        rightSubtreeOfNode->left = node;
        node->parent = rightSubtreeOfNode;

        if(rightSubtreeOfNode->left)
            rightSubtreeOfNode->left->parent = node;

        updateNode(node);
        updateNode(rightSubtreeOfNode);

        return rightSubtreeOfNode;
    }

    BinaryTreeNode* leftRightRotation(BinaryTreeNode* node){
        node->left = leftRotation(node->left);
        node->left->parent = node;
        return rightRotation(node);
    }

    BinaryTreeNode* rightLeftRotation(BinaryTreeNode* node){
        node->right = rightRotation(node->right);
        node->right->parent = node;
        return leftRotation(node);
    }

    BinaryTreeNode* rotate(BinaryTreeNode* node){

        if(!node || (node->delta <= 1 && node->delta >= -1))
            return node;

        if(node->delta == 2 && node->left->delta == 1)
            return rightRotation(node);

        if(node->delta == -2 && node->right->delta == -1)
            return leftRotation(node);

        if(node->delta == 2 && node->left->delta == -1)
            return leftRightRotation(node);

        return rightLeftRotation(node);
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

    void print_traversals(){
        cout << "InOrder: ";
        inorder(getRoot());
        cout << "\nPreOrder: ";
        preorder(getRoot());
        cout << "\nPostOrder: ";
        postorder(getRoot());
        cout << endl;
    }
};

/*
    Represents a single operation i.e find, insert or remove an element from
    the balanced binary search tress
*/
class Operation{
    /*
        Value of flag: {0: find, 1: insert, 2: delete}
    */
public:    
    int flag = 0, value = 0;
    Operation(int f, int val){
        flag = f;
        value = val;
    }
};

// Number of test cases
int num_test = 1;

/*
    Each test case is a sequence of operations and expected values
    Each expected value is a boolean associated with the operation
        i.e found/absent, inserted/not inserted, removed/failed to remove
*/
class TestCase{

public:    
    vector<Operation*> operations;
    vector<bool> expected;
    bool print_traversals; 
    // Print inorder, preorder, postorder traversals after each operation

    TestCase(vector<Operation*>& op, vector<bool>& exp, bool p){
        operations = op;
        expected = exp;
        print_traversals = p;
    }

    bool validate(){
        
        BinarySearchTree bst;
        Operation* operation;
        bool passed, e;
        
        for(int i = 0; i < operations.size(); i++){
            
            operation = operations.at(i);
            e = expected.at(i);
            passed = true;
            
            switch(operation->flag){
                case 0: passed = (bst.find(operation->value) == e);
                        break;
                case 1: bst.insert(operation->value);
                        break;
                case 2: bst.remove(operation->value);
                        break;
            }
            
            if(!passed)
                return false;
            if(print_traversals)
                bst.print_traversals();
        }

        return true;
    }

    void free_test_case(){
        for(auto operation: operations)
            free(operation);
    }
};

int main(){

    vector<Operation*> operations = {
                                        new Operation(1, 6),
                                        new Operation(1, 2),
                                        new Operation(1, 4),
                                        new Operation(1, 5),
                                        new Operation(1, 1),
                                        new Operation(1, 3),
                                        new Operation(2, 2),
                                        new Operation(2, 3),
                                        new Operation(2, 1),
                                        new Operation(2, 5),
                                        new Operation(2, 6),
                                        new Operation(2, 4),
                                };
    vector<bool> expected = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    auto test_case = TestCase(operations, expected, false);
    bool is_valid = test_case.validate();

    if(is_valid)
        cout << "Test case passed\n";
    else
        cout << "Test case failed\n";

    test_case.free_test_case();

    return 0;
}