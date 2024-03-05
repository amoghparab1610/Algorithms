#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

#include "heap.hpp"
#include "graph.hpp"

using namespace std;

set<unsigned long long>& combinations(unsigned int start, unsigned int k, unsigned int n){

    auto* res = new set<unsigned long long>();

    if (k == 0 && start < n){
        res->insert(0);
        return *res;
    } else if(k == 1 && start == n-1){
        res->insert(1);
        return *res;
    }

    for(unsigned int i=start; i<n; i++){
        if(n-i-k-1 >= 0) {
            auto &res1 = combinations(i+1, k, n);
            if(!res1.empty())
                for(auto num: res1)
                    res->insert(num*2);
        }
        if(n-i-k >= 0) {
            auto &res2 = combinations(i+1, k-1, n);
            if(!res2.empty())
                for(auto num: res2)
                    res->insert(num*2+1);
        }
    }
    return *res;
}

class ShortestPath : public Graph {

public:
    explicit ShortestPath(bool isDirected) : Graph(isDirected) {}

    void dijkstra(unsigned int start, unsigned int end){

        bool* visited = new bool[N];
        long* dist = new long[N];
        auto* prev = new unsigned int[N];

        for(unsigned int i = 0; i < N; i++){
            dist[i] = LONG_MAX;
            visited[i] = false;
        }

        dist[start] = 0;
        prev[start] = start;
        
        Heap* heap = new Heap();
        heap->insert(new HeapNode(0, {start, start}));

        while(heap->getSize()){

            auto node = heap->remove();
            auto& edge = node->edge;

            if(visited[node->edge.second])
                continue;

            visited[edge.second] = true;

            for(const auto& [v, w] : *graph.at(edge.second)){
                if(!visited[v]){

                    auto newDist = node->key+w;
                    if(newDist < dist[v]){
                        
                        dist[v] = newDist;
                        prev[v] = edge.second;
                        heap->insert(new HeapNode(newDist, {edge.second, v}));
                    }
                }
            }
        }

        if(dist[end] < LONG_MAX)
            print_shortest_path(start, end, dist, prev);
        else
            cout << "Path doesn't exist\n";

        free(heap);
        free(prev);
        free(dist);
        free(visited);
    }

    void bellman_ford(unsigned int start, unsigned int end) const{

        long* dist = new long[N];
        auto* prev = new unsigned int [N];

        for(unsigned int i = 0 ; i < N; i ++)
            dist[i] = LONG_MAX;
        dist[start] = 0;
        prev[start] = 0;

        for(unsigned int k = 0; k < N; k++)
            for(unsigned int i = 0; i < N; i++)
                for(const auto& [j, w]: *graph.at(i)) {
                    if(dist[i] == LONG_MAX)
                        continue;
                    auto newDist = dist[i] + w;
                    if (newDist < dist[j]) {
                        dist[j] = newDist;
                        prev[j] = i;
                    }
                }

        if(dist[end] < LONG_MAX)
            print_shortest_path(start, end, dist, prev);
        else
            cout << "Path doesn't exist\n";

        free(dist);
        free(prev);
    }

    void floyd_warshall(unsigned int start, unsigned int end){

        long dist[N][N][N+1];
        unsigned int prev[N][N];

        for(unsigned int i = 0; i < N; i ++) {
            for (unsigned int j = 0; j < N; j++)
                dist[i][j][0] = LONG_MAX;
            dist[i][i][0] = 0;
        }

        for(unsigned int i = 0; i < N; i ++)
            for(const auto& [j, w]: *graph.at(i)) {
                dist[i][j][0] = w;
                prev[i][j] = i;
            }

        for (unsigned int k = 1; k <= N; k++)
            for(unsigned int i = 0; i < N; i ++)
                for (unsigned int j = 0; j < N; j++){

                    dist[i][j][k] = dist[i][j][k-1];

                    if(dist[i][k-1][k-1] == LONG_MAX || dist[k-1][j][k-1] == LONG_MAX)
                        continue;

                    auto newDist = dist[i][k-1][k-1] + dist[k-1][j][k-1];
                    if(newDist < dist[i][j][k]){
                        dist[i][j][k] = newDist;
                        prev[i][j] = prev[k-1][j];
                    }
                }

        string path = to_string(end);
        auto u = end;
        while(u != start){
            u = prev[start][u];
            path = to_string(u).append(", ").append(path);
        }

        cout << "Shortest dist from " << start << "->" << end << ": " << dist[start][end][N] << "\n";
        cout << "Shortest path from " << start << "->" << end << ": " << path << endl;
    }

    void initialize_tsp(unsigned int S, vector<map<unsigned long long, long>*>* memo){

        for(unsigned int i = 0; i < N; i++)
            graph.at(i)->insert({i, 0});

        for(unsigned int i = 0; i < N; i++)
            for(unsigned int j = 0; j < N; j++)
                if(graph.at(i)->find(j) == graph.at(i)->end())
                    graph.at(i)->insert({j, LONG_MAX});

        for(unsigned int i = 0; i < N; i++)
            memo->push_back(new map<unsigned long long, long>());

        for(const auto& [i, w]: *graph.at(S))
            memo->at(i)->insert({1 << S | 1 << i, w});
    }

    void solve_tsp(unsigned int S, vector<map<unsigned long long, long>*>* memo){

        for(unsigned int k = 3; k <= N; k++){
            for(auto state: combinations(0, k, N)){

                if(!(state & (1 << S)))
                    continue;

                for(unsigned int e = 0; e < N; e++){

                    if(e == S || !(state & (1 << e)))
                        continue;
                    auto m = state ^ (1 << e);
                    long minDist = LONG_MAX;

                    for(unsigned int j = 0; j < N; j++){
                        if(j == S || j == e || !(state & (1 << j)))
                            continue;

                        auto newDist = memo->at(j)->at(m) + graph.at(j)->at(e);
                        if(newDist < minDist)
                            minDist = newDist;
                    }
                    memo->at(e)->insert({state, minDist});
                }
            }
        }
    }

    long find_optimal_cost(unsigned int S, vector<map<unsigned long long, long>*>* memo){

        long minDist = LONG_MAX;
        unsigned long long endState = (1 << N)-1;

        for(unsigned int e = 0; e < N; e++){
            if(e == S)
                continue;
            auto newDist = memo->at(e)->at(endState) + graph.at(e)->at(S);
            if(newDist < minDist)
                minDist = newDist;
        }
        return minDist;
    }

    vector<unsigned int>& find_optimal_path(unsigned int S, vector<map<unsigned long long, long>*>* memo){

        unsigned long long state = (1 << N)-1;
        unsigned int end_vertex = S;
        unsigned int last_vertex = S;

        auto* optPath = new vector<unsigned int>();
        optPath->push_back(S);

        for(unsigned int i = 0; i < N-1; i++){

            long minDist = LONG_MAX;

            for(unsigned int e = 0; e < N; e++){
                if(e == S || !(state & (1 << e)))
                    continue;
                
                auto newDist = memo->at(e)->at(state) + graph.at(e)->at(end_vertex);
                if(newDist < minDist){
                    minDist = newDist;
                    last_vertex = e;
                }
            }
            end_vertex = last_vertex;
            state = state ^ (1 << end_vertex);
            optPath->push_back(end_vertex);
        }

        optPath->push_back(S);
        reverse(optPath->begin(), optPath->end());
        return *optPath;
    }

    void tsp(unsigned int start){

        auto memo = new vector<map<unsigned long long, long>*>();

        initialize_tsp(start, memo);
        solve_tsp(start, memo);
        auto optDist = find_optimal_cost(start, memo);
        auto optPath = find_optimal_path(start, memo);

        cout << "Optimal distance: " << optDist << "\n";
        cout << "Optimal path: ";
        print_list(optPath);
    }
};

int main(){

    auto* graph = new ShortestPath(true);
    graph->read_graph();

    graph->dijkstra(0, (graph->N)-1);
    graph->bellman_ford(0, (graph->N)-1);
    graph->floyd_warshall(0, (graph->N)-1);

    graph->tsp(0);

    graph->clean();
    free(graph);

    return 0;
}