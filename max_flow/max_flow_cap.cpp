#include "max_flow_edge.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class MaxFlowGraph{

public:
    unsigned int source=0, sink=0, N=0, M=0;
    int max_cap = 0, cap = 1;
    vector<map<unsigned int, MaxFlowEdge*>*> adj_list;
    vector<MaxFlowEdge*> augPath;
    bool* visited{};

    void read_graph(){

        int a, b, c;
        cin >> N >> M >> source >> sink;
        visited = new bool [N];

        for(unsigned int i = 0; i < N; i++) {
            adj_list.push_back(new map<unsigned int, MaxFlowEdge *>());
            visited[i] = false;
        }

        for(unsigned int i = 0; i < M; i++){
            cin >> a >> b >> c;
            adj_list.at(a)->insert({b, new MaxFlowEdge(a, b, c)});
            adj_list.at(b)->insert({a, new MaxFlowEdge(b, a, 0)});
            if(c > max_cap)
                max_cap = c;
        }

        while(cap * 2 <= max_cap)
            cap = cap * 2;
    }

    int dfs(unsigned int s, int cap){

        if(s == sink)
            return INT_MAX;

        for(auto& edge: *adj_list.at(s)){

            auto remFlow = edge.second->capacity - edge.second->flow;

            if(remFlow > cap && !visited[edge.first]){

                visited[edge.first] = true;
                augPath.push_back(edge.second);
                auto bottleneck = dfs(edge.first, cap);
                bottleneck = (bottleneck < remFlow ? bottleneck : remFlow);

                if(bottleneck > 0)
                    return bottleneck;
            }
        }
        return 0;
    }

    int maxFlowDFS(){
        int maxFlow = 0, bottleneck;
        visited[source] = true;

        do{
            bottleneck = dfs(source, cap);
            if(bottleneck == 0)
                cap = cap/2;
            else
                maxFlow += bottleneck;

            for(auto edge: augPath){
                edge->flow += bottleneck;
                auto back_edge = adj_list.at(edge->v)->at(edge->u);
                back_edge->flow -= bottleneck;
                visited[edge->v] = false;
            }
            augPath.clear();

        }while(cap > 0);

        return maxFlow;
    }
};

int main(){

    auto* dag = new MaxFlowGraph();
    dag->read_graph();

    auto max_flow= dag->maxFlowDFS();
    cout << "Max Flow: " << max_flow << "\n";

    free(dag);
    return 0;
}