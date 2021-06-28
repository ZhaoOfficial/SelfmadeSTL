#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <cstddef>

namespace SelfMadeSTL {

	// tags are tagged for function overloaded resolution
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// in the case that we lost something
	template <typename Category,
			  typename T,
			  typename Distance = ptrdiff_t,
			  typename Pointer = T*,
			  typename Reference = T&>
	struct iterator {
		typedef Category						iterator_category;
		typedef T								value_type;
		typedef Distance						difference_type;
		typedef Pointer							pointer;
		typedef Reference						reference;
	};

	// read only
	template <typename T, typename Distance>
	struct input_iterator : public iterator<input_iterator_tag, T> {};

	// write only
	struct output_iterator {
		typedef output_iterator_tag				iterator_category;
		typedef void							value_type;
		typedef void							difference_type;
		typedef void							pointer;
		typedef void							reference;
	};

	// read only
	template <typename T, typename Distance>
	struct forward_iterator : public iterator<forward_iterator_tag, T> {};

	// read only
	template <typename T, typename Distance>
	struct bidirectional_iterator : public iterator<bidirectional_iterator_tag, T> {};

	// read only
	template <typename T, typename Distance>
	struct random_access_iterator : public iterator<random_access_iterator_tag, T> {};

	// using partial specialization
	// iterator traits getting information of iterators
	// regarding pointer as a kind of iterator
	// for well defined iterator
	template <typename I>
	struct iterator_traits {
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::value_type			value_type;
		typedef typename I::difference_type		difference_type;
		typedef typename I::pointer				pointer;
		typedef typename I::reference			reference;
	};

	// for pointer
	template <typename T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	// for const pointer
	template <typename T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	// determine iterator category
	// auxilary function
	template <typename I>
	inline typename iterator_traits<I>::iterator_category __iterator_category(const I&) {
		typedef typename iterator_traits<I>::iterator_category category;
		return category();
	}

	// determine iterator distance type
	// auxilary function
	template <typename I>
	inline typename iterator_traits<I>::difference_type* __difference_type(const I&) {
		return static_cast<typename iterator_traits<I>::difference_type*>(0);
	}

	// determine iterator distance type
	// auxilary function
	template <typename I>
	inline typename iterator_traits<I>::value_type* __value_type(const I&) {
		return static_cast<typename iterator_traits<I>::value_type*>(0);
	}

	// determine iterator category
	template <typename I>
	inline typename iterator_traits<I>::iterator_category iterator_category(const I& it) {
		return __iterator_category(it);
	}

	// determine iterator distance type
	template <typename I>
	inline typename iterator_traits<I>::difference_type* difference_type(const I& it) {
		return __difference_type(it);
	}

	// determine iterator distance type
	template <typename I>
	inline typename iterator_traits<I>::value_type* value_type(const I& it) {
		return __value_type(it);
	}
	// end template partialization

	// distance function for variant iterator type
	// for input iterator, auxilary
	template <typename I>
	inline typename iterator_traits<I>::difference_type
	__distance(I first, I last, input_iterator_tag) {
		typename iterator_traits<I>::difference_type n = 0;
		while (first != last) {
			first++;
			n++;
		}
		return n;
	}

	// for random access iterator, auxilary
	template <typename I>
	inline typename iterator_traits<I>::difference_type
	__distance(I first, I last, random_access_iterator_tag) {
		return last - first;
	}

	// interface
	template <typename I>
	inline typename iterator_traits<I>::difference_type
	distance(I first, I last) {
		typedef typename iterator_traits<I>::iterator_category _category;
		return __distance(first, last, _category());
	}

	// distance function for variant iterator type
	// for input iterator, forward, auxilary
	template <typename I, typename Distance>
	inline void	__advance(I& it, Distance n, input_iterator_tag) {
		while (n--)
			it++;
	}

	// for bidirectional, auxilary
	template <typename I, typename Distance>
	inline void	__advance(I& it, Distance n, bidirectional_iterator_tag) {
		if (n >= 0) {
			while (n--)
				it++;
		} else {
			while (n++)
				it--;
		}
	}

	// for random access iterator, auxilary
	template <typename I, typename Distance>
	inline void	__advance(I& it, Distance n, random_access_iterator_tag) {
		it += n;
	}

	// interface
	template <typename I, typename Distance>
	inline void	advance(I& it, Distance n) {
		__advance(it, n, iterator_category(it));
	}
};

#endif // _ITERATOR_H_