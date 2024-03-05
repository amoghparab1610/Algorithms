#ifndef COMPETITIVE_PROGRAMMING_GRAPH_HPP
#define COMPETITIVE_PROGRAMMING_GRAPH_HPP

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <set>

class Graph{

public:
    bool isDirected;
    unsigned int N;
    std::vector<std::map<unsigned int, long>*> graph;

    explicit inline Graph(bool is_directed = false){
        this->isDirected = is_directed;
        this->N = 0;
    }

    static void print_shortest_path(unsigned int, unsigned int, const long*, const unsigned int*);

    static void print_list(const std::vector<unsigned int>&);

    void print_adj_list();

    virtual void clean();

    void read_graph();
};

#endif //COMPETITIVE_PROGRAMMING_GRAPH_HPP
