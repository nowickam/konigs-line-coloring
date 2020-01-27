#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "Konigs.h"

using namespace std;


vector< vector<int> > FormAdjMatrix(int n)
{
	// initializing adjacency matrix, adding start and sink, and setting the values to 0
	vector<vector<int>> AdjMatrix;
	for (int i = 0; i <= n + 1; i++)
	{
		vector<int> row;
		AdjMatrix.push_back(row);
		for (int j = 0; j <= n + 1; j++)
			AdjMatrix[i].push_back(0);
	}

	return AdjMatrix;
}

void AddEdge(vector<vector<int>> &AdjMatrix, int i, int j)
{
	AdjMatrix[i][j] = 1;
	//start
	AdjMatrix[0][i] = 1;
	//sink
	AdjMatrix[j][AdjMatrix.size() - 1] = 1;
}

void DeleteEdge(vector<vector<int>> &AdjMatrix, int i, int j)
{
	AdjMatrix[i][j] = 0;
	//start
	AdjMatrix[0][i] = 0;
	//sink
	AdjMatrix[j][AdjMatrix.size() - 1] = 0;
}

void Print(vector<vector<int>> Matrix)
{
	cout << "   ";
	for (int i = 0; i < Matrix.size(); i++)
		cout << i << " ";
	cout << endl;
	for (int i = 0; i < Matrix.size(); i++)
	{
		cout << i << "  ";
		for (int j = 0; j < Matrix[i].size(); j++)
			cout << Matrix[i][j] << " ";
		cout << endl;
	}
}

bool IsEmpty(vector<vector<int>> Matrix)
{
	// returns true if the graph is empty
	for (int i = 1; i < Matrix.size() - 1; i++)
		for (int j = 1; j < Matrix.size() - 1; j++)
			if (Matrix[i][j] == 1)
				return false;
	return true;
}



bool IsRegular(vector<vector<int>> Graph)
{
	//checks the regularity of the graph

	int degree = 0;
	int curDegree = 0;
	for (int i = 1; i < Graph.size() - 1; i++)
		degree += Graph[1][i];

	for (int i = 1; i < Graph.size() / 2; i++)
	{
		curDegree = 0;
		for (int j = 1; j < Graph.size() - 1; j++)
			curDegree += Graph[i][j];
		if (curDegree != degree)
			return false;
	}
	return true;
}

int InDegree(vector<vector<int>> Graph, int n)
{
	int degree = 0;
	for (int i = 0; i < Graph.size(); i++)
		degree += Graph[i][n];
	return degree;
}

int OutDegree(vector<vector<int>> Graph, int n)
{
	int degree = 0;
	for (int i = 0; i < Graph.size(); i++)
		degree += Graph[n][i];
	return degree;
}

int MaxDegree(vector<vector<int>> Graph)
{
	//computes delta(G)

	int degree = 0;
	int maxDegree = 0;
	for (int i = 1; i < Graph.size() / 2; i++)
	{
		degree = 0;
		for (int j = 1; j < Graph.size() - 1; j++)
		{
			degree += Graph[i][j];
		}
		if (degree > maxDegree)
			maxDegree = degree;
	}
	return maxDegree;
}

bool EqualDegree(vector<vector<int>> Graph, int d)
{
	//checks if all nodes in the graph are of degree d

	int sum = 0;
	for (int i = 1; i < Graph.size() / 2; i++)
		if (OutDegree(Graph, i) != d) return false;
	for (int i = Graph.size() / 2; i < Graph.size() - 1; i++)
		if (InDegree(Graph, i) != d) return false;

	return true;
}


vector<vector<int>> MakeRegular(vector<vector<int>> &Graph)
{
	//makes the bipartite graph regular

	vector<vector<int>> newGraph;

	//if the sizes of the bipartition classes are not equal, create a new graph with bipartition
	//classes equal in sizes
	if (Graph.size() % 2 != 0 || OutDegree(Graph, 0) != InDegree(Graph, Graph.size() - 1))
	{
		int newSize = max(InDegree(Graph, Graph.size() - 1), OutDegree(Graph, 0));
		newGraph = FormAdjMatrix(2 * newSize);
		for (int i = 1; i < Graph.size() - 1; i++)
		{
			for (int j = 1; j < Graph.size() - 1; j++)
				if (Graph[i][j] == 1)
					AddEdge(newGraph, i, newSize + (j - OutDegree(Graph, 0)));
		}
	}


	//if the sizes are equal, leave the graph
	else newGraph = Graph;


	int maxDegree = MaxDegree(newGraph) - 1;
	int n;

	//iterate until all the degrees are not equal
	while (!EqualDegree(newGraph, maxDegree))
	{
		//increase the degree if it was not possible to create a maxDegree-regular graph
		maxDegree++;
		for (int i = 1; i < newGraph.size() / 2; i++)
		{
			//iterate through the nodes in X and add edges if possible
			n = newGraph.size() / 2;
			while (n != newGraph.size() - 1 && OutDegree(newGraph, i) < maxDegree)
			{
				if (InDegree(newGraph, n) < maxDegree && newGraph[i][n] == 0)
					AddEdge(newGraph, i, n);
				n++;
			}
		}
	}

	return newGraph;
}

bool BFS(vector< vector<int> > &resAdjMatrix, int &source, int &sink, vector<int> &parent)
{
	list<int> queue;
	int n = resAdjMatrix.size();

	// an array for visited nodes, 0-not visited, 1-visited
	vector<int> visited;
	for (int i = 0; i < n; i++)
		visited.push_back(0);

	int s = source;
	queue.push_back(s);

	while (!queue.empty())
	{
		s = queue.front();
		visited[s] = 1;
		queue.pop_front();

		for (int i = 0; i < n; i++)
		{
			int v = i;
			int capacity = resAdjMatrix[s][v];

			// connected neighbor that has not been visited
			if (visited[v] == 0 && capacity > 0)
			{
				queue.push_back(v);
				visited[v] = 1;
				parent[v] = s;
			}
		}
	}

	// if we found a path to the sink
	if (visited[sink] == 1)
		return true;
	return false;
}
