#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <cassert>
#include <cstdlib>
#include <climits>
#include <new>

#include "stl_alloc.hpp"
#include "stl_construct.hpp"

namespace selfmadeSTL {
	// standard allocator but less efficient

	template <typename T>
	class allocator {
	public:
		// stl style interface
		typedef T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		// rebind allocator of type U
		template <typename U>
		struct rebind {
			typedef allocator<U> other;
		};

	public:
		// default constructor
		allocator();
		// copy constructor
		allocator(const allocator&);
		// generic copy constructor
		template <typename U>
		allocator(const allocator<U>&);
		// default destructor
		~allocator();

		// return the address of something
		pointer address(reference value) const;
		// return the address of some const thing
		const_pointer address(const_reference value) const;
		// maximum number of objects in init_page
		size_type init_page_size() const;
		// maximum number of objects
		size_type max_size() const;

		// allocate spaces for one type T object
		static pointer allocate();
		// allocate spaces for n type T objects
		static pointer allocate(size_type n);
		// deallocate space for one type T object
		static void deallocate(pointer ptr);
		// deallocate space for n type T objects
		static void deallocate(pointer ptr, size_type n);

		// new(const void* ptr) T(value)
		static void construct(pointer ptr);
		// new(const void* ptr) T()
		static void construct(pointer ptr, const_reference value);
		// p->~T()
		static void destroy(pointer ptr);
		// p->~T() for n type T objects
		static void destroy(pointer first, pointer last);
	};

	template <typename T>
	allocator<T>::allocator() {}

	template <typename T>
	allocator<T>::allocator(const allocator&) {}

	template <typename T>
	template <typename U>
	allocator<T>::allocator(const allocator<U>&) {}

	template <typename T>
	allocator<T>::~allocator() {}

	template <typename T>
	auto allocator<T>::address(reference value) const -> pointer {
		return (pointer)&value;
	}

	template <typename T>
	auto allocator<T>::address(const_reference value) const -> const_pointer {
		return (const_pointer)&value;
	}

	template <typename T>
	auto allocator<T>::init_page_size() const -> size_type {
		return std::max(size_type(1), size_type(4096 / sizeof(T)));
	}

	template <typename T>
	auto allocator<T>::max_size() const -> size_type {
		return std::max(size_type(1), size_type(UINT_MAX / sizeof(T)));
	}

	template <typename T>
	auto allocator<T>::allocate() -> pointer {
		return static_cast<pointer>(alloc::allocate(sizeof(T)));
	}

	template <typename T>
	auto allocator<T>::allocate(size_type n) -> pointer {
		if (n == 0)
			return nullptr;
		return static_cast<pointer>(alloc::allocate(sizeof(T) * n));
	}

	template <typename T>
	void allocator<T>::deallocate(pointer ptr) {
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
	}

	template <typename T>
	void allocator<T>::deallocate(pointer ptr, size_type n) {
		if (n == 0)
			return;
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	template <typename T>
	void allocator<T>::construct(pointer ptr) {
		new(ptr)T();
	}

	template <typename T>
	void allocator<T>::construct(pointer ptr, const_reference value) {
		new(ptr)T(value);
	}

	template <typename T>
	void allocator<T>::destroy(pointer ptr) {
		ptr->~T();
	}

	template <typename T>
	void allocator<T>::destroy(pointer first, pointer last) {
		for (; first != last; first++) {
			first->~T();
		}
	}
};

#endif // !_ALLOCATOR_H_