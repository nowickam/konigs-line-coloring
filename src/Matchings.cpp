#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <climits>
#include "Konigs.h"

using namespace std;

vector< vector<int> > FordFulkerson(vector< vector<int> > &adjMatrix, int &source, int &sink)
{
	// creating a residual graph (initially the same as the original)
	vector< vector<int> > resAdjMatrix;
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++)
	{
		vector<int> row;
		resAdjMatrix.push_back(row);
		for (int j = 0; j < adjMatrix[i].size(); j++)
		{
			resAdjMatrix[i].push_back(adjMatrix[i][j]);
		}
	}

	// creating an empty parent array for BFS to store a proper path
	vector<int> parent;
	for (int i = 0; i < n; i++)
	{
		parent.push_back(-1);
	}

	// calling BFS until there is no path left
	while (BFS(resAdjMatrix, source, sink, parent) == true)
	{
		int pathflow = INT_MAX;
		int v = sink;

		// find min capacity on the path - max flow
		while (v != source)
		{
			int u = parent[v];

			// updating the pathflow to this capacity if it is smaller
			int capacity = resAdjMatrix[u][v];
			pathflow = min(pathflow, capacity);

			v = u;
		}

		// updating the residual capacities of the edges and reverse edges
		v = sink;
		while (v != source)
		{
			int u = parent[v];

			resAdjMatrix[u][v] -= pathflow;
			resAdjMatrix[v][u] += pathflow;

			v = u;
		}

	}

	return resAdjMatrix;
}

vector<vector<int>> operator-(vector<vector<int>> M1, vector<int> M2)
{
	vector<vector<int>> M = M1;
	for (int i = 1; i < M2.size(); i++)
		M[i][M2[i]] = 0;
	return M;
}


vector<int> PrintMatchings(vector<vector<int>> Matrix, int &index)
{
	//array storing the matching
	vector<int> Match;
	for (int i = 0; i < Matrix.size() / 2; i++)
		Match.push_back(0);

	cout << "Color " << index << ": ";
	for (int i = Matrix.size() / 2; i < Matrix.size() - 1; i++)
	{
		//displaying the matching
		for (int j = 1; j < Matrix.size() / 2; j++)
			if (Matrix[i][j] == 1)
			{
				cout << j << "-" << i << " ";
				Match[j] = i;
			}

	}
	cout << endl;
	return Match;
}

void GenerateMatchings(vector<vector<int>> &Graph, int &source, int &sink, int &index)
{
	if (IsEmpty(Graph) == true)
		return;

	//generating a color/matching
	vector<vector<int>> coloredGraph = FordFulkerson(Graph, source, sink);
	index++;

	//printing the perfect matching and storing it
	vector<int> Matching = PrintMatchings(coloredGraph, index);

	//deleting the edges of the matching from the graph
	vector<vector<int>> newGraph = Graph - Matching;

	//generating matching for a subgraph
	GenerateMatchings(newGraph, source, sink, index);
}
