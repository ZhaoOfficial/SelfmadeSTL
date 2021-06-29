#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "stl_algorithm.hpp"
#include "stl_construct.hpp"
#include "stl_type_traits.hpp"

namespace SelfMadeSTL {

    // uninitialized_copy
    // separation of allocation and construction
    // commit or rollback

    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type) {
        // if it is a plain old data
        return copy(first, last, result);
    }

    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type) {
        // if it is not a plain old data
        // construct one by one
        for (; first != last; ++first, ++result) {
            construct(&*result, *first);
        }
        return result;
    }

    template <typename InputIterator, typename ForwardIterator, typename T>
    ForwardIterator _uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T* p) {
        // check by type traits is POD type
        typedef typename __type_traits<T>::is_POD_type is_POD;
        return _uninitialized_copy_aux(first, last, result, is_POD());
    }

    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
        return _uninitialized_copy(first, last, result, value_type(result));
    }

    // uninitialized_fill
    // almost the same as uninitialized_copy
    template <typename ForwardIterator, typename T>
    inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, __true_type) {
        fill(first, last, value);
    }

    template <typename ForwardIterator, typename T>
    inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, __false_type) {
        for (; first != last; ++first) {
            construct(&*first, value);
        }
    }

    template <typename ForwardIterator, typename T, typename I>
    inline void _uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value, I*) {
        typedef typename __type_traits<I>::is_POD_type is_POD;
        _uninitialized_fill_aux(first, last, value, is_POD());
    }

    template <typename ForwardIterator, typename T>
    inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
        _uninitialized_fill(first, last, value, value_type(first));
    }

    // uninitialized_fill_n
    template<typename ForwardIterator, typename size, typename T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, size n, const T& value, __true_type) {
        return fill_n(first, n, value);
    }

    template<typename ForwardIterator, typename size, typename T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, size n, const T& value, __false_type) {
        for (; n > 0; --n, ++first)
            construct(&*first, value);
        return first;
    }

    template<typename ForwardIterator, typename size, typename T, typename I>
    ForwardIterator _uninitialized_fill_n(ForwardIterator first, size n, const T& value, I* t) {
        typedef typename __type_traits<I>::is_POD_type is_POD;
        return _uninitialized_fill_n_aux(first, n, value, is_POD());
    }

    template<typename ForwardIterator, typename size, typename T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, size n, const T& value)  {
		return _uninitialized_fill_n(first, n, value, value_type(first));
	}
}

#endif // !_UNINITIALIZED_H_