#include "graph.h"


void Graph::TraverseDFS(int s)
{
	vector<int> visited(vertices.size(), 0);
	
	string output = "";

	//We would need a stack to store all the connected nodes to this node.
	stack<int> nodes;
	nodes.push(s);
	
	int i = 0;
	while (!nodes.empty())
	{
		i = nodes.top();
		nodes.pop();
		if (visited[i] == 0)
			output.append(to_string(i));

		//Add the connected nodes of the start node to the stack.
		for (auto j : vertices[i])
		{
			if(visited[j] == 0)
				nodes.push(j);
		}
		
		visited[i] = 1;
	}
	cout << output << endl;
}

void Graph::TraverseBFS(int s)
{
	vector<int> visited(vertices.size(), 0);

	string output = "";

	//We would need a stack to store all the connected nodes to this node.
	queue<int> nodes;
	nodes.push(s);

	int i = 0;
	while (!nodes.empty())
	{
		i = nodes.front();
		nodes.pop();
		if (visited[i] == 0)
			output.append(to_string(i));

		//Add the connected nodes of the start node to the stack.
		for (auto j : vertices[i])
		{
			if (visited[j] == 0)
				nodes.push(j);
		}

		visited[i] = 1;
	}
	cout << output << endl;
}

string DFS(vector<list<int>>& vertices, int s, vector<int>& visited)
{
	string output = "";

	//We would need a stack to store all the connected nodes to this node.
	stack<int> nodes;
	nodes.push(s);

	int i = 0;
	while (!nodes.empty())
	{
		i = nodes.top();
		nodes.pop();
		if (visited[i] == 0)
			output.append(to_string(i));

		//Add the connected nodes of the start node to the stack.
		for (auto j : vertices[i])
		{
			if (visited[j] == 0)
				nodes.push(j);
		}

		visited[i] = 1;
	}
	return output;
}

void Graph::TopoSort(int s)
{
	vector<int> visited(vertices.size(), 0);
	stack<int> nodes;
	int val = 0;
	for (auto i = 0; i < vertices.size(); ++i)
	{
		if(!visited[i])
			nodes.push(i);
		bool bComplete = true;
		while (!nodes.empty())
		{
			val = nodes.top();
			bComplete = true;
			for (auto j : vertices[val])
			{
				if (visited[j] == 0)
				{
					nodes.push(j);
					visited[j] = 1;
					bComplete = false;
				}
			}

			if (bComplete)
				break;
		}
	}
	
	//Print this in reverse for the topo sort.
	while(!nodes.empty())
	{
		cout << nodes.top() << "\t";
		nodes.pop();
	}

}