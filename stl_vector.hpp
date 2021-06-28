#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "stl_algorithm.hpp"
#include "stl_allocator.hpp"
#include "stl_iterator.hpp"
#include "stl_type_traits.hpp"
#include "stl_uninitialized.hpp"

namespace SelfMadeSTL {
    
    template <typename T, typename Alloc = allocator<T>>
    class vector {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef T*          iterator;
        typedef T&          reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        typedef const T*    const_pointer;
        typedef const T*    const_iterator;
        typedef const T&    const_reference;

    protected:
        void insert_aux(iterator pos, const T& x) {
            // if there are some space left
            if (finish != end_of_storage) {
                construct(finish, x);
            }
        }

        void insert_aux(iterator pos);

    protected:
        // start position of used
        iterator start;
        // end position of used
        iterator finish;
        // end position of all space
        iterator end_of_storage;

    public:
        // basic constructor, deconstructor
        explicit vector()
            : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
        vector(size_type n, const T& value)
            : start(nullptr), finish(nullptr), end_of_storage(nullptr) {
            start = Alloc::allocate(n);
            finish = SelfMadeSTL::uninitialized_fill_n(start, n, value);
            end_of_storage = finish;
        }
        explicit vector(const size_type n)
            : start(nullptr), finish(nullptr), end_of_storage(nullptr) {
            start = Alloc::allocate(n);
            finish = SelfMadeSTL::uninitialized_fill_n(start, n, value_type());
            end_of_storage = finish;
        }
        vector(const vector& other);
        vector& operator=(const vector& other);
        ~vector() {}


        // iterator function
        iterator begin() { return start; }
        iterator end() { return finish; }
        const_iterator cbegin() const { return start; }
        const_iterator cend() const { return finish; }

        // container size/capacity function
        size_type size() const {
            return (size_type)(cend() - cbegin());
        }
        size_type capacity() const {
            return (size_type)(end_of_storage - cbegin());
        }
        bool empty() const { return cbegin() == cend(); }

        // element access function
        reference front() { return *begin(); }
        reference back() { return *(end() - 1); }
        reference operator[](size_type idx) { return *(begin() + idx); }
        const_reference front() const { return *begin(); }
        const_reference back() const { return *(end() - 1); }
        const_reference operator[](size_type idx) const { return *(begin() + idx); }

        // change element in vector function
        void push_back(const T& x) {
            if (finish != end_of_storage) {
                construct(finish, x);
                ++finish;
            }
            else {
                insert_aux(end(), x);
            }
        }
        iterator insert(iterator pos, const T& x);
        void clear();
        iterator erase(iterator pos);

        void swap(vector& other) {
            std::swap(start, other.start);
            std::swap(finish, other.finish);
            std::swap(end_of_storage, other.end_of_storage);
        }

    };

}

#endif // !_VECTOR_H_
