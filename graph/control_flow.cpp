#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
    Checks if control flow graph is valid, i.e nesting of loops is valid
*/

class ControlFLowGraph{

    unsigned int nodes, num_edges;
    vector<vector<unsigned int>*> edges;
    vector<vector<unsigned int>*> incoming_edges;
    map<unsigned int, map<unsigned int, unsigned int>*> incoming_back_edges;
    map<unsigned int, map<unsigned int, unsigned int>*> outgoing_back_edges;
    bool *visited, *explored;

    void dfs_back_edges(unsigned int u){
        if(visited[u])
            return;

        visited[u] = true;
        explored[u] = true;

        for(auto v: *edges.at(u)){
            if(!explored[v])
                dfs_back_edges(v);
            else if(visited[v]){
                incoming_back_edges.at(v)->emplace(u, 0);
                outgoing_back_edges.at(u)->emplace(v, 0);
            }
        }

        visited[u] = false;
    }

    bool dfs_check_valid_cfg(unsigned int u, vector<unsigned int>* stack){

        /*
         * If there are incoming back-edges at node u, insert node v on stack
         * where (v,u) is a back-edge
         * In case of multiple back edges incident on a single node, insert then in
         * the reverse order in which they were found
         */
        vector<unsigned int> back_edge_sources;

        for(auto v: *incoming_back_edges.at(u))
            back_edge_sources.push_back(v.first);

        while(!back_edge_sources.empty()) {
            stack->push_back(back_edge_sources.back());
            back_edge_sources.pop_back();
        }

        // Checking if all incoming edges (except back edges) are visited
        auto in_back_edges = incoming_back_edges.at(u);
        bool incoming_edges_visited = true;
        for(auto v: *incoming_edges.at(u)){
            if(!visited[v] && (in_back_edges->find(v) == in_back_edges->end())) {
                incoming_edges_visited = false;
                break;
            }
        }

        if(!incoming_edges_visited)
            return true;

        for(auto v: *outgoing_back_edges.at(u)){
            if(!stack->empty() && stack->back() == u)
                stack->pop_back();
            else
                return false;
        }

        visited[u] = true;

        // Visit outgoing non back-edges after all incoming edges are visited
        auto out_back_edges = outgoing_back_edges.at(u);
        bool res = true;

        for(auto v: *edges.at(u)){
            if(!visited[v] && (out_back_edges->find(v) == out_back_edges->end()))
                res = dfs_check_valid_cfg(v, stack);
            if(!res)
                return false;
        }

        return true;
    }

public:
    ControlFLowGraph(unsigned int n, unsigned int e){
        this->nodes = n;
        this->num_edges = e;
        visited = new bool[n];
        explored = new bool[n];
    }

    [[nodiscard]] unsigned int getNumberOfBasicBlocks() const {return nodes;}

    [[nodiscard]] unsigned int getNumberOfEdges() const {return num_edges;}

    [[nodiscard]] vector<unsigned int>* getEdges(unsigned int u) const {
        return edges.at(u);
    }

    [[nodiscard]] map<unsigned int, unsigned int>* getIncomingBackEdgesForNode(unsigned int u) const {
        return incoming_back_edges.at(u);
    }

    void read_graph(){
        unsigned int u, v;

        for (unsigned int i = 0; i < nodes; i++) {
            edges.push_back(new std::vector<unsigned int>());
            incoming_edges.push_back(new std::vector<unsigned int>());
            incoming_back_edges.emplace(i, new map<unsigned int, unsigned int>());
            outgoing_back_edges.emplace(i, new map<unsigned int, unsigned int>());
        }

        for (unsigned int j = 0; j < num_edges; j++){
            std::cin >> u >> v;
            edges.at(u)->push_back(v);
            incoming_edges.at(v)->push_back(u);
        }
    }

    void init(){
        for (unsigned int i = 0; i < nodes; i++){
            visited[i] = false;
            explored[i] = false;
        }
    }

    void find_back_edges(){
        dfs_back_edges(0);
    }

    bool is_CFG_valid(){
        init();
        auto stack = new vector<unsigned int>();

        dfs_check_valid_cfg(0, stack);
        bool is_valid = stack->empty();

        (is_valid ? cout << "Valid CFG\n" : cout << "Invalid CFG");

        free(stack);
        return is_valid;
    }

    void clean(){
        for (unsigned int i = 0; i < nodes; i++) {
            free(edges.at(i));
            free(incoming_edges.at(i));
        }
        free(visited);
        free(explored);
    }
};

int main(){

    int nodes, edges;
    cin >> nodes >> edges;

    auto cfg = new ControlFLowGraph(nodes, edges);
    cfg->read_graph();
    cfg->init();

    cfg->find_back_edges();
    cfg->is_CFG_valid();

    cfg->clean();
    free(cfg);

    return 0;
}