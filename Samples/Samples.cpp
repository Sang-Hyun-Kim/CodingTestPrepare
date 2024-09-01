#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
	int a[5] = { 1, 2, 3, 4, 5 };

	vector<int> vec;

	for (int i = 0; i < 5; i++) {
		vec.push_back(a[i]);
	}

	vector<bool> visited(5, true);

	for (int i = 0; i < vec.size() - 3; i++) visited[i] = false;
	do {
		for (int i = 0; i < vec.size(); i++) {
			if (visited[i])	cout << vec[i] << " ";
		}
		cout << endl;
	} while (next_permutation(visited.begin(), visited.end()));

	return 0;
}