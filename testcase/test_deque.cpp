#include <iostream>
#include <cstdlib>
#include <deque>
#include <complex>
#include <random>
#include <climits>

#include "../stl_deque.hpp"
#include "../stl_type_traits.hpp"
#include "test_function.hpp"

using std::cout;
using std::endl;
using std::complex;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::numeric_limits;

int main() {
	// initialize
	const size_t pod_size = 100000;
	const size_t npod_size = pod_size / 2;
	double* pod_data = new double[pod_size];
	Npod* npod_data = new Npod[npod_size];

	default_random_engine rng;
	uniform_real_distribution<double> uniform_double(
		numeric_limits<double>::min(), numeric_limits<double>::max()
	);
	for (size_t i = 0; i < pod_size; ++i) {
		pod_data[i] = uniform_double(rng);
	}
	for (size_t i = 0; i < npod_size; ++i) {
		npod_data[i].ptr->real(pod_data[2 * i]);
		npod_data[i].ptr->imag(pod_data[2 * i + 1]);
	}

	// testing
	{
		cout << "----- Test of POD default constructor and copy constructor -----\n";
		SelfMadeSTL::deque<double> self_default_pod;
	}

	return 0;
}