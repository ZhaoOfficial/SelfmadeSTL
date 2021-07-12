#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <complex>
#include <random>

#include "../stl_list.hpp"
#include "../stl_type_traits.hpp"

using std::cout;
using std::endl;
using std::complex;

int main() {

	{
		SelfMadeSTL::list<int> self_default;
		std::list<int> std_default;
	}

	return 0;
}