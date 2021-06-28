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
		cout << "size = " << self_nsame_pod.size() << ", "
			<< "capacity = " << self_nsame_pod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << self_nsame_pod.empty() << ", "
			<< "the first element is " << self_nsame_pod[0]
			<< endl;
		cout << "Here is the reference:" << endl;
		std::vector<int> std_nsame_pod(1024, 1024);
		cout << "size = " << std_nsame_pod.size() << ", "
			<< "capacity = " << std_nsame_pod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << std_nsame_pod.empty() << ", "
			<< "the first element is " << std_nsame_pod[0]
			<< endl;
	}
	cout << endl;
	{
		cout << "Test of n same constructor of non-POD:" << endl;
		SelfMadeSTL::vector<complex<double>> self_nsame_nonpod(1024, complex<double>(1024, 2048));
		cout << "size = " << self_nsame_nonpod.size() << ", "
			<< "capacity = " << self_nsame_nonpod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << self_nsame_nonpod.empty() << ", "
			<< "the first element is " << self_nsame_nonpod[0]
			<< endl;
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_nsame_nonpod(1024, complex<double>(1024, 2048));
		cout << "size = " << std_nsame_nonpod.size() << ", "
			<< "capacity = " << std_nsame_nonpod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << std_nsame_nonpod.empty() << ", "
			<< "the first element is " << std_nsame_nonpod[0]
			<< endl;
	}
	cout << endl;

	// --------------------------------------------------
	{
		cout << "Test of n default constructor of POD:" << endl;
		SelfMadeSTL::vector<int> self_n_pod(1024);
		cout << "size = " << self_n_pod.size() << ", "
			<< "capacity = " << self_n_pod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << self_n_pod.empty() << ", "
			<< "the first element is " << self_n_pod[0]
			<< endl;
		cout << "Here is the reference:" << endl;
		std::vector<int> std_nsame_pod(1024);
		cout << "size = " << std_nsame_pod.size() << ", "
			<< "capacity = " << std_nsame_pod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << std_nsame_pod.empty() << ", "
			<< "the first element is " << std_nsame_pod[0]
			<< endl;
	}
	cout << endl;
	{
		cout << "Test of n default constructor of non-POD:" << endl;
		SelfMadeSTL::vector<complex<double>> self_n_nonpod(1024);
		cout << "size = " << self_n_nonpod.size() << ", "
			<< "capacity = " << self_n_nonpod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << self_n_nonpod.empty() << ", "
			<< "the first element is " << self_n_nonpod[0]
			<< endl;
		cout << "Here is the reference:" << endl;
		std::vector<complex<double>> std_n_nonpod(1024);
		cout << "size = " << std_n_nonpod.size() << ", "
			<< "capacity = " << std_n_nonpod.capacity() << ", "
			<< std::boolalpha
			<< "is empty = " << std_n_nonpod.empty() << ", "
			<< "the first element is " << std_n_nonpod[0]
			<< endl;
	}
	cout << endl;

	
	return 0;
}