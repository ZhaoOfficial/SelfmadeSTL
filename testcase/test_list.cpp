#include <iostream>
#include <cstdlib>
#include <list>
#include <complex>
#include <random>
#include <climits>

#include "../stl_list.hpp"
#include "../stl_type_traits.hpp"
#include "test_function.hpp"

using std::cout;
using std::endl;
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
		selfmadeSTL::list<double> self_default_pod;
		cout << std::boolalpha << "is empty? "
			<< self_default_pod.empty() << "\n";

		self_default_pod.insert(self_default_pod.begin(), 0);
		self_default_pod.insert(self_default_pod.end(), pod_data[0]);
		self_default_pod.insert(self_default_pod.end(), pod_data + 1, pod_data + pod_size);
		cout << "insert: size = " << self_default_pod.size() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		self_default_pod.pop_front();
		self_default_pod.pop_back();
		cout << "pop: size = " << self_default_pod.size() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		selfmadeSTL::list<double> self_default_pod2(self_default_pod);
		cout << std::boolalpha << "is the same? "
			<< (self_default_pod == self_default_pod2) << ", "
			<< (self_default_pod != self_default_pod2) << "\n";

		self_default_pod2.insert(self_default_pod2.end(), self_default_pod.begin(), self_default_pod.end());
		self_default_pod2.insert(self_default_pod2.end(), 2, 1.0);
		cout << "insert: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.remove(1.0);
		cout << "remove: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.resize(pod_size - 1);
		cout << "resize: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.resize(2 * pod_size);
		cout << "resize: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.unique();
		cout << "unique: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.reverse();
		cout << "reverse: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.sort();
		cout << "sort: size = " << self_default_pod2.size() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		cout << std::boolalpha << "is smaller? "
			<< (self_default_pod < self_default_pod2) << "\n";
	}
	{
		cout << "----- Here is the reference -----\n";
		std::list<double> std_default_pod;
		cout << std::boolalpha << "is empty? "
			<< std_default_pod.empty() << "\n";

		std_default_pod.insert(std_default_pod.begin(), 0);
		std_default_pod.insert(std_default_pod.end(), pod_data[0]);
		std_default_pod.insert(std_default_pod.end(), pod_data + 1, pod_data + pod_size);
		cout << "insert: size = " << std_default_pod.size() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std_default_pod.pop_front();
		std_default_pod.pop_back();
		cout << "pop: size = " << std_default_pod.size() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std::list<double> std_default_pod2(std_default_pod);
		cout << std::boolalpha << "is the same? "
			<< (std_default_pod == std_default_pod2) << ", "
			<< (std_default_pod != std_default_pod2) << "\n";

		std_default_pod2.insert(std_default_pod2.end(), std_default_pod.begin(), std_default_pod.end());
		std_default_pod2.insert(std_default_pod2.end(), 2, 1.0);
		cout << "insert: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.remove(1.0);
		cout << "remove: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.resize(pod_size - 1);
		cout << "resize: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.resize(2 * pod_size);
		cout << "resize: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.unique();
		cout << "unique: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.reverse();
		cout << "reverse: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.sort();
		cout << "sort: size = " << std_default_pod2.size() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		cout << std::boolalpha << "is smaller? "
			<< (std_default_pod < std_default_pod2) << "\n";
	}
	cout << '\n';

	{
		cout << "----- Test of non-POD default constructor and copy constructor -----\n";
		selfmadeSTL::list<Npod> self_default_npod;
		cout << std::boolalpha << "is empty? "
			<< self_default_npod.empty() << "\n";

		self_default_npod.insert(self_default_npod.begin(), Npod());
		self_default_npod.insert(self_default_npod.end(), npod_data[0]);
		self_default_npod.insert(self_default_npod.end(), npod_data + 1, npod_data + npod_size);
		cout << "insert: size = " << self_default_npod.size() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << ", " << "\n";

		self_default_npod.pop_front();
		self_default_npod.pop_back();
		cout << "pop: size = " << self_default_npod.size() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << ", " << "\n";

		selfmadeSTL::list<Npod> self_default_npod2(self_default_npod);
		cout << std::boolalpha << "is the same? "
			<< (self_default_npod == self_default_npod2) << ", "
			<< (self_default_npod != self_default_npod2) << "\n";

		self_default_npod2.insert(self_default_npod2.end(), self_default_npod.begin(), self_default_npod.end());
		self_default_npod2.insert(self_default_npod2.end(), 2, Npod());
		cout << "insert: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		self_default_npod2.remove(Npod());
		cout << "remove: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		self_default_npod2.resize(npod_size - 1);
		cout << "resize: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		self_default_npod2.resize(2 * npod_size);
		cout << "resize: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		self_default_npod2.unique();
		cout << "unique: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		self_default_npod2.reverse();
		cout << "reverse: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		self_default_npod2.sort();
		cout << "sort: size = " << self_default_npod2.size() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << ", " << "\n";

		cout << std::boolalpha << "is smaller? "
			<< (self_default_npod < self_default_npod2) << "\n";
	}
	{
		cout << "----- Here is the reference -----\n";
		std::list<Npod> std_default_npod;
		cout << std::boolalpha << "is empty? "
			<< std_default_npod.empty() << "\n";

		std_default_npod.insert(std_default_npod.begin(), Npod());
		std_default_npod.insert(std_default_npod.end(), npod_data[0]);
		std_default_npod.insert(std_default_npod.end(), npod_data + 1, npod_data + npod_size);
		cout << "insert: size = " << std_default_npod.size() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << ", " << "\n";

		std_default_npod.pop_front();
		std_default_npod.pop_back();
		cout << "pop: size = " << std_default_npod.size() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << ", " << "\n";

		std::list<Npod> std_default_npod2(std_default_npod);
		cout << std::boolalpha << "is the same? "
			<< (std_default_npod == std_default_npod2) << ", "
			<< (std_default_npod != std_default_npod2) << "\n";

		std_default_npod2.insert(std_default_npod2.end(), std_default_npod.begin(), std_default_npod.end());
		std_default_npod2.insert(std_default_npod2.end(), 2, Npod());
		cout << "insert: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		std_default_npod2.remove(Npod());
		cout << "remove: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		std_default_npod2.resize(npod_size - 1);
		cout << "resize: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		std_default_npod2.resize(2 * npod_size);
		cout << "resize: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		std_default_npod2.unique();
		cout << "unique: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		std_default_npod2.reverse();
		cout << "reverse: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		std_default_npod2.sort();
		cout << "sort: size = " << std_default_npod2.size() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << ", " << "\n";

		cout << std::boolalpha << "is smaller? "
			<< (std_default_npod < std_default_npod2) << "\n";
	}
	cout << '\n';

	return 0;
}