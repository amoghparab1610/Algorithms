#include "tree.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

class Tree {

public:
    TreeNode* head{};
    vector<TreeNode*> nodes;
    int *tour_nodes, *tour_depth, *depth, *last, tour_index = 0;
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
        tour_nodes = new int[2*N+1];
        tour_depth = new int[2*N+1];
        depth = new int[N];
        last = new int[N];
    }

    int calculate_depth(TreeNode* node){
        if(node->children.empty()){
            depth[node->key] = 0;
            return 0;
        }

        int maxDepth = 0;
        for(auto& child: node->children){
            auto d = calculate_depth(child);
            if(d > maxDepth)
                maxDepth = d;
        }
        depth[node->key] = maxDepth+1;
        return depth[node->key];
    }

    void findEulerTour(TreeNode* node){

        tour_nodes[tour_index] = node->key;
        tour_depth[tour_index] = depth[node->key];
        last[node->key] = tour_index++;

        for(auto& child: node->children) {
            findEulerTour(child);
            tour_nodes[tour_index] = node->key;
            tour_depth[tour_index] = depth[node->key];
            last[node->key] = tour_index++;
        }
    }

    int findLCA(int x, int y){

        int index1 = last[x], index2 = last[y];
        int m = (index1 <= index2 ? index1 : index2);
        int n = (index1 >= index2 ? index1 : index2);

        int max_depth = tour_depth[m], max_depth_index = m;
        for(int i = m; i <= n; i++){
            if(tour_depth[i] > max_depth){
                max_depth = tour_depth[i];
                max_depth_index = i;
            }
        }
        return tour_nodes[max_depth_index];
    }
};

int main(){

    auto* tree = new Tree();
    tree->read_graph();
    tree->initialize_parents(tree->head);

    tree->calculate_depth(tree->head);
    tree->findEulerTour(tree->head);

    for(int i = 0; i < tree->N; i ++)
        cout << tree->depth[i] << " ";
    cout << "\n\n";
    for(int i = 0; i < tree->N; i ++)
        cout << tree->last[i] << " ";
    cout << "\n\n";
    for(int i = 0; i < tree->N*2-1; i ++)
        cout << tree->tour_depth[i] << " ";
    cout << "\n\n";
    for(int i = 0; i < tree->N*2-1; i++)
        cout << tree->tour_nodes[i] << " ";
    cout << "\n\n";

    cout << "LCA of 1 and 9: " << tree->findLCA(1, 9) << "\n";
    cout << "LCA of 4 and 9: " << tree->findLCA(4, 9) << "\n";
    cout << "LCA of 7 and 8: " << tree->findLCA(7, 8) << "\n";

    free(tree);
    return 0;
}
