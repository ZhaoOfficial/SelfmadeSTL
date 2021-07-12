#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>
#include <iostream>
#include <new>

#include "stl_construct.hpp"

namespace SelfMadeSTL {

	// primary space allocator
	template <int inst>
	class __malloc_alloc_template {
	private:
		// oom = out of memory
		static void *__oom_malloc(size_t);
		static void *__oom_realloc(void*, size_t);
		// function pointer
		static void (*__malloc_alloc_oom_handler)();

	public:
		static void* allocate(size_t n) {
			void *space = malloc(n);
			if (space == nullptr)
				space = __oom_malloc(n);
			return space;
		}

		static void deallocate(void* ptr, size_t n) {
			::operator delete(ptr);
		}

		static void reallocate(void* ptr, size_t old_size, size_t new_size) {
			void* space = realloc(ptr, new_size);
			if (space == nullptr)
				space = __oom_realloc(ptr, new_size);
			return space;
		}

		static void (*__set_malloc_handler(void (*f)()))() {
			void (*__old)() = __malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler = f;
			return(__old);
		}
	};

	template <int inst>
	void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

	template <int inst>
	void* __malloc_alloc_template<inst>::__oom_malloc(size_t n) {
		void (*malloc_handler)();
		void* space;

		while (true) {
			malloc_handler = __malloc_alloc_oom_handler;
			if (malloc_handler == 0) {
				std::cerr << "Out of memory.\n";
				exit(1);
			}
			// free
			(*malloc_handler)();
			// malloc
			space = malloc(n);
			if (space != nullptr)
				return space;
		}
	}

	template <int inst>
	void* __malloc_alloc_template<inst>::__oom_realloc(void* ptr, size_t n) {
		void (*malloc_handler)();
		void* space;

		while (true) {
			malloc_handler = __malloc_alloc_oom_handler;
			if (malloc_handler == 0) {
				std::cerr << "Out of memory.\n";
				exit(1);
			}
			// free
			(*malloc_handler)();
			// malloc
			space = realloc(ptr, n);
			if (space != nullptr)
				return space;
		}
	}

	typedef __malloc_alloc_template<0> malloc_alloc;

	// capsule

	template<class T, class _Alloc>
	class simple_alloc {
	public:
		static T* allocate(size_t __n) {
			return 0 == __n ? 0 : static_cast<T*>(_Alloc::allocate(__n * sizeof(T)));
		}
		static T* allocate(void) {
			return static_cast<T*>(_Alloc::allocate(sizeof(T)));
		}
		static void deallocate(T* __p, size_t __n) {
			if (0 != __n)
				_Alloc::deallocate(__p, __n * sizeof(T));
		}
		static void deallocate(T* __p) {
			_Alloc::deallocate(__p, sizeof(T));
		}
	};


	// secondary space allocator
	// apply internal interfaces for stl_allocator
	// in responsible for memory allocation and deallocation

	template <bool threads, int inst>
	class __default_alloc_template {
	private:
		// small block should be the multiply of 8
		enum {_ALIGN = 8};
		// the max size of small block
		enum {_MAX_BYTES = 128};
		// number of free lists
		enum {_NFREELISTS = _MAX_BYTES/_ALIGN};
		
		// round up to be the multiply of 8
		static size_t Round_Up(size_t bytes) {
			return (((bytes) + _ALIGN - 1) & ~(_ALIGN - 1));
		}

	private:
		union obj {
			union obj* next;
			char client[1];
		};

		// 16 free lists
		static obj* volatile free_list[_NFREELISTS];
		// use the n^th free list 
		static size_t freelist_index(size_t bytes) {
			return (((bytes) + _ALIGN - 1) / _ALIGN - 1);
		}

		// return an object of size n,
		// and optionally adds to size n free list.
		static void* refill(size_t n);
		// allocates a chunk for nobjs of size "size".
		// nobjs may be reduced if it is inconvenient to
		// allocate the requested number.
		static char* chunk_alloc(size_t size, int& nobjs);
		
		// Chunk allocation state
		// start position of free list
		static char* start_free;
		// end position of free list
		static char* end_free;
		static size_t heap_size;

	public:
		// allocate space
		static void* allocate(size_t bytes);
		// deallocate space
		static void  deallocate(void* ptr, size_t n) {
			obj* q = (obj*)ptr;
			obj* volatile* my_free_list;

			if (n > (size_t)_MAX_BYTES) {
				malloc_alloc::deallocate(ptr, n);
				return;
			}

			my_free_list = free_list + freelist_index(n);
			q->next = *my_free_list;
			*my_free_list = q;
		}
		// reallocate space
		static void* reallocate(void* ptr, size_t old_size, size_t new_size);
	};

	template <bool threads, int inst>
	char* __default_alloc_template<threads, inst>::start_free = 0;

	template <bool threads, int inst>
	char* __default_alloc_template<threads, inst>::end_free = 0;

	template <bool threads, int inst>
	size_t __default_alloc_template<threads, inst>::heap_size = 0;

	template <bool threads, int inst>
	typename __default_alloc_template<threads, inst>::obj* volatile
	__default_alloc_template<threads, inst>::free_list[_NFREELISTS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	template <bool threads, int inst>
	void* __default_alloc_template<threads, inst>::allocate(size_t n) {
		obj* volatile* my_free_list;
		obj* space;

		// if more than 128
		if (n > (size_t)_MAX_BYTES) {
			return (malloc_alloc::allocate(n));
		}

		my_free_list = free_list + freelist_index(n);
		space = *my_free_list;
		if (space == nullptr) {
			// no available free list
			void* r = refill(Round_Up(n));
			return r;
		}
		// adjust free list
		*my_free_list = space->next;
		return space;
	}

	template <bool threads, int inst>
	void* __default_alloc_template<threads, inst>::reallocate(void* ptr, size_t old_size, size_t new_size) {
		return 0;
	}

	typedef __default_alloc_template<false, 0> alloc;

	template <bool threads, int inst>
	void* __default_alloc_template<threads, inst>::refill(size_t n) {
		int nobjs = 20;

		char* chunk = chunk_alloc(n, nobjs);
		obj* volatile* my_free_list;
		obj* space;
		obj* current_obj, * next_obj;

		// if get one chunk
		if (nobjs == 1)
			return chunk;
		my_free_list = free_list + freelist_index(n);

		// build free list in chunk
		space = (obj*)chunk;
		*my_free_list = next_obj = (obj*)(chunk + n);
		for (int i = 1; ; i++) {
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if (nobjs - 1 == i) {
				current_obj->next = 0;
				break;
			}
			else {
				current_obj->next = next_obj;
			}
		}
		return space;
	}

	template <bool threads, int inst>
	char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs) {
		char* result;
		size_t total_bytes = size * nobjs;
		size_t bytes_left = end_free - start_free;

		// if enough for all
		if (bytes_left >= total_bytes) {
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		// if not enough for all but at least one
		else if (bytes_left >= size) {
			nobjs = bytes_left / size;
			total_bytes = size * nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		// if not enough for one
		else {
			size_t bytes_to_get = 2 * total_bytes + Round_Up(heap_size >> 4);
			// Try to make use of the left-over piece.
			if (bytes_left > 0) {
				// search for free list
				obj* volatile* my_free_list = free_list + freelist_index(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			// config heap space for memory pool
			start_free = (char*)malloc(bytes_to_get);
			if (start_free == NULL) {
				// malloc fails
				int i;
				obj* volatile* my_free_list, * p;
				// search for unused and big enough free list
				for (i = size; i <= _MAX_BYTES; i += _ALIGN) {
					my_free_list = free_list + freelist_index(i);
					p = *my_free_list;
					if (p != NULL) {
						// adjust free list
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						// adjust nobjs
						return chunk_alloc(size, nobjs);
					}
				}
				// no any space
				end_free = NULL;
				// this will throw exception
				start_free = (char*)malloc_alloc::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(size, nobjs);
		}
	}
};

#endif // !_ALLOC_H_