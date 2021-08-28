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
using std::default_random_engine;
using std::uniform_real_distribution;
using std::numeric_limits;


int main(int argc, char* argv[]) {
	// initialize
	const size_t npod_size = 15;
	Npod* npod_data = new Npod[npod_size];

	default_random_engine rng;
	uniform_real_distribution<double> uniform_double_low(
		1e1, 1e2
	);
	uniform_real_distribution<double> uniform_double_mid(
		1e2, 1e3
	);
	uniform_real_distribution<double> uniform_double_high(
		1e3, 1e4
	);
	for (size_t i = 0; i < 5; ++i) {
		npod_data[i].ptr->real(uniform_double_low(rng));
		npod_data[i].ptr->imag(uniform_double_low(rng));
	}
	for (size_t i = 5; i < npod_size - 5; ++i) {
		npod_data[i].ptr->real(uniform_double_mid(rng));
		npod_data[i].ptr->imag(uniform_double_mid(rng));
	}
	for (size_t i = npod_size - 5; i < npod_size; ++i) {
		npod_data[i].ptr->real(uniform_double_high(rng));
		npod_data[i].ptr->imag(uniform_double_high(rng));
	}

	// testing
	{
		cout << "----- selfmade -----\n";
		selfmadeSTL::priority_queue<Npod> self_max(npod_data, npod_data + npod_size - 5);
		cout << "max heap: size = " << self_max.size() << ", "
			<< "top() = " << self_max.top().ptr->real() << ", "
			<< self_max.top().ptr->imag() << "\n";

		for (size_t i = npod_size - 5; i < npod_size; ++i) {
			self_max.push(npod_data[i]);
		}
		cout << "push: size = " << self_max.size() << ", "
			<< "top() = " << self_max.top().ptr->real() << ", "
			<< self_max.top().ptr->imag() << "\n";

		for (size_t i = 0; i < 5; ++i) {
			self_max.pop();
		}
		cout << "pop: size = " << self_max.size() << ", "
			<< "top() = " << self_max.top().ptr->real() << ", "
			<< self_max.top().ptr->imag() << "\n";

		selfmadeSTL::priority_queue<Npod, selfmadeSTL::vector<Npod>, selfmadeSTL::greater<Npod>> self_min(npod_data + 5, npod_data + npod_size);
		cout << "min heap: size = " << self_min.size() << ", "
			<< "top() = " << self_min.top().ptr->real() << ", "
			<< self_min.top().ptr->imag() << "\n";

		for (size_t i = 0; i < 5; ++i) {
			self_min.push(npod_data[i]);
		}
		cout << "push: size = " << self_min.size() << ", "
			<< "top() = " << self_min.top().ptr->real() << ", "
			<< self_min.top().ptr->imag() << "\n";

		for (size_t i = 0; i < 5; ++i) {
			self_min.pop();
		}
		cout << "pop: size = " << self_min.size() << ", "
			<< "top() = " << self_min.top().ptr->real() << ", "
			<< self_min.top().ptr->imag() << "\n";

	}
	cout << endl;
	{
		cout << "----- reference -----\n";
		std::priority_queue<Npod> std_max(npod_data, npod_data + npod_size - 5);
		cout << "max heap: size = " << std_max.size() << ", "
			<< "top() = " << std_max.top().ptr->real() << ", "
			<< std_max.top().ptr->imag() << "\n";

		for (size_t i = npod_size - 5; i < npod_size; ++i) {
			std_max.push(npod_data[i]);
		}
		cout << "push: size = " << std_max.size() << ", "
			<< "top() = " << std_max.top().ptr->real() << ", "
			<< std_max.top().ptr->imag() << "\n";

		for (size_t i = 0; i < 5; ++i) {
			std_max.pop();
		}
		cout << "pop: size = " << std_max.size() << ", "
			<< "top() = " << std_max.top().ptr->real() << ", "
			<< std_max.top().ptr->imag() << "\n";

		std::priority_queue<Npod, std::vector<Npod>, std::greater<Npod>> std_min(npod_data + 5, npod_data + npod_size);
		cout << "min heap: size = " << std_min.size() << ", "
			<< "top() = " << std_min.top().ptr->real() << ", "
			<< std_min.top().ptr->imag() << "\n";

		for (size_t i = 0; i < 5; ++i) {
			std_min.push(npod_data[i]);
		}
		cout << "push: size = " << std_min.size() << ", "
			<< "top() = " << std_min.top().ptr->real() << ", "
			<< std_min.top().ptr->imag() << "\n";

		for (size_t i = 0; i < 5; ++i) {
			std_min.pop();
		}
		cout << "pop: size = " << std_min.size() << ", "
			<< "top() = " << std_min.top().ptr->real() << ", "
			<< std_min.top().ptr->imag() << "\n";
	}
	cout << endl;

	delete[] npod_data;
};