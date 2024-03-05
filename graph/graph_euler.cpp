#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

#include "graph.hpp"

using namespace std;

class Euler : public Graph {

public:
    int* in_degree{};
    int* out_degree{};
    unsigned int* degree{};
    unsigned int s_vertex{}, e_vertex{};
    vector<unsigned int> eulerPath;

    explicit Euler(bool is_directed = false) : Graph(is_directed) {}

    void init(){
        in_degree = new int [N];
        out_degree = new int [N];
        degree = new unsigned int [N];

        for(unsigned int i = 0; i < N; i++){
            in_degree[i] = 0;
            out_degree[i] = 0;
            degree[i] = 0;
        }
    }

    void calculateDegree(){
        for(unsigned int u = 0; u < N; u++)
            for(auto& [v, w]: *graph.at(u)){
                in_degree[v] += 1;
                out_degree[u] += 1;
            }
        for(unsigned int u = 0; u < N; u++)
            degree[u] = in_degree[u] + out_degree[u];
    }

    bool checkIfEulerianPathExists(){
        if(isDirected){
            unsigned num_s_vertex = 0, num_e_vertex = 0;
            for(unsigned int u = 0; u < N; u++){
                if((in_degree[u] - out_degree[u]) > 1 || (out_degree[u] - in_degree[u]) > 1)
                    return false;
                else if((in_degree[u] - out_degree[u]) == 1) {
                    e_vertex = u;
                    num_e_vertex += 1;
                } else if ((out_degree[u] - in_degree[u]) == 1){
                    s_vertex = u;
                    num_s_vertex += 1;
                }
            }
            return (num_s_vertex == 1 && num_e_vertex == 1) ||
            (num_s_vertex == 0 && num_e_vertex == 0);
        }else{
            unsigned int num_odd = 0;
            for(unsigned int u = 0; u < N; u++){
                if(degree[u] % 2 != 0) {
                    s_vertex = u;
                    num_odd += 1;
                }
            }
            return (num_odd == 0 || num_odd == 2);
        }
    }

    bool checkIfEulerianCircuitExists(){
        if(isDirected){
            for(unsigned int u = 0; u < N; u++)
                if(in_degree[u] != out_degree[u])
                    return false;
            return true;
        }else{
            for(unsigned int u = 0; u < N; u++)
                if(degree[u]%2 != 0)
                    return false;
            return true;
        }
    }

    void findEulerPath(unsigned int u){
        for(auto& [v, w]: *graph.at(u)){
            if(w > 0){
                graph.at(u)->at(v) = w-1;
                if(!isDirected)
                    graph.at(v)->at(u) = w -1;
                findEulerPath(v);
            }
        }
        eulerPath.push_back(u);
    }

    static std::string getPath(const vector<unsigned int>& vertices){
        std::string path;
        for(auto u: vertices)
            path = std::to_string(u).append(" ").append(path);
        return path;
    }

    static void findEulerPathOrCircuit(bool isDirected, bool eulerPathOrCircuit){
        auto* graph = new Euler(isDirected);
        graph->read_graph();

        graph->init();
        graph->calculateDegree();

        bool pathExists;
        if(eulerPathOrCircuit)
            pathExists = graph->checkIfEulerianPathExists();
        else
            pathExists = graph->checkIfEulerianCircuitExists();

        if(pathExists) {
            graph->findEulerPath(graph->s_vertex);
            cout << "Euler " << (eulerPathOrCircuit ? "Path: " : "Circuit: ") << getPath(graph->eulerPath) << "\n";
        }
        else
            cout << "No Euler " << (eulerPathOrCircuit ? "Path" : "Circuit") << "\n";

        graph->clean();
        free(graph);
    }
};

int main(){

    Euler::findEulerPathOrCircuit(true, true);
    Euler::findEulerPathOrCircuit(true, false);

    return 0;
}