#include "max_flow_edge.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class MaxFlowGraph{

public:
    unsigned int source=0, sink=0, N=0, M=0;
    vector<map<unsigned int, MaxFlowEdge*>*> adj_list;

    void read_graph(){

        int a, b, c;
        cin >> N >> M >> source >> sink;

        for(unsigned int i = 0; i < N; i++)
            adj_list.push_back(new map<unsigned int, MaxFlowEdge *>());

        for(unsigned int i = 0; i < M; i++){
            cin >> a >> b >> c;
            adj_list.at(a)->insert({b, new MaxFlowEdge(a, b, c)});
        }
    }

    vector<unsigned int> topological_sort(unsigned int start = 0){

        vector<unsigned int> tpsort;
        vector<unsigned int> list = {start};
        bool *visited = new bool[N];

        for(unsigned int i = 0; i < N; i++)
            visited[i] = false;

        while(!list.empty()){

            unsigned int u = list.back();

            if(visited[u]){
                list.pop_back();
                continue;
            }

            bool all_neighbours_visited = true;

            for(auto& [v, w]: *adj_list.at(u)){
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

        return tpsort;
    }

    int maxFlow(){

        int* dp = new int[N];
        int maxFlow = 0;
        unsigned int u;
        auto tp_sort = topological_sort(source);

        for(unsigned int i = 0; i < N; i++)
            dp[i] = 0;
        dp[sink] = INT_MAX;

        for(int i = N-1; i >= 0 ; i--){
            u = tp_sort.at(i);
            for(auto& [v, w]: *adj_list.at(u))
                dp[u] += (dp[v] < w->capacity ? dp[v] : w->capacity);
        }
        maxFlow = dp[source];
        free(dp);
        return maxFlow;
    }
};

int main(){

    auto* dag = new MaxFlowGraph();
    dag->read_graph();

    auto max_flow= dag->maxFlow();
    cout << "Max Flow: " << max_flow << "\n";

    free(dag);
    return 0;
}