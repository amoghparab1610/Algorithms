#include "max_flow_edge.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class MaxFlowGraph{

public:
    unsigned int source=0, sink=0, N=0, M=0;
    int *level{};
    vector<map<unsigned int, MaxFlowEdge*>*> adj_list;
    vector<MaxFlowEdge*> augPath;
    bool* visited{};

    void read_graph(){

        int a, b, c;
        cin >> N >> M >> source >> sink;
        visited = new bool [N];
        level = new int[N];

        for(unsigned int i = 0; i < N; i++) {
            adj_list.push_back(new map<unsigned int, MaxFlowEdge *>());
            visited[i] = false;
        }

        for(unsigned int i = 0; i < M; i++){
            cin >> a >> b >> c;
            adj_list.at(a)->insert({b, new MaxFlowEdge(a, b, c)});
            adj_list.at(b)->insert({a, new MaxFlowEdge(b, a, 0)});
        }
    }

    int dfs(unsigned int s){

        if(s == sink)
            return INT_MAX;

        for(auto& edge: *adj_list.at(s)){

            auto remFlow = edge.second->capacity - edge.second->flow;

            if((level[s] < level[edge.first]) && !visited[edge.first]){

                visited[edge.first] = true;
                augPath.push_back(edge.second);
                auto bottleneck = dfs(edge.first);
                bottleneck = (bottleneck < remFlow ? bottleneck : remFlow);

                if(bottleneck > 0)
                    return bottleneck;
            }
        }
        return 0;
    }

    bool calculate_level(){

        auto* v = new bool[N];
        for(unsigned int i = 0; i < N; i++) {
            level[i] = -1;
            v[i] = false;
        }
        level[source] = 0;
        v[source] = true;

        vector<MaxFlowEdge*> queue;
        // Initialize the queue with valid (remaining flow > 0) outgoing edges from the source
        for(auto& edge: *adj_list.at(source))
            if(edge.second->capacity - edge.second->flow > 0)
                queue.push_back(edge.second);

        while(!queue.empty()){

            auto curr_edge = queue.front();
            queue.erase(queue.begin());
            level[curr_edge->v] = level[curr_edge->u]+1;
            v[curr_edge->v] = true;

            for(auto& edge: *adj_list.at(curr_edge->v)){
                auto remFlow = edge.second->capacity - edge.second->flow;
                if(remFlow > 0 && !v[edge.first])
                    queue.push_back(edge.second);
            }
        }
        free(v);
        return level[sink] != -1;
    }

    int maxFlowDFS(){
        int maxFlow = 0, bottleneck;
        bool level_graph_exists = calculate_level();
        visited[source] = true;

        do{
            bottleneck = dfs(source);
            maxFlow += bottleneck;

            for(auto edge: augPath){
                edge->flow += bottleneck;
                auto back_edge = adj_list.at(edge->v)->at(edge->u);
                back_edge->flow -= bottleneck;
                visited[edge->v] = false;
            }
            augPath.clear();
            level_graph_exists = calculate_level();

        }while(level_graph_exists);

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