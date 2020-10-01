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
	int countDistations(int node, vector<int>& lengths_empty); //lengths_empty - distance vector / BFS
	int acyclicityCheck(vector<int>& empty_vector); // empty_vector includes topological order if it exists / DFS
	void strongComponentSearch(vector<int>& empty_vector); // empty_vector - strong components / DFS
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
	int findComponents(vector<int>& lengths_empty); //lengths_empty - components numbers / BFS
	int acyclicityCheck(vector<int>& empty_vector); // empty_vector includes topological order if it exists / DFS
	void strongComponentSearch(vector<int>& empty_vector);
private:
	void make_simple(map<int, set<int>>& list);
};
