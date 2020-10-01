#include "Adjacency_list.h"

enum COLOR {
	WHITE,
	GREY,
	BLACK
};

// DirAdjList

DirAdjList::DirAdjList(string filename) {
	ifstream fin(filename);
	string buffer;
	int number, point;
	if (fin.is_open()) {
		while (getline(fin, buffer)) {
			stringstream ss(buffer);
			ss >> point;
			if (point > max_number) max_number = point;
			while (ss >> number) {
				list[point].insert(number);
				if (number > max_number) max_number = number;
			}
		}
		fin.close();
	}
}

void DirAdjList::print(ostream& out, string fsep, string osep) {
	for (const auto& item : list) {
		out << item.first << fsep;
		auto end_it = item.second.end();
		auto current_it = item.second.begin();
		if (current_it != end_it) {
			out << *current_it;
			current_it++;
		}
		while(current_it != end_it) {
			out << osep << *current_it;
			current_it++;
		}
		out << endl;
	}
}

int DirAdjList::bfs_distations(int node, vector<int>& lengths_empty) {
	try {
		list.at(node);
	}
	catch (const out_of_range& e) {
		vector<int> colors(max_number + 1);
		for (auto& color : colors) {
			color = -1;
		}
		swap(lengths_empty, colors);
		return -1;
	}
	queue<int> nodes;

	vector<int> colors(max_number + 1);
	for (auto& color : colors) {
		color = -1;
	}

	int step = 1;
	nodes.push(node);
	colors[node] = 0;

	while (!nodes.empty()) {
		int v = nodes.front();
		nodes.pop();

		for (const auto& item : list[v]) {
			if (colors[item] == -1) { 
				colors[item] = colors[v] + 1;
				nodes.push(item);
			}
		}
	}
	swap(lengths_empty, colors);
	return 0;
}

void DFS_dir(bool& is_acyclic_start_true, const int v, vector<COLOR>& colors,
	map<int, set<int>>& list,
	vector<int>& back_toporder) {
	if (colors[v] == WHITE) {
		colors[v] = GREY;
		if (list.find(v) != list.end()) {
			set<int> nodes = list[v];
			for (const auto& item : nodes) {
				if (colors[item] == WHITE) {
					DFS_dir(is_acyclic_start_true, item, colors, list, back_toporder);
				}
				if (colors[item] == GREY) {
					is_acyclic_start_true = false;
				}
			}
		}
		colors[v] = BLACK;
		back_toporder.push_back(v);
	}
}

int DirAdjList::dfs_acyclicityCheck(vector<int>& empty_vector) {
	vector<int> toporder;
	vector<COLOR> colors(max_number + 1);
	for (auto& color : colors) {
		color = WHITE;
	}
	bool is_acyclic = true;
	for (const auto& item : list) {
		DFS_dir(is_acyclic, item.first, colors, list, toporder);
	}
	if (is_acyclic) {
		swap(toporder, empty_vector);
		return 0;
	}
	else {
		return -1;
	}
}

// SimpleAdjList

SimpleAdjList::SimpleAdjList(string filename) : DirAdjList(filename) {
	// making simple
	for (auto& item : list) {
		for (auto& elem : item.second) {
			int num = item.first;
			
			if (list.find(elem) == list.end()) {
				list[elem].insert(num);
			} else if (list[elem].find(num) == list[elem].end()) {
				list[elem].insert(num);
			}
		}
	}
}

int SimpleAdjList::bfs_findComp(vector<int>& lengths_empty) {
	queue<int> nodes;

	vector<int> colors(max_number + 1);
	for (auto& color : colors) {
		color = -1;
	}

	int counter = 0;

	for (const auto& elem : list) {
		int node = elem.first;
		if (colors[node] != -1) continue;

		counter++;
		nodes.push(node);
		colors[node] = counter;

		while (!nodes.empty()) {
			
			int v = nodes.front();
			nodes.pop();

			for (const auto& item : list[v]) {
				if (colors[item] == -1) {
					colors[item] = counter;
					nodes.push(item);
				}
			}
		}
	}
	swap(lengths_empty, colors);
	return 0;
}

void DFS_simple(bool& is_acyclic_start_true, const int v, vector<COLOR>& colors,
	map<int, set<int>>& list,
	vector<int>& back_toporder,
	const int& parent) {
	if (colors[v] == WHITE) {
		colors[v] = GREY;
		if (list.find(v) != list.end()) {
			set<int> nodes = list[v];
			for (const auto& item : nodes) {
				if (colors[item] == WHITE) {
					DFS_simple(is_acyclic_start_true, item, colors, list, back_toporder, v);
				}
				if (colors[item] == GREY && parent != item) {
					is_acyclic_start_true = false;
				}
			}
		}
		colors[v] = BLACK;
		back_toporder.push_back(v);
	}
}

int SimpleAdjList::dfs_acyclicityCheck(vector<int>& empty_vector) {
	vector<int> toporder;
	vector<COLOR> colors(max_number + 1);
	for (auto& color : colors) {
		color = WHITE;
	}
	bool is_acyclic = true;
	for (const auto& item : list) {
		DFS_simple(is_acyclic, item.first, colors, list, toporder, -1);
	}
	if (is_acyclic) {
		swap(toporder, empty_vector);
		return 0;
	}
	else {
		return -1;
	}
}
