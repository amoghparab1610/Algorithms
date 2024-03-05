#include "tree.hpp"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Tree {

public:

    unsigned int* degree{}, N=0;
    vector<set<unsigned int>*> edges;
    vector<set<unsigned int>*> adj_list;
    set<unsigned int> centers;
    bool* visited;

    void read_tree(){

        unsigned int a, b;

        cin >> N;
        edges.reserve(N);
        degree = new unsigned int [N];
        visited = new bool[N];

        for(unsigned int i = 0; i < N; i++) {
            edges.push_back(new set<unsigned int>());
            degree[i] = 0;
            visited[i] = false;
        }

        for(unsigned int i = 0; i < N-1; i++){
            cin >> a >> b;
            edges.at(a)->insert(b);
            edges.at(b)->insert(a);
            degree[a] += 1;
            degree[b] += 1;
        }
    }

    void copy_edges(){
        adj_list.reserve(N);
        for(unsigned int i = 0; i < N; i++) {
            adj_list.push_back(new set<unsigned int>());
            for(unsigned int v: *edges.at(i))
                adj_list.back()->insert(v);
        }
    }

    void find_tree_centers(){

        for(unsigned int i = 0; i < N; i++)
            centers.insert(i);

        while(centers.size() > 2){

            vector<unsigned int> degree_one_vertices;
            for(auto u: centers){
                if(degree[u] == 1)
                    degree_one_vertices.push_back(u);
            }

            for(auto u: degree_one_vertices){
                auto v = *edges.at(u)->begin();
                edges.at(u)->erase(v);
                edges.at(v)->erase(u);
                degree[u] -= 1;
                degree[v] -= 1;
                centers.erase(u);
            }
        }
    }

    TreeNode* root_tree(unsigned int k, TreeNode* parent, bool* visited){

        vector<TreeNode*> children;
        visited[k] = true;
        auto* node = new TreeNode(k, parent);

        for(auto v: *adj_list.at(k)){
            if(!visited[v])
                children.push_back(root_tree(v, node, visited));
        }

        node->setChildren(children);
        return node;
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
};

int main() {

    auto *tree = new Tree();
    tree->read_tree();
    tree->copy_edges();
    tree->find_tree_centers();

    cout << "Tree Centers: ";
    for(auto center: tree->centers)
        cout << " " << center;
    cout << "\n";

    auto* root = tree->root_tree(*tree->centers.begin(), nullptr, tree->visited);

    cout << "Pre Order Traversal: ";
    tree->pre_order(root);
    cout << "\n";

    cout << "Post Order Traversal: ";
    tree->post_order(root);
    cout << "\n";

    free(tree);
    return 0;
}