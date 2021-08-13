#include <iostream>
#include <cstdlib>
#include <queue>
#include <complex>
#include <random>

#include "../stl_heap.hpp"
#include "../stl_queue.hpp"
#include "../stl_type_traits.hpp"
#include "test_function.hpp"

using std::cout;
using std::endl;
using std::complex;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::numeric_limits;


int main(int argc, char* argv[]) {
	// initialize
	const size_t npod_size = 10000;
	Npod* npod_data = new Npod[npod_size];

	default_random_engine rng;
	uniform_real_distribution<double> uniform_double(
		0.0, 1e6
	);
	for (size_t i = 0; i < npod_size; ++i) {
		npod_data[i].ptr->real(uniform_double(rng));
		npod_data[i].ptr->imag(uniform_double(rng));
	}

	// testing
	{

	}
	cout << endl;
	{

	}
	cout << endl;

	delete[] npod_data;
};