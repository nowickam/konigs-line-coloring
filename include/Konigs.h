
#ifndef KONIGS_H
#define KONIGS_H

#include <vector>
using namespace std;

vector< vector<int> > FormAdjMatrix(int);
void AddEdge(vector<vector<int>>&, int, int);
void DeleteEdge(vector<vector<int>>&, int , int );
void Print(vector<vector<int>> );
bool IsEmpty(vector<vector<int>> );
bool IsRegular(vector<vector<int>> );
vector<vector<int>> MakeRegular(vector<vector<int>> &);
bool BFS(vector< vector<int> > &, int &, int &, vector<int> &);
void GenerateMatchings(vector<vector<int>> &, int &, int &, int &);
vector<int> PrintMatchings(vector<vector<int>> , int &);


#endif // !KONIGS_H
