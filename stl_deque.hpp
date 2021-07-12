#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "stl_algorithm.hpp"
#include "stl_allocator.hpp"
#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"
#include "stl_uninitialized.hpp"

namespace SelfMadeSTL {

	template <typename T, typename Alloc = alloc>
	class deque {
	public:
		typedef T               value_type;
		typedef T*              pointer;
		typedef T&              reference;
		typedef size_t          size_type;
		typedef ptrdiff_t       difference_type;
		typedef const T*        const_pointer;
		typedef const T&        const_reference;

		typedef simple_alloc<T, Alloc> deque_allocator;

	public:
		deque();
		~deque();

	private:

	};

}

#endif // !_DEQUE_H_