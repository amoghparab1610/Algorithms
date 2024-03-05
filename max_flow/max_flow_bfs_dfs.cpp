#include "max_flow_edge.hpp"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class MaxFlowGraph{

public:
    unsigned int source=0, sink=0, N=0, M=0;
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
        }
    }

    int dfs(unsigned int s){

        if(s == sink)
            return INT_MAX;

        for(auto& edge: *adj_list.at(s)){

            auto remFlow = edge.second->capacity - edge.second->flow;

            if(remFlow > 0 && !visited[edge.first]){

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

    void bfs(unsigned int s, unsigned int* last_vertex){

        vector<MaxFlowEdge*> queue;
        visited[s] = true;

        // Initialize the queue with valid (remaining flow > 0) outgoing edges from the source
        for(auto& edge: *adj_list.at(s))
            if(edge.second->capacity - edge.second->flow > 0) {
                queue.push_back(edge.second);
                last_vertex[edge.second->v] = edge.second->u;
            }

        // Iterate while queue is empty or till sink is found
        while(!queue.empty()){

            auto curr_edge = queue.front();
            queue.erase(queue.begin());
            visited[curr_edge->v] = true;

            for(auto& edge: *adj_list.at(curr_edge->v)){

                auto remFlow = edge.second->capacity - edge.second->flow;

                if(remFlow > 0 && !visited[edge.first]){

                    visited[edge.first] = true;
                    queue.push_back(edge.second);
                    last_vertex[edge.first] = curr_edge->v;

                    if(edge.first == sink)
                        return;
                }
            }
        }
    }

    int maxFlowBFS(){

        int maxFlow = 0, bottleneck;
        auto* last_vertex = new unsigned int[N];

        do{

            for(unsigned int i = 0; i < N; i++) {
                visited[i] = false;
                last_vertex[i] = N;
            }
            visited[source] = true;

            bfs(source, last_vertex);

            bottleneck = 0;
            if(visited[sink]){

                vector<MaxFlowEdge*> path;
                bottleneck = INT_MAX;
                unsigned int u = sink;
                MaxFlowEdge* edge;

                while(u != source){

                    edge = adj_list.at(last_vertex[u])->at(u);
                    path.push_back(edge);
                    auto remFlow = edge->capacity - edge->flow;
                    bottleneck = (bottleneck < remFlow ? bottleneck : remFlow);
                    u = last_vertex[u];
                }

                for(auto e: path){
                    e->flow += bottleneck;
                    auto back_edge = adj_list.at(e->v)->at(e->u);
                    back_edge->flow -= bottleneck;
                }

                maxFlow += bottleneck;
            }
        }while(bottleneck > 0);

        return maxFlow;
    }

    int maxFlowDFS(){
        int maxFlow = 0, bottleneck;
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

        }while(bottleneck > 0);

        return maxFlow;
    }
};

int main(){

    auto* dag = new MaxFlowGraph();
    dag->read_graph();

    auto max_flow= dag->maxFlowBFS();
    cout << "Max Flow: " << max_flow << "\n";

    free(dag);
    return 0;
}