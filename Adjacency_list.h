#pragma once
#include "Includes_and_variables.h"

class SimpleAdjList;

class DirAdjList{
public:
	DirAdjList(string filename);
	void print(ostream& out = cout, string fsep = " ", string osep = " ");
	int bfs_distations(int node, vector<int>& lengths_empty); //lengths_empty - distances vector
	int dfs_acyclicityCheck(vector<int>& empty_vector);
protected:
	int max_number = 0;
	map<int, set<int>> list;
};

class SimpleAdjList : public DirAdjList {
public:
	SimpleAdjList(string filename);
	int bfs_findComp(vector<int>& lengths_empty); //lengths_empty - components numbers
	int dfs_acyclicityCheck(vector<int>& empty_vector);
};
