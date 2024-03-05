#include <map>
#include <vector>
#include <iostream>

using namespace std;

class MaxFlowEdge {
public:
    int flow, capacity;
    unsigned int u, v;

    inline MaxFlowEdge(unsigned int a, unsigned int b, int c) {
        u = a;
        v = b;
        capacity = c;
        flow = 0;
    }
    [[nodiscard]] bool isResidual() const { return capacity == 0; }
};

class MaxFlowGraph{

public:
    unsigned int source=0, sink=0, n=0, m=0, e=0, N=0;
    vector<map<unsigned int, MaxFlowEdge*>*> adj_list;
    vector<MaxFlowEdge*> augPath;
    bool* visited{};

    void read_graph(){

        int a, b, c;
        cin >> n >> m >> e;
        sink = n+m+1;
        N = n+m+2;
        visited = new bool [N];

        for(unsigned int i = 0; i < N; i++) {
            adj_list.push_back(new map<unsigned int, MaxFlowEdge *>());
            visited[i] = false;
        }

        for(unsigned int i = 0; i < e; i++){
            cin >> a >> b;
            adj_list.at(a)->insert({b, new MaxFlowEdge(a, b, 1)});
            adj_list.at(b)->insert({a, new MaxFlowEdge(b, a, 0)});
        }

        for(unsigned int i = 1; i <= m; i++){
            adj_list.at(source)->insert({i, new MaxFlowEdge(source, i, 1)});
            adj_list.at(i)->insert({source, new MaxFlowEdge(i, source, 0)});
        }

        for(unsigned int i = m+1; i <= n+m; i++){
            adj_list.at(i)->insert({sink, new MaxFlowEdge(i, sink, 1)});
            adj_list.at(sink)->insert({i, new MaxFlowEdge(sink, i, 0)});
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

    int maxFlow(){
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

    auto max_flow= dag->maxFlow();
    cout << "Max Flow: " << max_flow << "\n";

    free(dag);
    return 0;
}