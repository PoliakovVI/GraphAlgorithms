#include "Adjacency_list.h"

enum COLOR {
	WHITE,
	GREY,
	BLACK
};

// DirAdjList

//private

DirAdjList& DirAdjList::reverse() {
	map<int, set<int>> newlist;

	// making reverse
	for (const auto& item : list) {
		for (const auto& elem : item.second) {
			newlist[elem].insert(item.first);
		}
	}

	swap(list, newlist);
	return *this;
}

DirAdjList::DirAdjList() {

}

// public

DirAdjList::DirAdjList(string filename) {
	ifstream fin(filename);
	string line;
	int number, point;

	if (fin.is_open()) {
		while (getline(fin, line)) {

			// parcing line with stream
			stringstream ss(line);
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

DirAdjList::DirAdjList(const DirAdjList& dal) {
	this->max_number = dal.max_number;
	this->list = dal.list;
}

void DirAdjList::print(ostream& out, string fsep, string osep) {
	for (const auto& item : list) {
		// out the beginning with separator
		out << item.first << fsep;

		auto end_it = item.second.end();
		auto current_it = item.second.begin();

		//is_empty check
		if (current_it != end_it) { 
			out << *current_it;
			current_it++;
		}

		// out other elements
		while(current_it != end_it) {
			out << osep << *current_it;
			current_it++;
		}
		out << endl;
	}
}

int DirAdjList::countDistations(int node, vector<int>& lengths_empty) {

	// node existence in list check
	if(list.find(node) == list.end()){
		vector<int> colors(max_number + 1);
		for (auto& color : colors) {
			color = -1; // means no ways to other nodes
		}
		swap(lengths_empty, colors);
		return -1;
	}

	queue<int> nodes;

	vector<int> colors(max_number + 1);
	for (auto& color : colors) {
		color = -1; // filling with negative distance
	}

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

void DFS_dir_acyclic(bool& is_acyclic_start_true, const int v, vector<COLOR>& colors,
	map<int, set<int>>& list,
	vector<int>& back_toporder) {
	if (colors[v] == WHITE) {
		colors[v] = GREY;
		if (list.find(v) != list.end()) {
			set<int> nodes = list[v];

			for (const auto& item : nodes) {
				if (colors[item] == WHITE) {
					DFS_dir_acyclic(is_acyclic_start_true, item, colors, list, back_toporder);
				}
				if (colors[item] == GREY) {
					is_acyclic_start_true = false; // acyclicity check
				}
			}
		}
		colors[v] = BLACK;
		back_toporder.push_back(v);
	}
}

int DirAdjList::acyclicityCheck(vector<int>& empty_vector) {
	vector<int> toporder;
	vector<COLOR> colors(max_number + 1);

	// making all white
	for (auto& color : colors) {
		color = WHITE;
	}

	// lainching DFS
	bool is_acyclic = true;
	for (const auto& item : list) {
		DFS_dir_acyclic(is_acyclic, item.first, colors, list, toporder);
	}

	swap(toporder, empty_vector);

	if (is_acyclic) {
		return 0;
	}
	else {
		return -1;
	}
}

void DFS_dir_color(const int v, vector<int>& colors,
	int current_color, map<int, set<int>>& list,
	vector<int>& back_toporder) {
	if (colors[v] == -2) { // if current white (it needs for start nodes check)
		colors[v] = -1;
		if (list.find(v) != list.end()) {
			set<int> nodes = list[v];

			for (const auto& item : nodes) {
				if (colors[item] == -2) { // if white
					DFS_dir_color(item, colors, current_color, list, back_toporder);
				} 
			}
		}
		colors[v] = current_color;
		back_toporder.push_back(v);
	}
}

void DirAdjList::strongComponentSearch(vector<int>& empty_colors) {
	vector<int> toporder;
	vector<int> empty_vector;

	empty_colors.clear();

	for (int i = 0; i < max_number + 1; i++) {
		empty_colors.push_back(-2); // fillng with white
	}

	for (const auto& item : list) {
		DFS_dir_color(item.first, empty_colors, 1, list, toporder);
	}

	for (auto& color : empty_colors) {
		color = -2; // filling with white
	}

	std::reverse(toporder.begin(), toporder.end()); // making it direct

	DirAdjList copy_list(*this);
	copy_list.reverse();

	int current_color = 0;
	for (const auto& item : toporder) {
		if (empty_colors[item] == -2) {
			current_color++;
			DFS_dir_color(item, empty_colors, current_color, copy_list.list, empty_vector);
		}
	}

	// filling nodes that have no edges
	for (auto& item : empty_colors) {
		if (item == -2) {
			current_color++;
			item = current_color;
		}
	}
}

// SimpleAdjList

// private

void SimpleAdjList::make_simple(map<int, set<int>>& list){
	for (auto& item : list) {
		for (auto& elem : item.second) {
			int num = item.first;

			if (list.find(elem) == list.end()) {
				list[elem].insert(num);
			}
			else if (list[elem].find(num) == list[elem].end()) {
				list[elem].insert(num);
			}
		}
	}
}

// public

SimpleAdjList::SimpleAdjList(string filename) : DirAdjList(filename) {
	make_simple(list);	
}

SimpleAdjList::SimpleAdjList(const SimpleAdjList* sal){
	this->max_number = sal->max_number;
	this->list = sal->list;
}

void SimpleAdjList::findComponents(vector<int>& lengths_empty) {
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

	for (auto& item : colors) {
		if (item == -1) {
			counter++;
			item = counter;
		}
	}

	swap(lengths_empty, colors);
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

int SimpleAdjList::acyclicityCheck(vector<int>& empty_vector) {
	vector<int> toporder;
	vector<COLOR> colors(max_number + 1);

	for (auto& color : colors) {
		color = WHITE;
	}

	bool is_acyclic = true;


	for (const auto& item : list) {
		DFS_simple(is_acyclic, item.first, colors, list, toporder, -1);
	}

	swap(toporder, empty_vector);

	if (is_acyclic) {
		return 0;
	}
	else {
		return -1;
	}
}

void SimpleAdjList::strongComponentSearch(vector<int>& empty_vector) {
	this->findComponents(empty_vector);
}

int DFS_simple_articulation_points(const int v, vector<int>& colors, 
	map<int, set<int>>& list, vector<int>& M_statistics, vector<int>& entrances,
	const int& parent, int& timer) {
	colors[v] = -1; // <- grey
	entrances[v] = timer; // <- timer
	timer++;

	int tree_edges_counter = 0;

	// node in list existence
	if (list.find(v) != list.end()) {
		set<int> nodes = list[v];

		for (const auto& item : nodes) {

			if (colors[item] == -2) {
				tree_edges_counter++;
				DFS_simple_articulation_points(item, colors, list, M_statistics,
					entrances, v, timer);

				if (M_statistics[v] > 0) {
					M_statistics[v] = min(M_statistics[v], M_statistics[item]);
				}
				else {
					M_statistics[v] = M_statistics[item];
					/*if (M_statistics[item] != -1) {
						M_statistics[v] = M_statistics[item];
					}
					else {
						M_statistics[v] = entrances[v];
					}*/
				}

				if (M_statistics[item] >= entrances[v] || M_statistics[item] == -1) {
					colors[v] = 1;
				}
			}
			else if (colors[item] == -1 && parent != item) {
				if (M_statistics[v] > 0) {
					M_statistics[v] = min(M_statistics[v], entrances[item]);
				}
				else {
					M_statistics[v] = entrances[item];
				}
			}
		}
	}
	if (colors[v] != 1) colors[v] = 0;
	return tree_edges_counter;
}

void SimpleAdjList::articulationPointsSearch(vector<int>& empty_vector){
	vector<int> colors(max_number + 1);
	vector<int> M_statistics(max_number + 1);
	vector<int> entrances(max_number + 1);

	for (auto& color : colors) {
		color = -2;
	}
	for (auto& M : M_statistics) {
		M = -1;
	}

	int timer = 1;

	for (const auto& item : list) {
		if (colors[item.first] == -2) {
			int tree_edges_number = DFS_simple_articulation_points(item.first, colors, list, 
				M_statistics, entrances, -1, timer);
			if (tree_edges_number > 1) {
				colors[item.first] = 1;
			}
			else {
				colors[item.first] = 0;
			}
		}
	}

	for (auto& color : colors) {
		if (color == -2) color = 0;
	}

	swap(colors, empty_vector);
}
