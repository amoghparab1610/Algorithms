#include <iostream>
#include <algorithm>
#include <vector>
#include "graph.hpp"

using namespace std;

class Traversal : public Graph{

public:
    explicit Traversal(bool is_directed = false): Graph (is_directed) {}

    void bfs(unsigned int start = 0){

        vector<unsigned int> list = {start};
        bool *visited = new bool[N];
        cout << "BFS traversal: ";

        while (!list.empty()){

            unsigned int u = list.front();
            list.erase(list.begin());

            if(!visited[u]){
                visited[u] = true;
                cout << u << " ";
            }

            for(auto& [v,w]: *graph.at(u)){
                if (!visited[v])
                    list.push_back(v);
            }
        }
        cout << "\n";
        free(visited);
    }

    void dfs(unsigned int start = 0){

        vector<unsigned int> list = {start};
        bool *visited = new bool[N];
        cout << "DFS traversal: ";

        while (!list.empty()){

            unsigned int u = list.back();
            list.pop_back();

            if(!visited[u]){
                visited[u] = true;
                cout << u << " ";
            }

            for(auto& [v, w]: *graph.at(u)){
                if (!visited[v])
                    list.push_back(v);
            }
        }
        cout << "\n";
        free(visited);
    }

    bool detect_cycle(unsigned int u, bool* visited){

        visited[u] = true;
        
        for(auto& [v, w]: *graph.at(u)){
            if(visited[v] || detect_cycle(v, visited))
                return true;
        }

        visited[u] = false;
        return false;
    }

    bool cycle_exists(){

        bool *visited = new bool[N];
        for(unsigned int i = 0; i < N; i++)
            visited[i] = false;

        bool isCyclePresent = detect_cycle(0, visited);
        
        if(isCyclePresent)
            cout << "Cycle detected\n";
        else
            cout << "Cycle not found\n";

        free(visited);
        return isCyclePresent;
    }

    vector<unsigned int> topological_sort(unsigned int start = 0){

        vector<unsigned int> tpsort;
        vector<unsigned int> list = {start};
        bool *visited = new bool[N];

        while(!list.empty()){

            unsigned int u = list.back();

            if(visited[u]){
                list.pop_back();
                continue;
            }

            bool all_neighbours_visited = true;

            for(auto& [v, w]: *graph.at(u)){
                if (!visited[v]){
                    list.push_back(v);
                    all_neighbours_visited = false;
                }
            }
            if(all_neighbours_visited){
                visited[u] = true;
                tpsort.push_back(u);
                list.pop_back();
            }
        }
        free(visited);
        reverse(tpsort.begin(), tpsort.end());

        cout << "Topological Sort: ";
        print_list(tpsort);

        return tpsort;
    }

    void longest_path_in_dag(){

        auto tp_sort = topological_sort();
        auto* path = new unsigned int[N];
        auto* next = new unsigned int[N];

        unsigned int end_node = tp_sort.back(), start_node = tp_sort.front(), next_node = end_node;
        next[end_node] = end_node;

        for(unsigned int i = N-1; ; i--){
           
            auto u = tp_sort.at(i);
            unsigned int max_length = 0;

            for(auto& [v, w]: *graph.at(u)){
                if(max_length <= path[v]){
                    max_length = path[v];
                    next_node = v;
                }
            }

            path[u] = max_length+1;
            next[u] = next_node;

            if (i == 0)
                break;
        }

        unsigned int u = start_node;
        vector<unsigned int> path_nodes;

        while(u != end_node){
            path_nodes.push_back(u);
            u = next[u];
        }
        path_nodes.push_back(end_node);

        cout << "Longest Path length in DAG: " << path[start_node] << "\n";
        cout << "Longest Path: ";
        print_list(path_nodes);

        free(path);
        free(next);
    }
};

int main(){

    auto* graph = new Traversal(true);
    graph->read_graph();
    
    graph->bfs();
    graph->dfs();

    bool cycle_found = graph->cycle_exists();
    if(cycle_found)
        cout << "Cycle exists\n";
    else{
        graph->topological_sort();
        graph->longest_path_in_dag();
    }

    graph->clean();
    free(graph);

    return 0;
}