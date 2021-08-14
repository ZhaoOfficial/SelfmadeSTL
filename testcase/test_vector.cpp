#include <iostream>
#include <cstdlib>
#include <vector>
#include <complex>
#include <random>
#include <climits>

#include "../stl_vector.hpp"
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
		selfmadeSTL::vector<double> self_default_pod;
		cout << std::boolalpha << "is empty? "
			<< self_default_pod.empty() << "\n";

		self_default_pod.insert(self_default_pod.begin(), 0.0);
		self_default_pod.push_back(pod_data[0]);
		self_default_pod.insert(self_default_pod.end(), pod_data + 1, pod_data + pod_size);
		cout << "push_back: size = " << self_default_pod.size() << ", "
			<< "capacity = " << self_default_pod.capacity() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		self_default_pod.pop_back();
		cout << "pop: size = " << self_default_pod.size() << ", "
			<< "capacity = " << self_default_pod.capacity() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n";

		selfmadeSTL::vector<double> self_default_pod2(self_default_pod);
		cout << std::boolalpha << "is the same? "
			<< (self_default_pod == self_default_pod2) << ", "
			<< (self_default_pod != self_default_pod2) << "\n";

		self_default_pod2.insert(self_default_pod2.end(), self_default_pod.begin(), self_default_pod.end());
		self_default_pod2.insert(self_default_pod2.end(), 2, 1.0);
		cout << "insert: size = " << self_default_pod2.size() << ", "
			<< "capacity = " << self_default_pod2.capacity() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.erase(self_default_pod2.begin());
		cout << "erase: size = " << self_default_pod2.size() << ", "
			<< "capacity = " << self_default_pod2.capacity() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.resize(pod_size / 2);
		cout << "resize: size = " << self_default_pod2.size() << ", "
			<< "capacity = " << self_default_pod2.capacity() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.resize(2 * pod_size);
		cout << "resize: size = " << self_default_pod2.size() << ", "
			<< "capacity = " << self_default_pod2.capacity() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod2.shrink_to_fit();
		cout << "shrink_to_fit: size = " << self_default_pod2.size() << ", "
			<< "capacity = " << self_default_pod2.capacity() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";

		self_default_pod.swap(self_default_pod2);
		cout << "swap: size1 = " << self_default_pod.size() << ", "
			<< "capacity1 = " << self_default_pod.capacity() << ", "
			<< "front() = " << self_default_pod.front() << ", "
			<< "back() = " << self_default_pod.back() << "\n"
			<< "swap: size2 = " << self_default_pod2.size() << ", "
			<< "capacity2 = " << self_default_pod2.capacity() << ", "
			<< "front() = " << self_default_pod2.front() << ", "
			<< "back() = " << self_default_pod2.back() << "\n";
	}
	cout << endl;
	{
		cout << "----- Here is the reference -----\n";
		std::vector<double> std_default_pod;
		cout << std::boolalpha << "is empty? "
			<< std_default_pod.empty() << "\n";

		std_default_pod.insert(std_default_pod.begin(), 0.0);
		std_default_pod.push_back(pod_data[0]);
		std_default_pod.insert(std_default_pod.end(), pod_data + 1, pod_data + pod_size);
		cout << "push_back: size = " << std_default_pod.size() << ", "
			<< "capacity = " << std_default_pod.capacity() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std_default_pod.pop_back();
		cout << "pop: size = " << std_default_pod.size() << ", "
			<< "capacity = " << std_default_pod.capacity() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n";

		std::vector<double> std_default_pod2(std_default_pod);
		cout << std::boolalpha << "is the same? "
			<< (std_default_pod == std_default_pod2) << ", "
			<< (std_default_pod != std_default_pod2) << "\n";

		std_default_pod2.insert(std_default_pod2.end(), std_default_pod.begin(), std_default_pod.end());
		std_default_pod2.insert(std_default_pod2.end(), 2, 1.0);
		cout << "insert: size = " << std_default_pod2.size() << ", "
			<< "capacity = " << std_default_pod2.capacity() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.erase(std_default_pod2.begin());
		cout << "erase: size = " << std_default_pod2.size() << ", "
			<< "capacity = " << std_default_pod2.capacity() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.resize(pod_size / 2);
		cout << "resize: size = " << std_default_pod2.size() << ", "
			<< "capacity = " << std_default_pod2.capacity() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.resize(2 * pod_size);
		cout << "resize: size = " << std_default_pod2.size() << ", "
			<< "capacity = " << std_default_pod2.capacity() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod2.shrink_to_fit();
		cout << "shrink_to_fit: size = " << std_default_pod2.size() << ", "
			<< "capacity = " << std_default_pod2.capacity() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";

		std_default_pod.swap(std_default_pod2);
		cout << "swap: size1 = " << std_default_pod.size() << ", "
			<< "capacity1 = " << std_default_pod.capacity() << ", "
			<< "front() = " << std_default_pod.front() << ", "
			<< "back() = " << std_default_pod.back() << "\n"
			<< "swap: size2 = " << std_default_pod2.size() << ", "
			<< "capacity2 = " << std_default_pod2.capacity() << ", "
			<< "front() = " << std_default_pod2.front() << ", "
			<< "back() = " << std_default_pod2.back() << "\n";
	}
	cout << endl;
	{
		cout << "----- Test of non-POD default constructor and copy constructor -----\n";
		selfmadeSTL::vector<Npod> self_default_npod;
		cout << std::boolalpha << "is empty? "
			<< self_default_npod.empty() << "\n";

		self_default_npod.insert(self_default_npod.begin(), Npod());
		self_default_npod.push_back(npod_data[0]);
		self_default_npod.insert(self_default_npod.end(), npod_data + 1, npod_data + npod_size);
		cout << "push_back: size = " << self_default_npod.size() << ", "
			<< "capacity = " << self_default_npod.capacity() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n";

		self_default_npod.pop_back();
		cout << "pop: size = " << self_default_npod.size() << ", "
			<< "capacity = " << self_default_npod.capacity() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n";

		selfmadeSTL::vector<Npod> self_default_npod2(self_default_npod);
		cout << std::boolalpha << "is the same? "
			<< (self_default_npod == self_default_npod2) << ", "
			<< (self_default_npod != self_default_npod2) << "\n";

		self_default_npod2.insert(self_default_npod2.end(), self_default_npod.begin(), self_default_npod.end());
		self_default_npod2.insert(self_default_npod2.end(), 2, Npod());
		cout << "insert: size = " << self_default_npod2.size() << ", "
			<< "capacity = " << self_default_npod2.capacity() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod2.erase(self_default_npod2.begin());
		cout << "erase: size = " << self_default_npod2.size() << ", "
			<< "capacity = " << self_default_npod2.capacity() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod2.resize(npod_size / 2);
		cout << "resize: size = " << self_default_npod2.size() << ", "
			<< "capacity = " << self_default_npod2.capacity() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod2.resize(2 * npod_size);
		cout << "resize: size = " << self_default_npod2.size() << ", "
			<< "capacity = " << self_default_npod2.capacity() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod2.shrink_to_fit();
		cout << "shrink_to_fit: size = " << self_default_npod2.size() << ", "
			<< "capacity = " << self_default_npod2.capacity() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";

		self_default_npod.swap(self_default_npod2);
		cout << "swap: size1 = " << self_default_npod.size() << ", "
			<< "capacity1 = " << self_default_npod.capacity() << ", "
			<< "front() = " << self_default_npod.front().ptr->real() << ", "
			<< self_default_npod.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod.back().ptr->real() << ", "
			<< self_default_npod.back().ptr->imag() << "\n"
			<< "size2 = " << self_default_npod2.size() << ", "
			<< "capacity2 = " << self_default_npod2.capacity() << ", "
			<< "front() = " << self_default_npod2.front().ptr->real() << ", "
			<< self_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << self_default_npod2.back().ptr->real() << ", "
			<< self_default_npod2.back().ptr->imag() << "\n";
	}
	cout << endl;
	{
		cout << "----- Here is the reference -----\n";
		selfmadeSTL::vector<Npod> std_default_npod;
		cout << std::boolalpha << "is empty? "
			<< std_default_npod.empty() << "\n";

		std_default_npod.insert(std_default_npod.begin(), Npod());
		std_default_npod.push_back(npod_data[0]);
		std_default_npod.insert(std_default_npod.end(), npod_data + 1, npod_data + npod_size);
		cout << "push_back: size = " << std_default_npod.size() << ", "
			<< "capacity = " << std_default_npod.capacity() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n";

		std_default_npod.pop_back();
		cout << "pop: size = " << std_default_npod.size() << ", "
			<< "capacity = " << std_default_npod.capacity() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n";

		selfmadeSTL::vector<Npod> std_default_npod2(std_default_npod);
		cout << std::boolalpha << "is the same? "
			<< (std_default_npod == std_default_npod2) << ", "
			<< (std_default_npod != std_default_npod2) << "\n";

		std_default_npod2.insert(std_default_npod2.end(), std_default_npod.begin(), std_default_npod.end());
		std_default_npod2.insert(std_default_npod2.end(), 2, Npod());
		cout << "insert: size = " << std_default_npod2.size() << ", "
			<< "capacity = " << std_default_npod2.capacity() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod2.erase(std_default_npod2.begin());
		cout << "erase: size = " << std_default_npod2.size() << ", "
			<< "capacity = " << std_default_npod2.capacity() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod2.resize(npod_size / 2);
		cout << "resize: size = " << std_default_npod2.size() << ", "
			<< "capacity = " << std_default_npod2.capacity() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod2.resize(2 * npod_size);
		cout << "resize: size = " << std_default_npod2.size() << ", "
			<< "capacity = " << std_default_npod2.capacity() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod2.shrink_to_fit();
		cout << "shrink_to_fit: size = " << std_default_npod2.size() << ", "
			<< "capacity = " << std_default_npod2.capacity() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";

		std_default_npod.swap(std_default_npod2);
		cout << "swap: size1 = " << std_default_npod.size() << ", "
			<< "capacity1 = " << std_default_npod.capacity() << ", "
			<< "front() = " << std_default_npod.front().ptr->real() << ", "
			<< std_default_npod.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod.back().ptr->real() << ", "
			<< std_default_npod.back().ptr->imag() << "\n"
			<< "size2 = " << std_default_npod2.size() << ", "
			<< "capacity2 = " << std_default_npod2.capacity() << ", "
			<< "front() = " << std_default_npod2.front().ptr->real() << ", "
			<< std_default_npod2.front().ptr->imag() << ", "
			<< "back() = " << std_default_npod2.back().ptr->real() << ", "
			<< std_default_npod2.back().ptr->imag() << "\n";
	}
	cout << endl;

	return 0;
}