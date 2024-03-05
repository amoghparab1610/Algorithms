#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

class ControlFLowGraph{

    unsigned int nodes, num_edges, counter;
    set<unsigned int> **dominator_tree, **dominance_frontiers;
    vector<unsigned int> **dominator_tree_inverse;
    vector<vector<unsigned int>*> outgoing_edges;
    vector<vector<unsigned int>*> incoming_edges;

    unsigned long long *dominators{};
    map<unsigned int, unsigned int> immediate_dominator;
    map<unsigned int, vector<unsigned int>*> natural_loops;
    vector<pair<unsigned int, unsigned int>> back_edges;
    bool *visited;
    unsigned int *dfs_ordering, *dfs_ordering_inverse;

    vector<unsigned int>* find_one_bit_positions(unsigned int u){

        unsigned long long x = (1 << (nodes-1));
        unsigned int v = nodes-1;
        auto d = new vector<unsigned int>();

        while(x > 0){

            if((x & dominators[u]))
                d->push_back(v);

            v -= 1;
            x = x >> 1;
        }
        return d;
    }

    void dfs(unsigned int u = 0){
        visited[u] = true;

        for(auto v: *outgoing_edges.at(u))
            if(!visited[v])
                dfs(v);

        dfs_ordering[--counter] = u;
        dfs_ordering_inverse[u] = counter;
    }

    void dfs_reachable_nodes(unsigned int u, unsigned int x, set<unsigned int>& reachable_nodes){

        visited[u] = true;
        reachable_nodes.emplace(u);

        if(u == x)
            return;

        for(auto v: *outgoing_edges.at(u))
            if(!visited[v] && (dfs_ordering_inverse[u] < dfs_ordering_inverse[v]))
                dfs_reachable_nodes(v, x, reachable_nodes);
    }

public:
    ControlFLowGraph(unsigned int n, unsigned int e){
        this->nodes = n;
        this->num_edges = e;
        visited = new bool[n];
        dominators = new unsigned long long [n];
        dfs_ordering = new unsigned int [n];
        dfs_ordering_inverse = new unsigned int [n];
        dominator_tree = new set<unsigned int>*[n];
        dominance_frontiers = new set<unsigned int>*[n];
        dominator_tree_inverse = new vector<unsigned int>*[n];
        counter = n;
    }

    [[nodiscard]] unsigned int getNumberOfBasicBlocks() const {return nodes;}

    [[nodiscard]] unsigned int getNumberOfEdges() const {return num_edges;}

    [[nodiscard]] vector<unsigned int>* getEdges(unsigned int u) const {
        return outgoing_edges.at(u);
    }

    void read_graph(){
        unsigned int u, v;

        for (unsigned int i = 0; i < nodes; i++) {
            outgoing_edges.push_back(new std::vector<unsigned int>());
            incoming_edges.push_back(new std::vector<unsigned int>());
        }

        for (unsigned int j = 0; j < num_edges; j++){
            std::cin >> u >> v;
            outgoing_edges.at(u)->push_back(v);
            incoming_edges.at(v)->push_back(u);
        }
    }

    void dominator_data_flow_analysis(unsigned int start = 0){

        unsigned int node;
        vector<unsigned int> work_list = {start};
        unsigned long long x = (1 << nodes)-1, in_node, out_node;

        while(!work_list.empty()){

            node = work_list.front();
            work_list.erase(work_list.begin());

            in_node = (node == start ? 0 : x);
            for(auto v: *incoming_edges.at(node))
                in_node = in_node & dominators[v];

            out_node = (1 << node) | in_node;
            if(dominators[node] != out_node) {
                dominators[node] = out_node;

                for(auto v: *outgoing_edges.at(node))
                    work_list.push_back(v);
            }
        }

        for (unsigned int i = 0; i < nodes; ++i)
            dominators[i] = dominators[i] ^ (1 << i);
    }

    void construct_dominator_tree(){

        for(unsigned int u = 0; u < nodes; u++){

            auto d = find_one_bit_positions(u);

            for(auto v : *d) {
                dominator_tree[u]->emplace(v);
                dominator_tree_inverse[v]->push_back(u);
            }

            free(d);
        }
    }

    void find_immediate_dominators(unsigned int start = 0){

        unsigned long long x, d;
        unsigned int idom;

        for(unsigned int u = 0; u < nodes; u++){

            x = 0;
            for(auto v: *dominator_tree[u])
                x = x | dominators[v];

            idom = start, d = u;
            for(auto v: *dominator_tree[u]){
                d = (1 << v) & x;
                if(d == 0)
                    idom = v;
            }

            if(u != start)
                immediate_dominator[u] = idom;
        }
    }

    void find_back_edges(){
        for(unsigned int u = 0; u < nodes; u++){
            for(auto v: *outgoing_edges.at(u))
                if(dfs_ordering_inverse[v] < dfs_ordering_inverse[u])
                    back_edges.emplace_back(u, v);
        }
    }

    void find_natural_loops(){
        for(auto& [u, v]: back_edges){

            if(natural_loops.find(v) == natural_loops.end())
                natural_loops.emplace(v, new vector<unsigned int>());

            set<unsigned int> reachable_nodes;
            reset_visited();
            dfs_reachable_nodes(v, u, reachable_nodes);

            for(auto w: reachable_nodes)
                natural_loops.at(v)->push_back(w);
        }
    }

    void find_dominance_frontiers(){

        for(unsigned int i = nodes-1; i >= 1; i--){

            auto u = dfs_ordering[i];
            cout << "Node " << u << "\n";

            // Nodes in dominance frontiers of children of node u not strictly dominated by u
            for(auto v: *dominator_tree_inverse[u]){
                cout << v << ": ";
                for(auto df: *dominance_frontiers[v]){

                    cout << df << " ";
                    const auto& dominators_of_df = *dominator_tree[df];

                    if(dominators_of_df.find(u) == dominators_of_df.end())
                        dominance_frontiers[u]->emplace(df);
                }
            }

            // Successors of node u not strictly dominated by u
            for(auto v: *outgoing_edges.at(u)){

                const auto& dominators_of_v = *dominator_tree[v];

                if(dominators_of_v.find(u) == dominators_of_v.end())
                    dominance_frontiers[u]->emplace(v);
            }
        }
    }

    void print(unsigned int start = 0){
        cout << "\n\nDFS ordering: ";
        for(unsigned int i = 0; i < nodes; i++)
            cout << dfs_ordering[i] << " ";
        cout << "\n\n";

        cout << "Dominators\n";
        for(unsigned int i = 0; i < nodes; i++){
            cout << i << ": ";
            for(auto v: *dominator_tree[i])
                cout << v << " ";
            cout << "\n";
        }
        cout << "\n";

        cout << "Immediate Dominator\n";
        for(unsigned int i = 0; i < nodes; i++)
            cout << i << ": " << (i == start ? "" : to_string(immediate_dominator[i])) << "\n";

        cout << "\nBack edges\n";
        for(auto& [u, v]: back_edges)
            cout << "(" << u << ", " << v << ") " ;
        cout << "\n";

        cout << "\nNatural loops\n";
        for(auto& [u, v]: natural_loops){
            cout << u << ": ";
            for(auto w: *v)
                cout << w << " ";
            cout << "\n";
        }

        cout << "\nDominance Frontiers\n";
        for(unsigned int i = 0; i < nodes; i++){
            cout << i << ": ";
            for(auto v: *dominance_frontiers[i])
                cout << v << " ";
            cout << "\n";
        }
    }

    void init(){
        unsigned long long x = (1 << nodes)-1;
        for (unsigned int i = 0; i < nodes; i++) {
            dominators[i] = x;
            dominator_tree[i] = new set<unsigned int>();
            dominance_frontiers[i] = new set<unsigned int>();
            dominator_tree_inverse[i] = new vector<unsigned int>();
        }
        reset_visited();
        dfs(0);
    }

    void reset_visited(){
        for (unsigned int i = 0; i < nodes; i++)
            visited[i] = false;
    }

    void clean(){
        for (unsigned int i = 0; i < nodes; i++) {
            free(outgoing_edges.at(i));
            free(incoming_edges.at(i));
            free(dominator_tree[i]);
            free(dominance_frontiers[i]);
            free(dominator_tree_inverse[i]);
        }
        free(visited);
        free(dominators);
        free(dfs_ordering);
        free(dfs_ordering_inverse);
    }
};

int main(){

    int nodes, edges;
    cin >> nodes >> edges;

    auto cfg = new ControlFLowGraph(nodes, edges);
    cfg->read_graph();
    cfg->init();

    cfg->dominator_data_flow_analysis();
    cfg->construct_dominator_tree();
    cfg->find_immediate_dominators();

    cfg->find_back_edges();
    cfg->find_natural_loops();
    cfg->find_dominance_frontiers();

    cfg->print();

    cfg->clean();
    free(cfg);

    return 0;
}