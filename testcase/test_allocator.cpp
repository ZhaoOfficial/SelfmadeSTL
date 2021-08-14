#include <iostream>
#include <vector>
#include <list>

#include "../stl_allocator.hpp"

using namespace std;

int main() {
	int arr[5] = { 0, 1, 2, 3, 4 };

	vector<int, selfmadeSTL::allocator<int>> vec(arr, arr + 5);
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec[i] << ' ';
	}

	cout << endl;

	list<int, selfmadeSTL::allocator<int>> li(arr, arr + 5);
	for (auto it = li.begin(); it != li.end(); it++) {
		cout << *it << ' ';
	}

	cout << endl;

	selfmadeSTL::allocator<int> A;
	cout << A.init_page_size() << "[1024]\n";
	cout << A.max_size() << "[1073741823]\n";

	cout << endl;
}