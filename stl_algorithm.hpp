#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cstdlib>
#include <memory>

#include "stl_iterator.hpp"
#include "stl_pair.hpp"
#include "stl_type_traits.hpp"

namespace selfmadeSTL {

	//! O(1)
	template <typename T>
	inline const T& min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	//! O(1)
	template <typename T, typename Compare>
	inline const T& min(const T& a, const T& b, Compare comp) {
		return comp(a, b) ? a : b;
	}

	//! O(1)
	template <typename T>
	inline const T& max(const T& a, const T& b) {
		return a < b ? b : a;
	}

	//! O(1)
	template <typename T, typename Compare>
	inline const T& max(const T& a, const T& b, Compare comp) {
		return comp(a, b) ? b : a;
	}

	// find a iterator point to the maximal element for a range
	//! O(n)
	template <typename ForwardIterator>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
		if (first == last) {
			return last;
		}
		ForwardIterator result = first;
		for (++first; first != last; ++first) {
			if (*result < *first) {
				result = first;
			}
		}
		return result;
	}

	//! O(n)
	template <typename ForwardIterator, typename Compare>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		if (first == last) {
			return last;
		}
		ForwardIterator result = first;
		for (++first; first != last; ++first) {
			if (comp(*result, *first)) {
				result = first;
			}
		}
		return result;
	}

	// find a iterator point to the minimal element for a range
	//! O(n)
	template <typename ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
		if (first == last) {
			return last;
		}
		ForwardIterator result = first;
		for (++first; first != last; ++first) {
			if (*first < *result) {
				result = first;
			}
		}
		return result;
	}

	//! O(n)
	template <typename ForwardIterator, typename Compare>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		if (first == last) {
			return last;
		}
		ForwardIterator result = first;
		for (++first; first != last; ++first) {
			if (comp(*first, *result)) {
				result = first;
			}
		}
		return result;
	}

	//! O(1)
	template <typename T>
	inline const T& median(const T& a, const T& b, const T& c) {
		if (comp(a, b)) {
			if (comp(b, c)) return b;
			else if(comp(a, c)) return c;
			else return a;
		}
		else if (comp(a, c)) return a;
		else if (comp(b, c)) return c;
		else return b;
	}

	//! O(1)
	template <typename T, typename Compare>
	inline const T& median(const T& a, const T& b, const T& c, Compare comp) {
		if (a < b) {
			if (b < c) return b;
			else if(a < c) return c;
			else return a;
		}
		else if (a < c) return a;
		else if (b < c) return c;
		else return b;
	}

	//! fill !//
	// fill the same `value` in [`first`, `last`)
	//! O(n)
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value) {
		for (; first != last; ++first) {
			*first = value;
		}
	}

	//! fill_n !//
	// fill `n` same `value` start from `first`
	//! O(n)
	template <typename OutputIterator, typename Size, typename T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
		for (; n > 0; --n, ++first) {
			*first = value;
		}
		return first;
	}

	// fill `n` same `value` start from `first`
	// specilized for char
	//! O(1)
	template <typename Size>
	char* fill_n(char* first, Size n, const char& value) {
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

	// fill `n` same `value` start from `first`
	// specilized for wchar_t
	//! O(1)
	template <typename Size>
	wchar_t* fill_n(wchar_t* first, Size n, const wchar_t& value) {
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	//! copy !//
	// InputIterator version
	//! O(n)
	template <typename InputIterator, typename OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag) {
		for ( ; first != last; ++first, ++result) {
			*result = *first;
		}
		return result;
	}

	// RandomAccessIterator version
	//! O(n)
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
	//! O(1)
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
	//! O(n)
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

	//! copy_backward !//
	//! O(n)
	template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename Distance>
	inline BidirectionalIterator2 __copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result, bidirectional_iterator_tag, Distance*) {
		while (first != last) {
			*--result = *--last;
		}
		return result;
	}

	//! O(n)
	template <typename RandomAccessIterator, typename BidirectionalIterator, typename Distance>
	inline BidirectionalIterator __copy_backward(RandomAccessIterator first, RandomAccessIterator last, BidirectionalIterator result, random_access_iterator_tag, Distance*) {
		for (Distance n = last - first; n > 0; --n) {
			*--result = *--last;
		}
		return result;
	}

	template <typename InputIterator, typename OutputIterator>
	struct __copy_backward_dispatch {
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
			return __copy_backward(first, last, result, iterator_category(first), difference_type(first));
		}
	};

	//! O(1)
	template <typename T>
	T* __copy_backward_trivial(const T* first, const T* last, T* result, __true_type) {
		const ptrdiff_t len = last - first;
		memmove(result - len, first, sizeof(T) * len);
		return result - len;
	}

	template <typename T>
	T* __copy_backward_trivial(const T* first, const T* last, T* result, __false_type) {
		return __copy_backward(first, last, result, iterator_category(first), difference_type(first));
	}

	template <typename T>
	struct __copy_backward_dispatch<T*, T*> {
		T* operator()(T* first, T* last, T* result) {
			typedef typename __type_traits<T>::has_trivial_assignment_operator assign;
			return __copy_backward_trivial(first, last, result, assign());
		}
	};

	template <typename T>
	struct __copy_backward_dispatch<const T*, T*> {
		T* operator()(T* first, T* last, T* result) {
			typedef typename __type_traits<T>::has_trivial_assignment_operator assign;
			return __copy_backward_trivial(first, last, result, assign());
		}
	};

	// reversely copy the value in [`first`, `last`) to container
	// end with `output` (exclusive)
	//! O(n)
	template <typename BidirectionalIterator1, typename BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 output) {
		return __copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2>()(first, last, output);
	}

	//! comparison !//

	// check if it is the same between [`first1`, `last1`) 
	// and an iterator start from `first2`
	//! O(n)
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}
	
	//! O(n)
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
	//! O(n)
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
	//! O(n)
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
	//! O(n)
	inline bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2) {
		const size_t len1 = last1 - first1;
		const size_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return (result != 0) ? (result < 0) : (len1 < len2);
	}

	// return -1, 0, 1
	//! O(n)
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
	//! O(n)
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

	//! mismatch !//
	// return -1, 0, 1
	//! O(n)
	int lexicographical_compare_3way(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2) {
		const ptrdiff_t len1 = last1 - first1;
		const ptrdiff_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return (result != 0) ? result : ((len1 == len2) ? 0 : (len1 < len2 ? -1 : 1));
	}

	//! O(n)
	template <typename InputIterator1, typename InputIterator2>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1 && *first1 == *first2) {
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename BinaryOperator>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryOperator op) {
		while (first1 != last1 && op(*first1, *first2)) {
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	// swap two elements pointed by iterators
	//! O(1)
	template <typename ForwardIterator1, typename ForwardIterator2>
	inline void iter_swap(ForwardIterator1 first, ForwardIterator2 second) {
		auto temp = *first;
		*first = *second;
		*second = temp;
	}

	//! O(1)
	template <typename T>
	inline void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	//! set algorithms !//
	// set algorithms suppose they are in the same (ascending or descending) order
	// $S_1 \supset S_2$
	//! O(n)
	template <typename InputIterator1, typename InputIterator2>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				++first1;
			}
			else if (*first2 < *first1) {
				return false;
			}
			else {
				++first1;
				++first2;
			}
		}
		return first2 == last2;
	}

	// $S_1 \supset S_2$
	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				++first1;
			}
			else if (comp(*first2, *first1)) {
				return false;
			}
			else {
				++first1;
				++first2;
			}
		}
		return first2 == last2;
	}

	// $S_1 \cup S_2$
	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				*result = *first1;
				++first1;
			}
			else if (*first2 > *first1) {
				*result = *first2;
				++first2;
			}
			else {
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}
		// append tails
		result = copy(first1, last1, result);
		result = copy(first2, last2, result);
		return result;
	}

	// $S_1 \cup S_2$
	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				*result = *first1;
				++first1;
			}
			else if (comp(*first2, *first1)) {
				*result = *first2;
				++first2;
			}
			else {
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}
		result = copy(first1, last1, result);
		result = copy(first2, last2, result);
		return result;
	}

	// $S_1 \cap S_2$
	//! O(n)
	template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
	OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				++first1;
			}
			else if (*first2 < *first1) {
				++first2;
			}
			else {
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
		}
		return result;
	}
	
	// $S_1 \cap S_2$
	//! O(n)
	template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
	OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				++first1;
			}
			else if (comp(*first2, *first1)) {
				++first2;
			}
			else {
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
		}
		return result;
	}

	// $S_1 - S_2$
	//! O(n)
	template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1) {
				++first2;
			}
			else {
				++first1;
				++first2;
			}
		}
		result = copy(first1, last1, result);
		return result;
	}
	
	// $S_1 - S_2$
	//! O(n)
	template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (comp(*first2, *first1)) {
				++first2;
			}
			else {
				++first1;
				++first2;
			}
		}
		result = copy(first1, last1, result);
		return result;
	}

	// $(S_1 - S_2) \cup (S_2 - S_1)$
	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1) {
				*result = *first2;
				++first2;
				++result;
			}
			else {
				++first1;
				++first2;
			}
		}
		result = copy(first1, last1, result);
		result = copy(first2, last2, result);
		return result;
	}

	// $(S_1 - S_2) \cup (S_2 - S_1)$
	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
	OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (comp(*first2, *first1)) {
				*result = *first2;
				++first2;
				++result;
			}
			else {
				++first1;
				++first2;
			}
		}
		result = copy(first1, last1, result);
		result = copy(first2, last2, result);
		return result;
	}

	// $S_1 + S_2$
	//! O(n)
	template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
		while (first1 != last1 && first2 != last2) {
			if (*first2 < *first1) {
				*result = *first2;
				++first2;
			}
			else {
				*result = *first1;
				++first1;
			}
			++result;
		}
		result = copy(first1, last1, result);
		result = copy(first2, last2, result);
		return result;
	}

	// $S_1 + S_2$
	//! O(n)
	template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first2, *first1)) {
				*result = *first2;
				++first2;
			}
			else {
				*result = *first1;
				++first1;
			}
			++result;
		}
		result = copy(first1, last1, result);
		result = copy(first2, last2, result);
		return result;
	}


	// find the first two equal adjacent value
	//! O(n)
	template<typename ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
		if (first == last) {
			return last;
		}
		ForwardIterator next = first;
		while (++next != last) {
			if (*first == *next) {
				return first;
			}
			first = next;
		}
		return last;
	}

	//! O(n)
	template<typename ForwardIterator, typename BinaryOperator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryOperator op) {
		if (first == last) {
			return last;
		}
		ForwardIterator next = first;
		while (++next != last) {
			if (op(*first, *next)) {
				return first;
			}
			first = next;
		}
		return last;
	}

	//! count !//
	// count the number of elements in [`first, `last`)
	// which are equal to `value`
	//! O(n)
	template<typename InputIterator, typename T>
	typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& value) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first) {
			if (*first == value) {
				++n;
			}
		}
		return n;
	}

	// count the number of elements in [`first`, `last`)
	// which satisfy the Predicate.
	//! O(n)
	template <typename InputIterator, typename Predicate>
	typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first) {
			if (pred(*first)) {
				++n;
			}
		}
		return n;
	}

	//! search !//
	// linear search
	//! O(mn)
	template <typename ForwardIterator1, typename ForwardIterator2, typename Distance1, typename Distance2>
	ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*) {
		Distance1 d1 = distance(first1, last1);
		Distance2 d2 = distance(first2, last2);
		// can not find if smaller
		if (d1 < d2) {
			return last1;
		}

		ForwardIterator1 curr1 = first1;
		ForwardIterator1 curr2 = first2;
		while (curr2 != last2) {
			// if match, check next
			if (*curr1 == *curr2) {
				++curr1;
				++curr2;
			}
			else {
				// can not find if smaller
				if (d1 == d2) {
					return last1;
				}
				else {
					// restart from next element of curr1
					curr1 = ++first1;
					curr2 = first2;
				}
				--d1;
			}
		}
		return first1;
	}
	
	// search range 2 in range 1
	//! O(mn)
	template <typename ForwardIterator1, typename ForwardIterator2>
	inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
		return __search(first1, last1, first2, last2, difference_type(first1), difference_type(first2));
	}

	// match one by one
	//! O(mn)
	template <typename ForwardIterator1, typename ForwardIterator2, typename Distance1, typename Distance2, typename BinaryOperator>
	ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*, BinaryOperator op) {
		Distance1 d1 = distance(first1, last1);
		Distance2 d2 = distance(first2, last2);
		// can not find if smaller
		if (d1 < d2) {
			return last1;
		}

		ForwardIterator1 curr1 = first1;
		ForwardIterator1 curr2 = first2;
		while (curr2 != last2) {
			// if match, check next
			if (op(*curr1, *curr2)) {
				++curr1;
				++curr2;
			}
			else {
				// can not find if smaller
				if (d1 == d2) {
					return last1;
				}
				else {
					// restart from next element of curr1
					curr1 = ++first1;
					curr2 = first2;
				}
				--d1;
			}
		}
		return first1;
	}
	
	// search range 2 in range 1
	//! O(mn)
	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryOperator>
	inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryOperator op) {
		return __search(first1, last1, first2, last2, difference_type(first1), difference_type(first2), op);
	}

	// find successive elements in range that are equal to `value`
	// ! O(n)
	template <typename ForwardIterator, typename Integer, typename T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value) {
		if (count <= 0) {
			return first;
		}
		else {
			while (first != last && *first != value) {
				++first;
			}
			while (first != last) {
				// match first
				Integer n = count - 1;
				ForwardIterator i = first;
				++i;
				while (i != last && n != 0 && *i == value) {
					++i;
					--n;
				}
				if (n == 0) {
					return first;
				}
				else {
					// not match
					first = i;
					while (first != last && *first != value) {
						++first;
					}
				}
			}
		}
		return last;
	}

	// find successive elements in range that are equal to `value`
	// ! O(n)
	template <typename ForwardIterator, typename Integer, typename T, typename BinaryOperator>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value, BinaryOperator op) {
		if (count <= 0) {
			return first;
		}
		else {
			while (first != last && !op(*first, value)) {
				++first;
			}
			while (first != last) {
				// match first
				Integer n = count - 1;
				ForwardIterator i = first;
				++i;
				while (i != last && n != 0 && op(*i, value)) {
					++i;
					--n;
				}
				if (n == 0) {
					return first;
				}
				else {
					// not match
					first = i;
					while (first != last && !op(*first, value)) {
						++first;
					}
				}
			}
		}
		return last;
	}

	//! find !//
	// find the first element that is equal to `value`
	//! O(n)
	template <typename InputIterator, typename T>
	inline InputIterator find(InputIterator first, InputIterator last, const T& value) {
		while (first != last && *first != value) {
			++first;
		}
		return first;
	}

	// find the first element that satisfy the Predicate
	//! O(n)
	template <typename InputIterator, typename Predicate>
	inline InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
		while (first != last && !pred(*first)) {
			++first;
		}
		return first;
	}

	// find the first element in [`first1`, `last1`)
	// that is also in [`first2`, `last2`)
	//! O(mn)
	template <typename InputIterator, typename ForwardIterator>
	InputIterator find_first_of(InputIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2) {
		for (; first1 != last1; ++first1) {
			for (ForwardIterator it = first2; it != last2; ++it) {
				if (*first1 == *it) {
					return first1;
				}
			}
		}
		return last1;
	}

	//! O(mn)
	template <typename InputIterator, typename ForwardIterator, typename BinaryOperator>
	InputIterator find_first_of(InputIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryOperator op) {
		for (; first1 != last1; ++first1) {
			for (ForwardIterator it = first2; it != last2; ++it) {
				if (op(*first1, *it)) {
					return first1;
				}
			}
		}
		return last1;
	}

	//! find_end !//
	// forward iterator version
	//! O(mn)
	template <typename ForwardIterator1, typename ForwardIterator2>
	ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator2 last1, ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag) {
		if (first2 == last2) {
			return last1;
		}
		else {
			ForwardIterator1 result = last1;
			while (true) {
				// use search to find match elements
				ForwardIterator1 new_result = search(first1, last1, first2, last2);
				if (new_result == last1) {
					// if not found, return what we have found
					return result;
				}
				else {
					// prepare for next iteration
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	// forward iterator version
	//! O(mn)
	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryOperator>
	ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator2 last1, ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag, BinaryOperator op) {
		if (first2 == last2) {
			return last1;
		}
		else {
			ForwardIterator1 result = last1;
			while (true) {
				ForwardIterator1 new_result = search(first1, last1, first2, last2, op);
				if (new_result == last1) {
					return result;
				}
				else {
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	// bidirectional iterator version, maybe faster from end
	//! O(mn)
	template<typename BidirectionalIterator1, typename BidirectionalIterator2>
	BidirectionalIterator1 __find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1, BidirectionalIterator2 first2, BidirectionalIterator2 last2, bidirectional_iterator_tag, bidirectional_iterator_tag) {
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter1 rfirst1(last1);
		reviter2 rlast2(first2);
		reviter2 rfirst2(last2);
		reviter1 rresult = search(rfirst1, rlast1, rfirst2, rlast2);
		if (rresult == rlast1) {
			return last1;
		}
		else {
			BidirectionalIterator1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}

	// bidirectional iterator version, maybe faster from end
	//! O(mn)
	template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryOperator>
	BidirectionalIterator1 __find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1, BidirectionalIterator2 first2, BidirectionalIterator2 last2, bidirectional_iterator_tag, bidirectional_iterator_tag, BinaryOperator op) {
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter1 rfirst1(last1);
		reviter2 rlast2(first2);
		reviter2 rfirst2(last2);
		reviter1 rresult = search(rfirst1, rlast1, rfirst2, rlast2, op);
		if (rresult == rlast1) {
			return last1;
		}
		else {
			BidirectionalIterator1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}

	// search [`first2`, `last2`) from the end of the [`first1`, `last1`)
	template <typename ForwardIterator1, typename ForwardIterator2>
	inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
		typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
		typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;

		return __find_end(first1, last1, first2, last2, category1(), category2());
	}

	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryOperator>
	inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryOperator op) {
		typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
		typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;

		return __find_end(first1, last1, first2, last2, category1(), category2(), op);
	}

	//! each !//
	// apply a function to every element of a range
	//! O(n)
	template<typename InputIterator, typename UnaryOperator>
	UnaryOperator for_each(InputIterator first, InputIterator last, UnaryOperator op) {
		for (; first != last; ++first) {
			op(*first);
		}
		return op;
	}

	// generate values for a range, using operator=
	//! O(n)
	template <typename ForwardIterator, typename Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
		for (; first != last; ++first) {
			*first = gen();
		}
	}

	// generate values for n elements, using operator=
	//! O(n)
	template <typename OutputIterator, typename Size, typename Generator>
	OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
		for (; n > 0; --n, ++first) {
			*first = gen();
		}
		return first;
	}

	// transform one range into another range using unary or binary operation
	//! O(n)
	template <typename InputIterator, typename OutputIterator, typename UnaryOperator>
	OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperator op) {
		for (; first != last; ++first, ++result) {
			*result = op(*first);
		}
		return result;
	}

	// transform one range into another range using unary or binary operation
	//! O(n)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperator>
	OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, BinaryOperator op) {
		for (; first1 != last1; ++first1, ++first2, ++result) {
			*result = op(*first1, *first2);
		}
		return result;
	}

	//! remove !//
	// copy all elements that are not equal to `value`
	// to `result`, they can be the same container
	// UB when the container expands
	//! O(n)
	template <typename InputIterator, typename OutputIterator, typename T>
	OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value) {
		for (; first != last; ++first) {
			if (*first != value) {
				*result = *first;
				++result;
			}
		}
		return result;
	}

	// remove all the elements that are equal to `value`
	//! O(n)
	template <typename ForwardIterator, typename T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
		first = find(first, last, value);
		ForwardIterator next = first;
		return first == last ? first : remove_copy(++next, last, first, value);
	}

	// copy all elements that satisfy the predicate
	// to `result`, they can be the same container
	// UB when the container expands
	//! O(n)
	template <typename InputIterator, typename OutputIterator, typename Predicate>
	OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred) {
		for (; first != last; ++first) {
			if (!pred(*first)) {
				*result = *first;
				++result;
			}
		}
		return result;
	}

	// remove all the elements that satisfy the predicate
	//! O(n) 
	template <typename ForwardIterator, typename Predicate>
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
		first = find_if(first, last, pred);
		ForwardIterator next = first;
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}

	//! replace !//
	// replace all the elements that are equal to old_value to new_value
	//! O(n) 
	template <typename ForwardIterator, typename T>
	void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value) {
		for (; first != last; ++first) {
			if (*first == old_value) {
				*first = new_value;
			}
		}
	}

	// similar to replace, the output container maybe different
	//! O(n)
	template <typename InputIterator, typename OutputIterator, typename T>
	OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value) {
		for (; first != last; ++first, ++result) {
			*result = (*first == old_value ? new_value : *first);
		}
		return result;
	}

	// replace all the elements that satisfy the predicate to new_value
	//! O(n)
	template <typename ForwardIterator, typename Predicate, typename T>
	void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value) {
		for (; first != last; ++first) {
			if (pred(*first)) {
				*first = new_value;
			}
		}
	}

	// similar to replace, the output container maybe different
	//! O(n)
	template <typename InputIterator, typename OutputIterator, typename Predicate, typename T>
	OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred, const T& new_value) {
		for (; first != last; ++first, ++result) {
			*result = (pred(*first) ? new_value : *first);
		}
		return result;
	}

	//! reverse !//
	// bidirectional iterator version
	//! O(n)
	template <typename BidirectionalIterator>
	void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag) {
		while (true) {
			// here we --last
			if (first == last || first == --last) {
				return;
			}
			else {
				// so we only ++first
				iter_swap(++first, last);
			}
		}
	}

	// random access iterator version
	//! O(n)
	template <typename RandomAccessIterator>
	void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		while (first < last) {
			iter_swap(first++, --last);
		}
	}

	// reverse elements in container
	//! O(n)
	template <typename BidirectionalIterator>
	inline void reverse(BidirectionalIterator first, BidirectionalIterator last) {
		__reverse(first, last, iterator_category(first));
	}

	// copy reversely
	//! O(n)
	template <typename BidirectionalIterator, typename OutputIterator>
	OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result) {
		while (first != last) {
			--last;
			*result = *last;
			++result;
		}
		return result;
	}

	//! rotate !//
	// gcd
	//! O(log(n))
	template <typename EuclideanRingElement>
	EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n) {
		while (n != 0) {
			EuclideanRingElement t = m % n;
			m = n;
			n = t;
		}
		return m;
	}

	template <typename RandomAccessIterator, typename Distance, typename T>
	void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator initial, Distance shift, T*) {
		T value = *initial;
		RandomAccessIterator ptr1 = initial;
		RandomAccessIterator ptr2 = ptr1 + shift;

		while (ptr2 != initial) {
			*ptr1 = *ptr2;
			ptr1 = ptr2;
			if (last - ptr2 > shift) {
				ptr2 += shift;
			}
			else {
				ptr2 = first + (shift - (last - ptr2));
			}
			*ptr1 = value;
		}
	}

	// forward iterator version
	//! O(n)
	template <typename ForwardIterator, typename Distance>
	void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag) {
		for (ForwardIterator i = middle; iter_swap(first, i); ++first, ++i) {
			// each time we swap the same length of the elements
			// from first and middle. Once one range is over, we
			// redo it until all ranges are over.			
			// first to middle is over
			if (first == middle) {
				if (i == middle) {
					return;
				}
				middle = i;
			}
			// middle to last is over
			else if (i == last) {
				i = middle;
			}
		}
	}

	// bidirectional iterator version
	//! O(n)
	template <typename BidirectionalIterator, typename Distance>
	void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, bidirectional_iterator_tag) {
		reverse(first, middle);
		reverse(middle, last);
		reverse(first, last);
	}

	// random access iterator version
	//! O(n)
	template <typename RandomAccessIterator, typename Distance>
	void __rotate(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Distance*, random_access_iterator_tag) {
		Distance n = __gcd(last - first, middle - first);
		while (n--) {
			__rotate_cycle(first, last, first + n, middle - first, value_type(first));
		}
	}

	// swap two ranges
	//! O(n)
	template <typename ForwardIterator>
	inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last) {
		if (first == middle || middle == last) {
			return;
		}
		else {
			__rotate(first, middle, last, difference_type(first), iterator_category(first));
		}
	}

	// similar to rotate, different container
	//! O(n)
	template <typename ForwardIterator, typename OutputIterator>
	OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result) {
		result = copy(middle, last, result);
		result = copy(first, middle, result);
		return result;
	}

	// similar to rotate, same length of two ranges
	// iterators can come from different containers
	//! O(n)
	template <typename ForwardIterator1, typename ForwardIterator2>
	ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			iter_swap(first1, first2);
		}
		return first2;
	}

	//! unique !//
	// forward iterator version
	//! O(n)
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag) {
		*result = *first;
		while (++first != last) {
			// if not match, reserve it
			if (*result != *first) {
				++result;
				*result = *first;
			}
		}
		return ++result;
	}

	// output iterator version
	//! O(n)
	template <typename InputIterator, typename OutputIterator>
	OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag) {
		auto value = *first;
		*result = value;
		while (++first != last) {
			if (value != *first) {
				value = *first;
				++result;
				*result = value;
			}
		}
		return ++result;
	}

	// remove duplicate nearby elements, maybe different container
	template <typename InputIterator, typename OutputIterator>
	inline OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result) {
		if (first == last) {
			return result;
		}
		return __unique_copy(first, last, result, iterator_category(result));
	}

	// remove duplicate nearby elements
	//! O(n)
	template <typename ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
		first = adjacent_find(first, last);
		return unique_copy(first, last, first);
	}

	// forward iterator version
	//! O(n)
	template <typename InputIterator, typename ForwardIterator, typename BinaryOperator>
	ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag, BinaryOperator op) {
		*result = *first;
		while (++first != last) {
			// if not match, reserve it
			if (!op(*result, *first)) {
				++result;
				*result = *first;
			}
		}
		return ++result;
	}

	// output iterator version
	//! O(n)
	template <typename InputIterator, typename OutputIterator, typename BinaryOperator>
	OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag, BinaryOperator op) {
		auto value = *first;
		*result = value;
		while (++first != last) {
			if (!op(value, *first)) {
				value = *first;
				++result;
				*result = value;
			}
		}
		return ++result;
	}

	// remove duplicate nearby elements, maybe different container
	template <typename InputIterator, typename OutputIterator, typename BinaryOperator>
	inline OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result, BinaryOperator op) {
		if (first == last) {
			return result;
		}
		return __unique_copy(first, last, result, iterator_category(result), op);
	}

	// remove duplicate nearby elements
	//! O(n)
	template <typename ForwardIterator, typename BinaryOperator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryOperator op) {
		first = adjacent_find(first, last, op);
		return unique_copy(first, last, first, op);
	}

	//! search algorithm !//

	// a way of binary search, return the first proper
	// position in the range that can insert a new value
	//! O(n)
	template <typename ForwardIterator, typename T, typename Distance>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*) {
		Distance len = distance(first, last);
		Distance half;
		ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (*middle < value) {
				first = middle;
				++first;
				len = len - half - 1;
			}
			else {
				len = half;
			}
		}
		return first;
	}

	template <typename ForwardIterator, typename T>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value) {
		return __lower_bound(first, last, value, difference_type(first));
	}

	//! O(n)
	template <typename ForwardIterator, typename T, typename Distance, typename Compare>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, Compare comp) {
		Distance len = distance(first, last);
		Distance half;
		ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(*middle, value)) {
				first = middle;
				++first;
				len = len - half - 1;
			}
			else {
				len = half;
			}
		}
		return first;
	}

	template <typename ForwardIterator, typename T, typename Compare>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
		return __lower_bound(first, last, value, difference_type(first), comp);
	}

	// a way of binary search, return the last proper
	// position in the range that can insert a new value
	//! O(n)
	template <typename ForwardIterator, typename T, typename Distance>
	ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*) {
		Distance len = distance(first, last);
		Distance half;
		ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (value < *middle) {
				len = half;
			}
			else {
				first = middle;
				++first;
				len = len - half - 1;
			}
		}
		return first;
	}

	template <typename ForwardIterator, typename T>
	inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value) {
		return __upper_bound(first, last, value, difference_type(first));
	}

	//! O(n)
	template <typename ForwardIterator, typename T, typename Distance, typename Compare>
	ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, Compare comp) {
		Distance len = distance(first, last);
		Distance half;
		ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(value, *middle)) {
				len = half;
			}
			else {
				first = middle;
				++first;
				len = len - half - 1;
			}
		}
		return first;
	}

	template <typename ForwardIterator, typename T, typename Compare>
	inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
		return __upper_bound(first, last, value, difference_type(first), comp);
	}

	// binary search
	//! O(n)
	template <typename ForwardIterator, typename T>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& value) {
		ForwardIterator target = lower_bound(first, last, value);
		// value may be smaller than the first element
		return target != last && !(value < *target);
	}

	//! O(n)
	template <typename ForwardIterator, typename T, typename Compare>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
		ForwardIterator target = lower_bound(first, last, value, comp);
		// value may be smaller than the first element
		return target != last && !comp(value, *target);
	}

	//! permutation algorithm !//

	// change inplace
	//! O(n)
	template <typename BidirectionalIterator>
	bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
		// 0
		if (first == last) {
			return false;
		}
		
		BidirectionalIterator i = first;
		++i;
		// 1
		if (i == last) {
			return false;
		}
		i = last;
		--i;

		// from last to first
		for(;;) {
			BidirectionalIterator j = i;
			--i;
			// if ascending
			if (*i < *j) {
				BidirectionalIterator k = last;
				while (!(*i < *--k)) {}
				iter_swap(i, k);
				reverse(j, last);
				return true;
			}
			if (i == first) {
				reverse(first, last);
				return false;
			}
		}
	}

	//! O(n)
	template <typename BidirectionalIterator, typename Compare>
	bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
		if (first == last) {
			return false;
		}
		
		BidirectionalIterator i = first;
		++i;
		if (i == last) {
			return false;
		}
		i = last;
		--i;

		for(;;) {
			BidirectionalIterator j = i;
			--i;
			if (comp(*i, *j)) {
				BidirectionalIterator k = last;
				while (!comp(*i, *--k)) {}
				iter_swap(i, k);
				reverse(j, last);
				return true;
			}
			if (i == first) {
				reverse(first, last);
				return false;
			}
		}
	}

	//! O(n)
	template <typename BidirectionalIterator>
	bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
		if (first == last) {
			return false;
		}
		BidirectionalIterator i = first;
		++i;
		if (i == last) {
			return false;
		}
		i = last;
		--i;

		for (;;) {
			BidirectionalIterator j = i;
			--i;
			if (*j < *i) {
				BidirectionalIterator k = last;
				while (!(*--k < *i)) {}
				iter_swap(i, k);
				reverse(j, last);
				return true;
			}
			if (i == last) {
				reverse(first, last);
				return false;
			}
		}
	}

	//! O(n)
	template <typename BidirectionalIterator, typename Compare>
	bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
		if (first == last) {
			return false;
		}
		BidirectionalIterator i = first;
		++i;
		if (i == last) {
			return false;
		}
		i = last;
		--i;

		for (;;) {
			BidirectionalIterator j = i;
			--i;
			if (comp(*j, *i)) {
				BidirectionalIterator k = last;
				while (!comp(*--k, *i)) {}
				iter_swap(i, k);
				reverse(j, last);
				return true;
			}
			if (i == last) {
				reverse(first, last);
				return false;
			}
		}
	}

	//! random shuffle !//

	// random shuffle a range
	//! O(n)
	template <typename RandomAccessIterator>
	inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
		if (first == last) {
			return;
		}
		for (RandomAccessIterator i = first + 1; i != last; ++i) {
			iter_swap(i, first + rand() % ((i - first) + 1));
		}
	}

	//! O(n)
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& rng) {
		if (first == last) {
			return;
		}
		for (RandomAccessIterator i = first + 1; i != last; ++i) {
			iter_swap(i, first + rng((i - first) + 1));
		}
	}

	//! sorting algorithm !//

	// partition for quick sort
	//! O(n)
	template <typename BidirectionalIterator, typename Predicate>
	BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
		while (true) {
			while (true) {
				if (first == last)
					return first;
				else if (pred(*first))
					++first;
				else
					break;
			}
			--last;
			while (true) {
				if (first == last)
					return first;
				else if (!pred(*last))
					--last;
				else
					break;
			}
			iter_swap(first, last);
			++first;
		}
	}

}

#endif // !_ALGORITHM_H_