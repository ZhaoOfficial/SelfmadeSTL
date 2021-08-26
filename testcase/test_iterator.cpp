#include <iostream>

#include "../stl_iterator.hpp"
#include "../stl_function.hpp"
#include "../stl_vector.hpp"
#include "../stl_list.hpp"

#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

using std::cout;
using std::endl;

int main() {

	{
		selfmadeSTL::vector<int> v(1);
		selfmadeSTL::list<int> l;
		int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
		selfmadeSTL::ostream_iterator<int> oi(cout, " ");
		auto bi = selfmadeSTL::back_inserter(v);
		auto fi = selfmadeSTL::front_inserter(l);
		auto i = selfmadeSTL::inserter(l, l.begin());

		selfmadeSTL::transform(arr, arr + 10, bi, selfmadeSTL::identity<int>());
		selfmadeSTL::transform(v.begin(), v.end(), oi, selfmadeSTL::identity<int>());
		cout << endl;
		selfmadeSTL::transform(arr, arr + 10, fi, selfmadeSTL::identity<int>());
		selfmadeSTL::transform(l.begin(), l.end(), oi, selfmadeSTL::identity<int>());
		cout << endl;
		selfmadeSTL::transform(arr, arr + 10, i, selfmadeSTL::identity<int>());
		selfmadeSTL::transform(l.begin(), l.end(), oi, selfmadeSTL::identity<int>());
		cout << endl;
	}

	{
		std::vector<int> v(1);
		std::list<int> l;
		int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
		std::ostream_iterator<int> oi(cout, " ");
		auto bi = std::back_inserter(v);
		auto fi = std::front_inserter(l);
		auto i = std::inserter(l, l.begin());

		auto identity = [](auto x) { return x; };
		std::transform(arr, arr + 10, bi, identity);
		std::transform(v.begin(), v.end(), oi, identity);
		cout << endl;
		std::transform(arr, arr + 10, fi, identity);
		std::transform(l.begin(), l.end(), oi, identity);
		cout << endl;
		std::transform(arr, arr + 10, i, identity);
		std::transform(l.begin(), l.end(), oi, identity);
		cout << endl;
	}


	return 0;
}