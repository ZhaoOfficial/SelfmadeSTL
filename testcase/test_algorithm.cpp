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
	cout << std::boolalpha;

	cout << "adjacent_find: " << *adjacent_find(v.begin(), v.end()) << endl;
	cout << "adjacent_find: " << *adjacent_find(v.begin(), v.end(), equal_to<int>()) << endl;

	cout << "count: " << count(v.begin(), v.end(), 6) << endl;
	cout << "count: " << count_if(v.begin(), v.end(), bind2nd(less<int>(), 7)) << endl;

	cout << "find: " << *find(v.begin(), v.end(), 4) << endl;
	cout << "find: " << *find_if(v.begin(), v.end(), bind2nd(greater<int>(), 2)) << endl;

	vector<int> v2(arr + 6, arr + 8);
	cout << "find_end: " << *(find_end(v.begin(), v.end(), v2.begin(), v2.end()) + 3) << endl;
	cout << "find_first_of: " << *(find_first_of(v.begin(), v.end(), v2.begin(), v2.end()) + 3) << endl;

	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	generate(v2.begin(), v2.end(), add2());
	cout << "generate: ";
	for_each(v2.begin(), v2.end(), display<int>());
	cout << endl;

	generate_n(v.begin(), 3, add2());
	cout << "generate_n: ";
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	remove(v.begin(), v.end(), 6);
	cout << "remove: ";
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	vector<int> v3(12);
	cout << "remove_copy: ";
	remove_copy(v.begin(), v.end(), v3.begin(), 6);
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	cout << "remove_if: ";
	remove_if(v.begin(), v.end(), bind2nd(less<int>(), 6));
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	cout << "remove_copy_if: ";
	remove_copy_if(v.begin(), v.end(), v3.begin(), bind2nd(less<int>(), 7));
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	cout << "replace: ";
	replace(v.begin(), v.end(), 6, 3);
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	cout << "replace_copy: ";
	replace_copy(v.begin(), v.end(), v3.begin(), 3, 5);
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	cout << "replace_if: ";
	replace_if(v.begin(), v.end(), bind2nd(less<int>(), 5), 2);
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	cout << "replace_copy_if: ";
	replace_copy_if(v.begin(), v.end(), v3.begin(), bind2nd(equal_to<int>(), 8), 9);
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	cout << "reverse: ";
	reverse(v.begin(), v.end());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	cout << "reverse_copy: ";
	reverse_copy(v.begin(), v.end(), v3.begin());
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	cout << "rotate: ";
	rotate(v.begin(), v.begin() + 4, v.end());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	cout << "rotate_copy: ";
	rotate_copy(v.begin(), v.begin() + 5, v.end(), v3.begin());
	for_each(v3.begin(), v3.end(), display<int>());
	cout << endl;

	int arr2[] = { 2, 8 };
	vector<int> v4(arr2, arr2 + 2);
	cout << "search" << *search(v.begin(), v.end(), v4.begin(), v4.end()) << endl;

	cout << "search_n" << *search_n(v.begin(), v.end(), 2, 8) << endl;

	cout << "search_n" << *search_n(v.begin(), v.end(), 3, 8, less<int>()) << endl;

	cout << "swap_ranges: ";
	swap_ranges(v4.begin(), v4.end(), v.begin());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;
	for_each(v4.begin(), v4.end(), display<int>());
	cout << endl;

	cout << "transform: ";
	transform(v.begin(), v.end(), v.begin(), bind2nd(minus<int>(), 2));
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	cout << "transform: ";
	transform(v.begin(), v.end(), v.begin(), v.begin(), plus<int>());
	for_each(v.begin(), v.end(), display<int>());
	cout << endl;

	vector<int> v5(arr, arr + sizeof(arr) / sizeof(int));
	vector<int> v6(arr + 4, arr + 8);
	vector<int> v7(15);
	cout << "max_element: " << *max_element(v5.begin(), v5.end()) << endl;
	cout << "min_element: " << *min_element(v5.begin(), v5.end()) << endl;

	cout << "includes: " << includes(v5.begin(), v5.end(), v6.begin(), v6.end()) << endl;

	cout << "merge: ";
	merge(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin());
	for_each(v7.begin(), v7.end(), display<int>());
	cout << endl;
	
	cout << "partition: ";
	partition(v7.begin(), v7.end(), even());
	for_each(v7.begin(), v7.end(), display<int>());
	cout << endl;

	cout << "unique: ";
	unique(v5.begin(), v5.end());
	for_each(v5.begin(), v5.end(), display<int>());
	cout << endl;

	cout << "unique_copy: ";
	unique_copy(v5.begin(), v5.end(), v7.begin());
	for_each(v7.begin(), v7.end(), display<int>());
	cout << endl;

	int arr3[8] = { 12, 17, 20, 22, 23, 30, 33, 40 };
	vector<int> v8(arr3, arr3 + 8);

	cout << "lower_bound: " << *lower_bound(v8.begin(), v8.end(), 21) << endl;
	cout << "upper_bound: " << *upper_bound(v8.begin(), v8.end(), 21) << endl;
	cout << "lower_bound: " << *lower_bound(v8.begin(), v8.end(), 22) << endl;
	cout << "upper_bound: " << *upper_bound(v8.begin(), v8.end(), 22) << endl;

	cout << "binary_search: " << binary_search(v8.begin(), v8.end(), 33) << endl;
	cout << "binary_search: " << binary_search(v8.begin(), v8.end(), 34) << endl;

	cout << "next_permutation: ";
	next_permutation(v8.begin(), v8.end());
	for_each(v8.begin(), v8.end(), display<int>());
	cout << endl;
	cout << "prev_permutation: ";
	prev_permutation(v8.begin(), v8.end());
	for_each(v8.begin(), v8.end(), display<int>());
	cout << endl;

	cout << "random_shuffle: ";
	random_shuffle(v8.begin(), v8.end());
	for_each(v8.begin(), v8.end(), display<int>());
	cout << endl;

	return 0;
}