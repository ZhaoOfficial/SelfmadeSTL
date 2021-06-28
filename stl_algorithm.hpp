#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <cstdlib>
#include <memory>

#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"

namespace SelfMadeSTL {

	// O(n)
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& x) {
		for (; first != last; ++first) {
			*first = x;
		}
	}

	// O(n)
	template <typename OutputIterator, typename Size, typename T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
		for (; n > 0; --n, ++first) {
			*first = value;
		}
		return first;
	}

	template <typename Size>
	char* fill_n(char* first, Size n, const char& value) {
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

	template <typename Size>
	wchar_t* fill_n(wchar_t* first, Size n, const wchar_t& value) {
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	// O(n)
	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		for (; first != last; ++first, ++result) {
			*result = *first;
		}
		return result;
	}

}

#endif // !_ALGORITHM_H