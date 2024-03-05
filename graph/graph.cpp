#include "graph.hpp"

void Graph::print_shortest_path(unsigned int start, unsigned int end,
                                const long* dist,
                                const unsigned int* prev) {

    std::string path = std::to_string(end);
    auto u = end;
    while(u != start){
        u = prev[u];
        path = std::to_string(u).append(", ").append(path);
    }

    std::cout << "Shortest dist from " << start << "->" << end << ": " << dist[end] << "\n";
    std::cout << "Shortest path from " << start << "->" << end << ": " << path << std::endl;
}

void Graph::print_list(const std::vector<unsigned int>& list) {
    for(unsigned int i : list)
        std::cout << " " << i;
    std::cout << "\n";
}

void Graph::print_adj_list() {
    for (unsigned int i = 0; i < N; i++){
        std::cout << i << ": {";
        for(const auto& [v, w] : *graph.at(i))
            std::cout << v << ": " << w << ", ";
        std::cout << "}\n";
    }
}

void Graph::clean(){
    for (unsigned int i = 0; i < N; i++)
        free(graph.at(i));
}

void Graph::read_graph(){

    unsigned int M, u, v;
    long w;
    std::cin >> N >> M;

    for (unsigned int i = 0; i < N; i++)
        graph.push_back(new std::map<unsigned int, long>());

    for (unsigned int j = 0; j < M; j++){
        std::cin >> u >> v >> w;
        graph.at(u)->insert({v, w});
        if (!isDirected)
            graph.at(v)->insert({u, w});
    }
}