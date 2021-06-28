#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <new>

#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"

namespace SelfMadeSTL {

	// in responsible for construct and destruct

	// construct with value
	template <typename T1, typename T2>
	inline void construct(T1* ptr, const T2& value) {
		new(ptr)T1(value);
	}

	// construct without value
	template <typename T>
	inline void construct(T* ptr) {
		new(ptr)T();
	}

	// destruct, argument is a *pointer*
	template<typename T>
	inline void destory(T* ptr) {
		ptr->~T();
	}

	// non-trivial destructor
	template <typename I>
	inline void __destroy_aux(I first, I last, __false_type) {
		for (; first != last; first++)
			destory(&*first);
	}

	// trivial destructor
	template <typename I>
	inline void __destroy_aux(I, I, __true_type) {}

	// for different value type
	template <typename I, typename T>
	inline void __destory(I first, I last, T*) {
		typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
		__destroy_aux(first, last, trivial_destructor());
	}

	template <typename I>
	inline void destory(I first, I last) {
		__destory(first, last, value_type(first));
	}

	inline void destory(char*, char*) {}
	inline void destory(wchar_t*, wchar_t*) {}
};

#endif // _CONSTRUCT_H_