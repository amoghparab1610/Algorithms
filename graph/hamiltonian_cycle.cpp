#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

bool** adj_matrix;
int* visited;
int start = 0, N = 0, E = 0;

void print_cycle(vector<int>* cycle){
    for(int v: *cycle)
        cout << v << " ";
    cout << start << "\n";
}

void find_cycles(int u, int k, vector<int>* cycle){
    if(k == N){
        if(adj_matrix[u][start])
            print_cycle(cycle);
        return;
    }
    for(int v = 0; v < N; v++){
        if(!visited[v] && adj_matrix[u][v]){
            visited[v] = true;
            cycle->push_back(v);
            find_cycles(v, k+1, cycle);
            visited[v] = false;
            cycle->pop_back();
        }
    }
}

void find_hamiltonian_cycles(int u){
    visited[u] = true;
    auto cycle = new vector<int>();
    cycle->push_back(u);
    find_cycles(u, 1, cycle);
}

int main(){

    cin >> N >> E;

    visited = new int[N];
    adj_matrix = new bool*[N];

    for(int i = 0; i < N; i++) {

        adj_matrix[i] = new bool[N];
        visited[i] = 0;

        for(int j = 0; j < N; j++)
            adj_matrix[i][j] = false;
    }

    int u, v;
    for(int i = 0; i < E; i++){
        cin >> u >> v;
        adj_matrix[u][v] = true;
        adj_matrix[v][u] = true;
    }

    find_hamiltonian_cycles(start);

    free(adj_matrix);
    free(visited);
    return 0;
}
