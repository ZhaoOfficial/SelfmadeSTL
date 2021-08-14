#include <iostream>

#include "../stl_function.hpp"
#include "../stl_numeric.hpp"
#include "../stl_vector.hpp"

using std::cout;
using std::endl;
using namespace selfmadeSTL;

int main() {

	int arr[5] = { 1, 2, 3, 4, 5 };
	vector<int> u(arr, arr + 5);
	vector<int> v(5, 0);

	cout << "accumulate: " << accumulate(u.begin(), u.end(), 0) << endl;
	cout << "accumulate: " << accumulate(u.begin(), u.end(), 0, multiply<int>()) << endl;
	adjacent_difference(u.begin(), u.end(), v.begin());
	cout << "adjacent_difference: ";
	for (auto &i : v) {
		cout << i << " ";
	}
	cout << endl;
	adjacent_difference(u.begin(), u.end(), v.begin(), multiply<int>());
	cout << "adjacent_difference: ";
	for (auto &i : v) {
		cout << i << " ";
	}
	cout << endl;
	partial_sum(u.begin(), u.end(), v.begin());
	cout << "partial_sum: ";
	for (auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
	partial_sum(u.begin(), u.end(), v.begin(), multiply<int>());
	cout << "partial_sum: ";
	for (auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
	cout << "inner_product: " << inner_product(u.begin(), u.end(), v.begin(), 0) << endl;
	cout << "inner_product: " << inner_product(u.begin(), u.end(), v.begin(), 0, plus<int>(), plus<int>()) << endl;
	cout << "power: " << power(2ULL, 50) << endl;
	iota(v.begin(), v.end(), 6);
	cout << "partial_sum: ";
	for (auto& i : v) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}