#include "Adjacency_list.h"
#include <functional>

int main() {
	const int v = 5;

	DirAdjList list1("input.txt");
	list1.print(cout, ": ", ", ");
	vector<int> lenghts;
	list1.bfs_distations(v, lenghts);

	int i = 0;
	cout << endl << endl;
	for (const auto& item : lenghts) {
		cout << i << " " << item << endl;
		i++;
	}
	cout << endl << endl;

	lenghts.clear();
	list1.dfs_acyclicityCheck(lenghts);

	i = 0;
	cout << endl << endl;
	for (const auto& item : lenghts) {
		cout << " " << item;
	}
	cout << endl << endl;

	SimpleAdjList list2("input.txt");
	
	lenghts.clear();
	list2.print(cout, ": ", ", ");
	cout << list2.dfs_acyclicityCheck(lenghts);

	i = 0;
	cout << endl << endl;
	for (const auto& item : lenghts) {
		cout << " " << item;
	}
	cout << endl << endl;

	getchar();
	return 0;
}