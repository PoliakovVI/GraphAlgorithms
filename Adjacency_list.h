#pragma once
#include "Includes_and_variables.h"

class SimpleAdjList;
class DirAdjList;

// classes

class DirAdjList{
public:
	DirAdjList(string filename);
	DirAdjList(const DirAdjList& dal);
	void print(ostream& out = cout, string fsep = " ", string osep = " ");
	int bfs_distations(int node, vector<int>& lengths_empty); //lengths_empty - distances vector
	int dfs_acyclicityCheck(vector<int>& empty_vector); // empty_vector includes topological order if it exists
	void strongComponentSearch(vector<int>& empty_vector);
protected:
	int max_number = -1;
	map<int, set<int>> list;
	DirAdjList();
private:
	DirAdjList& reverse(); // reverses the graph
};

class SimpleAdjList : public DirAdjList {
public:
	SimpleAdjList(string filename);
	SimpleAdjList(const SimpleAdjList* sal);
	int bfs_findComp(vector<int>& lengths_empty); //lengths_empty - components numbers
	int dfs_acyclicityCheck(vector<int>& empty_vector); // empty_vector includes topological order if it exists
private:
	void make_simple(map<int, set<int>>& list);
};
