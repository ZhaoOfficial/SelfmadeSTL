#include <iostream>

#include "../stl_algorithm.hpp"
#include "../stl_function.hpp"
#include "../stl_vector.hpp"
#include "test_function.hpp"

using namespace selfmadeSTL;
using std::cout;
using std::endl;

int main() {

	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));

	cout << *adjacent_find(v.begin(), v.end()) << endl;
	cout << *adjacent_find(v.begin(), v.end(), equal_to<int>()) << endl;

	cout << count(v.begin(), v.end(), 6) << endl;
	cout << count_if(v.begin(), v.end(), bind2nd(less<int>(), 7)) << endl;

	cout << *find(v.begin(), v.end(), 4) << endl;
	cout << *find_if(v.begin(), v.end(), bind2nd(greater<int>(), 2)) << endl;

	vector<int> v2(arr + 6, arr + 8);
	cout << *(find_end(v.begin(), v.end(), v2.begin(), v2.end()) + 3) << endl;
	cout << *(find_first_of(v.begin(), v.end(), v2.begin(), v2.end()) + 3) << endl;

	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	generate(v2.begin(), v2.end(), add2());
	for_each(v2.begin(), v2.end(), display<int>());
	cout << endl;

	generate_n(v.begin(), 3, add2());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	remove(v.begin(), v.end(), 6);
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	vector<int> v3(12);
	remove_copy(v.begin(), v.end(), v3.begin(), 6);
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	remove_if(v.begin(), v.end(), bind2nd(less<int>(), 6));
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	remove_copy_if(v.begin(), v.end(), v3.begin(), bind2nd(less<int>(), 7));
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	replace(v.begin(), v.end(), 6, 3);
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	replace_copy(v.begin(), v.end(), v3.begin(), 3, 5);
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	replace_if(v.begin(), v.end(), bind2nd(less<int>(), 5), 2);
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	replace_copy_if(v.begin(), v.end(), v3.begin(), bind2nd(equal_to<int>(), 8), 9);
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	reverse(v.begin(), v.end());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	reverse_copy(v.begin(), v.end(), v3.begin());
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	rotate(v.begin(), v.begin() + 4, v.end());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	rotate_copy(v.begin(), v.begin() + 5, v.end(), v3.begin());
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	int arr2[] = { 2, 8 };
	vector<int> v4(arr2, arr2 + 2);
	cout << *search(v.begin(), v.end(), v4.begin(), v4.end()) << endl;

	cout << *search_n(v.begin(), v.end(), 2, 8) << endl;

	cout << *search_n(v.begin(), v.end(), 3, 8, less<int>()) << endl;

	swap_ranges(v4.begin(), v4.end(), v.begin());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;
	for_each(v4.begin(), v4.end(), display<int>());
	cout << endl;

	transform(v.begin(), v.end(), v.begin(), bind2nd(minus<int>(), 2));
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	transform(v.begin(), v.end(), v.begin(), v.begin(), plus<int>());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;
	
	// set
	vector<int> v5(arr, arr + sizeof(arr) / sizeof(int));
	vector<int> v6(arr + 4, arr + 8);
	vector<int> v7(15);
	cout << *max_element(v5.begin(), v5.end()) << endl;
	cout << *min_element(v5.begin(), v5.end()) << endl;

	cout << includes(v5.begin(), v5.end(), v6.begin(), v6.end()) << endl;

	merge(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin());
	for_each(v7.begin(), v7.end(), display<int>());
	cout << endl;
	
	partition(v7.begin(), v7.end(), even());
	for_each(v7.begin(), v7.end(), display<int>());
	cout << endl;

	unique(v5.begin(), v5.end());
	for_each(v5.begin(), v5.end(), display<int>());
	cout << endl;

	unique_copy(v5.begin(), v5.end(), v7.begin());
	for_each(v7.begin(), v7.end(), display<int>());
	cout << endl;

	return 0;
}