#include "Adjacency_list.h"
#include <functional>

template<class T>
void print_range(T itbegin, T itend, bool print_with_index = false) {
	int index = 0;
	for (auto current_it = itbegin; current_it < itend; current_it++) {
		if (print_with_index) cout << index << " ";
		cout << *current_it;
		cout << endl;
		index++;
	}
}

int main() {
	DirAdjList list1("test.txt");
	list1.print(cout, ": ", ", ");
	vector<int> vec;

	cout << endl << "dists:" << endl;
	list1.countDistations(6, vec);
	print_range(vec.begin(), vec.end(), true);

	cout << endl << "acyclicity:" << endl;
	if (list1.acyclicityCheck(vec) == -1) cout << "acyclic" << endl;
	else print_range(vec.begin(), vec.end());

	cout << endl << "strong comp:" << endl;
	list1.strongComponentSearch(vec);
	print_range(vec.begin(), vec.end(), true);

	
	SimpleAdjList list2("test.txt");
	list2.print(cout, ": ", ", ");

	cout << endl << "dists:" << endl;
	list2.countDistations(6, vec);
	print_range(vec.begin(), vec.end(), true);

	cout << endl << "acyclicity:" << endl;
	if (list2.acyclicityCheck(vec) == -1) cout << "acyclic" << endl;
	else print_range(vec.begin(), vec.end());

	cout << endl << "comp:" << endl;
	list2.findComponents(vec);
	print_range(vec.begin(), vec.end(), true);

	cout << endl << "comp:" << endl;
	list2.strongComponentSearch(vec);
	print_range(vec.begin(), vec.end(), true);

	cout << endl << "art points:" << endl;
	list2.articulationPointsSearch(vec);
	print_range(vec.begin(), vec.end(), true);

	getchar();
	return 0;
}