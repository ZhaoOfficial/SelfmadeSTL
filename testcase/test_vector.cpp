#include <iostream>
#include <cstdlib>
#include <vector>
#include <complex>
#include <random>

#include "test_function.hpp"
#include "../stl_vector.hpp"
#include "../stl_type_traits.hpp"

using std::cout;
using std::endl;
using std::complex;

template <typename T>
void basic_test(T& vec) {
	cout << "size = " << vec.size() << ", "
		<< "capacity = " << vec.capacity() << ", "
		<< std::boolalpha
		<< "is empty = " << vec.empty() << endl;
}

template <typename T>
void element_test(T& vec) {
	cout << "The first is : " << vec.front() << ", "
		<< "The middle is : " << vec[vec.size() / 2] << ", "
		<< "The last is : " << vec.back() << endl;

}

int main(int argc, char* argv[]) {

	std::default_random_engine rng;
	std::uniform_int_distribution<int> uniform_int(0, 10);
	std::uniform_real_distribution<double> uniform_double(0, 1);
	// --------------------------------------------------
	{
		int* arr1 = new int[1024];
		int* arr2 = new int[1024];
		for (size_t i = 0; i < 1024; ++i) {
			arr1[i] = uniform_int(rng);
			arr2[i] = uniform_int(rng);
		}
		cout << "Test of default constructor of POD:" << endl;
		SelfMadeSTL::vector<int> self_default_pod;
		SelfMadeSTL::vector<int> self_default_pod2;
		basic_test(self_default_pod);
		self_default_pod.insert(self_default_pod.begin(), arr1, arr1 + 1024);
		self_default_pod2.insert(self_default_pod2.begin(), arr2, arr2 + 1024);
		element_test(self_default_pod);
		element_test(self_default_pod2);
		cout << (self_default_pod == self_default_pod2) << ", "
			<< (self_default_pod != self_default_pod2) << ", "
			<< (self_default_pod < self_default_pod2) << endl;
		self_default_pod.swap(self_default_pod2);
		element_test(self_default_pod);
		element_test(self_default_pod2);


		cout << "Here is the reference:" << endl;
		std::vector<int> std_default_pod;
		std::vector<int> std_default_pod2;
		basic_test(std_default_pod);
		std_default_pod.insert(std_default_pod.begin(), arr1, arr1 + 1024);
		std_default_pod2.insert(std_default_pod2.begin(), arr2, arr2 + 1024);
		element_test(std_default_pod);
		element_test(std_default_pod2);
		cout << (std_default_pod == std_default_pod2) << ", "
			<< (std_default_pod != std_default_pod2) << ", "
			<< (std_default_pod < std_default_pod2) << endl;
		std_default_pod.swap(std_default_pod2);
		element_test(std_default_pod);
		element_test(std_default_pod2);
	}
	cout << endl;
	{
		cout << "Test of default constructor of non-POD:" << endl;
		SelfMadeSTL::vector<complex<double>> self_default_nonpod;
		basic_test(self_default_nonpod);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_default_nonpod;
		basic_test(std_default_nonpod);
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of n same constructor of POD:" << endl;
		
		SelfMadeSTL::vector<int> self_nsame_pod(1024);
		basic_test(self_nsame_pod);
		element_test(self_nsame_pod);

		cout << "Here is the reference:" << endl;
		std::vector<int> std_nsame_pod(1024);
		basic_test(std_nsame_pod);
		element_test(std_nsame_pod);
	}
	cout << endl;
	{
		cout << "Test of n same constructor of non-POD:" << endl;
		SelfMadeSTL::vector<complex<double>> self_nsame_nonpod(1024, complex<double>(1024, 2048));
		basic_test(self_nsame_nonpod);
		element_test(self_nsame_nonpod);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_nsame_nonpod(1024, complex<double>(1024, 2048));
		basic_test(std_nsame_nonpod);
		element_test(std_nsame_nonpod);
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of n default constructor:" << endl;
		SelfMadeSTL::vector<int> self_n_pod(1024);
		basic_test(self_n_pod);
		element_test(self_n_pod);
		cout << "Here is the reference:" << endl;
		std::vector<int> std_nsame_pod(1024);
		basic_test(std_nsame_pod);
		element_test(std_nsame_pod);
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of copy constructor:" << endl;
		SelfMadeSTL::vector<complex<double>> self_copying(1024, complex<double>(1024, 4096));
		SelfMadeSTL::vector<complex<double>> self_copied(self_copying);
		basic_test(self_copied);
		element_test(self_copied);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_copying(1024, complex<double>(1024, 4096));
		std::vector<complex<double>> std_copied(std_copying);
		basic_test(std_copied);
		element_test(std_copied);
	}
	cout << endl;

	// --------------------------------------------------
	{
		complex<double>* arr = new complex<double>[1024];
		cout << "Test of iterator constructor:" << endl;
		SelfMadeSTL::vector<complex<double>> self_it(arr, arr + 1024);
		basic_test(self_it);
		element_test(self_it);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_it(arr, arr + 1024);
		basic_test(std_it);
		element_test(std_it);
		cout << std::boolalpha << SelfMadeSTL::container_equal(self_it, std_it) << endl;
		delete[] arr;
	}
	cout << endl;

	// --------------------------------------------------
	{
		complex<double>* arr = new complex<double>[1024];
		cout << "Test of operator= :" << endl;
		SelfMadeSTL::vector<complex<double>> self_it(arr, arr + 1024);
		SelfMadeSTL::vector<complex<double>> self_copy = self_it;
		basic_test(self_copy);
		element_test(self_copy);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_it(arr, arr + 1024);
		std::vector<complex<double>> std_copy = std_it;
		basic_test(std_copy);
		element_test(std_copy);
		delete[] arr;
	}
	cout << endl;

	// --------------------------------------------------
	{
		complex<double>* arr = new complex<double>[1024];
		for (size_t i = 0; i < 1024; ++i) {
			arr[i] = complex<double>(uniform_double(rng), uniform_double(rng));
		}
		cout << "Test of functions:" << endl;
		SelfMadeSTL::vector<complex<double>> self_func(arr, arr + 128);
		basic_test(self_func);
		for (size_t i = 128; i < 256; ++i) {
			self_func.push_back(arr[i]);
		}
		self_func.insert(self_func.begin(), arr + 256, arr + 384);
		basic_test(self_func);
		self_func.shrink_to_fit();
		basic_test(self_func);
		element_test(self_func);
		self_func.resize(256);
		basic_test(self_func);
		element_test(self_func);
		for (size_t i = 384; i < 1024; ++i) {
			self_func.push_back(arr[i]);
		}
		basic_test(self_func);
		element_test(self_func);
		self_func.clear();
		basic_test(self_func);

		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_func(arr, arr + 128);
		basic_test(std_func);
		for (size_t i = 128; i < 256; ++i) {
			std_func.push_back(arr[i]);
		}
		std_func.insert(std_func.begin(), arr + 256, arr + 384);
		basic_test(std_func);
		std_func.shrink_to_fit();
		basic_test(std_func);
		element_test(std_func);
		std_func.resize(256);
		basic_test(std_func);
		element_test(std_func);
		for (size_t i = 384; i < 1024; ++i) {
			std_func.push_back(arr[i]);
		}
		basic_test(std_func);
		element_test(std_func);
		std_func.clear();
		basic_test(std_func);

		delete[] arr;
	}
	cout << endl;
	return 0;
}