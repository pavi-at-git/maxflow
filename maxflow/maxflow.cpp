// maxflow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define NODE 6
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class maxflow {
 
	//does a bfs on the graph and returns the path as list of edges
	bool bfs(int graph[NODE][NODE], vector<int> &path, int &bfsFlow, int source, int sink);


public:

	int m_rgraph[NODE][NODE],m_maxflow;
	bool fordFulkerson(int graph[NODE][NODE], int & maxflow, int source, int sink);
};
bool maxflow::fordFulkerson(int graph[NODE][NODE], int & maxflow, int source, int sink) {

	maxflow = 0;
	for (int i = 0; i < NODE; i++) {
		for (int j = 0; j < NODE; j++)
			m_rgraph[i][j] = graph[i][j];
	}
	vector<int> parent(NODE,-1);
	int bfsFlow = 100000;
	//do bfs till a path exist
	while (bfs(m_rgraph, parent, bfsFlow, source, sink)) {
		//fill the residual flow for an edge - a to b if the flow is reduced by bfsFlow then
		for (int i = sink; i != -1; i=parent[i]) {
			m_rgraph[parent[i]][i] -= bfsFlow; //decrement edge a to b by bfsFlow
			m_rgraph[i][parent[i]] += bfsFlow; //increment edge b to a by bfsFlow
		}
		parent.clear();
		parent.resize(NODE);
		maxflow += bfsFlow;
		bfsFlow = 100000;

	}
	
	return true;
}
bool maxflow::bfs(int graph[NODE][NODE], vector<int> &parent, int &bfsFlow, int source, int sink) {
	queue<int> nextNode;
	nextNode.push(source);

	bool visited[NODE];
	memset(visited, 0, sizeof(visited));
	visited[source] = true;
	
	parent[source] = -1;

	
	while(!nextNode.empty()) {

		source = nextNode.front();
		nextNode.pop();

		for (int i = 0; i < NODE; i++) {
			if ((graph[source][i] > 0 ) && !visited[i]) {
				
				parent[i] = source;
				visited[i] = true;
				nextNode.push(i);
				if (graph[source][i] < bfsFlow) {
					bfsFlow = graph[source][i];
				}
			}
		}
	}
	if (visited[sink]) {
		return true;
	}
	else
		return false;
}
int main()
{
	int flow = 0;
	int graph[NODE][NODE] = { { 0, 16, 13, 0, 0, 0 },	{ 0, 0, 10, 12, 0, 0 },
	{ 0, 4, 0, 0, 14, 0 },	{ 0, 0, 9, 0, 0, 20 },	{ 0, 0, 0, 7, 0, 4 },	{ 0, 0, 0, 0, 0, 0 } };;
	maxflow  flowAnalysis;

	
	flowAnalysis.fordFulkerson(graph, flow,0,5);
	cout << flow << " is the max flow";
	int integer=0;
	cin >> integer;
	return 0;
}

