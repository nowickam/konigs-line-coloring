
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include "Konigs.h"

using namespace std;

int main()
{
	srand(time(NULL));
	// creating bipartite graphs, indices of vertices start from 1
	//unregular graph on 8 vertices
	cout << "Graph 1:\n";
	vector< vector<int> > M1 = FormAdjMatrix(8);
	AddEdge(M1, 1, 6);
	AddEdge(M1, 1, 8);
	AddEdge(M1, 2, 7);
	AddEdge(M1, 2, 6);
	AddEdge(M1, 3, 8);
	AddEdge(M1, 3, 7);
	AddEdge(M1, 3, 4);
	AddEdge(M1, 3, 5);

	vector<vector<int>> M12 = MakeRegular(M1);

	int source = 0;
	int sink = 11;
	int index = 0;		//indices of colors

	if (IsRegular(M1) == true)
		GenerateMatchings(M1, source, sink, index);
	else GenerateMatchings(M12, source, sink, index);

	//regular graph on 6 vertices
	cout << "Graph 2:\n";
	vector< vector<int> > M2 = FormAdjMatrix(6);
	AddEdge(M2, 1, 5);
	AddEdge(M2, 1, 6);
	AddEdge(M2, 2, 4);
	AddEdge(M2, 2, 6);
	AddEdge(M2, 3, 4);
	AddEdge(M2, 3, 5);
	AddEdge(M2, 1, 4);
	AddEdge(M2, 2, 5);
	AddEdge(M2, 3, 6);


	source = 0;
	sink = 7;
	index = 0;		//indices of colors
	GenerateMatchings(M2, source, sink, index);

	//pseudorandom graph
	cout << "Graph 3:\n";
	int size = 2 + rand() % 10;
	int seed = 1;
	vector< vector<int> > M3 = FormAdjMatrix(size);
	int it = size * seed;
	int i = 0, j = 0;
	while (it >= 0)
	{
		i = 1 + rand() % (size / 2);
		j = 1 + size / 2 + rand() % (size / 2);
		if (i != j)AddEdge(M3, i, j);
		it--;
	}

	source = 0;
	sink = size + 1;
	index = 0;		//indices of colors
	//Print(M3);
	if (IsRegular(M3) == true)
		GenerateMatchings(M3, source, sink, index);
	else
	{
		vector<vector<int>> M31 = MakeRegular(M3);
		//Print(M31);
		sink = M31.size() - 1;
		GenerateMatchings(M31, source, sink, index);
	}

	system("pause");
	return 0;
}
