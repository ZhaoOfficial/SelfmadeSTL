#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <complex>

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
		<< "is empty = " << vec.empty() << ", "
		<< "the first element is " << vec[0]
		<< endl;
}

int main(int argc, char* argv[]) {

	srand(time(0));
	// --------------------------------------------------
	{
		cout << "Test of default constructor of POD:" << endl;
		SelfMadeSTL::vector<int> self_default_pod;
		cout << "size = " << self_default_pod.size() << ", "
			<< "capacity = " << self_default_pod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << self_default_pod.empty()
			<< endl;
		cout << "Here is the reference:" << endl;
		std::vector<int> std_default_pod;
		cout << "size = " << std_default_pod.size() << ", "
			<< "capacity = " << std_default_pod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << std_default_pod.empty()
			<< endl;
	}
	cout << endl;
	{
		cout << "Test of default constructor of non-POD:" << endl;
		SelfMadeSTL::vector<complex<double>> self_default_nonpod;
		cout << "size = " << self_default_nonpod.size() << ", "
			<< "capacity = " << self_default_nonpod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << self_default_nonpod.empty()
			<< endl;
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_default_nonpod;
		cout << "size = " << std_default_nonpod.size() << ", "
			<< "capacity = " << std_default_nonpod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << std_default_nonpod.empty()
			<< endl;
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of n same constructor of POD:" << endl;
		SelfMadeSTL::vector<int> self_nsame_pod(1024, 1024);
		basic_test(self_nsame_pod);
		cout << "Here is the reference:" << endl;
		std::vector<int> std_nsame_pod(1024, 1024);
		basic_test(std_nsame_pod);
	}
	cout << endl;
	{
		cout << "Test of n same constructor of non-POD:" << endl;
		SelfMadeSTL::vector<complex<double>> self_nsame_nonpod(1024, complex<double>(1024, 2048));
		basic_test(self_nsame_nonpod);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_nsame_nonpod(1024, complex<double>(1024, 2048));
		basic_test(self_nsame_nonpod);
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of n default constructor:" << endl;
		SelfMadeSTL::vector<int> self_n_pod(1024);
		basic_test(self_n_pod);
		cout << "Here is the reference:" << endl;
		std::vector<int> std_nsame_pod(1024);
		basic_test(std_nsame_pod);
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of copy constructor:" << endl;
		SelfMadeSTL::vector<complex<double>> self_copying(1024, complex<double>(1024, 4096));
		SelfMadeSTL::vector<complex<double>> self_copied(self_copying);
		basic_test(self_copied);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_copying(1024, complex<double>(1024, 4096));
		std::vector<complex<double>> std_copied(std_copying);
		basic_test(std_copied);
	}
	cout << endl;

	// --------------------------------------------------
	{
		complex<double>* arr = new complex<double>[1024];
		cout << "Test of iterator constructor:" << endl;
		SelfMadeSTL::vector<complex<double>> self_it(arr, arr + 1024);
		basic_test(self_it);
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_it(arr, arr + 1024);
		basic_test(std_it);
		delete[] arr;
	}
	cout << endl;

	return 0;
}