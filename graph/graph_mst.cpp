#include <algorithm>
#include <iostream>
#include <queue>

#include "edge.hpp"
#include "heap.hpp"
#include "graph.hpp"

using namespace std;

class GraphMST : public Graph {

public:
    explicit GraphMST(bool isDirected) : Graph(isDirected) {}

    void primMST(unsigned int start = 0) {

        long minCost = 0;
        bool* visited = new bool[N];
        auto* prev = new unsigned int[N];
        Heap* heap = new Heap();
        heap->insert(new HeapNode(0, {start,start}));
        vector<std::pair<unsigned int, unsigned int>> edges;

        for(unsigned int i = 0; i < N; i++)
            visited[i] = false;

        while(heap->getSize()){

            auto node = heap->remove();
            auto& edge = node->edge;

            if(visited[edge.second])
                continue;
            visited[edge.second] = true;

            edges.emplace_back(edge.first, edge.second);
            minCost += node->key;

            for(const auto& [v, w] : *graph.at(edge.second)){
                if(!visited[v])
                    heap->insert(new HeapNode(w, {edge.second, v}));
            }
        }

        cout << "MST cost: " << minCost << "\n";
        cout << "MST edges:\n";
        print_edges(edges);

        free(visited);
        free(prev);
        free(heap);
    }

    static void print_edges(const vector<std::pair<unsigned int, unsigned int>>& edges){
        for(auto& [u, v]: edges)
            cout << "(" << u << ", " << v << ")\n";
    }

    void kruskalMST() {

        auto *edges = new vector<Edge>();
        for(unsigned int u = 0; u < N; u++)
            for(auto& [v, w]: *graph.at(u))
                edges->emplace_back(u, v, w);

        sort(edges->begin(), edges->end(), edgeComparator);

        auto* parent = new unsigned int[N];
        auto* count = new unsigned int[N];

        for(unsigned int i = 0; i < N; i++){
            parent[i] = i;
            count[i] = 1;
        }

        long minCost = 0;

        while(!edges->empty()){

            const auto& edge = edges->back();
            edges->pop_back();

            auto parent_u = find_parent(edge.u, parent);
            auto parent_v = find_parent(edge.v, parent);

            if(parent_u == parent_v)
                continue;

            minCost += edge.w;

            if(count[parent_u] >= count[parent_v]){
                count[parent_u] += count[parent_v];
                merge(edge.v, parent_u, parent);
            }else{
                count[parent_v] += count[parent_u];
                merge(edge.u, parent_v, parent);
            }
        }

        cout << "Minimum Cost of Spanning Tree: " << minCost;

        free(edges);
        free(parent);
        free(count);
    }

    static bool edgeComparator(const Edge& a,const Edge& b){
        if (a.w > b.w)
            return true;
        return false;
    }

    static unsigned int find_parent(unsigned int u, const unsigned int* parent){

        auto p = u;
        while(parent[p] != p)
            p = parent[p];
        return p;
    }

    static void merge(unsigned int u, unsigned int p, unsigned int* parent){
        while(u != parent[u]){
            auto v = parent[u];
            parent[u] = p;
            u = v;
        }
        parent[u] = p;
    }
};

int main(){

    auto* graph = new GraphMST(true);
    graph->read_graph();

    graph->primMST(0);
    graph->kruskalMST();

    graph->clean();
    free(graph);

    return 0;
}