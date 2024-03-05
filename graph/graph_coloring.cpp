#include <iostream>
#include <set>
#include <cassert>

using namespace std;

bool** adj_matrix;
int* colors, *visited;
int N = 0, E = 0, K = 0;

void print_colors(){
    for(int i = 0; i < N; i++)
        cout << colors[i] << " ";
    cout << "\n";
}

bool find_k_coloring(int u, int k){
    if(u == N)
        return true;

    set<int> adj_colors;

    for(int v = 0; v < N; v++){
        if(adj_matrix[u][v] && colors[v] > 0)
            adj_colors.emplace(colors[v]);
    }

    for(int c = 1; c <= k; c++){
        if(adj_colors.find(c) == adj_colors.end()){
            colors[u] = c;
            bool res = find_k_coloring(u+1, k);
            if(res)
                return true;
        }
    }
    colors[u] = 0;
    return false;
}

bool k_coloring_exists(int k){
    return find_k_coloring(0, k);
}

int main(){

    cin >> N >> E >> K;

    colors = new int[N];
    visited = new int[N];
    adj_matrix = new bool*[N];

    for(int i = 0; i < N; i++) {

        adj_matrix[i] = new bool[N];
        colors[i] = 0;

        for(int j = 0; j < N; j++)
            adj_matrix[i][j] = false;
    }

    int u, v;
    for(int i = 0; i < E; i++){
        cin >> u >> v;
        adj_matrix[u][v] = true;
        adj_matrix[v][u] = true;
    }

    auto coloringFound = k_coloring_exists(K);
    if(coloringFound)
        cout << K << " coloring exists\n";
    else
        cout << K << " coloring doesn't exists\n";

    free(adj_matrix);
    free(colors);
    free(visited);
    return 0;
}
