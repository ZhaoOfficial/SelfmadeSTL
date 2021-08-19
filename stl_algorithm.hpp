#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cstdlib>
#include <memory>

#include "stl_iterator.hpp"
#include "stl_pair.hpp"
#include "stl_type_traits.hpp"

namespace selfmadeSTL {

	// O(1)
	template <typename T>
	inline const T& min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	// O(1)
	template <typename T, typename Compare>
	inline const T& min(const T& a, const T& b, Compare comp) {
		return comp(a, b) ? a : b;
	}

	// O(1)
	template <typename T>
	inline const T& max(const T& a, const T& b) {
		return a < b ? b : a;
	}

	// O(1)
	template <typename T, typename Compare>
	inline const T& max(const T& a, const T& b, Compare comp) {
		return comp(a, b) ? b : a;
	}

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

	// InputIterator version
	template <typename InputIterator, typename OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag) {
		for ( ; first != last; ++first, ++result) {
			*result = *first;
		}
		return result;
	}

	// RandomAccessIterator version
	template <typename RandomAccessIterator, typename OutputIterator, typename Distance>
	OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*) {
		for (Distance n = last - first; n > 0; --n, ++result, ++first) {
			*result = *first;
		}
		return result;
	}

	// RandomAccessIterator version
	template <typename RandomAccessIterator, typename OutputIterator>
	OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag) {
		return __copy_d(first, last, result, difference_type(first));
	}

	// iterator version
	template <typename InputIterator, typename OutputIterator>
	struct __copy_dispatch {
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
			return __copy(first, last, result, iterator_category(first));
		}
	};

	// has_trivial_assignment_operator
	template <typename T>
	T* __copy_trivial(const T* first, const T* last, T* result, __true_type) {
		memmove(result, first, sizeof(T) * (last - first));
		return result + (last - first);
	}

	// no_trivial_assignment_operator
	template <typename T>
	T* __copy_trivial(const T* first, const T* last, T* result, __false_type) {
		// pointer is a RandomAccessIterator
		return __copy_d(first, last, result, (ptrdiff_t*)(0));
	}

	template <typename T>
	struct __copy_dispatch<T*, T*> {
		T* operator()(T* first, T* last, T* result) {
			typedef typename __type_traits<T>::has_trivial_assignment_operator assign;
			return __copy_trivial(first, last, result, assign());
		}
	};

	template <typename T>
	struct __copy_dispatch<const T*, T*> {
		T* operator()(const T* first, const T* last, T* result) {
			typedef typename __type_traits<T>::has_trivial_assignment_operator assign;
			return __copy_trivial(first, last, result, assign());
		}
	};

	// copy the value in [`first`, `last`) to container
	// start from `output`
	// O(n)
	template <typename InputIterator, typename OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator output) {
		return __copy_dispatch<InputIterator, OutputIterator>()(first, last, output);
	}

	inline char* copy(const char* first, const char* last, char* result) {
		memmove(result, first, last - first);
		return result + (last - first);
	}

	inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result) {
		memmove(result, first, sizeof(wchar_t) * (last - first));
		return result + (last - first);
	}

	// reversely copy the value in [`first`, `last`) to container
	// end with `output` (exclusive)
	// O(n)
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

	// comparison

	// check if it is the same between [`first1`, `last1`) 
	// and an iterator start from `first2`
	// O(n)
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}
	
	template <typename InputIterator1, typename InputIterator2, typename BinaryOperator>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryOperator op) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!op(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

	// return 0, 1
	// O(n)
	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	// return 0, 1
	// O(n)
	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	// return 0, 1
	// O(n)
	inline bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2) {
		const size_t len1 = last1 - first1;
		const size_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return (result != 0) ? (result < 0) : (len1 < len2);
	}

	// return -1, 0, 1
	// O(n)
	template <typename InputIterator1, typename InputIterator2>
	int lexicographical_compare_3way(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				return -1;
			}
			if (*first2 < *first1) {
				return 1;
			}
			++first1;
			++first2;
		}
		if (first2 == last2) {
			return !(first1 == last1);
		}
		else {
			return 1;
		}
	}

	// return -1, 0, 1
	// O(n)
	template <typename InputIterator1, typename InputIterator2, typename Compare>
	int lexicographical_compare_3way(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 , InputIterator2 last2, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				return -1;
			}
			if (comp(*first2, *first1)) {
				return 1;
			}
			++first1;
			++first2;
		}
		if (first2 == last2) {
			return !(first1 == last1);
		}
		else {
			return 1;
		}
	}

	// return -1, 0, 1
	// O(n)
	int lexicographical_compare_3way(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2) {
		const ptrdiff_t len1 = last1 - first1;
		const ptrdiff_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return (result != 0) ? result : ((len1 == len2) ? 0 : (len1 < len2 ? -1 : 1));
	}

	// O(n)
	template <typename InputIterator1, typename InputIterator2>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1 && *first1 == *first2) {
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	// O(n)
	template <typename InputIterator1, typename InputIterator2, typename BinaryOperator>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryOperator op) {
		while (first1 != last1 && op(*first1, *first2)) {
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	// swap two elements pointed by iterators
	// O(1)
	template <typename ForwardIterator1, typename ForwardIterator2>
	inline void iter_swap(ForwardIterator1 first, ForwardIterator2 second) {
		auto temp = *first;
		*first = *second;
		*second = temp;
	}

	// O(1)
	template <typename T>
	inline void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}



}

#endif // !_ALGORITHM_H_