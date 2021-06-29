#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <cstdlib>
#include <memory>

#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"

namespace SelfMadeSTL {

	// fill the same `value` in [`first`, `last`)
	// O(n)
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value) {
		for (; first != last; ++first) {
			*first = value;
		}
	}

	// fill `n` same `value` start from `first`
	// O(n)
	template <typename OutputIterator, typename Size, typename T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
		for (; n > 0; --n, ++first) {
			*first = value;
		}
		return first;
	}

	// fill `n` same `value` start from `first`
	// specilized for char
	template <typename Size>
	char* fill_n(char* first, Size n, const char& value) {
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

	// fill `n` same `value` start from `first`
	// specilized for wchar_t
	template <typename Size>
	wchar_t* fill_n(wchar_t* first, Size n, const wchar_t& value) {
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	// copy the value in [`first`, `last`) to container
	// start from `output`
	// O(n)
	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator output) {
		for (; first != last; ++first, ++output) {
			*output = *first;
		}
		return output;
	}

	// reversely copy the value in [`first`, `last`) to container
	// end with `output` (exclusive)
	template <typename BidirectionalIterator>
	BidirectionalIterator copy_backward(BidirectionalIterator first, BidirectionalIterator last, BidirectionalIterator output) {
		if (first == last)
			return output;
		BidirectionalIterator rbegin = last - 1;
		for (; rbegin != first; --rbegin) {
			*--output = *rbegin;
		}
		*--output = *rbegin;
		return output;
	}

	// check if it is the same between [`first1`, `last1`) 
	// and an iterator start from `first2`
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}
}

#endif // !_ALGORITHM_H