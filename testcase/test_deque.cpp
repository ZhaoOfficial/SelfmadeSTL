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
	const size_t pod_size = 1000;
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
		selfmadeSTL::deque<double> self_default_pod;
		cout << std::boolalpha << "is empty? "
			<< self_default_pod.empty() << "\n";

		self_default_pod.insert(self_default_pod.begin(), 0.0);
		self_default_pod.insert(self_default_pod.end(), pod_data, pod_data + pod_size - 1);
		cout << "insert: size = " << self_default_pod.size() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		self_default_pod.push_back(pod_data[pod_size - 1]);
		cout << "push_back: size = " << self_default_pod.size() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		self_default_pod.pop_back();
		cout << "pop: size = " << self_default_pod.size() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		selfmadeSTL::deque<double> self_default_pod2(self_default_pod);
		cout << std::boolalpha << "is the same? "
			<< (self_default_pod == self_default_pod2) << ", "
			<< (self_default_pod != self_default_pod2) << "\n";

		self_default_pod2.erase(self_default_pod2.begin());
		cout << "erase: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.resize(pod_size / 2);
		cout << "resize: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.resize(2 * pod_size);
		cout << "resize: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod.swap(self_default_pod2);
		cout << "swap: size1 = " << self_default_pod.size() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n"
			<< "swap: size2 = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";
	}
	cout << endl;
	{
		cout << "----- Here is the reference -----\n";
		std::deque<double> std_default_pod;
		cout << std::boolalpha << "is empty? "
			<< std_default_pod.empty() << "\n";

		std_default_pod.insert(std_default_pod.begin(), 0.0);
		std_default_pod.insert(std_default_pod.end(), pod_data, pod_data + pod_size - 1);
		cout << "insert: size = " << std_default_pod.size() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std_default_pod.push_back(pod_data[pod_size - 1]);
		cout << "push_back: size = " << std_default_pod.size() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std_default_pod.pop_back();
		cout << "pop: size = " << std_default_pod.size() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std::deque<double> std_default_pod2(std_default_pod);
		cout << std::boolalpha << "is the same? "
			<< (std_default_pod == std_default_pod2) << ", "
			<< (std_default_pod != std_default_pod2) << "\n";

		std_default_pod2.erase(std_default_pod2.begin());
		cout << "erase: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.resize(pod_size / 2);
		cout << "resize: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.resize(2 * pod_size);
		cout << "resize: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod.swap(std_default_pod2);
		cout << "swap: size1 = " << std_default_pod.size() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n"
			<< "swap: size2 = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";
	}
	cout << endl;
	{
		cout << "----- Test of non-POD default constructor and copy constructor -----\n";
		selfmadeSTL::deque<Npod> self_default_npod;
		cout << std::boolalpha << "is empty? "
			<< self_default_npod.empty() << "\n";

		self_default_npod.insert(self_default_npod.begin(), Npod());
		self_default_npod.insert(self_default_npod.end(), npod_data, npod_data + npod_size - 1);
		cout << "insert: size = " << self_default_npod.size() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n";

		self_default_npod.push_back(npod_data[npod_size - 1]);
		cout << "push_back: size = " << self_default_npod.size() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n";

		self_default_npod.pop_back();
		cout << "pop: size = " << self_default_npod.size() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n";

		selfmadeSTL::deque<Npod> self_default_npod2(self_default_npod);
		cout << std::boolalpha << "is the same? "
			<< (self_default_npod == self_default_npod2) << ", "
			<< (self_default_npod != self_default_npod2) << "\n";

		self_default_npod2.erase(self_default_npod2.begin());
		cout << "erase: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod2.resize(npod_size / 2);
		cout << "resize: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod2.resize(2 * npod_size);
		cout << "resize: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod.swap(self_default_npod2);
		cout << "swap: size1 = " << self_default_npod.size() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n"
			<< "swap: size2 = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n";
	}
	cout << endl;
	{
		cout << "----- Here is the reference -----\n";
		selfmadeSTL::deque<Npod> std_default_npod;
		cout << std::boolalpha << "is empty? "
			<< std_default_npod.empty() << "\n";

		std_default_npod.insert(std_default_npod.begin(), Npod());
		std_default_npod.insert(std_default_npod.end(), npod_data, npod_data + npod_size - 1);
		cout << "insert: size = " << std_default_npod.size() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n";

		std_default_npod.push_back(npod_data[npod_size - 1]);
		cout << "push_back: size = " << std_default_npod.size() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n";

		std_default_npod.pop_back();
		cout << "pop: size = " << std_default_npod.size() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n";

		selfmadeSTL::deque<Npod> std_default_npod2(std_default_npod);
		cout << std::boolalpha << "is the same? "
			<< (std_default_npod == std_default_npod2) << ", "
			<< (std_default_npod != std_default_npod2) << "\n";

		std_default_npod2.erase(std_default_npod2.begin());
		cout << "erase: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod2.resize(npod_size / 2);
		cout << "resize: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod2.resize(2 * npod_size);
		cout << "resize: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod.swap(std_default_npod2);
		cout << "swap: size1 = " << std_default_npod.size() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n"
			<< "swap: size2 = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n";
	}

	return 0;
}