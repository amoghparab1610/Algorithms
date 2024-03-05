#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#include "graph.hpp"

using namespace std;

class SCC : public Graph{

public:
	vector<unsigned int> stack;
	set<unsigned int> nodesRemaining;
	bool* partOfSCC{};
	unsigned int* sccID{};
	unsigned int* nodeID{};
	unsigned int nextUnvisitedNode = 0;
	unsigned int nextNodeIdAvailable = 0;

	explicit SCC(bool isDirected): Graph(isDirected) {}

    void init(){

        partOfSCC = new bool[N];
        sccID = new unsigned int[N];
        nodeID = new unsigned int[N];

        for(unsigned int i = 0; i < N; i++){
            partOfSCC[i] = false;
            nodesRemaining.insert(i);
            nodeID[i] = N;
        }
    }

	unsigned int dfs(unsigned int u){

		if(nodeID[u] != N && nodeID[u] == sccID[u])
			return sccID[u];
		
		nodeID[u] = nextNodeIdAvailable++;
		sccID[u] = nodeID[u];
		stack.push_back(u);

		auto minLinkId = sccID[u];

		for(auto& [v, w]: *graph.at(u)){
			
			if(partOfSCC[v])
				continue;
			
			auto returnID = dfs(v);
			if(!partOfSCC[v] && (returnID < minLinkId))
				minLinkId = returnID;
		}

		sccID[u] = minLinkId;
        unsigned int n;
		
		if(nodeID[u] == sccID[u]){
			do{
				
				n  = stack.back();
				stack.pop_back();
				sccID[n] = sccID[u];
				partOfSCC[n] = true;
				nodesRemaining.erase(n);
			
			}while(n != u);
		}
		return sccID[u];
	}

    void printSCC(){
        cout << "SCC ID:";
        for(unsigned int i = 0; i < N; i ++)
            cout << " " << sccID[i];
        cout << "\n";
    }

	void findSCC(unsigned int start = 0){

		while(!nodesRemaining.empty()){

			if(!stack.empty())
				nextUnvisitedNode = stack.back();
			else
				nextUnvisitedNode = *nodesRemaining.begin();

			dfs(nextUnvisitedNode);
		}
        printSCC();
	}

	void clean() override{
		free(sccID);
		free(nodeID);
		free(partOfSCC);
        Graph::clean();
	}
};

int main(){

    auto* graph = new SCC(true);
    graph->read_graph();
    graph->init();

    graph->findSCC();

    graph->clean();
    free(graph);

    return 0;
}