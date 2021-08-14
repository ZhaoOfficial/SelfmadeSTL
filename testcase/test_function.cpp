#include <iostream>
#include "../stl_function.hpp"

using std::cout;
using std::endl;
using namespace selfmadeSTL;

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
    // cout << "select1st: " << select1st<pair<int, int>>()(pair<int, int>(a, b)) << endl;
    // cout << "select2rd: " << select2rd<pair<int, int>>()(pair<int, int>(a, b)) << endl;
    cout << "project1st: " << project1st<int, int>()(a, b) << endl;
    cout << "project2rd: " << project2rd<int, int>()(a, b) << endl;
    
    return 0;
}