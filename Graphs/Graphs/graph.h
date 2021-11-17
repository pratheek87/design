#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class Graph
{
	int nVertices;
	vector<list<int>> vertices;
	bool bIsDirected;
	
public:

	Graph(int n, bool bDirected) : nVertices(n), bIsDirected(bDirected)
	{
		for (auto i=0 ; i<n ; ++i)
		{
			vertices.push_back(list<int>());
		}
	}

	void addEdge(int v1, int v2)
	{
		vertices[v1].push_front(v2);
		if (!bIsDirected)
			vertices[v2].push_front(v1);
	}

	void displayGraph()
	{
		for (auto i = 0; i < vertices.size() ; ++i)
		{
			cout << i;
			for (auto j : vertices[i])
			{
				cout << " --> " << j;
			}	
			cout << endl;
		}
	}

	void TraverseDFS(int startNode);
	void TraverseBFS(int startNode);

	void TopoSort(int);
};
