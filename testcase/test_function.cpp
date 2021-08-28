#include <iostream>
#include <random>

#include "../stl_algorithm.hpp"
#include "../stl_function.hpp"
#include "../stl_iterator.hpp"
#include "../stl_pair.hpp"
#include "../stl_vector.hpp"
#include "test_function.hpp"

using std::cout;
using std::endl;
using std::default_random_engine;
using std::uniform_real_distribution;
using namespace selfmadeSTL;

template<typename InputIterator, typename UnaryOperator>
UnaryOperator for_each_ptr(InputIterator first, InputIterator last, UnaryOperator op) {
    for (; first != last; ++first) {
        op(first);
    }
    return op;
}

template<typename InputIterator, typename UnaryOperator>
UnaryOperator for_each_ptr_2arg(InputIterator first, InputIterator last, const char* str, UnaryOperator op) {
    for (; first != last; ++first) {
        op(first, str);
    }
    return op;
}

template<typename InputIterator, typename UnaryOperator>
UnaryOperator for_each_ref_2arg(InputIterator first, InputIterator last, const char* str, UnaryOperator op) {
    for (; first != last; ++first) {
        op(*first, str);
    }
    return op;
}

int main() {
    
    int a = 1, b = 2;

    cout << std::boolalpha;
    cout << "equal_to: " << equal_to<int>()(a, b) << endl;
    cout << "not_equal_to: " << not_equal_to<int>()(a, b) << endl;
    cout << "less: " << less<int>()(a, b) << endl;
    cout << "less_equal: " << less_equal<int>()(a, b) << endl;
    cout << "greater: " << greater<int>()(a, b) << endl;
    cout << "greater_equal: " << greater_equal<int>()(a, b) << endl;
    cout << "negate: " << negate<int>()(a) << endl;
    cout << "plus: " << plus<int>()(a, b) << endl;
    cout << "minus: " << minus<int>()(a, b) << endl;
    cout << "multiply: " << multiply<int>()(a, b) << endl;
    cout << "divide: " << divide<int>()(a, b) << endl;
    cout << "modulu: " << modulu<int>()(a, b) << endl;
    cout << "identity_element: " << identity_element<int>(plus<int>()) << endl;
    cout << "identity_element: " << identity_element<int>(multiply<int>()) << endl;
    cout << "logical_and: " << logical_and<int>()(a, b) << endl;
    cout << "logical_or: " << logical_or<int>()(a, b) << endl;
    cout << "logical_not: " << logical_not<int>()(a) << endl;
    cout << "identity: " << identity<int>()(a) << endl;
    cout << "select1st: " << select1st<pair<int, int>>()(pair<int, int>(a, b)) << endl;
    cout << "select2rd: " << select2rd<pair<int, int>>()(pair<int, int>(a, b)) << endl;
    cout << "project1st: " << project1st<int, int>()(a, b) << endl;
    cout << "project2rd: " << project2rd<int, int>()(a, b) << endl;
    
    int arr[] = { 2, 21, 12, 7, 19, 23 };
    vector<int> v(arr, arr + 6);
    default_random_engine rng;
    uniform_real_distribution<double> uniform_double(0, 10);
    Npod npod_data[5] = { {0, 0} };
    for (size_t i = 0; i < 5; ++i) {
        npod_data[i].ptr->real(uniform_double(rng));
        npod_data[i].ptr->imag(uniform_double(rng));
    }
    vector<Npod> n(npod_data, npod_data + 5);
    
    ostream_iterator<int> out(cout, " ");

    cout << "not1: " << count_if(v.begin(), v.end(), not1(bind2nd(less<int>(), 12))) << endl;
    cout << "compose1: ";
    // x -> 3x + 9
    transform(v.begin(), v.end(), out, compose1(bind1st(multiply<int>(), 3), bind1st(plus<int>(), 3)));
    cout << endl;
    cout << "compose2: ";
    // x -> x^2 + 5x + 6
    transform(v.begin(), v.end(), out, compose2(multiply<int>(), bind1st(plus<int>(), 3), bind1st(plus<int>(), 2)));
    cout << endl;

    cout << "ptr_fun: ";
    for_each(v.begin(), v.end(), ptr_fun(print<int>));
    cout << endl;

    cout << "mem_fun: ";
    for_each_ptr(n.begin(), n.end(), mem_fun(&Npod::print));
    cout << endl;

    cout << "mem_fun_ref: ";
    for_each(n.begin(), n.end(), mem_fun_ref(&Npod::print));
    cout << endl;

    cout << "mem_fun1: ";
    for_each_ptr_2arg(n.begin(), n.end(), " @ ", mem_fun(&Npod::print_1arg));
    cout << endl;

    cout << "mem_fun1_ref: ";
    for_each_ref_2arg(n.begin(), n.end(), " @ ", mem_fun_ref(&Npod::print_1arg));
    cout << endl;

    return 0;
}